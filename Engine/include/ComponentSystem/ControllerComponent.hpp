#ifndef CONTROLLERCOMPONENT_HPP 
#define CONTROLLERCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <vector>
#include "Component.hpp"
#include "PhysicsComponent.hpp"

/*!
 * Component which serves as an interface for easily controlling and
 * manipulating a character.
 */
class ControllerComponent : public Component{
    public:
        /*!
         * Construct a ControllerComponent.
         * @param pc The PhysicsComponent which handles interactions between
         * the character and other GameObjects.
         */
        ControllerComponent(PhysicsComponent* pc);
        /*!
         * Destroy a ControllerComponent.
         */
        ~ControllerComponent();
        /*!
         * Update the status of this ControllerComponent.
         * @param dt The time, in ms, that has passed since the last update.
         */
        void Update(double dt) override;
        /*!
         * Hard set the character's velocity to the given X and Y values.
         * @param x The X velocity to set.
         * @param y The Y velocity to set.
         */
        void SetVelocity(float x, float y);
        /*!
         * Get the current X velocity of the character.
         * @return The current X velocity of the character.
         */
        float GetXVelocity();
        /*!
         * Get the current Y velocity of the character.
         * @return The current Y velocity of the character.
         */
        float GetYVelocity();
        /*!
         * Is the character currently on the ground?
         * @return Whether or not the character is on the ground.
         */
        bool IsGrounded();

    private:
        PhysicsComponent* physics;

        int mMoveDirection = 0;
};


#endif
