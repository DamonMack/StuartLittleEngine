#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"
#include "../TinyMath.hpp"

/*!
 * Keeps track of an objects position
 */
class TransformComponent : public Component{
    public:
    /*!
     * Construct a TransformComponent.
     * @param x the object's x pos
     * @param y the object's y pos
     */
        TransformComponent(int x, int y);
        ~TransformComponent();

        void Update(double dt) override {};
        void Render(SDL_Renderer *ren) override {};

        /*!
         * Get the current X pos of the object.
         * @return The current X pos of the object.
         */
        float GetX();
        /*!
         * Get the current Y pos of the object.
         * @return The current Y pos of the object.
         */
        float GetY();
        /*!
         * Set the current X pos of the object.
         * @param x desired x pos
         */
        void SetX(float x);
        /*!
         * Set the current y pos of the object.
         * @param y desired y pos
         */
        void SetY(float y);

        Vec2D position;
    private:
        
};


#endif
