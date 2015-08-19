//Class CWindow contains data about the parameters of a window

#ifndef _CWindow_H
#define _CWindow_H

#include <string>
#include <GL/glew.h>   
#include <GLFW/glfw3.h> 

class CWindow
{
public:
	CWindow(){;}							// constructor

	CWindow(const CWindow & rhs) {; }		// copy constructor
	~CWindow() {; }							// deconstructor


	GLFWwindow *MainWindow;		// pointer for the main window object
	std::string strWinTitle;	// title for the window
	GLuint main_win_width;			// main window width
	GLuint main_win_height;		// main width heigh
	GLuint main_pos_x;			// x position of main window
	GLuint main_pos_y;			// y position of main window
};

#endif