//
// Created by Jonathan Lehman on 4/4/23.
//

#ifndef FINALPROJECT_SIMON_JON_DAMON_JASON_CAMERA_HPP
#define FINALPROJECT_SIMON_JON_DAMON_JASON_CAMERA_HPP

#include <tuple>

/*!
 * Singleton class representing the game's camera. Any renderable GameObject
 * should reference this camera in order to find out its screen position, and
 * the camera's current zoom level.
 */
class Camera {

public:
    /*!
     * Obtain the current singleton instance. Creates it if it doesn't exist.
     * @return The instance of this class.
     */
    static Camera& GetInstance();
    /*!
     * Convert the given point from a screen space point to a world space point.
     * @param screenPoint The screen space point to convert.
     * @return The given point, in world space.
     */
    std::pair<float, float> screenToWorldPoint(std::pair<float, float> screenPoint);
    /*!
     * Convert the given point from a world space point to a screen space point.
     * @param worldPoint The world space point to convert.
     * @return The given point, in screen space.
     */
    std::pair<float, float> worldToScreenPoint(std::pair<float, float> worldPoint);
    /*!
     * The world space position of the camera. The same as the world space position
     * of the top left of the screen.
     */
    std::pair<float, float> position;
    /*!
     * The current zoom level of the camera.
     */
    float zoom = 4;
};

#endif //FINALPROJECT_SIMON_JON_DAMON_JASON_CAMERA_HPP
