#include "stdafx.h"
#include <iostream>
//#include "../Headers/Main.h"
#include "../Headers/Mesh.h"
//#include "../Headers/Shader.h"
//#include "../Headers/Texture.h"
//#include "../Headers/SOIL.h"

//using namespace std;

//#include <fstream>
//bool fexists(const std::string& filename) {
//  ifstream ifile(filename.c_str());
//  return ifile != NULL;
//}

// A constructor for the mesh class.  Makes a simple triangle to ensure that the drawing buffer doesnt blow up unexpectedly.  We will
// use the RESERVE and RESIZE operators to modifiy to thecorrect sizes for different structures.
Mesh::Mesh()
{
	printf("\nMesh constructor called...");
	
	MeshVertexInfo = new VertexInfo;
	MeshVertexInfo->VertexID = -1;			// the vertex number
	MeshVertexInfo->x_pos=0.0f;				// x coord
	MeshVertexInfo->y_pos=0.0f;				// y coord
	MeshVertexInfo->z_pos=0.0f;				// z coord
	MeshVertexInfo->red=1.0f;				// red value (0-1)
	MeshVertexInfo->green=1.0f;				// green value (0-1)
	MeshVertexInfo->blue=1.0f;				// blue value (0-1)
	MeshVertexInfo->texture_u_coord=0.0f;	// texture coord., x dir (0-1)
	MeshVertexInfo->texture_v_coord=0.0f;	// texture coord., y dir (0-1)
	MeshVertexInfo->previous = NULL;
	MeshVertexInfo->next = NULL;
	// Since nothing is currently stored, the first and last members are pointed to the previous value (NULL);
	firstVertexInfo = MeshVertexInfo;		// point the first member to the previous value
	lastVertexInfo = MeshVertexInfo;		// point the last member to the previous value

	MeshIndexInfo = new IndexInfo;
	MeshIndexInfo->index_value = -1;		// default value to indicate an undefined index list
	MeshIndexInfo->next = NULL;				
	MeshIndexInfo->previous = NULL;
	// Since nothing is currently stored, the first and last members are pointed to the previous value (NULL);
	firstIndexInfo = MeshIndexInfo;		// point the first member to the previous value
	lastIndexInfo = MeshIndexInfo;		// point the last member to the previous value

	VertexNumber = -1;					// start with a VertexNumber of -1 to indicate no vertices created

	//g_vertex_buffer_data.resize(0);			// delete the previous default buffer
	//vertex_buffer_data.resize(0);
	//vertex_index_data.resize(0);

	//// declare a vertex buffer to contain 9 elements (a minimal triangle)
	//g_vertex_buffer_data.reserve(24);		// allocate 9 elements for the three nodes of a triangle
	//vertex_buffer_data.reserve(24);			// allocate 9 elements for the three nodes of a triangle
	//vertex_index_data.reserve(3);			// allocate 3 elements for the three indices of the nodes of a triangle

	//MeshSize = 24;

	//// Data for a simple triangle
	////1st node
	//vertex_buffer_data.push_back(0.5f);			// x-coord
	//vertex_buffer_data.push_back(-0.5f);			// y-coord
	//vertex_buffer_data.push_back(0.0f);				// z-coord
	//vertex_buffer_data.push_back(1.0f);				// red color
	//vertex_buffer_data.push_back(0.0f);				// green color
	//vertex_buffer_data.push_back(0.0f);				// blue color
	//vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
	//vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
	////2nd node
	//vertex_buffer_data.push_back(-0.5f);				// x-coord
	//vertex_buffer_data.push_back(-0.5f);			// y-coord
	//vertex_buffer_data.push_back(0.0f);				// z-coord
	//vertex_buffer_data.push_back(0.0f);				// red color
	//vertex_buffer_data.push_back(0.0f);				// green color
	//vertex_buffer_data.push_back(0.0f);				// blue color
	//vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
	//vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
	////3rd node
	//vertex_buffer_data.push_back(0.0f);				// x-coord
	//vertex_buffer_data.push_back(0.5f);				// y-coord
	//vertex_buffer_data.push_back(0.0f);				// z-coord
	//vertex_buffer_data.push_back(0.0f);				// red color
	//vertex_buffer_data.push_back(0.0f);				// green color
	//vertex_buffer_data.push_back(1.0f);				// blue color
	//vertex_buffer_data.push_back(0.5f);				// texture coordinate 1
	//vertex_buffer_data.push_back(1.0f);				// texture coordinate 2

	//vertex_index_data.push_back(0);
	//vertex_index_data.push_back(1);
	//vertex_index_data.push_back(2);


	//// Data for a simple triangle
	////1st node
	//g_vertex_buffer_data.push_back(-1.0f);
	//g_vertex_buffer_data.push_back(-1.0f);
	//g_vertex_buffer_data.push_back(0.0f);
	//g_vertex_buffer_data.push_back(1.0f);				// red color
	//g_vertex_buffer_data.push_back(0.0f);				// green color
	//g_vertex_buffer_data.push_back(0.0f);				// blue color
	//g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
	//g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
	////2nd node
	//g_vertex_buffer_data.push_back(1.0f);
	//g_vertex_buffer_data.push_back(-1.0f);
	//g_vertex_buffer_data.push_back(0.0f);
	//g_vertex_buffer_data.push_back(0.0f);				// red color
	//g_vertex_buffer_data.push_back(1.0f);				// green color
	//g_vertex_buffer_data.push_back(0.0f);				// blue color
	//g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
	//g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
	////3rd node
	//g_vertex_buffer_data.push_back(0.0f);
	//g_vertex_buffer_data.push_back(1.0f);
	//g_vertex_buffer_data.push_back(0.0f);
	//g_vertex_buffer_data.push_back(0.0f);				// red color
	//g_vertex_buffer_data.push_back(0.0f);				// green color
	//g_vertex_buffer_data.push_back(1.0f);				// blue color
	//g_vertex_buffer_data.push_back(0.5f);				// texture coordinate 1
	//g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
	//
	//TargetWindow = WINDOW_VIEW1;  // Default to the main window.  See application.h for the declarations.
	//MeshType = MESH_UNDEFINED;
	//TextureAlreadyLoaded = false;	// Tells the mesh that a texture is needed to be loaded on the intial render cycle.


}

void Mesh::Initialize()
{
	printf("\nInitializing Mesh...");
	GLuint node_num;
	node_num = AddMeshVertex(MeshVertexInfo, -0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f);
	AddMeshIndex(MeshIndexInfo, node_num);
	node_num = AddMeshVertex(MeshVertexInfo,  0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f);
	AddMeshIndex(MeshIndexInfo, node_num);
	node_num = AddMeshVertex(MeshVertexInfo,  0.0f,  0.6f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, -1.0f);
	AddMeshIndex(MeshIndexInfo, node_num);


	
}

GLuint Mesh::AddMeshVertex(VertexInfo *head, GLfloat x, GLfloat y, GLfloat z, GLfloat red, GLfloat green, GLfloat blue, GLfloat u, GLfloat v)
{
	printf("\nAdding vertex #%i to list.",VertexNumber+1);
	VertexInfo *newVertex = new VertexInfo;
	newVertex->VertexID = (VertexNumber+1);  // increment the vertex ID based on the current VertexNumber
	VertexNumber++;							 // then increment the counter for subsequent initializations

	newVertex->x_pos=x;				// x coord
	newVertex->y_pos=y;				// y coord
	newVertex->z_pos=z;				// z coord
	newVertex->red=red;				// red value (0-1)
	newVertex->green=green;				// green value (0-1)
	newVertex->blue=blue;				// blue value (0-1)
	newVertex->texture_u_coord=u;	// texture coord., x dir (0-1)
	newVertex->texture_v_coord=v;	// texture coord., y dir (0-1)
	newVertex->previous = NULL;
	newVertex->next = NULL;
	
	VertexInfo *curVertex = head;

	if (head->VertexID == -1)
	{
//		printf("\nAdding first shader..");
		MeshVertexInfo = newVertex;
		lastVertexInfo = newVertex;
		return newVertex->VertexID;
	}
	while (curVertex)
	{
		if(curVertex->next == NULL)
		{
			curVertex->next = newVertex;
			lastVertexInfo = curVertex->next;
			return newVertex->VertexID;
		}
		curVertex = curVertex->next;
	}
	return newVertex->VertexID;
}

void Mesh::AddMeshIndex(IndexInfo *head, int index_val)
{
	printf("\nAdding index value: %i to list.", index_val);
	IndexInfo *newIndex = new IndexInfo;

	newIndex->index_value=index_val;				// Next index to add
	newIndex->previous = NULL;
	newIndex->next = NULL;
	
	IndexInfo *curIndex = head;

	if (head->index_value == -1)
	{
		MeshIndexInfo = newIndex;
		lastIndexInfo = newIndex;
		return;
	}
	while (curIndex)
	{
		if(curIndex->next == NULL)
		{
			curIndex->next = newIndex;
			lastIndexInfo = curIndex->next;
			return;
		}
		curIndex = curIndex->next;
	}
	return;
}

void Mesh::ShowMeshVertexDetails(struct VertexInfo *head)
{
	printf("\nShow details of the vertex data.");

	VertexInfo *list = head;
	printf("\n===============================================================");
	printf("\nShowing details of the contents stored by the vertex details...");

	if (head->VertexID == -1)
	{
		printf("\n...No Vertex Info added at this time...");
		return;
	}

	while(list)
	{
		printf("\nVertex (node) ID:          %i ", list->VertexID);
		printf("\nVertex coords:           X=%f,   Y=%f,   Z=%f",list->x_pos, list->y_pos, list->z_pos);				// x coord
		printf("\nVertex colors:           R=%f,   G=%f,   B=%f",list->red, list->green, list->blue);	
		printf("\nVertex texture coords:   U=%f,   V=%f", list->texture_u_coord, list->texture_v_coord);	
		printf("\n---------------------------------------------------------------");
		list=list->next;
	}
	printf("\n===============================================================");
	return;
}

void Mesh::ShowMeshIndexDetails(struct IndexInfo *head)
{
	printf("\n===============================================================");
	printf("\nShow details of the index data.");
	IndexInfo *list = head;
	
	if (head->index_value == -1)
	{
		printf("\n...No Vertex Info added at this time...");
		return;
	}

	while(list)
	{
		printf("\nIndex value:  %i ", list->index_value);
		list=list->next;
	}
	printf("\n===============================================================");
	return;
}


//void Mesh::CreateMesh(int WinNum, int mesh_type, GLfloat param1, GLfloat param2, GLfloat param3)
//{
//	float width = param1;
//	float height = param2;
//	float depth = param3;
//
//	switch(mesh_type)
//	{
//		case MESH_TRIANGLE:
//		{
//			g_vertex_buffer_data.resize(0);			// delete the previous default buffer
//			vertex_buffer_data.resize(0);
//			vertex_index_data.resize(0);
//
//			g_vertex_buffer_data.reserve(24);		// allocate 9 elements for a triangle
//			vertex_buffer_data.reserve(24);			// allocate 9 elements for a triangle
//			vertex_index_data.reserve(3);			// allocate 3 elements for the three nodes of a triangle
//
//			MeshSize = 24;
//
//			// Data for a simple triangle
//			//////////////////////
//			//  Uses ELEMENT INDICES
//			//////////////////////
//			//1st node
//			vertex_buffer_data.push_back((GLfloat)-width);
//			vertex_buffer_data.push_back((GLfloat)height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(1.0f);				// red color
//			vertex_buffer_data.push_back(0.0f);				// green color
//			vertex_buffer_data.push_back(0.0f);				// blue color
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//2nd node
//			vertex_buffer_data.push_back((GLfloat)width);
//			vertex_buffer_data.push_back((GLfloat)height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(0.0f);				// red color
//			vertex_buffer_data.push_back(1.0f);				// green color
//			vertex_buffer_data.push_back(0.0f);				// blue color
//			vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//3rd node
//			vertex_buffer_data.push_back((GLfloat)0.0);
//			vertex_buffer_data.push_back((GLfloat)-height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(0.0f);				// red color
//			vertex_buffer_data.push_back(0.0f);				// green color
//			vertex_buffer_data.push_back(1.0f);				// blue color
//			vertex_buffer_data.push_back(0.5f);				// texture coordinate 1
//			vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//
//			vertex_index_data.push_back(0);
//			vertex_index_data.push_back(2);
//			vertex_index_data.push_back(1);
//			////////////////////////////////////
//
//			////////////////////////////////////
//			// Using vertex arrays
//			////////////////////////////////////
//			//1st node
//			g_vertex_buffer_data.push_back((GLfloat)-width);
//			g_vertex_buffer_data.push_back((GLfloat)height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(1.0f);				// red color
//			g_vertex_buffer_data.push_back(0.0f);				// green color
//			g_vertex_buffer_data.push_back(0.0f);				// blue color
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//2nd node
//			g_vertex_buffer_data.push_back((GLfloat)width);
//			g_vertex_buffer_data.push_back((GLfloat)height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(0.0f);				// red color
//			g_vertex_buffer_data.push_back(1.0f);				// green color
//			g_vertex_buffer_data.push_back(0.0f);				// blue color
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//3rd node
//			g_vertex_buffer_data.push_back((GLfloat)0.0);
//			g_vertex_buffer_data.push_back((GLfloat)-height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(0.0f);				// red color
//			g_vertex_buffer_data.push_back(0.0f);				// green color
//			g_vertex_buffer_data.push_back(1.0f);				// blue color
//			g_vertex_buffer_data.push_back(0.5f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//			///////////////////////////////////////
//			/*
//			// Data for a simple triangle
//			//1st node
//			g_vertex_buffer_data.push_back(-1.0f);
//			g_vertex_buffer_data.push_back(1.0f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//2nd node
//			g_vertex_buffer_data.push_back(1.0f);
//			g_vertex_buffer_data.push_back(1.0f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//3rd node
//			g_vertex_buffer_data.push_back(0.0f);
//			g_vertex_buffer_data.push_back(-1.0f);
//			g_vertex_buffer_data.push_back(0.0f);
//			*/
//
//			cout << "\nCreatingMesh() Triangle...";
//			break;
//		}
//		case MESH_SQUARE:
//		{
//			g_vertex_buffer_data.resize(0);			// delete the previous default buffer
//			vertex_buffer_data.resize(0);			// delete the previous default buffer
//			vertex_index_data.resize(0);			// delete the previous default buffer
//
//			g_vertex_buffer_data.reserve(48);		// allocate 18 elements for two triangle
//			vertex_buffer_data.reserve(32);		// allocate 12 elements for the four nodes of a square
//			vertex_index_data.reserve(6);		// allocate 6 elements for indices of the two triangles comprising the square
//
//			MeshSize=36;
//
//			// Data for a simple square
//			//////////////////////
//			//  Uses ELEMENT INDICES
//			//////////////////////
//			//1st node
//			vertex_buffer_data.push_back((GLfloat)-0.5*width);
//			vertex_buffer_data.push_back((GLfloat)-0.5*height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(1.0f);				// red color
//			vertex_buffer_data.push_back(0.0f);				// green color
//			vertex_buffer_data.push_back(0.0f);				// blue color
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//2nd node
//			vertex_buffer_data.push_back((GLfloat)-0.5*width);
//			vertex_buffer_data.push_back((GLfloat)0.5*height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(0.0f);				// red color
//			vertex_buffer_data.push_back(1.0f);				// green color
//			vertex_buffer_data.push_back(0.0f);				// blue color
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//			//3rd node
//			vertex_buffer_data.push_back((GLfloat)0.5*width);
//			vertex_buffer_data.push_back((GLfloat)0.5*height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(0.0f);				// red color
//			vertex_buffer_data.push_back(0.0f);				// green color
//			vertex_buffer_data.push_back(1.0f);				// blue color
//			vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//			//4th node
//			vertex_buffer_data.push_back((GLfloat)0.5*width);
//			vertex_buffer_data.push_back((GLfloat)-0.5*height);
//			vertex_buffer_data.push_back((GLfloat)depth);
//			vertex_buffer_data.push_back(1.0f);				// red color
//			vertex_buffer_data.push_back(0.0f);				// green color
//			vertex_buffer_data.push_back(0.0f);				// blue color
//			vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//
//			//Triangle #1 indices (CCW order)
//			vertex_index_data.push_back(0);
//			vertex_index_data.push_back(2);
//			vertex_index_data.push_back(1);
//			// Triangle #2 indices (CCW order)
//			vertex_index_data.push_back(0);
//			vertex_index_data.push_back(3);
//			vertex_index_data.push_back(2);
//			////////////////////////////////////
//
//			////////////////////////////////////
//			// Using vertex arrays
//			////////////////////////////////////
//			//1st node
//			g_vertex_buffer_data.push_back((GLfloat)-0.5*width);
//			g_vertex_buffer_data.push_back((GLfloat)-0.5*height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(1.0f);				// red color
//			g_vertex_buffer_data.push_back(0.0f);				// green color
//			g_vertex_buffer_data.push_back(0.0f);				// blue color
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//2nd node
//			g_vertex_buffer_data.push_back((GLfloat)0.5*width);
//			g_vertex_buffer_data.push_back((GLfloat)0.5*height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(0.0f);				// red color
//			g_vertex_buffer_data.push_back(1.0f);				// green color
//			g_vertex_buffer_data.push_back(0.0f);				// blue color
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//			//3rd node
//			g_vertex_buffer_data.push_back((GLfloat)-0.5*width);
//			g_vertex_buffer_data.push_back((GLfloat)0.5*height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(0.0f);				// red color
//			g_vertex_buffer_data.push_back(0.0f);				// green color
//			g_vertex_buffer_data.push_back(1.0f);				// blue color
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//			//4th vertex
//			g_vertex_buffer_data.push_back((GLfloat)-0.5*width);
//			g_vertex_buffer_data.push_back((GLfloat)-0.5*height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(1.0f);				// red color
//			g_vertex_buffer_data.push_back(0.0f);				// green color
//			g_vertex_buffer_data.push_back(0.0f);				// blue color
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//5th vertex
//			g_vertex_buffer_data.push_back((GLfloat)0.5*width);
//			g_vertex_buffer_data.push_back((GLfloat)-0.5*height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);
//			g_vertex_buffer_data.push_back(0.0f);				// red color
//			g_vertex_buffer_data.push_back(1.0f);				// green color
//			g_vertex_buffer_data.push_back(0.0f);				// blue color
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(0.0f);				// texture coordinate 2
//			//6th vertex
//			g_vertex_buffer_data.push_back((GLfloat)0.5*width);
//			g_vertex_buffer_data.push_back((GLfloat)0.5*height);
//			g_vertex_buffer_data.push_back((GLfloat)depth);	
//			g_vertex_buffer_data.push_back(0.0f);				// red color
//			g_vertex_buffer_data.push_back(0.0f);				// green color
//			g_vertex_buffer_data.push_back(1.0f);				// blue color
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 1
//			g_vertex_buffer_data.push_back(1.0f);				// texture coordinate 2
//			/*
//			// Data for a simple triangle
//			//1st node
//			g_vertex_buffer_data.push_back(-0.6f);
//			g_vertex_buffer_data.push_back(-0.6f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//2nd node
//			g_vertex_buffer_data.push_back(0.6f);
//			g_vertex_buffer_data.push_back(0.6f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//3rd node
//			g_vertex_buffer_data.push_back(-0.6f);
//			g_vertex_buffer_data.push_back(0.6f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//4th vertex
//			g_vertex_buffer_data.push_back(-0.6f);
//			g_vertex_buffer_data.push_back(-0.6f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//5th vertex
//			g_vertex_buffer_data.push_back(0.6f);
//			g_vertex_buffer_data.push_back(-0.6f);
//			g_vertex_buffer_data.push_back(0.0f);
//			//6th vertex
//			g_vertex_buffer_data.push_back(0.6f);
//			g_vertex_buffer_data.push_back(0.6f);
//			g_vertex_buffer_data.push_back(0.0f);	
//			*/
//			cout << "\nCreateMesh(): Square...";
//			break;
//		}
//		default:  // uses the default constructor from Mesh::Mesh()
//			break;
//	}
//	TargetWindow = WinNum;			// WinNum not currently used.  Target window is set by Model.cpp declaration
//	MeshType = mesh_type;
//	cout << "\nMESH CREATED:  MeshType: " << MeshType << " targetting window #: " << TargetWindow << endl;
//	return;
//}
//// Initialize the model with vertices, length, and the vertex and fragment shader files
////void Mesh::Initialize(Vertex3 vertices[], int length, std::string strVertex, std::string strFragment)
//void Mesh::Initialize(AppWindow **p_array, Mesh **MemberMesh, int num_mesh )
//{
///*
//	printf("\nInitializing mesh...");
//	GLFWwindow *Window;
//
//// Probably need a malloc() call here instead.
//	Mesh *MyMesh[3];				// A pointer to the Mesh class
//	for(int mesh_count=0; mesh_count<num_mesh; mesh_count++)
//	{
//		MyMesh[mesh_count] = (*(MemberMesh+mesh_count));
//
//		int i = MyMesh[mesh_count]->TargetWindow;
//		cout << "\nTargetting window #: " << TargetWindow << endl;
//
//		Window = (*(p_array+i))->GetWindow();
//
//	// Make sure the window is valid, if not, throw an error.
//		if ( Window == nullptr )
//		{
//			fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
//			DestroyMesh();
//			return;
//		}
//	}
//*/
//
//}
//
//// This is the function that will actually render the model to the backbuffer, usually every frame
//// if called in the GameLoop() function in Main.cpp.  **p_array is a pointer to the Windows stored in AppWindow.
////void Mesh::RenderMesh(AppWindow **WinID_array, Mesh **MemberMesh, int num_mesh, int num_VAO, int num_VBO)
//void Mesh::RenderMesh(Mesh **MemberMesh)
//{
//	printf("\nRender the mesh...");
//
////// Probably need a malloc() call here instead.
//	Mesh *MyMesh;				// A pointer to the Mesh class
//	MyMesh = (*(MemberMesh));
//
//	/////////////////////////////////////////////////////
//	//  Shader Stuff.  Currently all meshes use the same shader located in the /Shaders/ folder
//	// given by the strVertexFile and strFragmentFile
//	/////////////////////////////////////////////////////
//	strVertexFile = "Shaders/Shader.vertex";				// the vertex shader file location
//	strFragmentFile = "Shaders/Shader.fragment";			// the fragment shader file location
//	
//	//Test if the vertex shader file exists
//	if (!fexists(strVertexFile))
//		cout << "\nVertex shader file does not exist.  Check the file name in: " << strVertexFile;
//
//	//Test is the fragment shader file exists
//	if (!fexists(strFragmentFile))
//		cout << "\nFragment shader file does not exist.  Check the file name in: " << strFragmentFile;
//
//	Shader.Initialize(strVertexFile, strFragmentFile);			// initialize the shades.  StrVertexFile is the name of the vertex shader, strFragmentFile is the name of the fragment shader. 
////	Texture.Initialize();										// initializes the texture(s)
//	////////////////////////////////////////////////
//	//  End Shader programs Loading and Binding
//	////////////////////////////////////////////////
//
//	int num_VAO = 1;							// establishes 1 VAO (qty of VAO variables) -- Change this for multiple shaders if necessary
//	int num_VBO	= 1;							// establishes 1 VBO (qty of VBO variables) -- Change this for multiple buffers if necessary
//	int num_EBO = 1;
//	GLuint VertexArrayID[1];				// declare the VAO array
//	GLuint VertexBufferID[1];				// declare the VBO array
//	GLuint ElementBufferID[1];				// declare the EBO array (element buffer array) object for use with the indices.
//
//			
//	// Setup the VAO and VBO for the mesh
//	// current sets up 1 VAO or VBO -- might need more
//	glGenVertexArrays(num_VAO, VertexArrayID);					// Create the VAO
//	glGenBuffers(num_VBO, VertexBufferID);						// Create the VBO
//	glGenBuffers(num_EBO, ElementBufferID);						// Create the EBO
//	
//	for (int VAO_count=0;VAO_count<num_VAO;VAO_count++)
//	{
//		int VBO_count = VAO_count;  // A counter for the number of VBO arrays.  Assumed the same as VAO count
//		int EBO_count = VAO_count;
//		GLuint texture1;
//
//		// Stores the VAO and VBO data into their respective arrays
//		glBindVertexArray(VertexArrayID[VAO_count]);						
//		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID[VBO_count]);
//
//		// uses the vertex array (non indexed method)
//		// glBufferData(GL_ARRAY_BUFFER, (MyMesh->MeshSize)*sizeof(GLfloat), &(MyMesh->g_vertex_buffer_data).front(), GL_STATIC_DRAW);
//
//		// uses the vertex and indices methods
//		glBufferData(GL_ARRAY_BUFFER, (MyMesh->vertex_buffer_data).size()*sizeof(GLfloat), &(MyMesh->vertex_buffer_data).front(), GL_STATIC_DRAW);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferID[VAO_count]);
//	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (MyMesh->vertex_index_data).size()*sizeof(GLuint), &(MyMesh->vertex_index_data).front(), GL_STATIC_DRAW);
////		cout << "\nMyMesh->vertex_buffer_data.size()" << MyMesh->vertex_buffer_data.size();
////		cout << "\nMyMesh->vertex_index_data.size()" << MyMesh->vertex_index_data.size();
//		//getchar();
//
//		glVertexAttribPointer
//		(
//			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//			3,                  // size
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			8*sizeof(GLfloat),				// stride offset -- 3coords, 3rgb, 2text glfloat
//			//			0,                  
//			(GLvoid*)0
//			//			(void*)0            // array buffer offset
//		);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer
//		(
//			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//			3,                  // size
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			8*sizeof(GLfloat),				// stride offset -- 3coords, 3rgb, 2text glfloat
//			//			0,                  
//			(GLvoid*)(3 * sizeof(GLfloat))  // array buffer offset (because there are three GFLoat vertices.  Will need to adjust this if an alpha value is present.
//			//			(void*)0            // array buffer offset
//		);
//		glEnableVertexAttribArray(1);
//		// The texture attribute pointer
//		glVertexAttribPointer
//		(
//			2, 
//			2, 
//			GL_FLOAT,
//			GL_FALSE, 
//			8 * sizeof(GLfloat), 
//			(GLvoid*)(6 * sizeof(GLfloat))
//		);
//		glEnableVertexAttribArray(2); 
//
//		glBindVertexArray(0);				// unbind the VAO
//
////		if(!TextureAlreadyLoaded)
////		{
//			///////////////////////////////////
//		    // Load and create a texture 
//			//////////////////////////////////
//		    glGenTextures(1, &texture1);
//			glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
//			// Set the texture wrapping parameters
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//			// Set texture filtering parameters
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			// Load image, create texture and generate mipmaps
//			int width, height;
//			unsigned char* image = SOIL_load_image("Textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//			glGenerateMipmap(GL_TEXTURE_2D);
//			SOIL_free_image_data(image);
////			glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
//			////////////////////////////////
//			// End Loading Texture
//			////////////////////////////////
//			TextureAlreadyLoaded = true;
////		}
//
//		////////////////////////////////////////////////////////
//		//  Drawing the VAO with shaders etc.
//		////////////////////////////////////////////////////////
//		// Draw the first array object (will need an array for multiple objects)
//		// Now when we want to draw the first array object, we use the appropriate fragment shader	
//
////        // Bind Texture
////        glBindTexture(GL_TEXTURE_2D, texture);
//
//		Shader.TurnOn();											// turns on the shader.
//
//		
//		//		Texture.TurnOn();											// turns on the texture mapper.
//		///////////////////////////////////////////////
//		// TIME CHANGING GREEN COLOR STUFF
//		///////////////////////////////////////////////
///*
//		// sets a time changing color scheme into our shader.
//		Shader.timeValue = (GLfloat)glfwGetTime();
////		cout << "\nTime value: " << Shader.timeValue;
//		Shader.greenValue = (GLfloat)((sin(Shader.timeValue) / 2) + 0.5);
////		cout << "\ngreenValue: " << Shader.greenValue;
//		Shader.vertexColorLocation = Shader.GetVariable("ourColor");
////		cout << "\nvertexColorLocation: " << Shader.vertexColorLocation << "    greenvalue: " << Shader.greenValue;
//		glUniform4f(Shader.vertexColorLocation, 0.0f, Shader.greenValue, 0.0f, 1.0f); // passes the variables to the shader program
//*/
//
//
//        // Bind Textures using texture units
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//		Texture.textureLocation1 = Shader.GetVariable("ourTexture1");
//	    glUniform1i(Texture.textureLocation1, 0);
////        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
///*
//		// Used for extra textures
//		//glActiveTexture(GL_TEXTURE1);
//        //glBindTexture(GL_TEXTURE_2D, texture2);
//        //glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);
//*/
//
//		//////////////////////////////////////////////
//		// MATRIX TRANSFORMATION STUFF
//		//////////////////////////////////////////////
//		// Create transformations
//        glm::mat4 transform;
//        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
//        transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
//
//        // Get matrix's uniform location and set matrix
//        Shader.transformLocation = Shader.GetVariable("transform");
//        glUniformMatrix4fv(Shader.transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
//		///////////////////////////////////////////////
//		// End transform stuff
//		///////////////////////////////////////////////
//
//      //  // Bind Texture
//		glBindVertexArray(VertexArrayID[VAO_count]);			// bind the VAO
//
//		// Uses the vertex array method
////		glDrawArrays(GL_TRIANGLES, 0, (MyMesh->MeshSize / 3) ); 	// Draw the shape ! 3 indices per triangle starting at 0 -> 1 triangle
//		// Uses the vertex and indices method
//		glDrawElements(GL_TRIANGLES, (MyMesh->vertex_index_data.size()), GL_UNSIGNED_INT, 0);
//
//		glBindVertexArray(0);										// clear the VBO
//		glDisableVertexAttribArray(0);								// clear the VAO
//		Shader.TurnOff();											// turns off the current shader so subsequent renders don't utilize a wrong shader.
//	}  // end for loop
//
//
//	return;
//
//
//
/////// TEST CODE FOR DRAWING TWO OBJECTS TO ONE SCREEN. WORKS!!
///*
//	    // Set up vertex data (and buffer(s)) and attribute pointers
//    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
//    GLfloat firstTriangle[] = {
//        -0.9f, -0.5f, 0.0f,  // Left 
//        -0.0f, -0.5f, 0.0f,  // Right
//        -0.45f, 0.5f, 0.0f,  // Top 
//    };
//    GLfloat secondTriangle[] = {
//         0.0f, -0.5f, 0.0f,  // Left
//         0.9f, -0.5f, 0.0f,  // Right
//         0.45f, 0.5f, 0.0f   // Top 
//    };
//    GLuint VBOs[2], VAOs[2];
//    glGenVertexArrays(2, VAOs); // We can also generate multiple VAOs or buffers at the same time
//    glGenBuffers(2, VBOs);
//    // ================================
//    // First Triangle setup
//    // ===============================
//    glBindVertexArray(VAOs[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
//    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
//    // ================================
//    // Second Triangle setup
//    // ===============================
//    glBindVertexArray(VAOs[1]);	// Note that we bind to a different VAO now
//    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// And a different VBO
//    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
//    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
//
//    // Game loop
////    while (!glfwWindowShouldClose(window))
////    {
//        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
//        glfwPollEvents();
//
//        // Render
//        // Clear the colorbuffer
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Activate shader (same shader for both triangles)
// //       glUseProgram(shaderProgram);
//        // Draw first triangle using the data from the first VAO
//        glBindVertexArray(VAOs[0]);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        // Then we draw the second triangle using the data from the second VAO
//        glBindVertexArray(VAOs[1]);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glBindVertexArray(0);
//
//        // Swap the screen buffers
//        glfwSwapBuffers(Window);
//getchar();
////    }
//    // Properly de-allocate all resources once they've outlived their purpose
//    glDeleteVertexArrays(2, VAOs);
//    glDeleteBuffers(2, VBOs);
//    // Terminate GLFW, clearing any resources allocated by GLFW.
////    glfwTerminate();
//*/
//}
//
//
//// This handles all the cleanup for our model, like the VBO/VAO buffers and shaders.
//void Mesh::DestroyMesh()
//{
//	printf("\nDestroying mesh...");
//
//	// If we have a valid vertex buffer, reset it's binding, delete it and clear the property
//	if (VertexBufferID)
//	{
//		printf("\nDestroying VertexBuffer...");
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glDeleteBuffers(1, &VertexBufferID);		// deletes the VBO
//		VertexBufferID = 0;
//	}
//
//	// If we have a valid vertex array, reset it's binding, delete it and clear the property
//	if (VertexArrayID)
//	{
//		printf("\nDestroying VertexArray...");
//		glBindVertexArray(0);
//		glDeleteVertexArrays(1, &VertexArrayID);	// Deletes the VAO
//		VertexArrayID = 0;
//	}
//
////	// If we have a valid shader program, delete it
////	if (programID)
////	{
////		printf("\nDestroying VertexArray...");
////		glDeleteProgram(programID);						// Deletes the shader program
////		programID = 0;
////	}
//	
//	// Be sure to stop pointing to the camera object
////	Camera = nullptr;
//
//	// Release the memory for the compiled shaders
////	Shader.Destroy();
//}