//
// Created by Jonathan Lehman on 4/13/23.
//

#include "Managers/Camera.hpp"
#include "ComponentSystem/CameraFocusComponent.hpp"

CameraFocusComponent::CameraFocusComponent(TransformComponent *transform, float leftEdge, float rightEdge, float strength, float zoom) {
    this->transform = transform;
    this->strength = strength;
    this->leftEdgePixel = leftEdge * 1280; // TODO temp, hardcoded window size
    this->rightEdgePixel = rightEdge * 1280;
    Camera::GetInstance().zoom = zoom;
}

CameraFocusComponent::~CameraFocusComponent() { }

void CameraFocusComponent::Update(double dt) {
    std::pair<int, int> camPos = Camera::GetInstance().position;
    float xChange = 0;
    float yChange = 0;
    if (Camera::GetInstance().worldToScreenPoint(std::pair<float, float>(transform->position.x, transform->position.y)).first < leftEdgePixel) {
        xChange = (Camera::GetInstance().worldToScreenPoint(std::pair<float, float>(transform->position.x, transform->position.y)).first - leftEdgePixel) * strength;
    }
    if (Camera::GetInstance().worldToScreenPoint(std::pair<float, float>(transform->position.x, transform->position.y)).first > rightEdgePixel) {
        xChange = (Camera::GetInstance().worldToScreenPoint(std::pair<float, float>(transform->position.x, transform->position.y)).first - rightEdgePixel) * strength;
    }
    Camera::GetInstance().position = std::pair<float, float>(camPos.first + xChange, camPos.second + yChange);
    Camera::GetInstance().position.second = (720 / Camera::GetInstance().zoom) * (Camera::GetInstance().zoom - 1); // TODO temp, hardcoded window size
}

void CameraFocusComponent::UpdateZoomBy(float amount) {
    if (Camera::GetInstance().zoom + amount > 0) {
        Camera::GetInstance().zoom += amount;
    }
}