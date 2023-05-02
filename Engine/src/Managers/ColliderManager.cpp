// I recommend an unordered_map for filling in the resource manager
#include <iostream>
#include "Managers/ColliderManager.hpp"

ColliderManager::ColliderManager(){
}

ColliderManager& ColliderManager::GetInstance() {
    static ColliderManager* s_instance = new ColliderManager; 
    return *s_instance; 
}


// store collider if sprite is added
int ColliderManager::StoreCollider(SpriteComponent* sc) {
    colliders.push_back(sc);
    return colliders.size() - 1;
}

// TODO: return sdl rect that given collider collides with
bool ColliderManager::CheckCollision(TileMapComponent* tmc, int colliderID, float xMove, float yMove, SDL_Rect* intersection) {
    SDL_Rect rect = colliders[colliderID]->GetDestRect();
    rect.x += xMove;
    rect.y += yMove;

    // so the character doesn't get stuck in the ground due to the edges of the rectangles colliding
    if (xMove == 0) {
        rect.w -= 1;
    }
    if (yMove == 0) {
        rect.h -= 1; 
    }

    // check collision with tiles
    if (tmc->CheckTileCollision(rect, intersection)) {
        return true;
    }

    // check collision with other objects
    // TODO: add hasCollider/isTrigger field to sprite component so an object can go through some other objects
    for(int i = 0; i < colliders.size(); i++) {
        if (i != colliderID) {
            SDL_Rect currRect = colliders[i]->GetDestRect();
            if(!colliders[i]->doesCollide()){
                return false;
            }
            
            if (SDL_IntersectRect(&currRect, &rect, intersection)) {
                return true;
            }
        }
    }

    return false;
}

bool ColliderManager::Colliding(int colliderID1, int colliderID2) {
    if (!colliders[colliderID1]->doesCollide() || !colliders[colliderID2]->doesCollide()) {
        return false;
    }
    SDL_Rect r1 = colliders[colliderID1]->GetDestRect();
    SDL_Rect r2 = colliders[colliderID2]->GetDestRect();
    return SDL_HasIntersection(&r1, &r2);
}