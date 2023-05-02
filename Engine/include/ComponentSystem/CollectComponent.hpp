#ifndef COLLECTCOMPONENT_HPP
#define COLLECTCOMPONENT_HPP

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"

/*!
 * Detects if the player collides with the collectable object
 */
class CollectComponent : public Component{
public:

   /*!
     * Construct a CollectComponent.
     * @param pt the player's transform
     * @param t the coin's transform
     * @param s the coin's sprite
     */
CollectComponent(TransformComponent* pt, TransformComponent* t, SpriteComponent* s);
~CollectComponent();


 /*!
 * Update the status of this CollectComponent. Checks if there is interaction between the player and collectable
 * @param dt The time, in ms, that has passed since the last update.
 */
void Update(double dt) override;
void Render(SDL_Renderer *ren) override {};

private:
TransformComponent* transform;
TransformComponent* playerT;
SpriteComponent* sprite;

};

#endif