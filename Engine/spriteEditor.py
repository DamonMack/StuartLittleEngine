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

class SpriteEditorProgram(Tk):
    def __init__(self):
        super().__init__()
        # Set up the editor GUI
        self.title('Sprite Editor')
        self.geometry("300x300")
        self.config(background= "white")

        # Setting up frame for loading and saving sprites
        self.fileFrame = LabelFrame(self, text="File")
        self.fileFrame.pack(fill="both", expand="yes")

        self.newButton = Button(self.fileFrame, text="Create New Sprite", fg="black",
                                command=self.createNewSprite)
        self.newButton.pack(side = TOP)

        self.loadButton = Button(self.fileFrame, text="Load Sprite", fg="black",
                                 command=self.loadSprite)
        self.loadButton.pack(side = TOP)

        self.saveButton = Button(self.fileFrame, text="Save Sprite", fg="black", state="disabled",
                                 command= self.saveSprite)
        self.saveButton.pack(side = TOP)

        self.editor = StuartLittleEngine.SpriteEditor()
        self.editorQuit = True
        self.currentName = ""
    
    def createNewSprite(self):
        self.NewSpriteEntrySuccess = False
        self.openNewSpriteWindow()

    def openNewSpriteWindow(self):
        top = Toplevel(self)
        top.geometry("300x300")
        top.grab_set()

        # Set boolean values to determine if all values have been entered
        self.filepathEntered = False
        self.frameCountEntered = False
        self.frameWidthEntered = False
        self.frameHeightEntered = False

        # Space for selecting a bmp sprite sheet
        fileLabel = Label(top, text="Select Sprite Sheet", width = 200)
        fileLabel.pack()
        filepathButton = Button(top, text="Select spritesheet bmp", fg="black",
                                command= lambda:self.askBMPFile(fileLabel))
        filepathButton.pack()

        # Space for entering Frame count
        countLabel = Label(top, text="Enter number of frames", width = 200)
        countLabel.pack()
        countButton = Button(top, text="Enter Frame Count", fg="black",
                                command= lambda:self.askFrameCount(countLabel))
        countButton.pack()

        # Space for entering Frame Rate
        timeLabel = Label(top, text="Enter time per frame", width = 200)
        timeLabel.pack()
        timeButton = Button(top, text="Enter Time Per Frame (ms)", fg="black",
                             command= lambda:self.askFrameTime(timeLabel))
        timeButton.pack()

        # Space for entering Frame width
        widthLabel = Label(top, text="Enter the width of the sprite", width = 200)
        widthLabel.pack()
        widthButton = Button(top, text="Enter Frame Width", fg="black",
                                command= lambda:self.askFrameWidth(widthLabel))
        widthButton.pack()

        # Space for entering Frame width
        heightLabel = Label(top, text="Enter the height of the sprite", width = 200)
        heightLabel.pack()
        heightButton = Button(top, text="Enter Frame Height", fg="black",
                                command= lambda:self.askFrameHeight(heightLabel))
        heightButton.pack()

        ConfirmButton = Button(top, text="Create Map", fg="black", command= lambda:self.finalizeNewMapEntry(top))
        ConfirmButton.pack(side=BOTTOM)
    
    # Retrieves a BMP filepath from the user and stores the value. Updates the label passed
    def askBMPFile(self, label):
        if(platform.system()=="Darwin"):
            filepath = filedialog.askopenfilename(title= "Select a sprite sheet file")
        else:
            filepath = filedialog.askopenfilename(title= "Select a sprite sheet file",
                                                filetypes = [("Bitmap image",
                                                            "*.bmp*"),])
        if(not filepath == ""):
            # Since game engine uses relative paths, we have to calculate the relative path from the absolute path
            self.currentFilePath = './' + os.path.relpath(filepath)
            label.configure(text="File Opened: "+self.currentFilePath)
            self.filepathEntered = True
    
    def askFrameCount(self, label):
        count = askinteger("Frame Count", "Please enter the number of frames for the sprite", minvalue=1)

        if(count is not None):
            label.configure(text="Frame Count: "+ str(count))
            self.currentFrameCount = count
            self.frameCountEntered = True


    def askFrameTime(self, label):
        count = askinteger("Time Per Frame", "Please enter the time per frame (ms)", minvalue=1)

        if(count is not None):
            label.configure(text="Time Per Frame: "+ str(count))
            self.currentFrameTime = count
            self.frameTimeEntered = True

    def askFrameWidth(self, label):
        width = askinteger("Frame Width", "Please enter the width of the sprite", minvalue=1)

        if(width is not None):
            label.configure(text="Frame Count: "+ str(width))
            self.currentFrameWidth = width
            self.frameWidthEntered = True

    def askFrameHeight(self, label):
        height = askinteger("Frame Height", "Please enter the height of the sprite", minvalue=1)

        if(height is not None):
            label.configure(text="Frame Count: "+ str(height))
            self.currentFrameHeight = height
            self.frameHeightEntered = True
    
    def finalizeNewMapEntry(self, top):
        complete = self.filepathEntered and self.frameCountEntered and self.frameTimeEntered and self.frameWidthEntered and self.frameHeightEntered
        if(complete):
            self.NewMapEntrySuccess = True
            top.destroy()
            self.editor.InitializeGraphicsSubSystem(1280, 720)
            self.editor.Start()
            self.editor.CreateNewSprite(self.currentFilePath,
                                        self.currentFrameCount,
                                        self.currentFrameTime,
                                        self.currentFrameWidth,
                                        self.currentFrameHeight)
            self.editorQuit = False
            self.newButton["state"] = "disabled"
            self.loadButton["state"] = "disabled"
            self.saveButton["state"] = "active"
            self.after(100, self.updateEditor)
        else:
            mb.showerror("Incomplete Values!", "Sprite cannot be created without entering all the values")

    def loadSprite(self):
        if(platform.system()=="Darwin"):
            filepath = filedialog.askopenfilename(title= "Select a sprite file")
        else:
            filepath = filedialog.askopenfilename(title= "Select a sprite file",
                                                filetypes = [("Sprite File",
                                                            "*.txt*"),])
        if(not filepath == ""):
            self.currentFilePath = './' + os.path.relpath(filepath)
            self.currentName = os.path.basename(self.currentFilePath)
            self.editor.InitializeGraphicsSubSystem(1280, 720)
            self.editor.Start()
            self.editor.LoadSprite(self.currentFilePath)
            self.editorQuit = False
            self.newButton["state"] = "disabled"
            self.loadButton["state"] = "disabled"
            self.saveButton["state"] = "active"
            self.after(100, self.updateEditor)
    
    def saveSprite(self):
        if(self.currentName == ""):
            self.currentName = askstring("Sprite", "Please enter a name for your sprite (NOTE: this is not the filepath)")
            while(self.currentName == None or self.currentName == ""):
                self.currentName = askstring("Sprite", "Please enter a non-empty name for your sprite (NOTE: this is not the filepath)")
        self.editor.SaveSprite(os.path.splitext(self.currentName)[0])
        mb.showinfo("Sprite saved", "The sprite was saved successfully")

    def updateEditor(self):
        if(not self.editorQuit):
            self.editorQuit = self.editor.Input()
            self.editor.Render()
            self.after(100, self.updateEditor)
        else:
            confirmQuit = mb.askyesno("Are You Sure?", "You are about to quit the application, are you sure you want to do that?")
            if(confirmQuit):
                finalsave = mb.askyesno("Save Sprite?", "Would you like to save the current sprite before quitting?")
                if(finalsave):
                    self.saveSprite()
                self.editor.Shutdown()
                self.destroy()
            else:
                self.editorQuit = False
                self.editor.Render()
                self.after(100, self.updateEditor)
                
    def start(self):
        self.mainloop()

# editor = mygameengine.SpriteEditor()
# editor.InitializeGraphicsSubSystem(1280, 720)
# editor.Start()
# editor.CreateNewSprite("./images/sprite.bmp", 5, 75, 87)
# quit = False
# while(not quit):
#     quit = editor.Input()
#     editor.Render()

# editor.Shutdown()

window = SpriteEditorProgram()
window.start()