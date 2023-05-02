//
// Created by Jonathan Lehman on 4/4/23.
//

#include "Managers/Camera.hpp"

Camera& Camera::GetInstance() {
    static Camera* instance = new Camera();
    return *instance;
}

std::pair<float, float> Camera::screenToWorldPoint(std::pair<float, float> screenPoint) {
    return std::pair<float, float>(position.first + (screenPoint.first / zoom),
                               position.second + (screenPoint.second / zoom));
}

std::pair<float, float> Camera::worldToScreenPoint(std::pair<float, float> worldPoint) {
    return std::pair<float, float>((worldPoint.first - position.first) * zoom,
                                   (worldPoint.second - position.second) * zoom);
}
