#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <string>
// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "../Headers/GraphicsManager.h"
#include "../Headers/Camera.h"
#include "../Headers/ShaderManager.h"
#include "../Headers/Shader.h"
#include "../Headers/SOIL.h"			// include the soil image loader based on stb_image for texture loading


// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Headers/DrawingShapes.h"	// include the drawing shapes definitions
#include "../Headers/Cursor.h"

#include "../utils/MathUtils.cpp"



// forward declaration
class GraphicsManager;  // forward declare the graphics manager class
//class Cursor;			// forward declare the cursor class

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_click_callback(int b, int s, int mouse_x, int mouse_y);
void Do_Movement();
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool firstMouse = true;

// Cursor intialization
CCursor *cursor = 0;
//CCursor *cursor = new CCursor(glm::vec3(0.0f, 0.0f, 0.0f));		// create a new cursor
//CCursor *CursorObj = cursor;												// store the object in the graphics manager

// Grid attributes
CGrid *gridLine = 0;
//CGrid *GridLine = new CGrid(30, 0.1f, 40, 0.1f);
//CGrid *DrawingGridLine = GridLine;		// storing the gridline in our graphics manager
bool IsActiveGridToggle = true;
bool IsActivePicking = true;

// Light attributes
bool IsPausedLight = true;
glm::vec3 lightPos(0.0f, 2.0f, 0.0f);  // a default light source position
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);  // a default light source position

// Deltatime
GLfloat deltaTime = 0.0f;			// time between current frame and last frame
GLfloat lastFrame = 0.0f;			// time of last frame

/*
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
*/

/*
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
*/

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

	//assert (restart_gl_log());
	//// start GL context and O/S window using the GLFW helper library
	//gl_log ("starting GLFW\n%s\n", glfwGetVersionString());
	//// register the error call-back function that we wrote, above
	//glfwSetErrorCallback (glfw_error_callback);

	// This tries to first init the GLFW library and make sure it is available
	if ( !glfwInit() )
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* Window; 
	
	// Set our OpenGL version to 3.3 using the core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//	glfwWindowHint(GLFW_SAMPLES, 4);	// This tells OpenGL that we want a multisampling value of 4 (anti-aliasing)
	//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);  // This tells OpenGL that the window will not have a border.

	//This creates the main window, needed to launch the OpenGL context
	// Create the window.  Still need to consider full screen mode options here.
	Window = glfwCreateWindow(MyWinInfo->main_win_width, MyWinInfo->main_win_height, MyWinInfo->strWinTitle.c_str(), nullptr, nullptr);

	// Make sure the window is valid, if not, throw an error.
	if ( Window == nullptr )
	{
		fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
		glfwTerminate();
		return -1;
	}

	glfwSetWindowPos(Window, MyWinInfo->main_pos_x, MyWinInfo->main_pos_y);	// size and relocate the window

	glfwMakeContextCurrent(Window); // make the context current

    // Set the required callback functions
    glfwSetKeyCallback(Window, key_callback);
	glfwSetCursorPosCallback(Window, mouse_callback);
	glfwSetScrollCallback(Window, scroll_callback);

	// GLFW options
	glfwSetCursorPos(Window, WIDTH/2, HEIGHT/2);				// move the cursor to the middle of the screen
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // show the cursor (toggled off when camera is active)

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, MyWinInfo->main_win_width, MyWinInfo->main_win_height);		
	glEnable(GL_DEPTH_TEST);  // Must remember to clear GL_DEPTH_BUFFER_BIT in a glClear statement
	glDepthFunc(GL_LESS);

	glClearColor(0.4f, 0.5f, 0.5f, 1.0f);	// Clear the colorbuffer (set it to a grayscale)
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );			// Clear the screen
	glfwSwapBuffers(Window);				// Swap the buffer to create an initial colored screen

	// at this point the context is active, so store a variable to tell the main application
	IsLoadedOpenGL = true;	
	MyWinInfo->MainWindow = Window;			// store the pointer to the MainWindow so we can retrieve it later
	
	return 0;
}

// Our main draw function
void GraphicsManager::Draw()
{
	std::string message;
	// Create and load shaders
	Shader ourShader("Shaders/DefaultShader.vertex", "Shaders/DefaultShader.fragment");
	Shader lightsourceShader("Shaders/ShaderLighting.vertex", "Shaders/ShaderLighting.fragment");
	Shader cursorShader("Shaders/ShaderLighting.vertex", "Shaders/ShaderLighting.fragment");
	Shader pickingShader("Shaders/ShaderPicking.vertex", "Shaders/ShaderPicking.fragment");				// shader used when picking mode is activated (not used??)
	Shader post_process_spShader("Shaders/post_process_sp.vertex","Shaders/post_process_sp.fragment");  // shader used for making a framebuffer for picking selecting
	// Create and load shape for our model, including gridline objects and the physical assets
	ModelManager ourModel(MODEL_LOAD_MODEL); // Loads the model elements

	// Create the main drawing grid line -- requires an OPENGL context for this step
	// Must use XY, XZ, or YZ plane designators....such that X < Y < Z in order of labelling
	gridLine = new CGrid(30, 0.1f, 40, 0.1f, XZ_PLANE);
	DrawingGridLine = gridLine;											// storing the gridline in our graphics manager

	// Create our cursor -- requires an OPENGL context for this step
	cursor = new CCursor(glm::vec3(0.0f, 0.0f, 0.0f));		// create a new cursor
	cursor->SetSnapValues(DrawingGridLine->GetSpacing1(), DrawingGridLine->GetSpacing2(), DrawingGridLine->GetPlane());
	CursorObj = cursor;		// store the object in the graphics manager

	// create our framebuffer
	// first create the framebuffer
	GLuint framebuffer;
	glGenFramebuffers (1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// create a color attachment texture
	GLuint textureColorbuffer = generateAttachmentTexture(false, false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// Create a renderbuffer object for depth and stencil attachment
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	// Use a single renderbuffer object for both depth AND stencil buffer.
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);  // now actually attach it
	// Now that we actually created the framebuffer andadded all attachments we want to check if it is actually complete now
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("\nERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// set up the screen space quad by creating two triangles to cover the entire screen, then provide
	// mapping coords for the framebuffer we just created
	//x, y vertex positions
	float ss_quad_pos[] = {
		-1.0, -1.0,
		1.0, -1.0,
		1.0, 1.0,
		1.0, 1.0,
		-1.0, 1.0,
		-1.0, -1.0
	};
	// per vertex texture coordsinates
	float ss_quad_st[] = {
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0
	};
	// create VBOs and VAO in the usual way
	// Load data into vertex buffers
	GLuint ss_quad_vbo = 0;
    glGenBuffers(1, &ss_quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ss_quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ss_quad_pos), ss_quad_pos, GL_STATIC_DRAW);

	GLuint ss_quad_texvbo =0;
	glGenBuffers(1, &ss_quad_texvbo);
	glBindBuffer(GL_ARRAY_BUFFER, ss_quad_texvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ss_quad_st), ss_quad_st, GL_STATIC_DRAW);

	GLuint ss_quad_vao = 0;
	glGenVertexArrays(1, &ss_quad_vao);
    glBindVertexArray(ss_quad_vao);

	// Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);	
    glBindBuffer(GL_ARRAY_BUFFER, ss_quad_vbo);
     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

		// Texture Coords
        glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, ss_quad_texvbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		
		glBindVertexArray(0); // clear the VAO
		
	// Game loop
    while (!glfwWindowShouldClose(MyWinInfo->MainWindow))
    {
		///////////////////////////////////////////////////
		// Bind to framebuffer and draw to color texture
		///////////////////////////////////////////////////
		// rebind our default framebuffer just-in-case and then clear it
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(IsActivePicking)
		{
			// bind the second (render-to-texture) framebuffer here
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			//printf("\nIs active picking value: %i",IsActivePicking);

			//  This line needed here? ---->  glClearColor
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		// then render scene as normal..
		//////////////////////////////////
		// Our normal rendering stuff
		//////////////////////////////////

		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
		Do_Movement();

        // Render
        // Clear the colorbuffer
        glClearColor(0.4f, 0.5f, 0.5f, 1.0f);   // a grey color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Depth buffer enabled, must clear the depth buffer bit too.
		glEnable(GL_DEPTH_TEST);


		// For a moving light source
		if(!IsPausedLight)
		{
		   lightPos.x = (GLfloat)(1.0f + sin(glfwGetTime()) * 2.0f);
		   lightPos.y = (GLfloat)(sin(glfwGetTime() / 2.0f) * 1.0f);
		   lightPos.z = (GLfloat)(cos(glfwGetTime() * 0.75f));
		}

		/////////////////////////
        // Draw the objects
		/////////////////////////
        ourShader.Use();

		GLint lightPosLoc    = glGetUniformLocation(ourShader.Program, "light.position");
        GLint viewPosLoc     = glGetUniformLocation(ourShader.Program, "viewPos");
        glUniform3f(lightPosLoc,    lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc,     camera.Position.x, camera.Position.y, camera.Position.z);
        // Set lights properties
        glm::vec3 lightColor;
		// Variable light Color code
        //lightColor.x = (GLfloat)(sin(glfwGetTime() * 2.0f));
        //lightColor.y = (GLfloat)(sin(glfwGetTime() * 0.7f));
        //lightColor.z = (GLfloat)(sin(glfwGetTime() * 1.3f));
		lightColor.x = 1.0f;
		lightColor.y = 1.0f;
		lightColor.z = 1.0f;
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence
        glUniform3f(glGetUniformLocation(ourShader.Program, "light.ambient"),  ambientColor.x, ambientColor.y, ambientColor.z);
        glUniform3f(glGetUniformLocation(ourShader.Program, "light.diffuse"),  diffuseColor.x, diffuseColor.y, diffuseColor.z);
        glUniform3f(glGetUniformLocation(ourShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
        // Set material properties
        glUniform3f(glGetUniformLocation(ourShader.Program, "material.ambient"),   1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(ourShader.Program, "material.diffuse"),   1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(ourShader.Program, "material.specular"),  0.5f, 0.5f, 0.5f); // Specular doesn't have full effect on this object's material
        glUniform1f(glGetUniformLocation(ourShader.Program, "material.shininess"), 32.0f);

		// Camera/View transformation
        glm::mat4 view;	// sets an indentity matrix in view
        view = camera.GetViewMatrix();

		//	glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)(MyWinInfo->main_win_width/MyWinInfo->main_win_height), 0.1f, 100.0f);  
		camera.SetProjectionMatrix(camera.Zoom, (GLfloat)(MyWinInfo->main_win_width/MyWinInfo->main_win_height), 0.1f, 100.0f);
		glm::mat4 projection;  
		projection = camera.GetProjectionMatrix();

		// Get the uniform locations
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(ourShader.Program, "view");
        GLint projLoc  = glGetUniformLocation(ourShader.Program, "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// Model
		glm::mat4 model;  // sets an identity matrix into model
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ourModel.Draw(ourShader, GL_TRIANGLES);

		// Draw the grid line structure if the the grid toggle is active
		if(IsActiveGridToggle)
		{					
			glm::mat4 model;
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(glGetUniformLocation(ourShader.Program, "material.ambient"),   1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(ourShader.Program, "material.diffuse"),   1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(ourShader.Program, "material.specular"),  0.0f, 0.0f, 0.0f); // Specular doesn't have full effect on this object's material
			glUniform1f(glGetUniformLocation(ourShader.Program, "material.shininess"), 32.0f);
			DrawingGridLine->Draw();
	
			//for (GLuint j = 0; j<2;j++)
			//{
			//	for (GLuint i = 0; i < 80; i++)
			//	{
			//		// Calculate the model matrix for each object and pass it to shader before drawing
			//		glm::mat4 model;
			//		GLfloat angle = (GLfloat)(90.0f * (3.14159 / 180.0) * j);
			//		//printf("\nAngle:  %f", angle);
			//		//model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
			//		model = glm::rotate(model, 90.0f*j, glm::vec3(0.0f, 1.0f, 0.0f));
			//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0+0.1*i));
			//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			//		gridModel.Draw(ourShader, GL_LINES);
			//	}
			//}
		}	

		/////////////////////////////// 
		//       Draw the cursor     //
		///////////////////////////////
		// WARNING!:  need to initialize this shader for it to work.
		// Currently using existing settings for the main objects.  Cursor needs
		// its own shader initialization

		// cursorShader.Use();
		model = glm::mat4();
		model = glm::translate(model, CursorObj->GetWorldCoords());
		model = glm::scale(model, glm::vec3(0.05f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		CursorObj->Draw();

		////////////////////////////////////////
		//  Draws the Lighting source lamp
		////////////////////////////////////////
		// Use cooresponding shader when setting uniforms/drawing objects
        lightsourceShader.Use();

		// Get location objects for the matrices on the lamp shader
        GLint lightmodelLoc = glGetUniformLocation(lightsourceShader.Program, "model");
        GLint lightviewLoc  = glGetUniformLocation(lightsourceShader.Program,  "view");
        GLint lightprojLoc  = glGetUniformLocation(lightsourceShader.Program,  "projection");
		// Set matrices
        // Pass the matrices to the shader
        glUniformMatrix4fv(lightviewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(lightprojLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the light (using first square of the container's vertex attributes)
		// Need to create an additional array just for light sources
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));
        glUniformMatrix4fv(lightmodelLoc, 1, GL_FALSE, glm::value_ptr(model));

		ourModel.Draw(lightsourceShader, GL_TRIANGLES);

//////////////////////////////////
// End of normal rendering stuff
//////////////////////////////////

		///////////////////////////////////////////////////
		//  Bind to default framebuffer again and draw the
		//  quad with attached screen texture
		///////////////////////////////////////////////////
		if(IsActivePicking)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			// Clear all relevant buffers
			glClearColor(0.4f, 0.5f, 0.5f, 1.0f);	// Set the clear color
			glClear(GL_COLOR_BUFFER_BIT);
			glDisable(GL_DEPTH_TEST); // We don't care about depth information when rendering a single quad

			// bind default framebuffer
			glBindFramebuffer (GL_FRAMEBUFFER, 0);
			// clear the framebuffer's color and depth buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// our post processing shader for the screen-space quad
			post_process_spShader.Use();
			// bind the quad's vao
			glBindVertexArray(ss_quad_vao);
			// activate the first texture slot and put texture from previous pass on it
//			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
			// draw the quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}

		// flip drawn framebuffer onto the display
		// Swap the screen buffers
	    glfwSwapBuffers(MyWinInfo->MainWindow);

		/////////////////////////////////////////////////////////////////
		//   Beginning picking subsection
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//   End picking subsection
		/////////////////////////////////////////////////////////////////
    }
	// Clean up
	glDeleteFramebuffers(1, &framebuffer);

    // Properly de-allocate all resources once they've outlived their purpose
	// glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &VBO);
    
	// Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return;
}

//	GLuint shader_program;				// program number for our main shader
//	GLuint lightingshader_program;		// program number for our lighting shader
//	ShaderInfo *temp;
//
//	// Retrieve the shader program ID for the normal shader.  This will need rework when
//	// multiple shaders are possible in the same rendering drawing.  But it does allow for the loading of the 
//	// default shader program in the event access is denied or an error exists within the shader manager records.
//	// This will need rework and possible inclusion in the main draw loop.
//	std::string strvertexfilename = "Shaders/Shader.vertex";
//	std::string strfragmentfilename = "Shaders/Shader.fragment";
//	temp = MyShaderManagerInfo->searchShaderInfo(MyShaderManagerInfo->ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//
//	if (!(temp == NULL))
//	{
//		shader_program = temp->ShaderProgramID;
//		printf("\nShader found.  Loading ShaderProgram ID = %i", shader_program);
//	} else {
//		strvertexfilename = "Shaders/DefaultShader.vertex";
//		strfragmentfilename = "Shaders/DefaultShader.fragment";
//		temp = MyShaderManagerInfo->searchShaderInfo(MyShaderManagerInfo->ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//		shader_program = temp->ShaderProgramID;		
//		printf("\nShader not found...Loading the default shader, ShaderProgramID %i",shader_program);
//	} 
//
//	//  Find the program number for our lighting shader.  Again this will need a more elegant rework 
//	//  when dealing with multiple shaders and effects.
//	strvertexfilename = "Shaders/ShaderLighting.vertex";
//	strfragmentfilename = "Shaders/ShaderLighting.fragment";
//	temp = MyShaderManagerInfo->searchShaderInfo(MyShaderManagerInfo->ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//	// check if a lighting shader exists.  If not, then skip
//	if (!(temp == NULL))
//	{
//		lightingshader_program = temp->ShaderProgramID;
//		printf("\nShader found.  Loading Lighting ShaderProgram ID = %i", lightingshader_program);
//	}

////////////////////////////////////////////
//  Snippet for creating ten random cubes
////////////////////////////////////////////
//		// creates ten cubes based on the position data prescribed earlier
//        for (GLuint i = 0; i < 10; i++)
//        {
//            // Calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model;
//            model = glm::translate(model, cubePositions[i]);
//            GLfloat angle = 20.0f * i;
//            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
//            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//            glDrawArrays(GL_TRIANGLES, 0, 36); 
//        }
//        glBindVertexArray(0);
//
////		ModelManager ourModel;
////		ourModel.Draw();
//
//		// Swap the screen buffers
//		glfwSwapBuffers (MyWinInfo->MainWindow);
//
//		// Turn off the shader program and unbind any textures
//		glUseProgram(0);			
//		glBindTexture(GL_TEXTURE_2D, 0);	 
//
//	} 
//	// Properly de-allocate all vertex arrays
//	glDeleteVertexArrays(1, &vao);
//	glDeleteBuffers(1, &vbo);
//	// Terminate GLFW, clearing any resources allocated by GLFW
//	glfwTerminate();
//
//	return;
//}

void GraphicsManager::Destroy()
{
	printf("\nINCOMPLETE:  Destroying the Graphics Manager");
	printf("\nDeleting CursorObj in GraphicsManager class");
	delete CursorObj;
	printf("\nDeleting DrawingGridLine in GraphicsManager class");
	delete DrawingGridLine;
    //Finalize and clean up GLFW  
	printf("\nTerminating GLFW and OpenGL context");
    glfwTerminate(); 
	printf("\nDeleting the main drawing window in GraphicsManager class");
	delete MyWinInfo;
}

// Generates a texture that is suited for attachments to a framebuffer
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
    // What enum to use?
    GLenum attachment_type;
    if(!depth && !stencil)
        attachment_type = GL_RGB;
    else if(depth && !stencil)
        attachment_type = GL_DEPTH_COMPONENT;
    else if(!depth && stencil)
        attachment_type = GL_STENCIL_INDEX;

    //Generate texture ID and load texture data 
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if(!depth && !stencil)
        glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, WIDTH, HEIGHT, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
    else // Using both a stencil and depth test, needs special format arguments
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		if (camera.IsActiveCameraToggle)
		{
			printf("\nCamera turned off...");
			// enable the cursor
			glfwSetCursorPos(window, WIDTH/2, HEIGHT/2);				// move the cursor to the middle of the screen
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // show the cursor (used for the camera control)
			camera.IsActiveCameraToggle = false;						// flag the camera as turned off
		} else {		
			printf("\nCamera turned on...");
			// disable the cursor for the camera controls
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // hide the cursor (used for the camera control)
			camera.IsActiveCameraToggle = true;							// flag the camera as turned on
		}
	}

	// Pause the moving light
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (IsPausedLight)
		{
			printf("\nMoving Light is unpaused...");
			IsPausedLight = false;
		} else {
			printf("\nMoving Light is paused...");
			IsPausedLight = true;
		}
	}


	// Active the cursor snap
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		if (cursor->IsActiveCursorSnap)
		{
			printf("\nSnap is off...");
			cursor->IsActiveCursorSnap = false;
		} else {
			printf("\nSnap is on...");
			cursor->IsActiveCursorSnap = true;
		}
	}

	// Toggle the grid display
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		if (IsActiveGridToggle)
		{
			printf("\nGrid is hidden...");
			IsActiveGridToggle = false;
		} else {
			printf("\nGrid is visible...");
			IsActiveGridToggle = true;
		}
	}

	// Picking is active toggle
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
	{
		if (IsActivePicking == true)
		{
			printf("\nPicking mode disabled...");
			IsActivePicking = false;
					//printf("\nIs active picking value: %i",IsActivePicking);
		} else {
			printf("\nPicking objects...");
			IsActivePicking = true;
					//printf("\nIs active picking value: %i",IsActivePicking);
		}
	}

	if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Do_Movement()
{
	// actions possible only if the camera toggle is active
	if(camera.IsActiveCameraToggle)
	{
	    // Camera controls
	    if(keys[GLFW_KEY_A])
	        camera.ProcessKeyboard(LEFT, deltaTime);
	    if(keys[GLFW_KEY_D])
	        camera.ProcessKeyboard(RIGHT, deltaTime);
		if(keys[GLFW_KEY_S])
	        camera.ProcessKeyboard(BACKWARD, deltaTime);
		if(keys[GLFW_KEY_W])
	        camera.ProcessKeyboard(FORWARD, deltaTime);
		// Downward must be before upwards because both utilize the SPACE key
		if((keys[GLFW_KEY_SPACE]&&(keys[GLFW_KEY_LEFT_SHIFT])) || (keys[GLFW_KEY_SPACE]&&(keys[GLFW_KEY_RIGHT_SHIFT])))
			camera.ProcessKeyboard(DOWNWARD, deltaTime);
		if(keys[GLFW_KEY_SPACE])
			camera.ProcessKeyboard(UPWARD, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// activate the mouse camera control only if the toggle is turned on.
	if (camera.IsActiveCameraToggle)
	{
	    if (firstMouse)
	    {
	        lastX = (GLfloat) xpos;
	        lastY = (GLfloat) ypos;
	        firstMouse = false;
	    }

	    GLfloat xoffset = (GLfloat) xpos - lastX;
	    GLfloat yoffset = lastY - (GLfloat) ypos; // Reversed since y-coordinates go from bottom to top
	    lastX = (GLfloat) xpos;
	    lastY = (GLfloat) ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	} else {
		// set up for the ray casting calculation which projects a ray through the camera
		// and to the point clicked in the window (specified by xpos, ypos)
		printf("\nMouse position -- x: %f     y: %f",xpos, ypos);	// print mouse click location if the camera is disabled
		float x = (float)((2.0f * xpos) / WIDTH - 1.0f);
		float y = (float)(1.0f - (2.0f * ypos) / HEIGHT);
		float z = (float)(1.0f);
		glm::vec3 ray_nds = glm::vec3 (x, y, z);									// normalized device coords
		glm::vec4 ray_clip = glm::vec4 (ray_nds.x, ray_nds.y, -1.0, 1.0);			// homogeneous clip coords (reverse the z-direction)
		glm::vec4 ray_eye = glm::inverse (camera.GetProjectionMatrix()) * ray_clip;	// eye camera coordinates
		ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
		glm::vec4 ray_wor_temp = (glm::inverse (camera.GetViewMatrix()) * ray_eye);	// 4D world coordinates
		glm::vec3 ray_wor = glm::normalize(glm::vec3(ray_wor_temp.x, ray_wor_temp.y, ray_wor_temp.z));
		printf("\nRay Cast Vector -- length: %f -- x: %f   y: %f   z: %f", glm::length(ray_wor), ray_wor.x, ray_wor.y, ray_wor.z); 
		printf("\nCamera Position -- x: %f   y: %f   z: %f", camera.Position.x, camera.Position.y, camera.Position
			.z); 

//		glm::vec3 intersect_point = ray_intersect_plane(camera.Position, ray_wor, X_PLANE);
//		printf("\nX-plane intersect -- x: %f   y: %f   z: %f", intersect_point.x, intersect_point.y, intersect_point.z); 
//		intersect_point = ray_intersect_plane(camera.Position, ray_wor, Y_PLANE);
//		printf("\nY-plane intersect -- x: %f   y: %f   z: %f", intersect_point.x, intersect_point.y, intersect_point.z); 
		
		// The intersect plane can be converted between XY (Z=0), YZ (X=0), and XZ (Y=0) current options.
		glm::vec3 intersect_point = ray_intersect_plane(camera.Position, ray_wor, gridLine->GetPlane());
		printf("\nZ-plane intersect -- x: %f   y: %f   z: %f", intersect_point.x, intersect_point.y, intersect_point.z); 

		cursor->SetRayCast(ray_wor);				// store the ray in the cursor

		// For a Z-Plane snap
		if(cursor->IsActiveCursorSnap)
		{
			GLfloat new_x;
			GLfloat new_y;
			GLfloat new_z;

			// These checks set the new coordinate to 0.0 if its snap value is 0
			if (cursor->GetSnap().x == 0)
				new_x = 0.0;
			else
				new_x = intersect_point.x-fmod(intersect_point.x, cursor->GetSnap().x);

			if (cursor->GetSnap().y == 0)
				new_y = 0.0;
			else
				new_y = intersect_point.y-fmod(intersect_point.y, cursor->GetSnap().y);

			if (cursor->GetSnap().z == 0)
				new_z = 0.0;
			else
				new_z = intersect_point.z-fmod(intersect_point.z, cursor->GetSnap().z);

			/*printf("\nSnapValue: x:%f	y:%f	z:%f ",cursor->GetSnap().x,cursor->GetSnap().y,cursor->GetSnap().z);   
			printf("\n-- x: %f    y: %f    z: %f", new_x, new_y, new_z);*/
			// store the intersect point rounded down to the nearest snap value
			cursor->SetWorldCoords(glm::vec3(new_x, new_y, new_z)); 
		} else 
		{
			// store the intersect point with the specified plane from the ray-cast
			cursor->SetWorldCoords(intersect_point);
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// activate the mouse camera control only if the toggle is turned on.
	if (camera.IsActiveCameraToggle)
	    camera.ProcessMouseScroll((GLfloat)yoffset);
}