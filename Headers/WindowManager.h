#ifndef _WindowManager_H
#define _WindowManager_H

#include <string>										// Used for our STL string objects								
#include <GLFW/glfw3.h> 




struct WinInfo{
	GLFWwindow *Window;		// pointer for a window object
	GLuint WindowID;		// an ID number for each window
	std::string strWinTitle;	// title for the window
	GLuint width;			// main window width
	GLuint height;		// main width heigh
	GLuint pos_x;			// x position of main window
	GLuint pos_y;			// y position of main window
	bool bFullScreen;		// boolean to indicate fullscreen mode or not.
	WinInfo *next;			// linked list pointer
	WinInfo *previous;		// linked list pointer
	bool bIsVisible;		// boolean to indicate if a window is visible or not.
};

// to store the arrangement of the Windows in our application
// Is this needed if we already have WinInfo?  Maybe to be able to save
// custom configurations, or allow the user to move windows around?
struct WindowLayoutPattern
{
	GLuint WinLayoutID;			// identifier for each WindowLayout
	std::string strLayoutName;	// a string name to identify each layout
	WinInfo *Members;			// members belonging to a layout pattern

};

// This is our class definition for managing the creation of the window, input and the
// creating of the OpenGL context.  This class should be inherited from to create
// specific implementations like GLFW (i.e. GLFWManager), Win32, GLUT or SDL.
class WindowManager
{

public:
	WinInfo *MemberInfo;	// a linked list for the know windows
	WinInfo *firstMemberInfo;	// pointer to the first element in the list
	WinInfo *lastMemberInfo;	// pointer to the last element in the list

	WindowManager();	// constructor
	~WindowManager();   // destructor

	void Initialize();

	void AddWindow();		// adds a window to the WinInfo list
	void SearchWindow();	// search for a window in the list
	void DeletetWindow();	// deletes a window from the list

	void MoveWindow();		// moves a window
	void ResizeWindow();	// resizes a window

	void SaveLayout();		// saves a layout pattern -- 
	void ReadLayout();		// reads a layout pattern --

	void Destroy();
/*
	// This is needed so that the class inheriting this will have it's deconstructor called
	virtual ~WindowManager() {}

	// This initialized the window and creates the OpenGL context
	virtual int Initialize(int width, int height, std::string strTitle, bool bFullScreen = false) = 0;

	// This swaps the backbuffer to the front and should be called every frame
	virtual void SwapTheBuffers() = 0;

	// This processes any needed input for the application, like the Escape key
	virtual bool ProcessInput(bool continueGame) = 0;

	// This destroys the window and OpenGL context
	virtual void Destroy() = 0;
	*/
};

#endif // _WindowManager_H