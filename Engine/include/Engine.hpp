#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "GameObject.hpp"
#include "IGraphicsEngineRenderer.hpp"

/**!
 * This class sets up the main game engine
 */
class Engine{
public:
    /**!
     * Constructor of Engine
     */
    Engine();
    /**!
     * Destructor
     */
    ~Engine();
    /**!
     * Input engine
     * @param quit a boolean reference that will be updated to true if a quit event was handled
     */
    void Input(bool *quit);
    /**!
     * Per frame update
     */
    void Update(double dt);
    /**!
     * Per frame render. Renders everything
     */
    void Render();
    /**!
     * Pause the game by the given amount of milliseconds.
     */
    void Delay(int ms);
    /**!
     * Main Game Loop that runs forever
     */
    void MainGameLoop();
    /**!
     * Add the given gameObject to the game.
     */
    void AddGameObject(GameObject go);
    /**!
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();
    /**!
     * Request to startup the Graphics Subsystem
     */
	void InitializeGraphicsSubSystem();


private:
    //! Engine Subsystem
    // Setup the Graphics Rendering Engine
    IGraphicsEngineRenderer* mRenderer = nullptr;

    std::vector<GameObject> m_gameobjects;
};

#endif
