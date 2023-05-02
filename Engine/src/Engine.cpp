#include "Engine.hpp"
#include "Managers/Input.hpp"
#include "ComponentSystem/ControllerComponent.hpp"
#include "ComponentSystem/SpriteComponent.hpp"
#include "ComponentSystem/TransformComponent.hpp"
#include "ComponentSystem/TileMapComponent.hpp"
#include "ComponentSystem/PhysicsComponent.hpp"

// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include <tuple> // TODO temp

const double SCREEN_FPS = 60.0;
const double MAX_TICKS_PER_FRAME = 1000.0 / SCREEN_FPS;

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine() { }

// Proper shutdown and destroy initialized objects
Engine::~Engine(){ }

// Return whether the user quit the game
void Engine::Input(bool *quit) {
    Input::GetInstance().handleInput();
    *quit = Input::GetInstance().gotQuitInput();
}

// Update the Engine
void Engine::Update(double dt) {
    for (GameObject go : m_gameobjects) {
        go.Update(dt);
    }
}

// The render function gets called once per loop
void Engine::Render() {
    // Set the color of the empty framebuffer
    mRenderer->SetRenderDrawColor(92, 148, 252, 0xFF);
    // Clear the screen to the color of the empty framebuffer
    mRenderer->RenderClear();
    SDL_Renderer *ren = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
    for (GameObject go : m_gameobjects) {
        go.Render(ren);
    }
    // Flip the buffer to render
    mRenderer->RenderPresent();
}

void Engine::Delay(int ms) {
    SDL_Delay(ms);
}

//Loops forever!
void Engine::MainGameLoop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;

    double lastTime = (double)SDL_GetTicks();

    // While application is running
    while(!quit){
      // Get user input
      Input(&quit);
      // If you have time, implement your frame capping code here
      // Otherwise, this is a cheap hack for this lab.
      double elapsed = (double)SDL_GetTicks() - lastTime;
      if (elapsed < MAX_TICKS_PER_FRAME) {
        SDL_Delay(MAX_TICKS_PER_FRAME - elapsed);
        elapsed = MAX_TICKS_PER_FRAME;
      }
      double newTime = (double)SDL_GetTicks();
      //std::cout << "FPS: " << 1000.0 / (newTime - lastTime) << std::endl;
      lastTime = newTime;
      // Update our scene
      Update(elapsed);
      // Render using OpenGL
      Render();
      //Update screen of our specified window
    }
    // Disable text input
    SDL_StopTextInput();
}

void Engine::AddGameObject(GameObject go) {
    m_gameobjects.push_back(go);
}

void Engine::Shutdown(){
    // Shut down our Tile Systems
    if (mRenderer != nullptr) {
        delete mRenderer;
    }
}

void Engine::InitializeGraphicsSubSystem() {
    // Set up our Renderer
    mRenderer = new SDLGraphicsEngineRenderer(1280,720);
    if(nullptr == mRenderer) {
        std::cout << "Failed to initialize graphics subsystem." << std::endl;
        exit(1);
    }
}

