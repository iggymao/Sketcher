#include "stdafx.h"
#include <stdarg.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include "../Headers/AppWindow.h"
//#include "../Headers/Main.h"							// Include our main header for the application..includes the necessary includes for the application
//#include "../Headers/Mesh.h"							// Include our main header for the application..includes the necessary includes for the application

using namespace std;

//class AppWindow;	// forward declaration?
//class Mesh;			// forward declaration?
//
////Model g_Triangle;										// Our class to handle initializing and drawing our triangle
//
//FILE *stream;
//
//bool restart_gl_log()
//{
//	FILE* file = fopen(GL_LOG_FILE, "w");
//	if (!file) {
//		fprintf(stderr, "ERROR: could not open GL_LOG_FILE log file %s for writing\n", GL_LOG_FILE);
//		return false;
//	}
//	time_t now = time (NULL);
//	char* date = ctime(&now);
//	fprintf(file,"GL_LOG_FILE log. local time %s\n", date);
//	fclose(file);
//	return true;
//}
//
//bool gl_log_err (const char* message, ...) {
//	va_list argptr;
//	FILE* file = fopen (GL_LOG_FILE, "a");
//	if (!file)
//	{
//		fprintf(stderr,"ERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
//		return false;
//	}
//	va_start(argptr, message);
//	vfprintf(file, message, argptr);
//	va_end(argptr);
//	va_start (argptr, message);
//	vfprintf(stderr, message, argptr);
//	va_end (argptr);
//	fclose (file);
//	return true;
//}
//
//// A generic log file function
//bool gl_log (const char* message, ...) 
//{
//	va_list argptr;
//	FILE* file = fopen(GL_LOG_FILE, "a");
//	if(!file) {
//		fprintf(stderr,"ERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
//		return false;
//	}
//	va_start (argptr, message);
//	vfprintf(file, message, argptr);
//	va_end (argptr);
//	fclose(file);
//	return true;
//}
//
//void glfw_error_callback (int error, const char* description)
//{
//	gl_log_err ("GLFW ERROR: code %i msg: %s\n", error, description);
//}
//
//// a call-back function
//void glfw_window_size_callback(GLFWwindow* window, int width, int height) 
//{
//	// change the window size parameters somehow?
//	//ScreenWidth = width;
//	//ScreenHeight = height;
//
//	//update perspective matrices here???
//
//}
//
//
//
//
//static void error_callback(int error, const char* description)  
//{  
//    fputs(description, stderr);  
//    _fgetchar();  
//}  
//  
////Define the key input callback  
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)  
//{  
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
//    glfwSetWindowShouldClose(window, GL_TRUE);  
//} 

// This initializes our window and creates the OpenGL context
int AppWindow::Initialize(int width, int height, std::string strTitle, bool bFullScreen, int x_pos, int y_pos)
{
/*
	printf("\nCreating a window..");
	assert (restart_gl_log());
	// start GL context and O/S window using the GLFW helper library
	gl_log ("starting GLFW\n%s\n", glfwGetVersionString());
	// register the error call-back function that we wrote, above
	glfwSetErrorCallback (glfw_error_callback);


	// This tries to first init the GLFW library and make sure it is available
	if ( !glfwInit() )
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* Window; 
//	Window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);

	// This tells OpenGL that we want a multisampling value of 4 (anti-aliasing)
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Set our OpenGL version to 4 using the core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	GLFWmonitor* mon = glfwGetPrimaryMonitor();
	const GLFWvidmode* vmode = glfwGetVideoMode(mon);

//	// Create a window either in fullscreen or not
	if( bFullScreen )
		Window = glfwCreateWindow(width, height, strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		Window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr, nullptr);
//		AppWindow.SetWindow = glfwCreateWindow(width, height, strTitle.c_str(), nullptr, nullptr);


	// Make sure the window is valid, if not, throw an error.
	if ( Window == nullptr )
	{
		fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
		Destroy();

		return -1;
	}
	SetWindow(Window); // Stores the pointer to each of the windows
//	cout << "\nWindow Reference test for AppWin: " << GetWindow() << endl;

	SetWindowPos(x_pos, y_pos); // Sets the windows position and relocates it.
*/
	return 0;

}

//void AppWindow::SetWindowPos(int x_pos, int y_pos)
//{ 
//	x_WindowPos = x_pos; 
//	y_WindowPos = y_pos; 
//	glfwSetWindowPos(GetWindow(),x_pos,y_pos);
//}

// This can be used to free our resources in the window
void AppWindow::Destroy()
{
	printf ("\nDestroying a Window...");
	//	cout << "\nDestroying Window ID: " << GetWindow();

	//	//Close openGL window
	//	glfwDestroyWindow(GetWindow()); 
}




