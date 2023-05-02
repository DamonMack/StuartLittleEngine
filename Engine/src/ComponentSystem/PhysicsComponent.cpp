#include "Engine.hpp"
#include "ComponentSystem/PhysicsComponent.hpp"
#include "ComponentSystem/TileMapComponent.hpp"
#include "Managers/ColliderManager.hpp"
#include <iostream>

const float gravity = 0.1f;
const float MAX_SPEED = 10.f;
const float JUMP_SPEED = 30.f;
const float TERMINAL_VELOCITY = 25.f;

PhysicsComponent::PhysicsComponent(TransformComponent* tc, TileMapComponent* tmc, bool usesGravity, int colliderID):transform(tc),tilemap(tmc),usesGravity(usesGravity),colliderID(colliderID){
}

PhysicsComponent::~PhysicsComponent() { }

void PhysicsComponent::Update(double dt) {
    // adds gravity to velocity
    if (usesGravity) {
        velocity.y += gravity * dt;
        if (velocity.y > TERMINAL_VELOCITY) velocity.y = TERMINAL_VELOCITY; // helps player not fall through other objects
    }
    isGrounded = false;

    // Do max 3 collision checks -
    // e.g. if moving x: +0.2 and y: -0.2, check current position plus (x: +0.2, y: -0.2). If no collision, skip to last step
    // If there is a collision, check current position plus (x: +0.2, y: 0.0 ) -> If collision, set x velocity to overlap distance on x axis (0 as of now)
    // Then check current position plus (x: 0.0, y: -0.2) -> If collision, set y velocity to the overlap distance on y axis (0 as of now)
    // Then move by velocity vector
    SDL_Rect intersection;
    bool xCollision, yCollision = false;
    if (velocity.x == 0 || velocity.y == 0 || ColliderManager::GetInstance().CheckCollision(tilemap, colliderID, velocity.x, velocity.y, &intersection)) {
        if (velocity.x != 0 && ColliderManager::GetInstance().CheckCollision(tilemap, colliderID, velocity.x, 0, &intersection)) {
            xCollision = true;
            if (velocity.x > 0) {
                velocity.x -= intersection.w;
            }
            else {
                velocity.x += intersection.w;
            }
        }
        if (velocity.y != 0 && ColliderManager::GetInstance().CheckCollision(tilemap, colliderID, 0, velocity.y, &intersection)) {
            yCollision = true;
            if (velocity.y > 0) { 
                isGrounded = true; // allows player to jump again if collision on y axis with velocity pointing downward
                velocity.y -= intersection.h;
            }
            else {
                velocity.y += intersection.h;
            }
        }
    }

    // stop moving after collision (ignores correction from intersection because it's making everything feel worse for some reason)
    // TODO: fix collision correction with intersection
    if (xCollision) velocity.x = 0.f;
    if (yCollision) velocity.y = 0.f;
    
    transform->position += velocity;
}

// sets x velocity given movement direction (-1, 0, or 1)
void PhysicsComponent::SetXVelocity(int moveDirection) {
    velocity.x = MAX_SPEED * moveDirection;
}

void PhysicsComponent::SetVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}

float PhysicsComponent::GetXVelocity() {
    return velocity.x;
}

float PhysicsComponent::GetYVelocity() {
    return velocity.y;
}

bool PhysicsComponent::IsGrounded() {
    return isGrounded;
}

void PhysicsComponent::Jump() {
    if (isGrounded) {
        velocity.y -= JUMP_SPEED;
        isGrounded = false;
    }
}