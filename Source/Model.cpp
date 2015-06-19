
#include "stdafx.h"
#include <iostream>

//#include "../Headers/Volume.h"
#include "../Headers/Main.h"
#include "../Headers/Model.h"
#include "../Headers/ShaderManager.h"		// for testing the ShaderManageralgorithm


using namespace std;

// a log function calling gl_log in Application.h.  Must be called after GLEW has been initialized.
// A generic log file function
bool gl_log (const char* message, ...) ;
/*
bool gl_log (const char* message, ...) 
{
	va_list argptr;
	FILE* file = fopen(GL_LOG_FILE, "a");
	if(!file) {
		fprintf(stderr,"ERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
		return false;
	}
	va_start (argptr, message);
	vfprintf(file, message, argptr);
	va_end (argptr);
	fclose(file);
	return true;
}
*/

void log_gl_params () 
{
	GLenum params[]= 
	{
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* names[] = 
	{
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};

	gl_log ("GL Context Params:\n");
	// integers - only works if the order is 0-10 integer return types
	for (int i = 0; i<10; i++)
	{
		int v = 0;
		glGetIntegerv(params[i], &v);
		gl_log("%s %i\n", names[i], v);
	}
	// others
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv(params[10], v);
	gl_log("%s %i %i\n", names[10], v[0], v[1]);
	unsigned char s = 0;
	glGetBooleanv(params[11], &s);
	gl_log("%s %u\n", names[11], (unsigned int)s);
	gl_log("-------------------------------------\n");
}

double previous_seconds;
int frame_count;
/* we will use this function to update the window title with a frame rate */
void _update_fps_counter(GLFWwindow *window)
{
	double current_seconds;
	double elapsed_seconds;
	current_seconds = glfwGetTime();
	elapsed_seconds = current_seconds - previous_seconds;
	// limit text updates to 4 per second
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		char tmp[128];
		double fps = (double)frame_count / elapsed_seconds;
		sprintf(tmp, "OpenGL @ fps: %.2f", fps);
		glfwSetWindowTitle(window,tmp);
		frame_count = 0;
	}
	frame_count++;
}

Model::Model()
{
	printf("Model constructor...");
}

void Model::Initialize()
{
	printf("\nCreating a model...");

	ModelTargetWindow = WINDOW_VIEWMODEL;

	//////////////
	// Test Cases
	//////////////
	// Create Volume #1 in Window1
	Volume *MyVolume[MAX_MODEL_VOLUMES];		// creates an array to store a volume

	MyVolume[0] = new Volume;
	MyVolume[0]->Initialize(VOLUME_RIGHT_PRISM);
	MemberVolume[0] = MyVolume[0];
	MemberVolume[0]->VolTargetWindow = WINDOW_VIEW1;

	MyVolume[1] = new Volume;
	MyVolume[1]->Initialize(VOLUME_AREA);
	MemberVolume[1] = MyVolume[1];
	MemberVolume[1]->VolTargetWindow = WINDOW_VIEW2;

	return;
	
}

void Model::RenderModel(AppWindow **WinID_array)
{
	printf("\nRendering a model...");
	GLFWwindow *Window;
	Window = (*(WinID_array+ModelTargetWindow))->GetWindow();

	// Make sure the window is valid, if not, throw an error.
	if ((Window == nullptr) || (ModelTargetWindow >= MAX_WINDOWS) )
	{
		fprintf(stderr, "\nInvalid Window found in ModelMesh.cpp RenderModel() function");
		return;
	}

	glfwMakeContextCurrent(Window); // Initialize GLEW 

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}
	log_gl_params();  // list the parameters of the GLEW install.  Must be included after GLEW has been initialized.

	/////////////////////////////////////////////
	// Create and load the ShaderManager
	// This must be after the GLEW has been initialized because of the calls located in BuildShaderProgram method of
	// the ShaderManager class in ShaderManager.h
	ShaderManager shadermanager;
	shadermanager.Initialize();

	//populate the shade manager explicitly, eventually this should probably be moved out of this
	// method.  Perhaps up to the Application level??
	std::string strvertexfilename = "Shaders/test";
	std::string strfragmentfilename = "Shaders/junk";
	shadermanager.AddShader(shadermanager.MemberInfo, SHADER_VERTEX, strvertexfilename, strfragmentfilename);
	strvertexfilename = "Shaders/Shader.vertex";
	strfragmentfilename = "Shaders/Shader.fragment";
	shadermanager.AddShader(shadermanager.MemberInfo, SHADER_VERTEX, strvertexfilename, strfragmentfilename);
	// end adding to shader.

	ShaderInfo *temp = shadermanager.searchShaderInfo(shadermanager.MemberInfo, strvertexfilename, strfragmentfilename);
	printf("-----------------------------------------");
//	printf("\nEntry temp->ShaderID: %i", (*temp).ShaderID);
//	shadermanager.ShowDetails(shadermanager.MemberInfo);

	if(!temp)
	{
		printf("\nNo record found...aborting...");
		// maybe enter a log entry here?
	} else {
		shadermanager.BuildShaderProgram(temp);
//		printf("\nShader BuildShaderProgram complete");
	}
	shadermanager.ShowDetails(shadermanager.MemberInfo);
	getchar();  // to pause the compilation for now
	// End the ShaderManager creation
	//////////////////////////////////

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
	
	// Render
	glClearColor(0.4f, 0.5f, 0.5f, 1.0f);		// Clear the colorbuffer
	glClear( GL_COLOR_BUFFER_BIT );				// Clear the screen

	while(!glfwWindowShouldClose(Window))
	{
		Window = (*(WinID_array+ModelTargetWindow))->GetWindow();

		// Make sure the window is valid, if not, throw an error.
		if ((Window == nullptr) || (ModelTargetWindow >= MAX_WINDOWS) )
		{
			fprintf(stderr, "\nInvalid Window found in ModelMesh.cpp RenderModel() function");
			return;
		}

		glfwMakeContextCurrent(Window); // Initialize GLEW 
		_update_fps_counter(Window);
		glClearColor(0.4f, 0.5f, 0.5f, 1.0f);		// Clear the colorbuffer
		glClear( GL_COLOR_BUFFER_BIT );				// Clear the screen

		// Render the model members to the MODEL view (set by WINDOW_VIEWMODEL in Application.h).  Draws all members in Window #1
		for(int i=0;i<MAX_MODEL_VOLUMES;i++)
		{
			MemberVolume[i]->RenderVolume(ModelTargetWindow, WinID_array );
			cout << "\nRendering volume #: " << i << " to Window #: " << ModelTargetWindow;
		}

		// Then render the sub volumes out.  Draws volumes to their specified windows.
		for (int j=(WINDOW_VIEWMODEL+1);j<MAX_WINDOWS;j++)
		{
			Window = (*(WinID_array+j))->GetWindow();

			// Make sure the window is valid, if not, throw an error.
			if ((Window == nullptr) || (ModelTargetWindow >= MAX_WINDOWS) )
			{
				fprintf(stderr, "\nInvalid Window found in ModelMesh.cpp RenderModel() function");
				return;
			}

			glfwMakeContextCurrent(Window); // Initialize GLEW 
			_update_fps_counter(Window);

			glClear( GL_COLOR_BUFFER_BIT );				// Clear the screen

			for(int i=0;i<MAX_MODEL_VOLUMES;i++)
			{
				if (MemberVolume[i]->VolTargetWindow == j)
				{
					MemberVolume[i]->RenderVolume(MemberVolume[i]->VolTargetWindow, WinID_array );
					cout << "\nRendering volume #: " << i << " to SubWindow #: " << MemberVolume[i]->VolTargetWindow;
				} // end if
			}
		}
		// To swap the buffers...cycle through each of the AppWindows.
		for(int i=0;i<MAX_WINDOWS;i++)
		{
	//		cout << "Volume MemberMesh[" << i << "],  Type #: " << MemberMesh[i]->MeshType << " to TargetWindow #: " << TargetWindow;
			Window = (*(WinID_array+i))->GetWindow();
			glfwSwapBuffers(Window);
	//		getchar();
		}
//		getchar();
	} // end while
	return;
	
}