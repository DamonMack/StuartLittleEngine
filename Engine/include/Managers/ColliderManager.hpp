#ifndef COLLIDER_MANAGER_HPP
#define COLLIDER_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <vector>
#include <string>
#include "ComponentSystem/SpriteComponent.hpp"
#include "ComponentSystem/TileMapComponent.hpp"

/*!
 * Keeps track of all of the collision interactions in the program
 */
class ColliderManager{
public:
    /*!
     * creates an instance of the manager
     * @return the collider manager
     */
    static ColliderManager& GetInstance();
    /*!
     * stores the sprite's collider if it is added
     * @param collider the collider index
     */
    int StoreCollider(SpriteComponent* collider);
    /*!
     * checks all of the collisions between all of the objects 
     * @param tmc the tilemap
     * @param colliderID the collider index
     * @param xMove the player's x pos
     * @param yMove the player's y pos
     * @param intersection an SDL rect created from the sprite to detect collisons
     */
    bool CheckCollision(TileMapComponent* tmc, int colliderID, float xMove, float yMove, SDL_Rect* intersection);
     /*!
     * checks if there is a collision between two objects
     * @param colliderID1 the first collider index
     * @param colliderID2 the second collider index
     */
    bool Colliding(int colliderID1, int colliderID2);

private:
    ColliderManager();

    // map of collider ids to respective collider boxes/rectangles (maybe make a separate collider component later)
    std::vector<SpriteComponent*> colliders;
};


#endif
