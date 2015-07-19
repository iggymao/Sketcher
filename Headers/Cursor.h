#ifndef _Cursor_H
#define _Cursor_H

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/ModelManager.h"
#include "../Headers/Mesh.h"
#include "../Headers/Camera.h"


//forward declaration
class Camera;		// forward declaration for our camera class
class Shader;		// forward declaration for our shader class

class Cursor
{
public:
	// constructor
	Cursor(glm::vec3 world_coords){ 
		this->SetWorldCoords(world_coords);
	}

	void SetRayCast(glm::vec3 ray) {ray_cast = ray;}
	glm::vec3 GetRayCast() {return this->ray_cast;}

	void SetWorldCoords(glm::vec3 coords) {this->WorldCoords = coords;}
	glm::vec3 GetWorldCoords() {return this->WorldCoords;}

	void loadCursor();					// loads the graphic for the cursor
	void DrawCursor(int width, int height, Shader shader, Camera camera, int draw_type);  // draws the model, and thus all its meshes.

private:
	vector<Mesh> meshes;				// stores the known face meshes for this model

	glm::vec3 ray_cast;					// stores a casted ray to the mouse location through the camera.
	glm::vec3 WorldCoords;		// stores the coordinates of the cursor on he Z-plane of the drawing window
//	ModelManager modelmanager;			// stores the model information for the cursor

	
};

#endif