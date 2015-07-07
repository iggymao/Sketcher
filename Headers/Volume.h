#ifndef _Volume_H
#define _Volume_H

//// default volume shapes for mesh construction rules
//#define VOLUME_UNDEFINED		-1						// an undeclared or undefined region (used for intialization)
//#define VOLUME_PLANAR_REGION	0						// for a planar region
//#define VOLUME_AREA				1						// for a defined 2D area such as triangle or square
//#define VOLUME_RIGHT_PRISM		2						// for a right prism
//#define VOLUME_PYRAMID			3						// for a pyramid
//#define VOLUME_CONE				4						// for a cone
//#define VOLUME_TETRAHEDRON		5						// for a tetrahedron
//#define VOLUME_SPHERE			6						// for a sphere
//#define VOLUME_SPIRAL			7						// for a spiral shape
//#define VOLUME_OTHER_3D			8						// for other shapes
//#define MAX_VOLUME_QTY			9						// Number of differents defined known by the application.  Used as a parameter for the MODEL array

//#define MAX_VOL_MESHES 4			// the number of member meshes to hold in each volume

#include <GL/glew.h>  // for the GLuint, GLbool variable calls
#include "../Headers/Volume.h"
//#include "../Headers/Mesh.h"  // not used if forward declarations are functioning

// forward declarations
struct VertexInfo;					// found in Mesh.h
class Mesh;							// found in Mesh.h

struct VolumeInfo
{
	GLuint MeshID;					// unique identifier for a member mesh
	VertexInfo *meshinfo;			// store a pointer to a linked list containing the meshes that make up a volume
	GLuint CurrentMeshNumber;					// start with a CurrentMeshNumber of -1 to indicate no meshes created

	//To determine the orientation and position of a mesh within the 
	//volume  (consider this as local coords)
	// Pt has three coords (x, y, z) and Vect has three unit vectors <i, j, k>
	GLfloat MeshInsertPt[3];
	GLfloat MeshTanVect[3];				// a tangent vector for the orientation of a member mesh
	GLfloat MeshNormVect[3];			// a normal vector for the orientation of a member mesh
	GLfloat MeshBinormVect[3];			// a binormal vector for the orientation of a member mesh

	VolumeInfo *next;					// linked list parameter
	VolumeInfo *previous;				// linked list parameter
};

struct VAO_obj
{
	GLuint VAO;
	GLfloat *points;
	GLuint size_VAO;
};

struct VBO_obj
{
	GLuint VBO;
	GLfloat *points;
	GLuint size_VBO;
};

class Volume
{
private:
	GLuint VolumeID;					// Stores an ID for the volume
	static GLuint next_id;
public:


//	GLuint MeshID;	
	GLuint GetVolumeID() {return VolumeID;}
	static GLuint next_volume_id(){	next_id++; 	return next_id;	} // to obtain the next mesh number
				
	VolumeInfo *MemberMesh;				// a linked list containing the information pertaining to the member meshes
	VolumeInfo *firstVolumeInfo;		// pointer to the first value of MemberMesh
	VolumeInfo *lastVolumeInfo;			// pointer to the last value of MemberMesh

	// Insertion point vector
	// Pt has three coords (x, y, z) and Vect has three unit vectors <i, j, k>
	GLfloat VolInserPt[3];
	GLfloat VolTanVect[3];				// a tangent vector for the orientation of this volume
	GLfloat VolNormVect[3];			// a normal vector for the orientation of this volume
	GLfloat VolBinormVect[3];			// a binormal vector for the orientation of this volume

	Volume();									// a constructor for the volume class
	~Volume() {};								// a destructor for the volume class

	void Initialize();			// Initialize the class using a simple shape parameter defined in application.h
	// adds a mesh to the MemberMesh linked list
	int AddMesh(Mesh *mesh, GLfloat x, GLfloat y, GLfloat z, GLfloat tan_i, GLfloat tan_j, GLfloat tan_k, GLfloat norm_i, GLfloat norm_j, GLfloat norm_k, GLfloat binorm_i, GLfloat binorm_j, GLfloat binorm_k);
	void ShowVolumeDetails(VolumeInfo *MemberMesh);
	void DeleteMesh();				// deletes a mesh to the MemberMesh linked list
	void SearchMesh();				// search the MemberMesh linked list for a particular member mesh

	void CreateVAO();			// create VAO
	void CreateVBO();			// create VBO
	void CreateEBO();			// create EBO

//	GLuint VolumeType;							// stores the type of Volume as defined in Application.h
////	Mesh *MemberMesh[MAX_VOL_MESHES];			// array to hold pointers to the meshes used to create a volume (better to cast this into a std::vector container in the future)
//	int NumMeshes;								// stores the number of meshes in this volume
//	int NumVAO;									// stores the number of VAO needed by OpenGL
//	int NumVBO;									// stores the number of VBO needed by OpenGL
//	GLuint VolTargetWindow;						// stores the window # (as defined in Application.h) where this volume (and its meshes) will be drawn


//	void RenderVolume(AppWindow **p_array, GLuint **VolVBO_ID, GLuint **VolVAO_ID);		// Render the mesh members of the volume to the appropriate windows
//	void RenderVolume(int target_window, AppWindow **WinID_array);		// Render the mesh members of the volume to the appropriate windows

//	void Destroy();								// Destroys the member data

protected:
//	GLuint *VolVBO_ID[MAX_VOL_MESHES];								// The VBO Id stored by the VAO
//	GLuint *VolVAO_ID[MAX_VOL_MESHES];							// The VAO Id to bind when drawing

};

#endif