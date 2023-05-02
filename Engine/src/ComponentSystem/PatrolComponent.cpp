#include "ComponentSystem/PatrolComponent.hpp"

PatrolComponent::PatrolComponent(int d, int s, TransformComponent* tc)
{
    distance = d;
    transform = tc;
    speed = s;
}

PatrolComponent::~PatrolComponent(){}

void PatrolComponent::Update(double dt)
{
    transform->position.x += right ? speed : -speed;
    counter += right ? speed : -speed;
    if (counter >= distance) { right = false; }
    else if (counter <= 0) { right = true; }
}