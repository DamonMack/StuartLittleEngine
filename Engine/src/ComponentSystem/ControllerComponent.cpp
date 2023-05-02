#include "ComponentSystem/ControllerComponent.hpp"
#include "Managers/Input.hpp"

ControllerComponent::ControllerComponent(PhysicsComponent* pc) : physics(pc) { }

ControllerComponent::~ControllerComponent() { }

void ControllerComponent::Update(double dt) { }

void ControllerComponent::SetVelocity(float x, float y) {
    physics->SetVelocity(x, y);
}

float ControllerComponent::GetXVelocity() {
    return physics->GetXVelocity();
}

float ControllerComponent::GetYVelocity() {
    return physics->GetYVelocity();
}

bool ControllerComponent::IsGrounded() {
    return physics->IsGrounded();
}