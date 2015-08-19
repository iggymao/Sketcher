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
#include "../Headers/CWindow.h"
#include "../Headers/ModelManager.h"
#include "../Headers/DrawingShapes.h"
#include "../Headers/Cursor.h"
#include "../Headers/GUIElements.h"

//struct MainWinInfo{
//	GLFWwindow *MainWindow;		// pointer for the main window object
//	std::string strWinTitle;	// title for the window
//	GLuint main_win_width;			// main window width
//	GLuint main_win_height;		// main width heigh
//	GLuint main_pos_x;			// x position of main window
//	GLuint main_pos_y;			// y position of main window
//};

class GraphicsManager : public CWindow
{
public:
	GraphicsManager(GLuint win_width, GLuint win_height)	// default constructor
	{
		IsLoadedOpenGL = false;
		IsCreatedCursor = false;
		PickedMeshID.push_back(-1);						// set -1 into the PickedMeshID values to indicate no mesh is selected
		//IsActivePicking = 0;

		this->MyWinInfo = new CWindow;
//		MyWinInfo = new MainWinInfo;
		// set the window properties
		this->SetWinWidth(win_width);
		this->SetWinHt(win_height);
		(*(this->MyWinInfo)).strWinTitle = "GraphicsManager title";
		(*(this->MyWinInfo)).main_pos_x = 300;  // x-position (pixels)
		(*(this->MyWinInfo)).main_pos_y = 100;  // y-position (pixels)
	}
	GraphicsManager(const GraphicsManager & rhs) { ;}	// copy constructor
	~GraphicsManager() { Destroy();}					// destructor

	CWindow *MyWinInfo;									// structure containing the main window information
	//MainWinInfo *MyWinInfo;								// structure containing the main window information
	//ModelManager *MyModelManagerInfo;

	// Entities used by GraphicsManager
	CDrawingObjects *DrawingGridLine;	// The main drawing grid object
	CDrawingObjects *CursorObj;			// The main cursor for the drawing window
	CGUILayoutHUD *GUILayout;			// the HUD for our GUI

	vector<CDrawingObjects*> ModelObjects;	// The main array to hold  the Drawing Objects

	// Picking values and methods
	vector<GLint> PickedMeshID;			// An array to store picked mesh ID's, used in displaying selected objects in DrawNormal
	GLint GetPickingParentID(GLuint mesh_id)		// returns the parentobject ID for for a specific MeshID 
	{
		for (unsigned int j = 0; j < ModelObjects.size(); j++)
		{
			for(unsigned int i = 0; i<ModelObjects[j]->meshes.size(); i++)
			{
				if(ModelObjects[j]->meshes[i]->GetMeshID() == mesh_id)
					return ModelObjects[j]->meshes[i]->GetParentMeshID();
			}
		}
		return -1;		// no parent ID found for a given mesh #.
	}

	/* class methods */
	void Initialize();			// Starts the graphics manager
	void Draw();  // a basic draw routine controlled by the graphics manager -- diverts to DrawNormal and DrawPicking once inside
	void DrawNormal(Shader ourShader, Shader lightingShader, Shader cursorShader);		// a routine for drawing normal screens
	void DrawPicking(Shader pickingShader);		// a routine for drawing picked screens (changes the color of the objects based on IDs)
	int LaunchOpenGL();			// Launches the OpenGL routines and established the main context.

	GLuint GetWinHt() {return (*(this->MyWinInfo)).main_win_height;}
	void SetWinHt(GLuint height) {(*(this->MyWinInfo)).main_win_height = height;}
	GLuint GetWinWidth() {return (*(this->MyWinInfo)).main_win_width;}
	void SetWinWidth(GLuint width) {(*(this->MyWinInfo)).main_win_width = width;}

public:
	void Destroy();

	////View controls for our windows interactions, currently local to GraphicsManager.cpp
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	//void Do_movement();

	/* Data members and flags */
	bool IsLoadedOpenGL;		// a variable to let us know that OpenGL has been successfully loaded.
	bool IsCreatedCursor;		// a bool to tell us the cursor has been loaded
	//int IsActivePicking;		// a bool to tell us that picking (clicking on screen) is currently active

	GLfloat snap_value;			// a variable to store the snap_value for drafting
	
};

#endif