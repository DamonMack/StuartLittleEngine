#include "ComponentSystem/CollectComponent.hpp"

CollectComponent::CollectComponent(TransformComponent* pt, TransformComponent* t, SpriteComponent* s)
{
    transform = t;
    playerT = pt;
    sprite = s;
}

CollectComponent::~CollectComponent()
{

}

void CollectComponent::Update(double dt)
{
    
    //checks the distance between the player and the sprite
    int xdistance = abs(playerT->position.x - transform->position.x);
    int ydistance = abs(playerT->position.y - transform->position.y);

    //moves the sprite off the screen
    //if there is a level manager that keeps count of the coins will add 1 and delete sprite
    if(xdistance < 20 && ydistance < 20)
    {
        transform->position.x = 10000;
    }
    

}