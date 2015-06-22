#ifndef _GraphicsManager_H
#define _GraphicsManager_H

//Include GLEW and GLFW
#include <string>
#include <GL/glew.h>   
#include <GLFW/glfw3.h> 

struct MainWinInfo{
	GLFWwindow *MainWindow;		// pointer for the main window object
	std::string strWinTitle;	// title for the window
	GLuint main_win_width;			// main window width
	GLuint main_win_height;		// main width heigh
	GLuint main_pos_x;			// x position of main window
	GLuint main_pos_y;			// y position of main window
};

class GraphicsManager
{
public:
	~GraphicsManager() { Destroy();}

	MainWinInfo *MyWinInfo;	// structure containing the main window information
	void Initialize();			// Starts the graphics manager
	int LaunchOpenGL();			// Launches the OpenGL routines.

	bool IsLoadedOpenGL;		// a variable to let us know that OpenGL has been successfully loaded.

	void Destroy();
};

#endif