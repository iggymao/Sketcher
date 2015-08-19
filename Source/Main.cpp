#include "stdafx.h"
#include <iostream>
#include <string.h>
// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM Mathematics
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Headers/Application.h"			// Include our model header for the graphics manager
#include "../Headers/Mesh.h"				// Include the mesh header for testing purposes

// A constructor for the Application.
Application::Application(void)
{
	printf("\nApplication constructor");
}	

Application::~Application(void)
{
	printf("\nApplication destructor");
	Destroy();
	getchar();
}

// This is our own main() function which abstracts the required main() function to run this application.
int Application::Main()
{
	printf("\nCalling into GLMain()...starting main loop");

	// This is our main game loop which will run until we close the application 
//	AppLoop();

//	getchar();
	// Once we hit Escape this will clean up the application's resources.
//	Destroy();

	printf("\nEnding Program");
	getchar();
	return 0;
}

// This function initializes the the different subsystems for the application
void Application::Initialize()
{
	printf("\nInitializing Application");
	StartLogMgr();				//Start LogMgr;
	StartWindowsMgr();			//Start WindowsMgr;
	StartGraphicsMgr();			//Start GraphicsMgr;
	StartModelMgr();			//Start the ModelManager
/*
	StartFileMgr();				//Start FileMgr;
	StartPrintMgr();			//Start PrintMgr;
	StartInputMgr();			//Start InputMgr;
	StartNetworkMgr();			//StartNetworkMgr;
	StartAudioMgr();			//StartAudioMgr;
	StartEventMgr();			//StartEventMgr
*/
}

//// A method to set a Mesh ID into a model array
//void Application::SetMeshID(int counter, Mesh *pMesh)
//{
//	printf("\nSetMeshID into the Application Model array");
////	Model.reserve(Model.size()+1);
////	Model.push_back(counter);
////	Model[counter] = pMesh;
//}

//void Application::RenderApplication(AppWindow **p_array)
//{
///*
//	// Loop through all the windows owned by the application
//	for (int i=0;i<MAX_WINDOWS;i++)
//	{
////		cout << "======================================" << endl;
////		cout << "Array [" << i << "]:                  " << (*(p_array+i))->GetWindow() << endl;
////		cout << "GetWindowID(" << i << ")->GetWindow():" << GetWindowID(i)->GetWindow() << endl;
//
//
//// This chunk works...do not delete...references the **p_array format
//		//// Test function: This will render blue shades to the windows created by the application
//		//// Replace this line with a corrected call for rendering.
//		//(*(p_array+i))->RenderWindow((*(p_array+i))->GetWindow(), float(1.0-(float (i)/ float (MAX_WINDOWS))));
//
//	}
//*/
//}

//// This is our main loop where all the magic happens every frame
//void Application::AppLoop()
//{
//	printf("\nStarting Application Loop");
//}

// This can be used to free all of our resources in the application.
void Application::Destroy()
{
	GetLog()->Destroy();
	printf("\nDestroy logs..");
	GetLog()->gl_log(LOG_FILE, "\nDestroying the log manager");
	GetGraphMan()->Destroy();
	GetLog()->gl_log(LOG_FILE, "\nDestroying the graphics manager");
	printf("\nDestroy graphics manager.");
	GetLog()->gl_log(LOG_FILE, "\nDestroying the Application...");
	printf("\nDestroying Application");


}

void Application::StartLogMgr()				//Start LogMgr;
{
	printf("\nStart logging system...");
		// Do stuff here..

	LogManager *logmgr;
	logmgr = new LogManager;
	GetLog()->gl_log(LOG_FILE, "Starting the log manager...");

	logmgr->Initialize();
	SetLogMan(logmgr);	// stores the pointer to the logs manager in the main appl. class
	logmgr->restart_logs();
	logmgr->ShowDetails(logmgr->MemberInfo);
	return;
}
void Application::StartFileMgr()				//Start FileMgr;
{
	printf("\nStart File manager");
		// Do stuff here..
	return;
}
void Application::StartPrintMgr()			//Start PrintMgr;
{
	printf("\nStart Print manager");
		// Do stuff here..
	return;
}

int Application::StartGraphicsMgr()			//Start GraphicsMgr;
{
	printf("\nStart Graphics (OpenGL stuff)");
	// Do stuff here..

	GraphicsManager *graphmgr;
	graphmgr = new GraphicsManager(800,600);  // create a new GraphicsManager for a MainWindow size off width = 800 and height 600
//	graphmgr->Initialize();

	GetLog()->gl_log(LOG_FILE, "\nStarting the OPENGL launcher...");

	if(graphmgr->LaunchOpenGL() == 0)  // if we successfully navigate the context creation (return of 0 is success)
	{	
		GetLog()->gl_log(GL_LOG_FILE, "\nOPENGL context successfully created.");
		SetGraphMan(graphmgr);	// stores the pointer to the graphics manager in the main appl. class
	} else {
		GetLog()->gl_log(GL_LOG_FILE, "\nERROR:  Unsuccessful attempt to create OPENGL context in LaunchOpenGL()");
		return -1;
	}

	if(graphmgr->IsLoadedOpenGL)		// if the graphics manager successfully loads, then we'll report the context settings for the OPENGL case
		GetLog()->gl_log_params();

	//printf("\n    Pointer to graphmgr: %d",GetGraphMan());
/*
	// Start the shader manager.  Must be done after GLEW/GLFW have been initialized and the context
	// set to the main graphics window.
	ShaderManager *MyShaderManager;
	MyShaderManager = new ShaderManager;
	GetLog()->gl_log(LOG_FILE, "\nCreating the ShaderManager...");

	if (MyShaderManager->Initialize() == 0)
	{
		GetLog()->gl_log(GL_LOG_FILE, "\nShader manager successfully created.");

	} else {
		GetLog()->gl_log(GL_LOG_FILE, "\nERROR intializing the shader manager");	
	};
	MyShaderManager->ShowShaderDetails(MyShaderManager->ShaderMemberInfo);
	MyShaderManager->ShowTextureDetails(MyShaderManager->TextureMemberInfo);
	graphmgr->MyShaderManagerInfo = MyShaderManager;  // store the newly create shader manager in the graphics manager
*/
	// the main draw command
	graphmgr->Draw();
	return 0;
}

void Application::StartWindowsMgr()			//Start WindowsMgr;
{
	printf("\nStart Windows Manager to create multiple windows");

	// Make sure the window manager is initialized prior to calling this and creates the OpenGL context
	//if ( !WindowManager || WindowManager->Initialize(ScreenWidth, ScreenHeight, "I Beam Sketcher - GameTutorials - Matrices", false) != 0 )
	//{
		// Quit the application if the window couldn't be created with an OpenGL context
		//exit(-1);
	//}
		// Do stuff here..
		// Creating the application windows

/*
	AppWindow *MyWin[MAX_WINDOWS];

	//Create the primary model window
	sprintf_s(str,"\nMain Model Window #%d", 1);
	MyWin[0] = new AppWindow;
	MyWin[0]->Initialize(600,500, str, NULL, 200, 125);
	SetWindowID(0, MyWin[0]);

	//Create the subwindow viewports
	if(MAX_WINDOWS > 1)
	{
		for (int i=1;i<MAX_WINDOWS;i++)
		{
			sprintf_s(str, "\nTest Window #%d",i);
			MyWin[i] = new AppWindow;
			MyWin[i]->Initialize(300,250, str, NULL, 800, 125+(i-1
				)*250);
			SetWindowID(i, MyWin[i]);		
			// cout << "*MyWin[" << i << "]:" << *MyWin[i] << endl;
			// cout << "MyWin[" << i << "]:" << MyWin[i] << endl;
		}
	}
*/
	return;
}
void Application::StartModelMgr()			//Start the Model Managersubsystems;
{
	printf("\nStart Model Manager");

	/*
	ModelManager *modelmanager;
	modelmanager = new ModelManager;
	modelmanager->Initialize();
	SetModelMan(modelmanager);		// store the pointer to the modelmanager
    */
	// Do stuff here..
	////////////////////////////////////////////////////////////////


	// Creating and testing Mesh ID storage structures in Application.h
//	Mesh *MyMesh[MAX_MESH_QTY];
//	for (int i=0;i<5;i++)
//	{
//		MyMesh[i] = new Mesh;
//		SetMeshID(i, MyMesh[i]);
//		cout << "SetMeshID(i) = " << i << endl;
//	}
//	cout << "===================================" << endl;
//	cout << "Model size: " << Model.size() << endl;
//	for (int i=0;i<5;i++)
//	{

		//GetMeshID(i);
//		cout << "GetMeshID(i) = " << Model[i] << endl;
//	}

	return;
}

void Application::StartInputMgr()			//Start InputMgr;
{
	printf("\nStart Input Manager");
		// Do stuff here..
	return;
}
void Application::StartNetworkMgr()			//StartNetworkMgr;
{
	printf("\nStart Network Manager");
		// Do stuff here..
	return;
}
void Application::StartAudioMgr()			//StartAudioMgr;
{
	printf("\nStart Audio Manager");
		// Do stuff here..
	return;
}

void Application::StartEventMgr()			//StartEventMgr
{
	printf("\nStart Event Manager");
		// Do stuff here..
	return;
}