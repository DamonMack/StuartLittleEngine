//
// Created by Jonathan Lehman on 4/17/23.
//

#ifndef FINALPROJECT_SIMON_JON_DAMON_JASON_ANIMATORCOMPONENT_HPP
#define FINALPROJECT_SIMON_JON_DAMON_JASON_ANIMATORCOMPONENT_HPP

#include <vector>
#include <tuple>
#include <functional>
#include "SpriteComponent.hpp"

/*!
 * Component which manages multiple spriteComponents, and displays one of them,
 * depending on the conditions given which are associated with the sprites.
 * A GameObject should have an AnimatorComponent or a SpriteComponent - not both
 */
class AnimatorComponent : public Component {

public:
    /*!
     * Construct the AnimatorComponent
     */
    AnimatorComponent();
    /*!
     * Destroy the AnimatorComponent
     */
    ~AnimatorComponent();
    /*!
     * Update all SpriteComponents in this AnimatorComponent
     * @param dt The time passed since last frame
     */
    void Update(double dt) override;
    /*!
     * Render the first SpriteComponent whose condition is fulfilled
     * @param ren The renderer to use when rendering the component
     */
    void Render(SDL_Renderer *ren) override;
    /*!
     * Add a new SpriteComponent, with its condition, to the animator.
     * @param sprite The new SpriteComponent to add
     * @param condition The predicate (condition) associated with the new SpriteComponent
     */
    void AddSprite(SpriteComponent* sprite, std::function<bool()> condition);

private:
    std::vector<std::pair<SpriteComponent*, std::function<bool()>>> sprites;
};

#endif //FINALPROJECT_SIMON_JON_DAMON_JASON_ANIMATORCOMPONENT_HPP
