#ifndef PHYSICSCOMPONENT_HPP 
#define PHYSICSCOMPONENT_HPP

#include <vector>
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "TileMapComponent.hpp"


/*!
 * Applies the constraints of physics on the object
 */
class PhysicsComponent : public Component{
    public:
    /*!
     * Construct a PhysicsComponent.
     * @param tc the transformComp of the object for its position
     * @param tmc the current tilemap 
     * @param usesGravity determines if gravity applies
     * @param colliderID identifying the specific object being colliding with
     */
        PhysicsComponent(TransformComponent* tc, TileMapComponent* tmc, bool usesGravity, int colliderID);
        ~PhysicsComponent();

        void Update(double dt) override;
        void Render(SDL_Renderer *ren) override {};


        /*!
         * Checks if the object is moving left or right
         * @param moveDirection the direction of the object
         */
        void SetXVelocity(int moveDirection);
        /*!
         * Sets the current x and y velocity of the object.
         * @param x the x velocity
         * @param y the y velocity
         */
        void SetVelocity(float x, float y);
        /*!
         * Get the current X velocity of the object.
         * @return The current X velocity of the object.
         */
        float GetXVelocity();
        /*!
         * Get the current Y velocity of the object.
         * @return The current Y velocity of the object.
         */
        float GetYVelocity();
        /*!
         * Checks if the current object is grounded
         * @return true/false
         */
        bool IsGrounded();
        /*!
         * allow the object to jump
         * applies gravity to the object if it is not grounded
         */
        void Jump();

    private:
        TransformComponent* transform;
        TileMapComponent* tilemap;
        
        bool usesGravity;

        int colliderID;
        
        Vec2D velocity;
        bool isGrounded = false;
};


#endif