#ifndef GUIELEMENTS_H
#define GUIELEMENTS_H

// GL Includes
#include <GL\glew.h>									// Used for the OpenGL types like GLuint
#include "../Headers/DrawingShapes.h"					// includes our drawing shape information

const unsigned int NUM_BUTTONS = 10;		// number of buttons on the HUD

// Types of controls
const int GUI_CONTROL_UNDEINED = 0;
const int GUI_CONTROL_BUTTON = 0;

// default button dimensions
const GLfloat max_button_width = 0.15f;
const GLfloat max_button_ht = 0.10f;
const glm::vec3 button_gap = glm::vec3(0.03f, 0.03f, 0.0f);			// spacing between adjacent buttons (x, y, z)

class CGUIElementButton : public CRectangle
{
public:
	// default constructor
	CGUIElementButton(glm::vec3 model_pos, glm::vec3 model_unit_rot, glm::vec3 model_euler) 
		//: CRectangle(0.15f, 0.15f, model_pos, model_unit_rot, model_euler)
		: CRectangle(max_button_width, max_button_ht, model_pos, model_unit_rot, model_euler)
	{	
		this->button_width = max_button_width;
		this->button_ht = max_button_ht;
	}    

	CGUIElementButton(GLfloat width, GLfloat height, glm::vec3 model_pos, glm::vec3 model_unit_rot, glm::vec3 model_euler) 
		: CRectangle(width, height, model_pos, model_unit_rot, model_euler)
	{
		this->button_width = width;
		this->button_ht = height;
	}  

	// destructor
	~CGUIElementButton() {;}  

	// Draws the button
	void Draw() 
	{
		// now Draw mesh
		for(GLuint i=0; i < this->meshes.size(); i++)
		{
			//printf("------------------------------------");
			//printf("\n		Printing mesh #: %i",i);
			//printf("\n		   Button MeshID: %i", this->meshes[i]->GetMeshID());
			//printf("\n		   Button VAO #:  %i", this->meshes[i]->VAO);
			//printf("\n		   Button indices size #:  %i", this->meshes[i]->indices.size());
	        glBindVertexArray(this->meshes[i]->VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(CRectangle::draw_type, this->meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		return;
	}				

private:
	static const GLuint element_type = GUI_CONTROL_BUTTON;		// type of element
	GLfloat button_ht;			// button dimensions
	GLfloat button_width;		// button dimensions
//	glm::vec2 Position;			// insert pixel location (lower left corner)
	glm::vec4 Color;			// RGBA colors
};

class CGUILayoutHUD 
{
public:
	CGUILayoutHUD() 
	{
		this->next_insert_point = glm::vec3(-1.0f+button_gap.x, 1.0f-button_gap.y, 0.0f);
		printf("\nInsert point Initial:   x: %f    y: %f    z: %f",this->next_insert_point.x, this->next_insert_point.y, this->next_insert_point.z);

		for(unsigned int i = 0; i < NUM_BUTTONS; i++)
		{
			// Button1
			this->next_insert_point = this->next_insert_point - glm::vec3(0.0f, max_button_ht+button_gap.y, 0.0f);
			glm::vec3 model_pos = this->next_insert_point;
			printf("\nInsert point button #1:   x: %f    y: %f    z: %f",model_pos.x, model_pos.y, model_pos.z);
			//glm::vec3 model_pos = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 model_unit_rot = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 model_euler = glm::vec3(0.0f, 0.0f, 0.0f);
			CDrawingObjects *element = new CGUIElementButton(model_pos, model_unit_rot, model_euler);
			element->TranslateObjectData(model_pos);
			GUIMembers.push_back(element);
		}

		//// Button2
		//this->next_insert_point = this->next_insert_point - glm::vec3(0.0f, max_button_ht+button_gap.y, 0.0f);
		//glm::vec3 model_pos2 = this->next_insert_point;
		////glm::vec3 model_pos2 = glm::vec3(0.0f, 0.0f, 0.0f);
		//printf("\nInsert point button #2:   x: %f    y: %f    z: %f",model_pos2.x, model_pos2.y, model_pos2.z);
		//glm::vec3 model_unit_rot2 = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 model_euler2 = glm::vec3(0.0f, 0.0f, 0.0f);
		////CDrawingObjects *element2 = new CGUIElementButton(max_button_width, max_button_ht, model_pos2, model_unit_rot2, model_euler2);
		//CDrawingObjects *element2 = new CGUIElementButton(model_pos2, model_unit_rot2, model_euler2);
		//element2->TranslateObjectData(model_pos2);
		//GUIMembers.push_back(element2);
		//
		//for(unsigned int j=0; j < element2->meshes[0]->indices.size(); j++)
		//{
		//	printf("\nAfter returning:  x: %f   y: %f  z: %f", element2->meshes[1]->vertices[j].Position.x, element2->meshes[1]->vertices[j].Position.y, element2->meshes[1]->vertices[j].Position.z);
		//}

	}	// constructor
	~CGUILayoutHUD() {;}	// destructor

	glm::vec3 next_insert_point;		// stores the next insert point

	void Draw(GLfloat aspect, Shader shader)
	{
		shader.Use();		// turn on the shader

		// Camera/View transformation -- needed to match the original view and projection matrices for normal rendering
	    glm::mat4 view = glm::mat4();	// sets an identity matrix in view	
		glm::mat4 projection = glm::mat4();
		glm::mat4 model; 

		// Ortho projection    (-left, right,      -bottom,        top,          near,    far)
		projection = glm::ortho(-aspect, aspect, (GLfloat)-1.0f, (GLfloat)1.0f, -1.0f, 1.0f);		
//		model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 0.3f, 0.5f));

		// Get the uniform locations
	    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc  = glGetUniformLocation(shader.Program, "view");
		GLint projLoc  = glGetUniformLocation(shader.Program, "projection");
		//GLint HUDIDLoc  = glGetUniformLocation(HUDShader.Program, "HUDColor");
		
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//glm::mat4 model; = glm::mat4();  // sets an identity matrix into model
		//model = glm::translate(model, GUIMembers[i]->GetInsertPoint());  // translate (or set at the insertion point)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		for (unsigned int i = 0; i < this->GUIMembers.size(); i++)
		{
			model = glm::mat4();  // sets an identity matrix into model
			//printf("\n==========================================");
			//printf("\nPrinting GUI Member #: %i",i);
			GUIMembers[i]->Draw();
		}
	}

	vector<CDrawingObjects*> GUIMembers;
};
#endif 