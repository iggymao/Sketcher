#ifndef _Mesh_H
#define _Mesh_H

#define GLM_FORCE_RADIANS								// Make sure GLM is using radians instead of degrees

#include <GL\glew.h>									// Used for the OpenGL types like GLuint

//#include <stdio.h>										// Used for fprintf and stderr
//#include <stdlib.h>										// Used for the exit() function
//#include <glm\glm.hpp>									// Used for the GLM math library
//#include <glm/gtc/matrix_transform.hpp>					// Used for the GLM math library
//#include <glm/gtx/transform2.hpp>						// Used for the GLM math library
//#include <glm/gtc/type_ptr.hpp>							// Used for the GLM math library

//#include "Shader.h"										// Used for loading and running our shaders
//#include "Texture.h"
//#include "Camera.h"										// *NEW* Used to get access to the view and projection matrices
//#include <vector>

//using namespace std;
//using namespace glm;


// This is our custom class to store attributes for a vertex like the x,y,z values.
//class Vertex3
//{
//public:
//
//	float xyz[3];										// The x,y,z position
//	float rgba[4];										// The r,g,b,a (Red, Green, Blue, Alpha) color values
//};

struct VertexInfo
{
	GLuint VertexID;	// the vertex number

	GLfloat x_pos;		// x coord
	GLfloat y_pos;		// y coord
	GLfloat z_pos;		// z coord
	
	GLfloat red;		// red value (0-1)
	GLfloat green;		// green value (0-1)
	GLfloat blue;		// blue value (0-1)

	GLfloat texture_u_coord;	// texture coord., x dir (0-1)
	GLfloat texture_v_coord;	// texture coord., y dir (0-1)

	VertexInfo *previous;		// link to the previous element
	VertexInfo *next;			// link to the next element
};

struct IndexInfo
{
	GLuint index_value;
	IndexInfo *previous;		// link to the previous element
	IndexInfo *next;			// link to the next element
};

// The Mesh class to handle initializing, rendering and destroying of a 3D object
class Mesh
{
public:
	GLuint MeshID;						// Stores an ID for the mesh
	GLuint MeshType;					// Stores the type of Mesh as defined in Application.h
	GLuint VertexNumber;				// Stores the last Vertex number

	VertexInfo *MeshVertexInfo;			// a linked list to the vertex information for a specific node
	VertexInfo *firstVertexInfo;		// point the first member to the previous value
	VertexInfo *lastVertexInfo;		// point the last member to the previous value

	IndexInfo *MeshIndexInfo;			// a linked list to the index information for the nodal connectivity
	IndexInfo *firstIndexInfo;			// point the first member to the previous value
	IndexInfo *lastIndexInfo;		// point the last member to the previous value

	Mesh();								// mesh constructor
	~Mesh() {Destroy();}				// mesh deconstructor

	void Initialize();		// initialize a mesh member

	// adds a new VertexInfo to the MeshVertexInfo linked list returning the automatically generated NODE number
	// to be used in the AddMeshIndex parameter?
	// This will need a better method, but is functional for preliminary testing.
	GLuint AddMeshVertex(VertexInfo *head, GLfloat x, GLfloat y, GLfloat z, GLfloat red, GLfloat green, GLfloat blue, GLfloat u, GLfloat v);	
	void AddMeshIndex(IndexInfo *head, int index_val);	// adds a new IndexInfo to the MeshIndexInfo linked list 

	void ShowMeshVertexDetails(VertexInfo *head);
	void ShowMeshIndexDetails(IndexInfo *head);
	//	vector<GLfloat> vertex_data;		// create a vector to store the vertex information
//	vector<GLfloat> vertex_buffer_data; // create a vector of g_vertex_buffer_data to store the vertex data in a std::vector container
//	vector<GLuint> vertex_index_data;	// create a vector for the index data in a std::vector container.

	std::string strVertexFile;			// The name of the shader file to be used with the associated mesh
	std::string strFragmentFile;		// The name of the fragment file to be used with the associated mesh
	std::string strTextureFile;

	void Destroy();
	//	int TargetWindow;					// Target window for the rendering
//
//	vector<GLfloat> g_vertex_buffer_data;   // create a vector of g_vertex_buffer_data to store the vertex data in a std::vector container
//	

//	// to create a Mesh in a specific window (WindowNum) and of a particular type (as defined in Mesh.h);
//	// param1:  width of the object
//	// param2:  height of the object
//	// param3:  depth of the object
//	void CreateMesh(int WindowNum, int ObjectType, GLfloat param1, GLfloat param2, GLfloat param3);		
//	int MeshSize;			// stores the number of meshes that make up the volume
//
//	bool TextureAlreadyLoaded;
//	// These are created to standardize the index properties used for vertex properties.
//	static const GLuint kVertexIndex = 0;				// This is for the x,y,z vertices
//	static const GLuint kColorIndex = 1;				// This is for the r,g,b,a colors
//	static const GLuint kTextureIndex = 2;				// This is for the u,v texture coordinates
//	static const GLuint kNormalIndex = 3;				// This is for the x,y,z normals
//
//
//	// Set the scale of our mesh to 100% by default
//	Mesh();  // the default constructor will create a simple triangle of 3 nodes (9 elements)
//	//Mesh()		{ Scale = vec3(1.0f, 1.0f, 1.0f); }
//
//	~Mesh()	{ DestroyMesh(); }
//
//	// Takes in a list of x,y,z vertices and vertex length to create the VBO and VAO's from,
//	// as well as the text file locations for the vertex and fragment shaders to load.
////	void Initialize(Vertex3 vertices[], int length, std::string strVertex, std::string strFragment);
////	void Initialize(AppWindow **WinID_array, Mesh **MemberMesh, int num_mesh );
//
//	// This draws the Mesh to the backbuffer
////	void RenderMesh(AppWindow **WinID_array, Mesh **MemberMesh, int num_mesh, int num_VAO, int num_VBO);
////	void RenderMesh(Mesh **MemberMesh);
//
//	// Create the getter and setters for the mesh's position
////	vec3 GetPosition() { return Position; }
////	void SetPosition(vec3 position) { Position = position; }
//
//	// Create the getter and setters for the mesh's rotation
////	vec3 GetRotation() { return Rotation; }
////	void SetRotation(vec3 rotation) { Rotation = rotation; }
//
//	// Create the getter and setters for the mesh's scale
////	vec3 GetScale() { return Scale; }
////	void SetScale(vec3 scale) { Scale = scale; }
//
//	// This cleans up the VBO and VAO's
////	void DestroyMesh();
//
////protected:
//
//	Vertex3 *Vertices;									// The list of the vertices
////	GLint VerticesLength;								// The length of the vertices
////	GLuint VertexBufferID;								// The VBO Id stored by the VAO
////	GLuint VertexArrayID;								// The VAO Id to bind when drawing
//
////	vec3 Position;										// The mesh's position
////	vec3 Rotation;										// The mesh's rotation
////	vec3 Scale;											// The mesh's scale
//
//	// Our shader object to initialize and run the shaders
//	Shader Shader;
//
//	// Our texture object to initialize and run the texture routines
//	Texture Texture;
};

#endif
