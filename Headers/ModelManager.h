
#ifndef _ModelManager_H
#define _ModelManager_H

#include <vector>

#include <GL\glew.h>					// Used for the OpenGL types like GLuint  
#include <GLFW/glfw3.h> 

#include "../Headers/Mesh.h"
#include "../Headers/Shader.h"

const int MODEL_LOAD_MODEL		= 0;		// an integer to tell the model manager to load a model (for now its a cube)
const int MODEL_LOAD_GRID		= 1;		// NOT CURRENTLY USED:  an integer to tell the model manager to create a grid system
const int MODEL_LOAD_COORDSYS	= 2;		// an integer to tell the model manager to create the coordinate symbols
//const int MODEL_LOAD_AISC		= 3;		// a qualifier to tell the model manager it needs to create an AISC shape.

// forward declarations


/*
struct ModelInfo
{
	GLuint VolumeID;						// unique identifier for a volume
//	VolumeInfo *MemberVolume;			// store a pointer to a linked list containing the meshes that make up a volume
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
*/

class ModelManager : public Mesh2
{
public:
	ModelManager(){;}								// default constructor
	ModelManager(int model_type);					// constructor
	ModelManager(std::string aisc_shape);			// constructor for the AISC shape

	ModelManager(const ModelManager & rhs) { ;}		// copy constructor
	~ModelManager() { ;}							// destructor

	void Initialize(int model_type);			// to initialize data for the modelmanager
	void Draw();								// draws the model, and thus all its meshes

	void SaveModelFile() {;}					// Saves the model data
	void ReadModelFile() {;}					// Reads a model file
	void CreateCalculationData() {;}			// Converts the drawing data to the formats needed to perform our calculations

// this needs to be private / protected
public:
	/* Model Data */
	vector<Mesh2*> meshes;	// stores the known face meshes for this model
	vector<TextureData> textures_loaded;		// an array to record the loaded textures

	/* Functions */
	// Loads a model.  This method can be updated with a real image loader if needed
	void loadModel();		// load a model from source programs / prerendered mesh info
	void processNode();		// Processes a node in a recursive fashion.  Processes each individual mesh at the node and repeats the process.
	void processMesh();		// Processes the mesh's data

	//	void loadGrid();		// loads a line segment to represent the grid system
	// void Destroy();		// destroy the model manager
};

#endif //_ModelManager_H