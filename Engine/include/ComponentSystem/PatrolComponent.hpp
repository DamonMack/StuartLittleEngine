#ifndef PATROLCOMPONENT_HPP_
#define PATROLCOMPONENT_HPP_

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 * Allows a character to move left and right in a patrolling motion.
 */
class PatrolComponent : public Component{
public:
    /*!
     * Construct a PatrolComponent.
     * @param d The distance for this character to move right before turning back.
     * @param s The patrol speed.
     * @param tc The TransformComponent to manipulate.
     */
    PatrolComponent(int d, int s, TransformComponent* tc);
    /*!
     * Destroy this PatrolComponent.
     */
    ~PatrolComponent();

    /*!
     * Update the position of the character for the patrol.
     * @param dt The time that has passed since the last update.
     */
    void Update(double dt) override;

private:
    int distance, speed;
    int counter = 0;
    bool right = true;
    TransformComponent* transform;
};

#endif 