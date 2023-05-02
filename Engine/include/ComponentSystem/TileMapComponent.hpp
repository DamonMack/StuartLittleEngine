#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "../IGraphicsEngineRenderer.hpp"
#include "Component.hpp"

/**!
 * This is a minimal implementation of a TileMapComponent
 */
class TileMapComponent: public Component {
public:
    
    /**!
     * Constructor for a TileMapComponent
     */
    TileMapComponent(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* ren);
    
    /**!
     * Constructor for loading a tilemap from a tilemap file
    */
    TileMapComponent(std::string filepath, SDL_Renderer* ren);

    /**!
     * Constructor for loading a tilemap from a tilemap file
     */
    TileMapComponent(std::string filepath);

    /**!
     * Constructor for a TileMapComponent without renderer
     */
    TileMapComponent(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY);

    /**!
     * Destructor for a TileMapComponent
     */
    ~TileMapComponent();
    /**!
     * Temporary function for generating a simple
     * map to display some tiles
     */
    void GenerateSimpleMap();
    /**!
     * Function for printing text to console
     */
    void PrintMap();
    /**!
     * Set the 'type' of tile at an x and y position
     */
    void SetTile(int x, int y, int type);
    /**!
     * Return the tile type at an x and y position
     */
    int GetTileType(int x, int y);

    /**!
     * Returns a pointer to the tile sheet texture
    */
    SDL_Texture* GetTileSheet();

    /**!
     * Saves the tile map to a text file with the given name in the same directory as the tilesheet. (Warning: overwrites the original file)
    */
    void SaveTileMap(std::string tileMapName);

    /**!
     * Returns the number of rows in the tile sheet
    */
    int getTileSheetRows();

    /**!
     * Returns the number of columns in the tile sheet
    */
    int getTileSheetCols();

    /**!
     * Returns the width of the tiles in the tile sheet
    */
    int getTileWidth();

    /**!
     * Returns the height of the tiles in the tile sheet
    */
    int getTileHeight();

    /**!
     * Returns the x dimension of the tilemap
    */
    int getTileMapX();

    /**!
     * Returns the y dimension of the tilemap
    */
    int getTileMapY();

    /**!
     * Draw all of the tiles in the TileMapComponent
     */
    void Render(SDL_Renderer *ren) override;

    /**!
     * Renders the tile map for the tilemap editor
    */
    void RenderEditor(SDL_Renderer* ren);

    void Update(double dt) override{};

    // determines if the sdl rect is touching a tile with given type (maybe change to check for multiple tile types later)
    bool IsTouchingTile(SDL_Rect rect);

    bool CheckTileCollision(const SDL_Rect rect, SDL_Rect* intersection);

private:
    /**
     * Loads the tilemap with information from the provided file
    */
    void loadTileMap(std::string filepath);

    // Dimensions of our TileMapComponent and individual tiles.
    // Used for spiltting up the sprite sheet
    int m_Rows;
    int m_Cols;      
    // How big each tile is.
    int m_TileWidth;
    int m_TileHeight;
    // size of our TileMapComponent
    int m_MapX;
    int m_MapY; 

    // The filepath to the tilesheet
    std::string m_filepath;
    // Where our TileMapComponent is rendered
    // An SDL Surface contains pixel data to draw our TileMapComponent
    SDL_Surface *m_TileSpriteSheet = nullptr;
    SDL_Texture *m_Texture = nullptr;
    // Stores our tile types
    int* m_Tiles;

    SDL_Renderer* renderer;

    std::vector<SDL_Rect> srcRects;
    std::vector<SDL_Rect> destRects;
};

#endif
