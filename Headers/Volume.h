#ifndef _Volume_H
#define _Volume_H

// default volume shapes for mesh construction rules
#define VOLUME_UNDEFINED		-1						// an undeclared or undefined region (used for intialization)
#define VOLUME_PLANAR_REGION	0						// for a planar region
#define VOLUME_AREA				1						// for a defined 2D area such as triangle or square
#define VOLUME_RIGHT_PRISM		2						// for a right prism
#define VOLUME_PYRAMID			3						// for a pyramid
#define VOLUME_CONE				4						// for a cone
#define VOLUME_TETRAHEDRON		5						// for a tetrahedron
#define VOLUME_SPHERE			6						// for a sphere
#define VOLUME_SPIRAL			7						// for a spiral shape
#define VOLUME_OTHER_3D			8						// for other shapes
#define MAX_VOLUME_QTY			9						// Number of differents defined known by the application.  Used as a parameter for the MODEL array

#define MAX_VOL_MESHES 4			// the number of member meshes to hold in each volume

#include <GL/glew.h>  // for the GLuint, GLbool variable calls

//#include "../Headers/Main.h"

class Volume
{
public:
	GLuint VolumeID;							// stores the Volume ID
	GLuint VolumeType;							// stores the type of Volume as defined in Application.h
//	Mesh *MemberMesh[MAX_VOL_MESHES];			// array to hold pointers to the meshes used to create a volume (better to cast this into a std::vector container in the future)
	int NumMeshes;								// stores the number of meshes in this volume
	int NumVAO;									// stores the number of VAO needed by OpenGL
	int NumVBO;									// stores the number of VBO needed by OpenGL
	GLuint VolTargetWindow;						// stores the window # (as defined in Application.h) where this volume (and its meshes) will be drawn

	Volume();									// a constructor for the volume class
	~Volume() {};								// a destructor for the volume class

	void Initialize(int shape_code);			// Initialize the class using a simple shape parameter defined in application.h

//	void RenderVolume(AppWindow **p_array, GLuint **VolVBO_ID, GLuint **VolVAO_ID);		// Render the mesh members of the volume to the appropriate windows
//	void RenderVolume(int target_window, AppWindow **WinID_array);		// Render the mesh members of the volume to the appropriate windows

//	void Destroy();								// Destroys the member data

protected:
	GLuint *VolVBO_ID[MAX_VOL_MESHES];								// The VBO Id stored by the VAO
	GLuint *VolVAO_ID[MAX_VOL_MESHES];							// The VAO Id to bind when drawing

};

#endif