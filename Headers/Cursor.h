#ifndef _Cursor_H
#define _Cursor_H

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/DrawingShapes.h"
//#include "../Headers/ModelManager.h"
#include "../Headers/Mesh.h"
//#include "../Headers/Camera.h"

//forward declaration
//class Camera;		// forward declaration for our camera class
//class Shader;		// forward declaration for our shader class

class CCursor : public CDrawingObjects
{
public:
	// constructor
	CCursor(glm::vec3 world_coords)
	{ 
		SetWorldCoords(world_coords);
		SnapValueX = 0.5f;
		SnapValueY = 0.5f;
		SnapValueZ = 0.5f;

		IsActiveCursorSnap = false;
		draw_type = GL_TRIANGLES;

		MakeGridData();
		//meshes.push_back(MakeGridData());
		//CreateBoundingBox(this->meshes);
	}
	CCursor(const CCursor & rhs) { ;}		// copy constructor

	// deconstructor
	~CCursor() { 
		for(GLuint i=0;i<meshes.size();i++)
		{
			printf("\nDestroying cursor mesh #: %i",i);
			delete meshes[i];
			meshes[i]=0;			// set the meshes pointer to 0;
		}
	}						

//	GLuint draw_type;					// stores the draw_type GL_LINES, GL_TRIANGLES, etc.
	bool IsActiveCursorSnap;			// a bool to tell us the cursor snap is active

	void MakeGridData();				// create the data for the cursor model
	
	//void CreateBoundingBox(vector<Mesh2*> temp);			// creates a bounding box for the object based on the read in vertex data

	void Draw()
	{    
		// now Draw mesh
		for(GLuint i=0; i < this->meshes.size(); i++)
		{
	        glBindVertexArray(meshes[i]->VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(draw_type, meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		return;
	}

	// For storing the ray cast data into the screen
	void SetRayCast(glm::vec3 ray) {this->ray_cast = ray;}
	glm::vec3 GetRayCast() {return this->ray_cast;}

	// For handling the current coordinates of the cursor in World Space from calculations
	// and projection / view matrix inversion.  Currently in GraphicsManager.cpp.
	void SetWorldCoords(glm::vec3 coords) {this->WorldCoords = coords;}
	glm::vec3 GetWorldCoords() {return this->WorldCoords;}

	void SetSnapValues(GLfloat val1, GLfloat val2, int plane);  
	glm::vec3 GetSnap() {return glm::vec3(this->SnapValueX,this->SnapValueY,this->SnapValueZ);}
	
protected:
	//vector<Mesh2*> meshes;				// stores the known face meshes for this model
	//vector<glm::vec3> boundary;			// stores the six planes that define a cube around a drawing object

	GLfloat SnapValueX;					// a variable to store the snap value in X direction
	GLfloat SnapValueY;					// a variable to store the snap value in Y direction
	GLfloat SnapValueZ;					// a variable to store the snap value in Z direction

	glm::vec3 ray_cast;					// stores a casted ray to the mouse location through the camera.
	glm::vec3 WorldCoords;				// stores the coordinates of the cursor on he Z-plane of the drawing window
};

#endif