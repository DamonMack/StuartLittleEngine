#ifndef COMPONENT_HPP 
#define COMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include <iostream>

/*!
 * Base class for any Component that can be added to a GameObject.
 */
class Component{
    public:
        /*!
         * Construct a Component.
         */
        Component();
        /*!
         * Destroy the Component.
         */
        virtual ~Component();
        /*!
         * Update the status of the Component.
         * @param dt The time, in ms, that has passed since the last update.
         */
        virtual void Update(double dt) = 0;
        /*!
         * Render the Component.
         * @param ren The renderer to render the Component with.
         */
        virtual void Render(SDL_Renderer *ren);
};


#endif
