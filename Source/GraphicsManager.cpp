#include "stdafx.h"
#include <iostream>
// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include "../Headers/GraphicsManager.h"
#include "../Headers/Camera.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void Do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool firstMouse = true;
/*
// Initial camera values
glm::vec3 cameraPos		= glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront	= glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp		= glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat yaw		= -90.0f;		// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right
GLfloat pitch	=	0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat aspect = 45.0f;
*/

// Deltatime
GLfloat deltaTime = 0.0f;			// time between current frame and last frame
GLfloat lastFrame = 0.0f;			// time of last frame

const char* GL_type_to_string(GLenum type){
	switch(type) {
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
		default: break;
	}
	return "other";
}

void _print_shader_info_log (GLuint shader_index) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
		glGetShaderInfoLog (shader_index, max_length, &actual_length, log);
		printf ("shader info log for GL index %u:\n%s\n", shader_index, log);
}

void _print_programme_info_log(GLuint programme) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog(programme, max_length, &actual_length, log);
	printf ("program info log for GL index %u:\n%s", programme, log);
}

bool is_valid(GLuint programme) {
	glValidateProgram(programme);
	int params = -1;
	glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
	printf("program %i GL_VALIDATE_STATUS = %i\n", programme, params);
	if (GL_TRUE != params) {
		_print_programme_info_log (programme);
		return false;
	}
	return true;
}

void print_all(GLuint programme) {
	printf ("---------------------------------------\nshader programme %i info:\n", programme);
	int params = -1;
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	printf ("GL_LINK_STATUS = %i\n", params);
	glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
	printf ("GL_ATTACHED_SHADERS= %i\n", params);
	glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
	printf ("GL_ACTIVE_ATTRIBUTES=%i\n", params);
	for (GLuint i=0; i<(GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib(programme, i, max_length, &actual_length, &size, &type, name);
		if(size>1){
			for(int j=0; j<size; j++) {
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(programme, long_name);
				printf("  %i) type:%s  name:%s  location:%i\n", i, GL_type_to_string(type), long_name, location);
			}
		} else {
			int location = glGetAttribLocation(programme, name);
			printf("  %i) type:%s,  name:%s  location:%i\n", i, GL_type_to_string(type), name, location);
		}
	}
	glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
	printf("GL_ACTIVE_UNIFORMS = %i\n", params);
	for(GLuint i=0; i<(GLuint)params; i++) {
		char name[64];
		int max_length=64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform(programme, i, max_length, &actual_length, &size, &type, name);
		if (size>1){
			for (int j=0; j<size; j++) {
				char long_name[64];
				sprintf(long_name,"%s[%i]", name, j);
				int location = glGetUniformLocation (programme, long_name);
				printf ("  %i) type:%s name:%s  location:%i\n", i, GL_type_to_string(type), long_name, location);
			}
		} else {
			int location = glGetUniformLocation(programme, name);
			printf ("  %i) type:%s name:%s  location:%i\n", i, GL_type_to_string (type), name, location);
		}
	}

	_print_programme_info_log(programme);
}





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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

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

    // Set the required callback functions
    glfwSetKeyCallback(Window, key_callback);
	glfwSetCursorPosCallback(Window, mouse_callback);
	glfwSetScrollCallback(Window, scroll_callback);

	// GLFW options
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, MyWinInfo->main_win_width, MyWinInfo->main_win_height);		
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.4f, 0.5f, 0.5f, 1.0f);	// Clear the colorbuffer (set it to a grayscale)
	glClear( GL_COLOR_BUFFER_BIT );			// Clear the screen

	glfwSwapBuffers(Window);				// Swap the buffer to create an initial colored screen

	// at this point the context is active, so store a variable to tell the main application
	IsLoadedOpenGL = true;	


	//Shader Stuff
	/*const char* vertex_shader =
		"#version 330\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}";*/

	const char* vertex_shader =
		"#version 330\n"
		"layout (location = 0) in vec3 position;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"void main() {"
		"  gl_Position = projection * view * model * vec4 (position, 1.0f);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_color;"
		"void main() {"
		"  frag_color = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	// check for compile errors
	int params = -1;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
	if(GL_TRUE != params) { 
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", vs);
		_print_shader_info_log (vs);
		return false; // or exit or something
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	
	// check for compile errors
	params = -1;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
	if(GL_TRUE != params) { 
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", fs);
		_print_shader_info_log (fs);
		return false; // or exit or something
	}

	GLuint shader_program = glCreateProgram();
	glAttachShader (shader_program, fs);
	glAttachShader (shader_program, vs);
	glLinkProgram (shader_program);
	// check if link was successful
	params = -1;
	glGetProgramiv (shader_program, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: could not link shader programme GL index %u\n", shader_program);
		_print_programme_info_log (shader_program);
		return false;
	}
	 print_all(shader_program);		// print all the shader info
	// End Shader stuff

	// Vertex VAO, VBO stuff
//	GLfloat points[] = { 
//	0.0f, 0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	-0.5f, -0.5f, 0.0f,
////	0.0f, 0.5f, 0.0f
//	};

	// Set up vertex data (and buffer(s)) and attribute pointers
 		// X      Y      Z   TextU  TextV
	 GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


	GLuint vao=0;
	GLuint vbo=0;
	glGenVertexArrays (1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO

	while (!glfwWindowShouldClose(Window))
    {
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activated
		glfwPollEvents();
		Do_movement();

		// wipe the drawing surface clear
		glClearColor(0.4f, 0.5f, 0.5f, 1.0f);	// Clear the colorbuffer (set it to a grayscale)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // wipe the drawing surface clear

		glUseProgram(shader_program);						 // use our shader program

	    // Camera/View transformation
        glm::mat4 view;
 //       GLfloat radius = 20.0f;
 //       GLfloat camX = (GLfloat) (sin(glfwGetTime()) * radius);
 //       GLfloat camZ = (GLfloat) (cos(glfwGetTime()) * radius);
 //       view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
		view = camera.GetViewMatrix();
        // Projection 
        glm::mat4 projection;
//        projection = glm::perspective(aspect, (GLfloat)MyWinInfo->main_win_width / (GLfloat)MyWinInfo->main_win_height, 0.1f, 100.0f);
		projection = glm::perspective(camera.Zoom, (GLfloat)MyWinInfo->main_win_width / (GLfloat)MyWinInfo->main_win_height, 0.1f, 100.0f);

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(shader_program, "model");
        GLint viewLoc = glGetUniformLocation(shader_program, "view");
        GLint projLoc = glGetUniformLocation(shader_program, "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao);


		// creates ten cubes based on the position data prescribed earlier
        for (GLuint i = 0; i < 10; i++)
        {
            // Calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers (Window);
	} 
	// Properly de-allocate all vertex arrays
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	// Terminate GLFW, clearing any resources allocated by GLFW
	glfwTerminate();

	return 0;

}

void GraphicsManager::Destroy()
{
	printf("\nINCOMPLETE:  Destroying the Graphics Manager");
    //Finalize and clean up GLFW  
    glfwTerminate(); 
	delete MyWinInfo;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Do_movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (GLfloat) xpos;
        lastY = (GLfloat) ypos;
        firstMouse = false;
    }

    GLfloat xoffset = (GLfloat) xpos - lastX;
    GLfloat yoffset = lastY - (GLfloat) ypos; // Reversed since y-coordinates go from bottom to left
    lastX = (GLfloat) xpos;
    lastY = (GLfloat) ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}