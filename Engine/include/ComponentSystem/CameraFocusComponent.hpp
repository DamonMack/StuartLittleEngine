//
// Created by Jonathan Lehman on 4/13/23.
//

#ifndef FINALPROJECT_SIMON_JON_DAMON_JASON_CAMERAFOCUSCOMPONENT_HPP
#define FINALPROJECT_SIMON_JON_DAMON_JASON_CAMERAFOCUSCOMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 * Component which makes the camera follow a specific transform.
 */
class CameraFocusComponent : public Component {

public:
    /*!
     * Construct a CameraFocusComponent.
     * @param transform The transform for the camera to follow.
     * @param leftEdge Relative screen position (0 to 1) representing the left limit for the focus object.
     * @param rightEdge Relative screen position (0 to 1) representing the right limit for the focus object.
     * @param strength The speed with which the camera will move to catch the focus object, when off limits.
     * @param zoom The level of zoom that the camera should start with.
     */
    CameraFocusComponent(TransformComponent* transform, float leftEdge, float rightEdge, float strength, float zoom);
    /*!
     * Destroy the CameraFocusComponent.
     */
    ~CameraFocusComponent();

    /*!
     * Update the position of the camera based on the position of the focus object.
     * @param dt The time that has passed since last update.
     */
    void Update(double dt);
    /*!
     * Change the camera's zoom by the given amount.
     * @param amount The amount to change the camera zoom by.
     */
    void UpdateZoomBy(float amount);

private:
    TransformComponent* transform;
    float strength;
    int leftEdgePixel;
    int rightEdgePixel;
};

#endif //FINALPROJECT_SIMON_JON_DAMON_JASON_CAMERAFOCUSCOMPONENT_HPP
