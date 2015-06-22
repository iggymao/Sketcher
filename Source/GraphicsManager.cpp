#include "stdafx.h"
#include <iostream>
#include "../Headers/GraphicsManager.h"

void GraphicsManager::Initialize()
{
	printf("\n       Initializing Graphics Manager");
	// Do stuff here

	std::string strTitle = "OpenGL Window";
	GLuint width = 800;
	GLuint height = 600;
	GLuint x = 300;
	GLuint y = 100;

	MainWinInfo *meminfo;
	meminfo = new MainWinInfo;
	meminfo->MainWindow = NULL;
	meminfo->strWinTitle = "OpenGL Window";
	meminfo->main_win_width = width;
	meminfo->main_win_height = height;
	meminfo->main_pos_x = x;
	meminfo->main_pos_y = y;

	MyWinInfo = meminfo;

	IsLoadedOpenGL = false;
}

int GraphicsManager::LaunchOpenGL()
{
	printf("\n		StartingOpenGL");
	// Do stuff here
		
	printf("\nCreating a window..");
/*
	assert (restart_gl_log());
	// start GL context and O/S window using the GLFW helper library
	gl_log ("starting GLFW\n%s\n", glfwGetVersionString());
	// register the error call-back function that we wrote, above
	glfwSetErrorCallback (glfw_error_callback);
*/

	// This tries to first init the GLFW library and make sure it is available
	if ( !glfwInit() )
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* Window; 

	// This tells OpenGL that we want a multisampling value of 4 (anti-aliasing)
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Set our OpenGL version to 4 using the core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	//	GLFWmonitor* mon = glfwGetPrimaryMonitor();
	//	const GLFWvidmode* vmode = glfwGetVideoMode(mon);

	//This creates the main window, needed to launch the OpenGL context
//	std::string strTitle = "OpenGL Window";
//	GLuint width = 800;
//	GLuint height = 600;
	//	// Create a window either in fullscreen or not
	//	if( bFullScreen )
	//		Window = glfwCreateWindow(width, height, strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	//	else

	Window = glfwCreateWindow(MyWinInfo->main_win_width, MyWinInfo->main_win_height, MyWinInfo->strWinTitle.c_str(), nullptr, nullptr);
	MyWinInfo->MainWindow = Window;  // store the pointer to the MainWindow
	// Make sure the window is valid, if not, throw an error.
	if ( Window == nullptr )
	{
		fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(Window, MyWinInfo->main_pos_x, MyWinInfo->main_pos_y);


	glfwMakeContextCurrent(Window); // Initialize GLEW 

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, MyWinInfo->main_win_width, MyWinInfo->main_win_height);		

	glClearColor(0.4f, 0.5f, 0.5f, 1.0f);	// Clear the colorbuffer (set it to a grayscale)
	glClear( GL_COLOR_BUFFER_BIT );			// Clear the screen

	glfwSwapBuffers(Window);				// Swap the buffer to create an initial colored screen

	// at this point the context is active, so store a variable to tell the main application
	IsLoadedOpenGL = true;	

	return 0;

}

void GraphicsManager::Destroy()
{
	printf("\nINCOMPLETE:  Destroying the Graphics Manager");
    //Finalize and clean up GLFW  
    glfwTerminate(); 
	delete MyWinInfo;
}