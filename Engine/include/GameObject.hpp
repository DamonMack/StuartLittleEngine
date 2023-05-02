#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>

#include "ComponentSystem/Component.hpp"

/*!
 * Base class for all GameObjects in the game.
 */
class GameObject{
public:
    /*!
     * Construct a GameObject.
     */
    GameObject();
    /*!
     * Destroy the GameObject.
     */
    ~GameObject();
    /*!
     * Update the status of the gameObject.
     * @param dt The time that has passed since last update.
     */
    void Update(double dt);
    /*!
     * Render the gameObject.
     * @param ren The renderer to render the gameObject with.
     */
    void Render(SDL_Renderer *ren);
    /*!
     * Add the given component to the gameObject.
     * @param c The component to add to the gameObject.
     */
    void AddComponent(Component* c);
    /*!
     * Destroy all components associated with this GameObject.
     */
    void DeleteComponents();
    
private:
    std::vector<Component*> m_components;
};


#endif
