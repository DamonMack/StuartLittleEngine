#include <string>

#include "SpriteEditor.hpp"

// Constructor
SpriteEditor::SpriteEditor(){
}


// Destructor
SpriteEditor::~SpriteEditor(){
}

// Return Input
void SpriteEditor::Input(bool *quit){
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
                if(x >= 0 && x < m_spriteSheet->w - m_spriteWidth
                    && y >= 0 && y < m_spriteSheet->h - m_spriteHeight){
                    m_frames.at(m_currentFrame).x = x;
                    m_frames.at(m_currentFrame).y = y;
                }
                
            }
        }
        // Check if a key was pressed
        else if(e.type == SDL_KEYDOWN){
            // If a is pressed, move back through the current type
            if(e.key.keysym.sym == SDLK_a){
                decrementCurrentFrame();
            }
            // If d is pressed, move forward through the current type
            else if(e.key.keysym.sym == SDLK_d){
                incrementCurrentFrame();
            }
            else if(e.key.keysym.sym == SDLK_UP){
                if(m_frames.at(m_currentFrame).y > 0){
                    m_frames.at(m_currentFrame).y--;
                }
            }
            else if(e.key.keysym.sym == SDLK_DOWN){
                if(m_frames.at(m_currentFrame).y <= m_spriteSheet->h - m_spriteHeight){
                    m_frames.at(m_currentFrame).y++;
                }
            }
            else if(e.key.keysym.sym == SDLK_LEFT){
                if(m_frames.at(m_currentFrame).x > 0){
                    m_frames.at(m_currentFrame).x--;
                }
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){
                if(m_frames.at(m_currentFrame).x <= m_spriteSheet->w - m_spriteWidth){
                    m_frames.at(m_currentFrame).x++;
                }
            }
        }
        
      }
}

// Return Input
bool SpriteEditor::HandleInput(){
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
                if(x >= 0 && x < m_spriteSheet->w - m_spriteWidth
                    && y >= 0 && y < m_spriteSheet->h - m_spriteHeight){
                    m_frames.at(m_currentFrame).x = x;
                    m_frames.at(m_currentFrame).y = y;
                }
                
            }
        }
        // Check if a key was pressed
        else if(e.type == SDL_KEYDOWN){
            // If a is pressed, move back through the current type
            if(e.key.keysym.sym == SDLK_a){
                decrementCurrentFrame();
            }
            // If d is pressed, move forward through the current type
            else if(e.key.keysym.sym == SDLK_d){
                incrementCurrentFrame();
            }
            else if(e.key.keysym.sym == SDLK_UP){
                if(m_frames.at(m_currentFrame).y > 0){
                    m_frames.at(m_currentFrame).y--;
                }
            }
            else if(e.key.keysym.sym == SDLK_DOWN){
                if(m_frames.at(m_currentFrame).y <= m_spriteSheet->h - m_spriteHeight){
                    m_frames.at(m_currentFrame).y++;
                }
            }
            else if(e.key.keysym.sym == SDLK_LEFT){
                if(m_frames.at(m_currentFrame).x > 0){
                    m_frames.at(m_currentFrame).x--;
                }
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){
                if(m_frames.at(m_currentFrame).x <= m_spriteSheet->w - m_spriteWidth){
                    m_frames.at(m_currentFrame).x++;
                }
            }
        }
      }
      return false;
}

// Update SDL
void SpriteEditor::Update()
{

}


// Render
// The render function gets called once per loop
void SpriteEditor::Render(){
    // Set the color of the empty framebuffer
    mRenderer->SetRenderDrawColor(110, 130,170,0xFF);
    // Clear the screen to the color of the empty framebuffer
    mRenderer->RenderClear();

    SDL_Renderer* renderer = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = m_spriteSheet->w;
    dest.h = m_spriteSheet->h;
    SDL_RenderCopy(renderer, m_Texture, NULL, &dest);

    //SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    //SDL_RenderDrawRect(renderer, &frame);

    for(int i = 0; i < m_frames.size(); i++){
        if(i == m_currentFrame){
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        m_frames.at(i).w = m_spriteWidth;
        m_frames.at(i).h = m_spriteHeight;
        SDL_RenderDrawRect(renderer, &m_frames.at(i));
    }
    

    // Flip the buffer to render
    mRenderer->RenderPresent();
}



//Loops forever!
void SpriteEditor::MainGameLoop(){
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

void SpriteEditor::CreateNewSprite(std::string spriteSheetFilepath, int frameCount, int frameTime, int frameWidth, int frameHeight){
    m_spriteSheetPath = spriteSheetFilepath;
    m_frameTime = frameTime;
    m_spriteWidth = frameWidth;
    m_spriteHeight = frameHeight;

    // Destroy current sprite if it exists
    if(nullptr != m_spriteSheet){
        SDL_FreeSurface(m_spriteSheet);
    }
    if(nullptr != m_Texture){
        SDL_DestroyTexture(m_Texture);
    }
    m_frames.clear();

    SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();

    m_spriteSheet = SDL_LoadBMP(spriteSheetFilepath.c_str());

    if(nullptr == m_spriteSheet){
        SDL_Log("Failed to allocate surface");
    }else{
        m_Texture = SDL_CreateTextureFromSurface(renderer, m_spriteSheet);
    }

    for(int i = 0; i < frameCount; i++){
        SDL_Rect newFrame;
        newFrame.x = 0;
        newFrame.y = 0;
        newFrame.w = frameWidth;
        newFrame.h = frameHeight;
        m_frames.push_back(newFrame);
    }
    m_currentFrame = 0;
}

void SpriteEditor::LoadSprite(std::string filepath){
    // If a sprite is being edited, destroy it
    if(nullptr != m_spriteSheet){
        SDL_FreeSurface(m_spriteSheet);
    }
    if(m_Texture != nullptr){
        SDL_DestroyTexture(m_Texture);
    }

    // get directory of sprite file
    std::string directory = filepath.substr(0, filepath.find_last_of('/'));
    
    std::ifstream file;
    // open the file to start parsing
    file.open(filepath);
    if(file.is_open()){
        std::string line;

        // Retrieve the sprite sheet and create an SDL surface
        getline(file, line);
        m_spriteSheetPath = directory + '/' + line;
        m_spriteSheet = SDL_LoadBMP((directory + '/' + line).c_str());

        // Create the texture
        if(nullptr == m_spriteSheet){
            SDL_Log("Failed to allocate surface");
        }else{
            SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
            m_Texture = SDL_CreateTextureFromSurface(renderer, m_spriteSheet);
        }

        // Retrieve the frame count
        getline(file, line);
        int frameCount = std::stoi(line);

        // Retrieve the time per frame
        getline(file, line);
        m_frameTime = std::stoi(line);

        // Retrieve frame dimensions
        getline(file, line);
        m_spriteWidth = std::stoi(line);
        
        getline(file, line);
        m_spriteHeight = std::stoi(line);

        // Retrieve the tile information and populate m_frames
        // if frame count is higher than amount of frame data, set x and y to (0,0)
        m_frames.clear();
        for(int i = 0; i < frameCount; i++){
            SDL_Rect newFrame;
            if(getline(file, line)){
                newFrame.x = std::stoi(line);
            }else{
                newFrame.x = 0;
            }
            if(getline(file, line)){
                newFrame.y = std::stoi(line);
            }else{
                newFrame.y = 0;
            }

            newFrame.w = m_spriteWidth;
            newFrame.h = m_spriteHeight;
            m_frames.push_back(newFrame);
        }
        m_currentFrame = 0;
    }
}

void SpriteEditor::incrementCurrentFrame(){
    m_currentFrame++;
    if(m_currentFrame >= m_frames.size()){
        m_currentFrame = 0;
    }
}

void SpriteEditor::decrementCurrentFrame(){
    m_currentFrame--;
    if(m_currentFrame < 0){
        m_currentFrame = m_frames.size() - 1;
    }
}

void SpriteEditor::setCurrentFrame(int frame){
    if(frame >= m_frames.size()){
        m_currentFrame = m_frames.size() - 1;
    }
    else if(frame < 0){
        m_currentFrame = 0;
    }
    else{
        m_currentFrame = frame;
    }
}

void SpriteEditor::setSpriteWidth(int width){
    if(width <= 1){
        m_spriteWidth = width;
    }
}
    
void SpriteEditor::setSpriteHeight(int height){
    if(height <= 1){
        m_spriteHeight = height;
    }
}

void SpriteEditor::SaveSprite(std::string spriteName){
    // Get the directory of current sprite sheet
    std::string filepath = m_spriteSheetPath.substr(0, m_spriteSheetPath.find_last_of('/'));
    std::string spriteSheetName = m_spriteSheetPath.substr(m_spriteSheetPath.find_last_of('/') + 1);

    // Create the filepath for the for the sprite file
    filepath.append("/" + spriteName + ".txt");

    std::ofstream file;
    // Open the file to start writing (in truncate mode)
    file.open(filepath, std::ios::trunc);
    if(file.is_open()){
        // Write the file path to the sprite sheet
        file << spriteSheetName << std::endl;

        // Write the frame count to the file
        file << m_frames.size() << std::endl;

        file << m_frameTime << std::endl;

        // Write the sprite dimensions to the file
        file << m_spriteWidth << std::endl;
        file << m_spriteHeight << std::endl;

        // List out the x and y values of the frames
        for(int i = 0; i < m_frames.size(); i++){
            file << m_frames.at(i).x << std::endl;
            file << m_frames.at(i).y << std::endl;
        }
    }
    file.close();
}

void SpriteEditor::Start(){

    // Report which subsystems are being initialized
    if(mRenderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

}

void SpriteEditor::Shutdown(){
    // Shut down our Tile Systems
    if(nullptr!=mRenderer){
        delete mRenderer;
    } 
    if(m_Texture != nullptr){
        SDL_DestroyTexture(m_Texture);
    }
    if(m_spriteSheet != nullptr){
        SDL_FreeSurface(m_spriteSheet);
    }
}

void SpriteEditor::InitializeGraphicsSubSystem(int width, int height){
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

PYBIND11_MODULE(mygameengine2, m){
    m.doc() = "A sprite editor for our engine";

    py::class_<SpriteEditor>(m, "SpriteEditor")
            .def(py::init<>())
            .def("Start", &SpriteEditor::Start)
            .def("Shutdown", &SpriteEditor::Shutdown)
            .def("InitializeGraphicsSubSystem", &SpriteEditor::InitializeGraphicsSubSystem)
            .def("Input", &SpriteEditor::HandleInput)
            .def("CreateNewSprite", &SpriteEditor::CreateNewSprite)
            .def("SaveSprite", &SpriteEditor::SaveSprite)
            .def("LoadSprite", &SpriteEditor::LoadSprite)
            .def("Render", &SpriteEditor::Render)
            .def("SetCurrentFrame", &SpriteEditor::setCurrentFrame)
            .def("SetSpriteWidth", &SpriteEditor::setSpriteWidth)
            .def("SetSpriteHeight", &SpriteEditor::setSpriteHeight);
}
*/