#ifndef TILEMAPEDITOR
#define TILEMAPEDITOR

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "IGraphicsEngineRenderer.hpp"
#include "GameObject.hpp"
#include "ComponentSystem/TileMapComponent.hpp"

/**!
 * This is an SDL program for the creation and modification of tilemaps used in the engine
 */
class TileMapEditor{
public:
    /**!
     * Constructor of editor
     */
    TileMapEditor();
    /**!
     * Destructor
     */
    ~TileMapEditor();
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
     * Main Game Loop that runs forever Designed for use when editor is not run through pybind
     */
    void MainGameLoop();

    /**!
     * Creates a new tilemap given a filepath to a tile sheet, the dimensions of the tiles and the size of the tile map
     * @param tileSheetFileName A string with the filepath to the tile sheet
     * @param rows the number of rows in the tile sheet
     * @param cols the number of columns in the tile sheet
     * @param _TileWidth the width of each tile in pixels
     * @param _mapX the width of the tile map in tiles
     * @param _mapY the height of the tile map in tiles
    */
    void CreateTileMap(std::string tileSheetFileName, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY);

    /**!
     * Loads a tile map with information from the provided tile map file.
     * The tilemap file must be in the same directory as the tile sheet that it references.
     * @param filepath the filepath to the tilemap file
    */
    void LoadTileMap(std::string filepath);

    /**!
     * Sets the tile at the give x,y location to the editor's currently selected tile
     * @param x the x value of the tile to edit
     * @param y the y value of the tile to edit
    */
    void SetTile(int x, int y);

    /*! Moves the current type forward, or sets it to the first tile if in delete mode
     * Loops back to start if it exceeds the number tiles in the tile sheet
    */
    void incrementCurrentType();
    /**!
     * Moves the current type back, or sets it to the las tile if in delete mode
     * Loops back to end if it exceeds the number tiles in the tile sheet
    */
    void decrementCurrentType();

    /**!
     * Manually sets the current type to the provided value. Values clamp to -1 (inclusive) and the total number of tiles (exclusive).
     * @param type The numerical type to change the current type to
    */
    void setCurrentType(int type);

    /**!
     * Saves the tile map to a text file with the given name in the same directory as the tilesheet. (Warning: overwrites the original file)
     * @param tileMapName The name of the tile map, not the filepath
    */
    void SaveTileMap(std::string tileMapName);

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
    /**
     * Renderers the currently selected tile (or deletion) on the space where the mouse is.
    */
    void renderCursor();

    //! Engine Subsystem
    IGraphicsEngineRenderer* mRenderer = nullptr;

    // Keep track of the settings for the current tilemap
    //! Dimensions of tile sheet
    int m_Rows;
    int m_Cols;
    //! How big each tile is
    int m_TileWidth;
    int m_TileHeight;
    //! size of the tilemap
    int m_MapX;
    int m_MapY;

    // Editor values
    //! The number of tiles in the current tile sheet
    int m_typeCount;
    //! The type of the current tile being added when clicked
    // A value of <= -1 represents deletion of the selected tile
    int m_currentType;

    //! The tilemap that is currently being edited
    TileMapComponent* m_TileMap = nullptr;
};

#endif
