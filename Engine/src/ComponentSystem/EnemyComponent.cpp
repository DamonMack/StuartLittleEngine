#include "ComponentSystem/EnemyComponent.hpp"

EnemyComponent::EnemyComponent(TransformComponent* pt, TransformComponent* t)
{
    transform = t;
    playerT = pt;
}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::Update(double dt)
{
    int xdistance = abs(playerT->position.x - transform->position.x);
    int ydistance = abs(playerT->position.y - transform->position.y);

    //hardset to the enemy and player sprite size
    //detects if they collide 

    if(xdistance < 20 && ydistance < 20)
    {
        playerT->position.x = 128;
        playerT->position.y = 686;
    }
}