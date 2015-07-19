#ifndef _GraphicsManager_H
#define _GraphicsManager_H

//Include GLEW and GLFW
#include <string>
#include <GL/glew.h>   
#include <GLFW/glfw3.h> 
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "../Headers/ShaderManager.h"
#include "../Headers/ModelManager.h"
//#include "../utils/MathUtils.h"



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

	MainWinInfo *MyWinInfo;				// structure containing the main window information
	ShaderManager *MyShaderManagerInfo;	// class containing the shader manager info
	ModelManager *MyModelManagerInfo;

	void Initialize();			// Starts the graphics manager
	void Draw();				// a basic draw routine controlled by the graphics manager

	int LaunchOpenGL();			// Launches the OpenGL routines.

	////View controls for our windows interactions, currently local to GraphicsManager.cpp
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	//void Do_movement();

	bool IsLoadedOpenGL;		// a variable to let us know that OpenGL has been successfully loaded.

	void Destroy();
};

#endif