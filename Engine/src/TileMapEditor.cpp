#include <string>

#include "TileMapEditor.hpp"
#include "ComponentSystem/TileMapComponent.hpp"

// Constructor
TileMapEditor::TileMapEditor(){
}


// Destructor
TileMapEditor::~TileMapEditor(){
}

// Return Input
void TileMapEditor::Input(bool *quit){
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          *quit = true;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN){
            // Check if the left mouse button was clicked
            if(e.button.button == SDL_BUTTON_LEFT){
                // Retrive the location where the mouse was clicked.
                int x, y;
                SDL_GetMouseState(&x, &y);
                // Determine which tile was pressed and update the tilemap
                SetTile(x / m_TileWidth, y / m_TileHeight);
            }
            // check if the right mouse button was clicked
            else if (e.button.button == SDL_BUTTON_RIGHT){
                m_currentType = -1;
            }
        }
        // Check if a key was pressed
        else if(e.type == SDL_KEYDOWN){
            // If a is pressed, move back through the current type
            if(e.key.keysym.sym == SDLK_a){
                decrementCurrentType();
            }
            // If d is pressed, move forward through the current type
            else if(e.key.keysym.sym == SDLK_d){
                incrementCurrentType();
            }
        }
        
      }
}

// Return Input
bool TileMapEditor::HandleInput(){
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          return true;
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN){
            // Check if the left mouse button was clicked
            if(e.button.button == SDL_BUTTON_LEFT){
                // Retrive the location where the mouse was clicked.
                int x, y;
                SDL_GetMouseState(&x, &y);
                // Determine which tile was pressed and update the tilemap
                SetTile(x / m_TileWidth, y / m_TileHeight);
            }
            // check if the right mouse button was clicked
            else if (e.button.button == SDL_BUTTON_RIGHT){
                m_currentType = -1;
            }
        }
        // Check if a key was pressed
        else if(e.type == SDL_KEYDOWN){
            // If a is pressed, move back through the current type
            if(e.key.keysym.sym == SDLK_a){
                decrementCurrentType();
            }
            // If d is pressed, move forward through the current type
            else if(e.key.keysym.sym == SDLK_d){
                incrementCurrentType();
            }
        }
        
      }
      return false;
}

// Update SDL
void TileMapEditor::Update()
{

}


// Render
// The render function gets called once per loop
void TileMapEditor::Render(){
    // Set the color of the empty framebuffer
    mRenderer->SetRenderDrawColor(110, 130,170,0xFF);
    // Clear the screen to the color of the empty framebuffer
    mRenderer->RenderClear();

    SDL_Renderer* renderer = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
    
    // Render the tile map
    if(m_TileMap != nullptr){
        m_TileMap->RenderEditor(renderer);
        renderCursor();
    }

    // Flip the buffer to render
    mRenderer->RenderPresent();
}



//Loops forever!
void TileMapEditor::MainGameLoop(){

    if(m_TileMap == nullptr){
        std::cout << "Editor cannot be started without a tile map" << std::endl;
        std::cout << "Please create or load a tile map first" << std::endl;
        return;
    }
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;

    // While application is running
    while(!quit){
      // Get user input
      Input(&quit);
      // If you have time, implement your frame capping code here
      // Otherwise, this is a cheap hack for this lab.
      SDL_Delay(20);
      // Update our scene
      Update();
      
      // Render using OpenGL
      Render();
      //Update screen of our specified window
    }
    
    //Disable text input
    SDL_StopTextInput();
}

void TileMapEditor::CreateTileMap(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY){
    // Save the dimensions of the tilemap and the tile sheet
    m_Rows = rows;
    m_Cols = cols;
    m_TileWidth = _TileWidth;
    m_TileHeight = _TileHeight;
    m_MapX = _mapX;
    m_MapY = _mapY;
    m_typeCount = rows * cols;
    m_currentType = -1;

    // If there is currently a tile map being edited, destroy it
    if(nullptr!=m_TileMap){
        delete m_TileMap;
    }

    //Get pointer to renderer
    SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();

    //create the new tile map
    m_TileMap = new TileMapComponent(tileSheetFileName, m_Rows, m_Cols, m_TileWidth, m_TileHeight, m_MapX, m_MapY, renderer);
}

void TileMapEditor::LoadTileMap(std::string filepath){
    // If there is currently a tile map being edited, destroy it
    if(nullptr!=m_TileMap){
        delete m_TileMap;
    }

    //Get pointer to renderer
    SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();

    m_TileMap = new TileMapComponent(filepath, renderer);

    // Set the values once the tile map has successfully loaded
    m_Rows = m_TileMap->getTileSheetRows();
    m_Cols = m_TileMap->getTileSheetCols();
    m_TileWidth = m_TileMap->getTileWidth();
    m_TileHeight = m_TileMap->getTileHeight();
    m_MapX = m_TileMap->getTileMapX();
    m_MapY = m_TileMap->getTileMapY();
    m_typeCount = m_Rows * m_Cols;
    m_currentType = -1;
}

void TileMapEditor::SetTile(int x, int y){
    // Check that a map is being edited before attempting
    if(m_TileMap == nullptr){
        std::cout << "A tile map must be open before tiles can be set!" << std::endl;
        return;
    }

    // Check for deletion mode
    if(m_currentType <= -1){
        m_TileMap->SetTile(x, y, -1);
    }
    // Check that current type is within bounds of the tile sheet
    else if(m_currentType < m_typeCount){
        m_TileMap->SetTile(x, y, m_currentType);
    }
}

void TileMapEditor::incrementCurrentType(){
    // Check if a tile map is currently being edited
    if(m_TileMap != nullptr){
        // If in deletion mode, return to the start
        if(m_currentType <= -1){
            m_currentType = 0;
        }
        else{
            m_currentType++;
            if(m_currentType >= m_typeCount){
                m_currentType = 0;
            }
        }
    }
}

void TileMapEditor::decrementCurrentType(){
    // Check if a tile map is currently being edited
    if(m_TileMap != nullptr){
        // If in deletion mode, return to the start
        if(m_currentType <= -1){
            m_currentType = m_typeCount - 1;
        }
        else{
            m_currentType--;
            if(m_currentType < 0){
                m_currentType = m_typeCount - 1;
            }
        }
    }
}

void TileMapEditor::setCurrentType(int type){
    if(m_TileMap != nullptr){
        if(type < -1){
            m_currentType = -1;
        }
        else if (type >= m_typeCount){
            m_currentType = m_typeCount - 1;
        }
        else{
            m_currentType = type;
        }
    }
}

void TileMapEditor::renderCursor(){
    // Get the current mouse position and translate it to the dimensions of the tile map
    int x, y;
    SDL_GetMouseState(&x, &y);
    x /= m_TileWidth;
    y /= m_TileHeight;

    //check if the cursor is within the tilemap boundaries
    if(x < m_MapX && y < m_MapY){
        SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
        SDL_Rect cursor = {x * m_TileWidth, y * m_TileHeight, m_TileWidth, m_TileHeight};

        // A negative type means the editor is in delete mode, so the cursor is red
        if(m_currentType <= -1){
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &cursor);
        }
        // Check to make sure current type is within bounds of tile sheet
        else if (m_currentType < m_typeCount){
            SDL_Rect src;
            src.x = (m_currentType % m_Cols) * m_TileWidth;
            src.y = (m_currentType / m_Rows) * m_TileHeight;
            src.w = m_TileWidth;
            src.h = m_TileHeight;
            SDL_RenderCopy(renderer, m_TileMap->GetTileSheet(), &src, &cursor);
        }
    }
}

void TileMapEditor::SaveTileMap(std::string tileMapName){
    m_TileMap->SaveTileMap(tileMapName);
}

void TileMapEditor::Start(){

    // Report which subsystems are being initialized
    if(mRenderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

    SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();

    //m_TileMap = new TileMapComponent("./images/Tiles1.bmp",8,8,64,64,20,11,renderer);

}

void TileMapEditor::Shutdown(){
    // Shut down our Tile Systems
    if(nullptr!=mRenderer){
        delete mRenderer;
    } 

    // Destroy our tilemap
    if(nullptr!=m_TileMap){
        delete m_TileMap;
    }
}

void TileMapEditor::InitializeGraphicsSubSystem(int width, int height){
    // Setup our Renderer
    mRenderer = new SDLGraphicsEngineRenderer(width, height);
    if(nullptr == mRenderer){
        exit(1); // Terminate program if renderer 
                 // cannot be created.
                 // (Optional) TODO:   Could put an error 
                 //                    messeage, or try to 
                 //                    reinitialize the engine 
                 //                    with a different render
    }
}

/*
// pybindings
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(tileMapEditor, m){
    m.doc() = "A tilemap editor for our engine";

    py::class_<TileMapEditor>(m, "TileMapEditor")
            .def(py::init<>())
            .def("Start", &TileMapEditor::Start)
            .def("Shutdown", &TileMapEditor::Shutdown)
            .def("InitializeGraphicsSubSystem", &TileMapEditor::InitializeGraphicsSubSystem)
            .def("Input", &TileMapEditor::HandleInput)
            .def("CreateTileMap", &TileMapEditor::CreateTileMap)
            .def("SaveTileMap", &TileMapEditor::SaveTileMap)
            .def("LoadTileMap", &TileMapEditor::LoadTileMap)
            .def("Render", &TileMapEditor::Render)
            .def("SetCurrentType", &TileMapEditor::setCurrentType);
}
*/