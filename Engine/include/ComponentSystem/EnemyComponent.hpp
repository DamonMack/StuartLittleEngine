#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 * Detects if the player collides with the enemy
 */
class EnemyComponent : public Component{
public:

   /*!
     * Construct a EnemyComponent.
     * @param pt the player's transform
     * @param t the enemy's transform
     */
EnemyComponent(TransformComponent* pt, TransformComponent* t);
~EnemyComponent();

 /*!
 * Update the status of this EnemyComponent. Checks if there is interaction between the player and enemy
 * @param dt The time, in ms, that has passed since the last update.
 */
void Update(double dt) override;
void Render(SDL_Renderer *ren) override {};

private:
TransformComponent* transform;
TransformComponent* playerT;
};

#endif