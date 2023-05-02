#include "ComponentSystem/TransformComponent.hpp"

TransformComponent::TransformComponent(int x, int y) {
    position.x = x;
    position.y = y;
}

TransformComponent::~TransformComponent() {}

float TransformComponent::GetX() {
    return position.x;
}

float TransformComponent::GetY() {
    return position.y;
}

void TransformComponent::SetX(float x) {
    position.x = x;
}

void TransformComponent::SetY(float y) {
    position.y = y;
}
