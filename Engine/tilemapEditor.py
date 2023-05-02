#import the game engine library
from bin import StuartLittleEngine
# import all components
# from the tkinter library
from tkinter import *
from tkinter.simpledialog import askstring, askinteger
from tkinter import messagebox as mb
from tkinter import filedialog

#import os to work with files
import os
import platform

class TileEditorProgram(Tk):
    def __init__(self):
        super().__init__()
        # Set up the editor GUI
        self.title('Tilemap Editor')
        self.geometry("300x300")
        self.config(background= "white")

        # Setting up frame for loading and saving Tilemaps
        self.fileFrame = LabelFrame(self, text="File")
        self.fileFrame.pack(fill="both", expand="yes")

        self.newButton = Button(self.fileFrame, text="Create New Tilemap", fg="black",
                                command= self.createNewTileMap)
        self.newButton.pack(side = TOP)

        self.loadButton = Button(self.fileFrame, text="Load Tilemap", fg="black",
                                 command= self.loadTileMap)
        self.loadButton.pack(side = TOP)

        self.saveButton = Button(self.fileFrame, text="Save Tilemap", fg="black", state="disabled",
                                 command= self.saveTileMap)
        self.saveButton.pack(side = TOP)

        # create the tilemap editor
        self.editor = StuartLittleEngine.TileMapEditor()
        self.editorQuit = True
        self.currentName = ""
    
    # Retrieves a BMP filepath from the user and stores the value. Updates the label passed
    def askBMPFile(self, label):
        if(platform.system()=="Darwin"):
            filepath = filedialog.askopenfilename(title= "Select a tile sheet file")
        else:
            filepath = filedialog.askopenfilename(title= "Select a tile sheet file",
                                                filetypes = [("Bitmap image",
                                                            "*.bmp*"),])
        if(not filepath == ""):
            # Since game engine uses relative paths, we have to calculate the relative path from the absolute path
            self.currentFilePath = './' + os.path.relpath(filepath)
            label.configure(text="File Opened: "+self.currentFilePath)
            self.filepathEntered = True
    
    # Retrieves a tile sheet row count from the user and stores the value. Updates the label passed
    def askSheetRowCount(self, label):
        rows = askinteger("Tile Sheet Rows", "Please enter the number of rows in the tile sheet", minvalue=1)

        if (rows is not None):
            label.configure(text="Tile Sheet Rows: "+ str(rows))
            self.currentRowCount = rows
            self.SheetRowsEntered = True
    
    # Retrieves a tile sheet column count from the user and stores the value. Updates the label passed
    def askSheetColCount(self, label):
        cols = askinteger("Tile Sheet Columns", "Please enter the number of columns in the tile sheet", minvalue=1)

        if (cols is not None):
            label.configure(text="Tile Sheet Columns: "+ str(cols))
            self.currentColCount = cols
            self.SheetColsEntered = True
    
    # Retrieves a tile sheet tile width from the user and stores the value. Updates the label passed
    def askTileWidth(self, label):
        width = askinteger("Tile Width", "Please enter the width of each tile in the tile sheet", minvalue=1)

        if (width is not None):
            label.configure(text="Tile Width: "+ str(width))
            self.currentTileWidth = width
            self.TileWidthEntered = True
    
    # Retrieves a tile sheet tile height from the user and stores the value. Updates the label passed
    def askTileHeight(self, label):
        height = askinteger("Tile Height", "Please enter the height of each tile in the tile sheet", minvalue=1)

        if (height is not None):
            label.configure(text="Tile Height: "+ str(height))
            self.currentTileHeight = height
            self.TileHeightEntered = True

    # Retrieves a tile map column count from the user and stores the value. Updates the label passed
    def askMapX(self, label):
        mapX = askinteger("Tile Map Columns (X Dimension)", "Please enter the number of columns in the tile map", minvalue=1)

        if (mapX is not None):
            label.configure(text="Tile Map Columns (X Dimension): "+ str(mapX))
            self.currentMapX = mapX
            self.MapXEntered = True

    # Retrieves a tile map row count from the user and stores the value. Updates the label passed
    def askMapY(self, label):
        mapY = askinteger("Tile Map Rows (Y Dimension)", "Please enter the number of rows in the tile map", minvalue=1)

        if (mapY is not None):
            label.configure(text="Tile Map Rows (Y Dimension): "+ str(mapY))
            self.currentMapY = mapY
            self.MapYEntered = True
    
    # Checks if all of the inputs for the new tilemap have been entered. If the have, the top level window is closed and the new map is created
    def finalizeNewMapEntry(self, top):
        complete = self.filepathEntered and self.SheetRowsEntered and self.SheetColsEntered and self.TileWidthEntered and self.TileHeightEntered and self.MapXEntered and self.MapYEntered
        if(complete):
            self.NewMapEntrySuccess = True
            top.destroy()
            self.editor.InitializeGraphicsSubSystem(1280, 720)
            self.editor.Start()
            self.editor.CreateTileMap(self.currentFilePath,
                                      self.currentRowCount,
                                      self.currentColCount,
                                      self.currentTileWidth,
                                      self.currentTileHeight,
                                      self.currentMapX,
                                      self.currentMapY)
            self.editorQuit = False
            self.newButton["state"] = "disabled"
            self.loadButton["state"] = "disabled"
            self.saveButton["state"] = "active"
            self.after(100, self.updateEditor)
            
        else:
            mb.showerror("Incomplete Values!", "Tilemap cannot be created without entering all the values")

    # Creates a popup window that takes in values for creating a new tilemap
    def openNewMapWindow(self):
        top = Toplevel(self)
        top.geometry("300x400")
        top.grab_set()
        
        # Set boolean values to determine if all values have been entered
        self.filepathEntered = False
        self.SheetRowsEntered = False
        self.SheetColsEntered = False
        self.TileWidthEntered = False
        self.TileHeightEntered = False
        self.MapXEntered = False
        self.MapYEntered = False
        # Space for selecting a bmp tile sheet
        fileLabel = Label(top, text="Select Tile Sheet", width = 200)
        fileLabel.pack()
        filepathButton = Button(top, text="Select tilesheet bmp", fg="black", command= lambda:self.askBMPFile(fileLabel))
        filepathButton.pack()
        # entry for the number of rows in the tile sheet
        sheetRowsLabel = Label(top, text="Enter number of rows in tile sheet")
        sheetRowsLabel.pack()
        sheetRowsEntry = Button(top, text="Enter Tile Sheet Row Count", fg="black", command= lambda:self.askSheetRowCount(sheetRowsLabel))
        sheetRowsEntry.pack()

        # entry for the number of columns in the tile sheet
        sheetColsLabel = Label(top, text="Enter number of columns in tile sheet")
        sheetColsLabel.pack()
        sheetColsEntry = Button(top, text="Enter Tile Sheet Column Count", fg="black", command= lambda:self.askSheetColCount(sheetColsLabel))
        sheetColsEntry.pack()

        # entry for the width of the tiles in the tile sheet
        TileWidthLabel = Label(top, text="Enter width of each tile in the tile sheet")
        TileWidthLabel.pack()
        TileWidthEntry = Button(top, text="Enter Tile Width", fg="black", command= lambda:self.askTileWidth(TileWidthLabel))
        TileWidthEntry.pack()

        # entry for the height of the tiles in the tile sheet
        TileHeightLabel = Label(top, text="Enter height of each tile in the tile sheet")
        TileHeightLabel.pack()
        TileHeightEntry = Button(top, text="Enter Tile Height", fg="black", command= lambda:self.askTileHeight(TileHeightLabel))
        TileHeightEntry.pack()

        # Entry for number of Columns in Tilemap
        MapXLabel = Label(top, text="Enter number of columns in tile map")
        MapXLabel.pack()
        MapXEntry = Button(top, text="Enter Tile Map Column Count", fg="black", command= lambda:self.askMapX(MapXLabel))
        MapXEntry.pack()

        # Entry for number of columns in Tilemap
        MapYLabel = Label(top, text="Enter number of rows in tile map")
        MapYLabel.pack()
        MapYEntry = Button(top, text="Enter Tile Map Row Count", fg="black", command= lambda:self.askMapY(MapYLabel))
        MapYEntry.pack()

        ConfirmButton = Button(top, text="Create Map", fg="black", command= lambda:self.finalizeNewMapEntry(top))
        ConfirmButton.pack(side=BOTTOM)

    def createNewTileMap(self):
        self.NewMapEntrySuccess = False
        self.openNewMapWindow()
        
    def loadTileMap(self):
        if(platform.system()=="Darwin"):
            filepath = filedialog.askopenfilename(title= "Select a tilemap file")
        else:
            filepath = filedialog.askopenfilename(title= "Select a tilemap file",
                                                filetypes = [("Tilemap File",
                                                            "*.txt*"),])
        if(not filepath == ""):
            # Since game engine uses relative paths, we have to calculate the relative path from the absolute path
            self.currentFilePath = './' + os.path.relpath(filepath)
            self.currentName = os.path.basename(self.currentFilePath)
            self.editor.InitializeGraphicsSubSystem(1280, 720)
            self.editor.Start()
            self.editor.LoadTileMap(self.currentFilePath)
            self.editorQuit = False
            self.newButton["state"] = "disabled"
            self.loadButton["state"] = "disabled"
            self.saveButton["state"] = "active"
            self.after(100, self.updateEditor)
    
    def saveTileMap(self):
        if (self.currentName == ""):
            self.currentName = askstring("Tilemap", "Please enter a name for your tilemap (NOTE: this is not the filepath)")
            while(self.currentName == None or self.currentName == ""):
                self.currentName = askstring("Tilemap", "Please enter a non-empty name for your tilemap (NOTE: this is not the filepath)")

        self.editor.SaveTileMap(os.path.splitext(self.currentName)[0])
        mb.showinfo("Tile map saved", "The tilemap was saved successfully")
    
    def updateEditor(self):
        if(not self.editorQuit):
            self.editorQuit = self.editor.Input()
            self.editor.Render()
            self.after(100, self.updateEditor)
        else:
            confirmQuit = mb.askyesno("Are You Sure?", "You are about to quit the application, are you sure you want to do that?")
            if(confirmQuit):
                finalsave = mb.askyesno("Save Tilemap?", "Would you like to save the current tilemap before quitting?")
                if(finalsave):
                    self.saveTileMap()
                self.editor.Shutdown()
                self.destroy()
            else:
                self.editorQuit = False
                self.editor.Render()
                self.after(100, self.updateEditor)

    def launchEditor(self):
        
        self.editor.InitializeGraphicsSubSystem(1280, 720)
        self.editor.Start()
        self.editor.CreateTileMap("./images/Tiles1.bmp",8,8,64,64,20,11)
        self.editorQuit = False
        self.after(100, self.updateEditor)

    def start(self):
        
        self.mainloop()

        # clean up
        if(not self.editorQuit):
            self.editor.Shutdown()



# Create the tilemap editor from the library and setup
# editor = mygameengine.TileMapEditor()
# editor.InitializeGraphicsSubSystem(1280, 720)
# editor.Start()


# editor.CreateTileMap("./images/Tiles1.bmp",8,8,64,64,20,11)
# quit = False
# while(not quit):
#       quit = editor.Input()
#       editor.Render()
# editor.Shutdown()

window = TileEditorProgram()
window.start()

