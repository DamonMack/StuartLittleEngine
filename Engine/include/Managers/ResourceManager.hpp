#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

// I recommend a map for filling in the resource manager
#include <unordered_map>
#include <string>

/*!
 * Singleton class which manages textures, ensuring that the
 * same texture is never loaded multiple times, and providing a texture to
 * anything that asks for it.
 */
class ResourceManager {
public:
    /*!
     * Obtain the singleton instance of the class. Creates it if it doesn't exist.
     * @return The instance of the class.
     */
    static ResourceManager& GetInstance();
    /*!
     * Load the image into the game, creating a texture for it. If the image
     * has been loaded before, does nothing.
     * @param image_filename The file path of the image to load.
     * @param renderer The renderer to create the texture with.
     */
    void LoadResource(std::string image_filename, SDL_Renderer* renderer);
    /*!
     * Obtain the texture associated with the given file path.
     * @param image_filename The file path associated with the texture.
     * @return The texture associated with the given file path.
     */
    SDL_Texture* GetResource(std::string image_filename);
    /*!
     * Deactivate the ResourceManager and destroy all textures that have
     * been loaded.
     */
    void ShutDown();

private:
    std::unordered_map<std::string, SDL_Texture*> textures;
};


#endif
