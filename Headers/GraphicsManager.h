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
#include "../Headers/DrawingShapes.h"
#include "../Headers/Cursor.h"

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
	GraphicsManager() {
		IsLoadedOpenGL = false;
		IsCreatedCursor = false;
		PickedMeshID.push_back(-1);		// set -1 into the PickedMeshID values to indicate no mesh is selected
		//IsActivePicking = 0;
	
	}
	GraphicsManager(const GraphicsManager & rhs) { ;}	// copy constructor
	~GraphicsManager() { Destroy();}


	MainWinInfo *MyWinInfo;				// structure containing the main window information
//	ShaderManager *MyShaderManagerInfo;	// class containing the shader manager info
	ModelManager *MyModelManagerInfo;

	CGrid *DrawingGridLine;		// The main drawing grid object
	CCursor *CursorObj;			// The main cursor for the drawing window

	vector<ModelManager*> DrawingObjects;	// The main array to hold  the Drawing Objects

	vector<GLint> PickedMeshID;	//	An array to store picked member ID's, used in displaying selected objects in DrawNormal

	void Initialize();			// Starts the graphics manager

	void Draw();  // a basic draw routine controlled by the graphics manager -- diverts to DrawNormal and DrawPicking once inside
	// a routine for drawing normal screens
	void DrawNormal(Shader ourShader, Shader lightingShader, Shader cursorShader, ModelManager &ourModel, CGrid &gridline,  CCursor &cursor);
	// a routine for drawing picked screens (changes the color of the objects based on IDs)
	void DrawPicking(Shader pickingShader);	

	int LaunchOpenGL();			// Launches the OpenGL routines.

	////View controls for our windows interactions, currently local to GraphicsManager.cpp
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	//void Do_movement();

	bool IsLoadedOpenGL;		// a variable to let us know that OpenGL has been successfully loaded.
	bool IsCreatedCursor;		// a bool to tell us the cursor has been loaded
	//int IsActivePicking;		// a bool to tell us that picking (clicking on screen) is currently active

	GLfloat snap_value;			// a variable to store the snap_value for drafting
	void Destroy();
};

#endif