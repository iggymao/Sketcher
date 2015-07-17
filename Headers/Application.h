#ifndef _Application_H
#define _Application_H

#include "../Headers/ModelManager.h"			// Used to reference the modelmanager class		
#include "../Headers/GraphicsManager.h"			// Used to reference the graphics manager class
#include "../Headers/LogManager.h"				// Used to reference the logmanager class
#include "../Headers/AppWindow.h"

//#include "WindowManager.h"					// Used to reference the abstract base class


#define WINDOW_VIEW_UNDEFINED -1						// Used for initialization of the Volume classes only...
#define WINDOW_VIEWMODEL 0		// Must be the first in the list.  Controls the main modeling window
								// used in Model.cpp in the main reindering loop.
								// Counters for the main model windows of the application
#define WINDOW_VIEW1 1							// Counters for the subwindows of the application
#define WINDOW_VIEW2 2							// Counters for the subwindows of the application
#define MAX_WINDOWS 3							// Counter for the number of windows in the application.  Must be greater than the highest WINDOW_VIEW# defined above.

// default MESH primitives
#define MESH_UNDEFINED -1								// for an undeclared or undefined mesh primitive type (used for intialization)
#define MESH_TRIANGLE	0								// for a simple 2D Triangle
#define MESH_SQUARE		1								// for a simple 2D Square
#define MESH_OTHER_2D	2								// for another 2D Shape
#define MAX_MESH_TYPES	3								// should be one greater than the last MESH type defined above

#define MESH_USE_TEXTURE_TRUE	0						// tells the mesh to use an assigned texture
#define MESH_USE_TEXTURE_FALSE	1						// tells the mesh creator to ignore textures


// This is our main application class that handles orchestrating the init, main loop and cleanup
class Application
{
public:
	// Create a default constructor and deconstructor which cleans up
	Application();			//constructor
	~Application();			// destructor

	// This is the main function for our application, which is called by the main() function
	// in the WindowManager.cpp file.  This helps abstract out the environments entry point.
	int Main();

	// This gets and sets the window manager for the application.  This should be set right
	// after the GLApplication is created in the main() function.
//	WindowManager *GetWindowManager() { return WindowManager; }
//	void SetWindowManager(WindowManager *pWindowManager) { WindowManager = pWindowManager; }

	// This gets and sets a specified window within the application.  This will be used right after a window is created to allow the application
	// to know the handles of each of the windows...to be used in identifying a rendering target when the time comes.
	AppWindow *GetWindowID(int counter) {return Window[counter]; }
	AppWindow *GetWindowArray() {return *Window;}	// returns the Window array
	void SetWindowID(int counter, AppWindow *pAppWindow) { Window[counter] = pAppWindow; }
	
	LogManager *GetLog() {return LogMan;}				// gets the log manager
	void SetLogMan(LogManager *log) {LogMan = log;}		// sets the pointer to the log manager

	GraphicsManager *GetGraphMan() {return GraphicsMan;}  // gets the graphics manager handle
	void SetGraphMan(GraphicsManager *p_graphic) {GraphicsMan = p_graphic;}  // sets the pointer to the graphics manager

	ModelManager *GetModelMan() { return ModelMan;}		// get the model manager handle
	void SetModelMan(ModelManager *p_model) {ModelMan = p_model;}	// sets the pointer to the model manager
	
	// This initializes the application
	void Initialize();

	// This runs the game loop and only quits when the user hits Escape or closes the window
//	void AppLoop();

	// This cleans up the application and tells other objects to also cleanup
	void Destroy();

	void StartLogMgr();				//Start LogMgr;
	void StartFileMgr();				//Start FileMgr;
	void StartPrintMgr();			//Start PrintMgr;
	int StartGraphicsMgr();			//Start GraphicsMgr;
	void StartWindowsMgr();			//Start WindowsMgr;
	void StartModelMgr();			//Start ModelMgr;
	void StartInputMgr();			//Start InputMgr;
	void StartNetworkMgr();			//StartNetworkMgr;
	void StartAudioMgr();			//StartAudioMgr;
	void StartEventMgr();			//StartEventMgr

protected:
	// Our abstract window manager to create the window and manage input, which should be
	// environment agnostic.  Our main application shouldn't know if it's Win32 or GLFW.
	// This is instantiated and set in GLFWManager.cpp in the main() function.

//	WindowManager *WindowManager;
	AppWindow *Window[MAX_WINDOWS];			// An array to store the pointers to each of the windows of the application
	LogManager *LogMan;					// a pointer to the log manager
	GraphicsManager *GraphicsMan;		// a pointer to the graphics manager
	ModelManager *ModelMan;				// a pointer to the model manager

};

#endif