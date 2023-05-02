#ifndef SPRITEEDITOR
#define SPRITEEDITOR

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "IGraphicsEngineRenderer.hpp"

/**!
 * This is an SDL program for the creation and modification of sprites used in the engine
 */
class SpriteEditor{
public:
    /**
     * Constructor of editor
     */
    SpriteEditor();
    /**
     * Destructor
     */
    ~SpriteEditor();
    /**!
     * Handles inputs when the program is not being launched in Pybind
     * @param quit a boolean reference that will be updated to true if a quit event was handled
     */
    void Input(bool *quit);

    /**!
     * Handles all SDL events in the editor. Designed to be called through pybind.
     * Returns true if a quit action occurred.
    */
    bool HandleInput();
    /**!
     * Per frame update
     */
    void Update();
    /**!
     * Per frame render. Renders everything
     */
    void Render();
    /**!
     * Main Game Loop that runs forever
     */
    void MainGameLoop();

    /**
     * Creates a new sprite given a filepath to a tile sheet, the number of frames, and the width and height of the frames
     * @param spriteSheetFilepath The filepath to the sprite sheet being used to create the sprite
     * @param frameCount The number of frames in the sprite's animation
     * @param timePerFrame The time each frame should be shown in miliseconds
     * @param frameWidth The width of the sprite
     * @param frameHeight The height of the sprite
    */
    void CreateNewSprite(std::string spriteSheetFilepath, int frameCount, int timePerFrame, int frameWidth, int frameHeight);

    /**!
     * Loads a sprite with information from the provided sprite file.
     * The sprite file must be in the same directory as the sprite sheet that it references.
     * @param filepath the filepath to the sprite file
    */
    void LoadSprite(std::string filepath);

    /**!
     * Increments which frame is currently being edited in the program. If at the last frame, loops back to the first.
    */
    void incrementCurrentFrame();
    /**!
     * Decrements which frame is currently being edited in the program. If at the first frame, loops back to the last.
    */
    void decrementCurrentFrame();

    /**!
     * A function for manually choosing a specific frame to switch to. The value is clamped between 0 and the number of frames
     * @param frame The frame to switch
    */
    void setCurrentFrame(int frame);

    /**!
     * A function for resizing the sprite currently being edited. The width of all frames of the sprite will be changed
     * @param width The new width of the sprite.
    */
    void setSpriteWidth(int width);
    /**!
     * A function for resizing the sprite currently being edited. The height of all frames of the sprite will be changed
     * @param height The new height of the sprite.
    */
    void setSpriteHeight(int height);

    /**!
     * Saves the sprite to a text file with the given name in the same directory as the sprite sheet. (Warning: overwrites the original file)
     * @param spriteName The name of the sprite, not the filepath
    */
    void SaveSprite(std::string spriteName);
    /**!
     * Initialization and shutdown pattern
     * Explicitly call 'Start' to launch the engine
     */
    void Start();
    /**!
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();

    /**!
     * Request to startup the Graphics Subsystem
     * @param width The width of the SDL window
     * @param height The height of the SDL window
     */
	void InitializeGraphicsSubSystem(int width, int height);


private:

    //! Engine Subsystem
    IGraphicsEngineRenderer* mRenderer = nullptr;

    // The surface and texture of the sprite sheet we are editing
    std::string m_spriteSheetPath;
    SDL_Surface* m_spriteSheet = nullptr;
    SDL_Texture* m_Texture = nullptr;

    // How big the sprite is
    int m_spriteWidth;
    int m_spriteHeight;
    // Time Per Frame
    int m_frameTime;

    // Current editor state variables
    SDL_Rect frame;
    std::vector<SDL_Rect> m_frames;
    int m_currentFrame;

};

#endif
