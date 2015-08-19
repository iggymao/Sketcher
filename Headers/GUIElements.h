#ifndef GUIELEMENTS_H
#define GUIELEMENTS_H

// GL Includes
#include <GL\glew.h>									// Used for the OpenGL types like GLuint

// GLM Mathematics
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Headers/DrawingShapes.h"					// includes our drawing shape information

const unsigned int NUM_BUTTONS = 10;		// number of buttons on the HUD

// Types of controls
const int GUI_CONTROL_UNDEFINED = 0;
const int GUI_CONTROL_BUTTON = 0;

// forward declaration
//glm::vec3 PixeltoScreenCoords(glm::ivec3 pixel_coords, GLuint width, GLuint height);	   // from pixel to screen coords
//glm::ivec3 ScreentoPixelCoords(glm::vec3 screen_coords, GLuint width, GLuint height);   // from screen to pixel coords
//const GLuint HEIGHT, WIDTH;

class CGUIElementButton : public CRectangle
{
public:
	// default constructors
	CGUIElementButton(glm::vec3 button_dims, glm::vec3 model_pos, glm::vec3 model_unit_rot, glm::vec3 model_euler) 
		: CRectangle(button_dims.x, button_dims.y, model_pos, model_unit_rot, model_euler)
	{	
		GUIElementID = next_element_id();
		this->button_width = button_dims.x;
		this->button_ht = button_dims.y;

	}    
	// for constructing a rectangular button that isn't default
	CGUIElementButton(GLfloat width, GLfloat height, glm::vec3 model_pos, glm::vec3 model_unit_rot, glm::vec3 model_euler) 
		: CRectangle(width, height, model_pos, model_unit_rot, model_euler)
	{
		GUIElementID = next_element_id();
		this->button_width = width;
		this->button_ht = height;
	}  
	~CGUIElementButton() {;}		// destructor 

	/* Methods */
	void Draw();					// Draws the button
	void SetButtonCornerPts();		// Extracts the vertex data for the corner points of the button
	void ShowButtonCornerPts();		// Display the corner points	
	void SetButtonHt(GLfloat height) {this->button_ht = height;}
	GLfloat GetButtonHt() {return this->button_ht;}
	void SetButtonWidth(GLfloat width) {this->button_width = width;}
	GLfloat GetButtonWidth() {return this->button_width;}
	glm::vec4 GetColor() {return this->Color;}
	void SetColor(glm::vec4 color) {this->Color = color;}
	GLint GetGUIElementID() {return GUIElementID;}					// retrieves the Mesh's ID number

	/* Members */
	//	static const GLuint draw_type = GL_TRIANGLES;
	static GLuint next_element_id(){  next_id++; 	return next_id;	} 	// to obtain the next mesh number

	GLfloat xmin;
	GLfloat ymin;
	GLfloat xmax;
	GLfloat ymax;

private:
	GLint GUIElementID;			// A number to reference the meshID once they are created
	static GLuint next_id;

	static const GLuint element_type = GUI_CONTROL_BUTTON;		// type of element
	vector<glm::vec3> CornerPts;

	GLfloat button_ht;			// button dimensions
	GLfloat button_width;		// button dimensions
	glm::vec4 Color;			// RGBA colors
};

class CGUILayoutHUD 
{
public:
	CGUILayoutHUD(GLuint win_width, GLuint win_height);			// default constructor
	~CGUILayoutHUD() {;}		// destructor

	/* Methods */
	void Draw(Shader shader);
	void OnClick(GLuint button_id, GLfloat mouse_x, GLfloat mouse_y);
//	glm::vec3 PixeltoScreenCoords(glm::ivec3 pixel_coords, GLuint width, GLuint height);
//	glm::ivec3 ScreentoPixelCoords(glm::vec3 screen_coords, GLuint width, GLuint height);

	/* Members */
	vector<CGUIElementButton*> GUIMembers;
	glm::vec3 next_insert_point;		// stores the next insert point for a GUI element in screen coords
	glm::vec3 next_pixel_insert_point;  // stores the next insert point for a GUI element in pixel coords

	GLuint WinHt;
	GLuint WinWidth;
	GLfloat WinAspectRatio;

	// default button dimensions
	glm::vec3 pixel_button_dims;	// button dimensions (in pixels) -- (width, height, thick(not used = 0) )
	glm::vec3 button_dims;			// button width measured in screen coords
	glm::vec3 pixel_button_gap;	// gap measured in pixels between adjacent buttons (x, y, z)
	glm::vec3 button_gap;			// gap measured in screen coords

};

#endif 