#ifndef _ModelManager_H
#define _ModelManager_H


#include <GL\glew.h>					// Used for the OpenGL types like GLuint  
#include <GLFW/glfw3.h> 

// forward declarations
struct VolumeInfo;			// found in Volume.h
class Volume;				// found in Volume.h

struct ModelInfo
{
	GLuint VolumeID;						// unique identifier for a volume
	VolumeInfo *MemberVolume;			// store a pointer to a linked list containing the meshes that make up a volume
	//To determine the orientation of a volume within the model
	GLfloat TanVect[3];				// a tangent vector for the orientation of a member volume
	GLfloat NormVect[3];			// a normal vector for the orientation of a member volume 
	GLfloat BinormVect[3];			// a binormal vector for the orientation of a member volume

	// To determine the orientation and position of a volume within the overall model 
	// This would be considered this as global coords)
	// Pt has three coords (x, y, z) and Vect has three unit vectors <i, j, k>
	GLfloat VolInserPt[3];
	GLfloat VolTanVect[3];			// a tangent vector for the orientation of this volume
	GLfloat VolNormVect[3];			// a normal vector for the orientation of this volume
	GLfloat VolBinormVect[3];		// a binormal vector for the orientation of this volume

	ModelInfo *next;				// linked list parameter
	ModelInfo *previous;			// linked list parameter
};

class ModelManager
{
public:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	ModelManager();	// constructor

	struct ModelInfo *ModelMemberInfo;		// a linked list to the model members handled by the manager

	void Initialize();	// initializes the model manager



	void CreateModel();	// Create a model.  The entry into the Volume and Mesh classes

	void AddModel();	// add a member to the model list
	void SearchModel(); // search for a model in the ModelMemberInfo linked list

	void AddVolume();	// add a volume to the ModelInfo linked list.
	void SearchVolume();

	// Drawing array objects and methods for VAO, VBO, and EBO
	// IDEA:
	// Potentially consolidate these into one generic method for handling linked lists?
	void CreateVAO();	// creates the VAO for a specific model;
	void DeleteVAO();	// delete a VAO for the specific model;
	void FindVAO();		// finds a created VAO to speed up the creation process
	void CreateVBO();	// creates the VBO for a drawing;
	void DeleteVBO();	// delete a VBO for the model
	void FindVBO();		// finds a created VBO to speed up drawing process
	void CreateEBO();	// creates the EBO from the volume / mesh data
	void DeleteEBO();	// delete the EBO for the volume
	void FindEBO();		// finds a created EBO

	void RenderModel();	// renders the model

	void Destroy();		// destroy the model manager
};

#endif //_ModelManager_H