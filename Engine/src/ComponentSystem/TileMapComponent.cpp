#include <iostream>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <fstream>

#include "ComponentSystem/TileMapComponent.hpp"
#include "Managers/ResourceManager.hpp"
#include "Managers/Camera.hpp"

// Creates a new tile map.
// rows and cols are how many different tiles there are in the sprite sheet
// 
// _TileWidth and _TileHeight are the size of each individual
// tile in the sprite sheet.
// (Typically this works best if they are square for this implementation.)
//
// _mapX, and _mapY are the size of the TileMapComponent. This is the actual
// number of tiles in the game that the player sees, not how many tiles
// are in the actual sprite sheet file loaded.
TileMapComponent::TileMapComponent(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* ren){
    if(nullptr==ren){
        SDL_Log("No valid renderer found");
    }

    // Setup variables
    m_filepath = tileSheetFileName;
    m_Rows = rows;
    m_Cols = cols;
    m_TileWidth = _TileWidth;
    m_TileHeight = _TileHeight;
    m_MapX = _mapX;
    m_MapY = _mapY;
    renderer = ren;
    // Load the TileMapComponent Image
    // This is the image that will get
    // sliced into smaller subsections of individual tiles.
    m_TileSpriteSheet = SDL_LoadBMP(tileSheetFileName.c_str());
	
    if(nullptr == m_TileSpriteSheet){
           SDL_Log("Failed to allocate surface");
    }else{
        // Create a texture from our surface
        // Textures run faster and take advantage of
        //  hardware acceleration
        m_Texture = SDL_CreateTextureFromSurface(renderer, m_TileSpriteSheet);
    }

    // Setup the TileMapComponent array
    // This sets each tile to '0'
    m_Tiles = new int[m_MapX*m_MapY];
    for(int i=0; i < m_MapX*m_MapY; i++){
        m_Tiles[i] = -1; // Default value is no tile.
    }

    GenerateSimpleMap();

    SDL_Rect Src, Dest;
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
            // Select our Tile
            int currentTile = GetTileType(x,y);
            if(currentTile > -1 ){
                // Reverse lookup, given the tile type
                // and then figuring out how to select it
                // from the texture atlas.
                Src.x = (currentTile % m_Cols) * m_TileWidth;
                Src.y = (currentTile / m_Rows) * m_TileHeight;
                Src.w = m_TileWidth; 
                Src.h = m_TileHeight; 
                // Render our Tile at this location
                // Account for camera
                std::pair<int, int> screenPoint = Camera::GetInstance().worldToScreenPoint(
                        std::pair<int, int>(x*m_TileWidth, y*m_TileHeight));
                Dest.x = screenPoint.first / Camera::GetInstance().zoom;
                Dest.y = screenPoint.second / Camera::GetInstance().zoom;
                Dest.w = m_TileWidth;
                Dest.h = m_TileHeight;

                srcRects.push_back(Src);
                destRects.push_back(Dest);
            }
        }
    }
}

TileMapComponent::TileMapComponent(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY) {
    // Setup variables
    m_Rows = rows;
    m_Cols = cols;
    m_TileWidth = _TileWidth;
    m_TileHeight = _TileHeight;
    m_MapX = _mapX;
    m_MapY = _mapY;
    m_filepath = tileSheetFileName;

    // Setup the TileMapComponent array
    // This sets each tile to '0'
    m_Tiles = new int[m_MapX * m_MapY];
    for (int i = 0; i < m_MapX * m_MapY; i++) {
        m_Tiles[i] = -1; // Default value is no tile.
    }

    GenerateSimpleMap();

    SDL_Rect Src, Dest;
    for (int y= 0; y < m_MapY; y++){
        for( int x= 0; x < m_MapX; x++){
            // Select our Tile
            int currentTile = GetTileType(x,y);
            if (currentTile > -1 ){
                // Reverse lookup, given the tile type
                // and then figuring out how to select it
                // from the texture atlas.
                Src.x = (currentTile % m_Cols) * m_TileWidth;
                Src.y = (currentTile / m_Rows) * m_TileHeight;
                Src.w = m_TileWidth; 
                Src.h = m_TileHeight; 
                // Render our Tile at this location
                // Account for camera
                std::pair<int, int> screenPoint = Camera::GetInstance().worldToScreenPoint(
                        std::pair<int, int>(x*m_TileWidth, y*m_TileHeight));
                Dest.x = screenPoint.first / Camera::GetInstance().zoom;
                Dest.y = screenPoint.second / Camera::GetInstance().zoom;
                Dest.w = m_TileWidth;
                Dest.h = m_TileHeight;

                srcRects.push_back(Src);
                destRects.push_back(Dest);
            }
        }
    }
}

TileMapComponent::TileMapComponent(std::string filepath, SDL_Renderer* ren){
    if(nullptr==ren){
        SDL_Log("No valid renderer found");
    }
    loadTileMap(filepath);
}

TileMapComponent::TileMapComponent(std::string filepath) {
    loadTileMap(filepath);
}

// Destructor
TileMapComponent::~TileMapComponent(){
    //SDL_DestroyTexture(m_Texture);
    //SDL_FreeSurface(m_TileSpriteSheet);
    // Remove our TileMapComponent
    delete[] m_Tiles;
}

// Helper function to gegenerate a simlpe map
void TileMapComponent::GenerateSimpleMap(){
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
           if(y==0){ 
                SetTile(x,y,12);
           }
           if(y==m_MapY-1){ 
                SetTile(x,y,0);
           }
       }
    }
    SetTile(8,m_MapY-5,0);
    SetTile(9,m_MapY-5,0);
    SetTile(10,m_MapY-5,0);
    SetTile(11,m_MapY-4,0);
}

// Helper function to print out the tile map
// to the console
void TileMapComponent::PrintMap(){
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
            std::cout << std::setw(3) << GetTileType(x,y);
       }
         std::cout << "\n";
    }
}

// Sets a tile a certain type
void TileMapComponent::SetTile(int x, int y, int type){
    m_Tiles[y * m_MapX + x] = type;
}


// Returns what the tile is at a specific position.
int TileMapComponent::GetTileType(int x, int y){
    return m_Tiles[y * m_MapX + x];
}

SDL_Texture* TileMapComponent::GetTileSheet(){
    return m_Texture;
}

void TileMapComponent::SaveTileMap(std::string tileMapName){
    // Get the directory of current tilesheet
    std::string filepath = m_filepath.substr(0, m_filepath.find_last_of('/'));
    std::string tileSheetName = m_filepath.substr(m_filepath.find_last_of('/') + 1);

    // Create the filepath for the tilemap file
    filepath.append("/" + tileMapName + ".txt");

    std::ofstream file;
    // Open the file to start writing (in truncate mode)
    file.open(filepath, std::ios::trunc);
    std::cout << "Save: " << filepath << std::endl;
    if(file.is_open()){
        // Write the file path to the tilesheet
        file << tileSheetName << std::endl;

        // Write the number of rows and columns in the tile sheet
        file << m_Rows << std::endl;
        file << m_Cols << std::endl;

        // Write the tile dimensions 
        file << m_TileWidth << std::endl;
        file << m_TileHeight << std::endl;

        // Write the dimensions of the tile map
        file << m_MapX << std::endl;
        file << m_MapY << std::endl;

        // List out the types of the tiles in the tile map
        for(int y= 0; y < m_MapY; y++){
            for(int x= 0; x < m_MapX; x++){
                file << GetTileType(x,y) << std::endl;
            }
        }
    }
    file.close();
}

void TileMapComponent::loadTileMap(std::string filepath){
    // Get the directory of tile map file
    std::string directory = filepath.substr(0, filepath.find_last_of('/'));
    std::cout << "Directory: " << directory << std::endl;

    std::ifstream file;
    // open the file to start parsing
    file.open(filepath);
    if(file.is_open()){
        std::string line;

        // Retrieve the tile sheet and create an SDL surface
        getline(file, line);
        m_filepath = directory + '/' + line;
        /*
        m_TileSpriteSheet = SDL_LoadBMP((directory + '/' + line).c_str());

        // Create the texture
        if(nullptr == m_TileSpriteSheet){
           SDL_Log("Failed to allocate surface");
        }else{
            m_Texture = SDL_CreateTextureFromSurface(ren, m_TileSpriteSheet);
        }
         */

        // Retrieve the number of rows and columns in the tile sheet
        getline(file, line);
        m_Rows = std::stoi(line);

        getline(file, line);
        m_Cols = std::stoi(line);

        // Retrieve the dimensions of the tiles
        getline(file, line);
        m_TileWidth = std::stoi(line);

        getline(file, line);
        m_TileHeight = std::stoi(line);

        // Retrieve the dimensions of the tile map
        getline(file, line);
        m_MapX = std::stoi(line);

        getline(file, line);
        m_MapY = std::stoi(line);

        // Retrieve the tile types of the tile map
        // If the number of tiles in the map is greater than the amount of data in the file
        // then missing tiles will have the empty (-1) type
        m_Tiles = new int[m_MapX*m_MapY];
        for(int i=0; i < m_MapX*m_MapY; i++){
            if(getline(file, line)){
                m_Tiles[i] = std::stoi(line);
            }
            else{
                m_Tiles[i] = -1; // Default value is no tile.
            }
        }
    }
    file.close();

    //renderer = ren;
    SDL_Rect Src, Dest;
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
            // Select our Tile
            int currentTile = GetTileType(x,y);
            if(currentTile > -1 ){
                // Reverse lookup, given the tile type
                // and then figuring out how to select it
                // from the texture atlas.
                Src.x = (currentTile % m_Cols) * m_TileWidth;
                Src.y = (currentTile / m_Rows) * m_TileHeight;
                Src.w = m_TileWidth; 
                Src.h = m_TileHeight; 
                // Render our Tile at this location
                // Account for camera
                std::pair<int, int> screenPoint = Camera::GetInstance().worldToScreenPoint(
                        std::pair<int, int>(x*m_TileWidth, y*m_TileHeight));
                Dest.x = screenPoint.first / Camera::GetInstance().zoom;
                Dest.y = screenPoint.second / Camera::GetInstance().zoom;
                Dest.w = m_TileWidth;
                Dest.h = m_TileHeight;

                srcRects.push_back(Src);
                destRects.push_back(Dest);
            }
        }
    }
}

// render TileMapComponent
void TileMapComponent::Render(SDL_Renderer *ren) {
    if (m_Texture == nullptr) {
        ResourceManager::GetInstance().LoadResource(m_filepath, ren);
        m_Texture = ResourceManager::GetInstance().GetResource(m_filepath);
    }
    // iterate over srcRects and destRects
    for (int i = 0; i < srcRects.size(); i++) {
        // Account for camera
        SDL_Rect tempDest = destRects[i];

        std::pair<int, int> screenPoint = Camera::GetInstance().worldToScreenPoint(
                std::pair<int, int>(tempDest.x, tempDest.y));
        tempDest.x = screenPoint.first;
        tempDest.y = screenPoint.second;
        tempDest.w *= Camera::GetInstance().zoom;
        tempDest.h *= Camera::GetInstance().zoom;
        SDL_RenderCopy(ren, m_Texture, &srcRects[i], &tempDest);
    }
}

// render TileMap in a format specific to the tilemap editor
void TileMapComponent::RenderEditor(SDL_Renderer* ren){
    if(nullptr==ren){
        SDL_Log("No valid renderer found");
    }
    if (m_Texture == nullptr) {
        ResourceManager::GetInstance().LoadResource(m_filepath, ren);
        m_Texture = ResourceManager::GetInstance().GetResource(m_filepath);
    }
    
    SDL_Rect Src, Dest;
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
            // Select our Tile
            int currentTile = GetTileType(x,y);
            if(currentTile > -1 ){
                // Reverse lookup, given the tile type
                // and then figuring out how to select it
                // from the texture atlas.
                Src.x = (currentTile % m_Cols) * m_TileWidth;
                Src.y = (currentTile / m_Rows) * m_TileHeight;
                Src.w = m_TileWidth; 
                Src.h = m_TileHeight; 
                // Render our Tile at this location
                Dest.x = x*m_TileWidth;
                Dest.y = y*m_TileHeight;
                Dest.w = m_TileWidth;
                Dest.h = m_TileHeight;
                SDL_RenderCopy(ren, m_Texture, &Src, &Dest);
            }
        }
    }
}

int TileMapComponent::getTileSheetRows(){
    return m_Rows;
}

int TileMapComponent::getTileSheetCols(){
    return m_Cols;
}

int TileMapComponent::getTileWidth(){
    return m_TileWidth;
}

int TileMapComponent::getTileHeight(){
    return m_TileHeight;
}

int TileMapComponent::getTileMapX(){
    return m_MapX;
}

int TileMapComponent::getTileMapY() {
    return m_MapY;
}

bool TileMapComponent::IsTouchingTile(SDL_Rect rect) {
    int minX = std::floor(rect.x / m_TileWidth);
    int maxX = std::floor((rect.x + rect.w) / m_TileWidth);
    int minY = std::floor(rect.y / m_TileHeight);
    int maxY = std::floor((rect.y + rect.h) / m_TileHeight);
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (-1 < GetTileType(x, y)) {
                return true;
            }
        }
    }
    return false;
}

bool TileMapComponent::CheckTileCollision(const SDL_Rect rect, SDL_Rect* intersection) {
    for (SDL_Rect tile : destRects) {
        if (SDL_IntersectRect(&tile, &rect, intersection)) {
            return true;
        }
    }
    return false;
}