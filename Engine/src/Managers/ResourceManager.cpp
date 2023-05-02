// I recommend an unordered_map for filling in the resource manager
#include "Managers/ResourceManager.hpp"
#include <iterator>
#include <iostream>

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

void ResourceManager::LoadResource(std::string image_filename, SDL_Renderer* renderer){
    if (textures[image_filename] == nullptr) {
        SDL_Surface* spriteSheet = SDL_LoadBMP(image_filename.c_str());
        if (spriteSheet == nullptr){
            std::cerr << image_filename << " not found!\n";
        } else {
            std::cout << "SDL_LoadBMP allocated\n";
        }

        // Texture data on the GPU that we keep track of
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, spriteSheet);

        if (texture == nullptr) {
            std::cerr << "Error creating texture\n";
        } else {
            std::cout << "SDL_Texture allocated\n";
        }

        //store texture data
        textures[image_filename] = texture;

        // Free surface once we are done setting up our texture
        SDL_FreeSurface(spriteSheet);

        std::cout << "New copy of " << image_filename << " has been loaded\n";
    }
}

SDL_Texture* ResourceManager::GetResource(std::string image_filename){
    std::cout << "Retrieved saved copy of " << image_filename << " from GetResource\n";
    return textures[image_filename];
}

void ResourceManager::ShutDown() {
    // Free surface once we are done setting up our texture
    for (auto i = textures.begin(); i != textures.end(); i++) {
        SDL_DestroyTexture(i->second);
    }
}
