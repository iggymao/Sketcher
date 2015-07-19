#include "stdafx.h"
#include <iostream>
#include <vector>

// GL Includes
#include <GL\glew.h>									// Used for the OpenGL types like GLuint
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/Shader.h"
#include "../Headers/ModelManager.h"
#include "../Headers/Mesh.h"

//#include "../utils/MathUtils.h"			// generic math functions

class Mesh;			// forward declaration

ModelManager::ModelManager(int model_type)
{
	printf("\nModel Manager constructor...");
	switch(model_type)
	{
		case MODEL_LOAD_MODEL:
		{
			printf("\nLoading model...");
			loadModel();
			break;

		}
		case MODEL_LOAD_GRID:
		{
			loadGrid();
			printf("\nLoading grid...");
			break;
		}
		case MODEL_LOAD_COORDSYS:
		{
			printf("\nLoading coordinate system...");
			break;
		}
		default:
		{
			printf("\nUnknown model type...");
			break;
		}
	}
}

// Draws all the meshes known by the model
void ModelManager::Draw(Shader ourShader, int gl_drawtype)
{
	for(GLuint i=0; i < this->meshes.size(); i++)
	{
//		printf("\nmeshes.size(): %i",meshes.size());
		this->meshes[i].Draw(gl_drawtype);
	}
}

// Loads the data for drawing gridlines.
void ModelManager::loadGrid()
{
	// Set up vertex data (and buffer(s)) and attribute pointers
	//        Coords			     Colors		                Texture			    Normals
 	//    X      Y      Z  ||  R      G      B    Alpha  ||  TextU  TextV || LightX LightY LightZ

	// Note that the third data point is not used on a GL_LINE call, but is needed to avoid a seg. fault on the following routine
	GLfloat vertex_data[] = {
		-4.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		 0.0f,   0.0f,	  0.0f, 0.0f,  0.0f,
		+4.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f,		 0.0f,   0.0f,	  0.0f, 0.0f,  0.0f,
		 +2.0f, 0.0f, 2.0f,		0.0f, 0.0f, 0.0f, 1.0f,		 0.0f,   0.0f,	  0.0f, 0.0f,  0.0f
	};

	GLuint indexes[] =
	{
		0, 1, 2		// for a grid line only two points required.
	};

	string texture_files[] = {
		 "Textures/steel.jpg",
		 "Textures/Olaf.jpg"
	 };

	 // loop through the vertex data provided.  Note the "12" is the current number of elements in the data that
	 // are being processed.
	 int num_elems = 12;  // the current number of elements in the data

	 // Find the nodes related to the faces based upon connectivity indexes
	 // Loop through the index data.  Assumes three nodes per triangle for now
 	 int num_faceindex_elems = 3;		// the number of nodes per face
	 int f_max = (sizeof(indexes)/(num_faceindex_elems*sizeof(GLuint))); // computes the number of faces defined
	 printf("\nNumber of faces, f_max: %i", f_max);
	
	 vector<VertexData> face_vertices;			// stores the vertex data
	 // Loop once for each defined face
	 for(int f=0;f<f_max; f++)
	 {
		 //printf("\n=================================================================");
		 //printf("\nFace #: %i",f);
		 // =====  VERTEX DATA ========
		 VertexData face_vertex;
		 glm::vec3 A, B, C, vAB, vAC, normal_vec ;		// vectors for computing normals
		 face_vertices.resize(0);						// clear existing face_vertices vector
		 face_vertices.reserve(num_faceindex_elems);	// set the size of the vertices vector

		 GLuint face_node_number0 = (indexes[f*num_faceindex_elems+0]);  // node A from index
		 GLuint face_node_number1 = (indexes[f*num_faceindex_elems+1]);  // node B from index
		 GLuint face_node_number2 = (indexes[f*num_faceindex_elems+2]);  // node C# from index
		 
		 // For nodes A-B-C -- in that order for a triangular mesh
		 A = glm::vec3(vertex_data[(face_node_number0*num_elems+0)], vertex_data[(face_node_number0*num_elems+1)], vertex_data[(face_node_number0*num_elems+2)]);
		 B = glm::vec3(vertex_data[(face_node_number1*num_elems+0)], vertex_data[(face_node_number1*num_elems+1)], vertex_data[(face_node_number1*num_elems+2)]);
		 C = glm::vec3(vertex_data[(face_node_number2*num_elems+0)], vertex_data[(face_node_number2*num_elems+1)], vertex_data[(face_node_number2*num_elems+2)]);
		 vAB = B-A;						// position vector AB
		 vAC = C-A;						// position vector AC
		 normal_vec = glm::normalize(glm::cross(vAB,vAC));	// now compute vector AB x AC
		 //printf("\nCross Product --  x: %f   y: %f   z: %f",normal_vec.x, normal_vec.y, normal_vec.z);

//		 GLfloat temp_area = area_3P(A,B,C);
//		 printf("\nArea:  %f", temp_area);
//		 printf("\n0,0,-0.5f inside triangle? %b",point_inside_triangle(glm::vec3(0.0f,0.0f,-0.5f), A, B, C));

		 for(int k=0; k<num_faceindex_elems;k++) // loop through each of the index elements
		 {
			 GLuint face_node_number0 = (indexes[f*num_faceindex_elems+k]);  // node # from index
	 		 // record vertices for face nodes
			 face_vertex.Position = glm::vec3(vertex_data[(face_node_number0*num_elems+0)], vertex_data[(face_node_number0*num_elems+1)], vertex_data[(face_node_number0*num_elems+2)]);
			 // record colors for face nodes
			 face_vertex.Color = glm::vec4(vertex_data[(face_node_number0*num_elems+3)],vertex_data[(face_node_number0*num_elems+4)],vertex_data[(face_node_number0*num_elems+5)],vertex_data[(face_node_number0*num_elems+6)]);
			 // record texture coords for face nodes
			 face_vertex.TexCoords = glm::vec2(vertex_data[(face_node_number0*num_elems+7)], vertex_data[(face_node_number0*num_elems+8)]);
			 // record normal vectors for face nodes
//			 face_vertex.Normal = glm::vec3(vertex_data[(face_node_number0*num_elems+9)], vertex_data[(face_node_number0*num_elems+10)], vertex_data[face_node_number0*num_elems+11]);
			 face_vertex.Normal = glm::vec3(normal_vec.x, normal_vec.y, normal_vec.z);


			 face_vertices.push_back(face_vertex);			 // add the vertex to the end of the vertices vector

			 //printf("\nNode#: %i -- Vertex.Position.x: %f",face_node_number0, face_vertex.Position.x);
 			// printf("\nNode#: %i -- Vertex.Position.y: %f",face_node_number0, face_vertex.Position.y);
 			// printf("\nNode#: %i -- Vertex.Position.z: %f",face_node_number0, face_vertex.Position.z);
			 //printf("\nNode#: %i -- Vertex.Color.x: %f",face_node_number0, face_vertex.Color.x);
 			// printf("\nNode#: %i -- Vertex.Color.y: %f",face_node_number0, face_vertex.Color.y);
 			// printf("\nNode#: %i -- Vertex.Color.z: %f",face_node_number0, face_vertex.Color.z);
			 //printf("\nNode#: %i -- Vertex.TexCoords.x: %f",face_node_number0, face_vertex.TexCoords.x);
 			// printf("\nNode#: %i -- Vertex.TexCoords.y: %f",face_node_number0, face_vertex.TexCoords.y);
			 //printf("\nNode#: %i -- Vertex.Normal.x: %f",face_node_number0, face_vertex.Normal.x);
 			// printf("\nNode#: %i -- Vertex.Normal.y: %f",face_node_number0, face_vertex.Normal.y);
	 		// printf("\nNode#: %i -- Vertex.Normal.z: %f",face_node_number0, face_vertex.Normal.z);
			 //printf("\n-----------------------------------------");
		 }

		 // ====== INDEX DATA ======
		 //  Indices for each mesh will be 0, 1, 2 for a triangle, based on the order of the index_data (connectivity)
	 	 vector<GLuint> face_indices;			// stores the index data
		 face_indices.resize(0);				// clear an existing face_indices vector
		 face_indices.reserve(num_faceindex_elems);	// set the size of the indices
		 //printf("\n============== FACE INDEX POSITION ==============================");
		 for(int j=0; j<num_faceindex_elems;j++)
		 {
			 face_indices.push_back(j);
			 //printf("\nFace #: %i  -- Array:  %i,  indices: %i",f,j,j);
		 }

		 // ====== FRAGMENT DATA ======
		 // record textures
	 	 // Loop through the texture information (if present)
		 int k_max = (sizeof(texture_files)/sizeof(string));
		 vector<TextureData> face_textures;		// stores the texture data
		 face_textures.resize(0);				// clear previous face_texture arrays
		 face_textures.reserve(k_max);			// resize the array based on the number of elements
		 //printf("\n============== FACE TEXTURES ========================");
		 for (int k = 0; k < k_max; k++)
		 {
			 TextureData face_texture;
			 face_texture.id = k;
			 face_texture.path = texture_files[k];
			 face_textures.push_back(face_texture);

			 //printf("\nArray:  %i,  id: %i",k,face_textures[k].id);
			 //printf("\nArray:  %i,  path: %s",k,face_textures[k].path.c_str());
		}


		// Now create the mesh based on the data that has been read by calling the mesh constructor in mesh.h
		this->meshes.push_back(Mesh(face_vertices, face_indices, face_textures));
	 }
}

// Loads a model with supported extensions from programs such as ASSIMP (not currently installed)
void ModelManager::loadModel()
{
	this->processNode();	// needed for more elaborate model loading algorithms.  For now just forward through it
}

// Processes a node in a  recursive fashion.  Processes each mesh at a particular node and repeats the process, storing the data in "meshes" in our class definition.
void ModelManager::processNode()
{
//	this->meshes.push_back(this->processMesh());
	this->processMesh();
}

//  This is the routine to load a model, whether it be from a basic format as current
// or for future loads from a more expansive system such as ASSIMP or Blender or 3DSMax
void ModelManager::processMesh()
{
	GLfloat red = 1.0f;
	GLfloat green = 0.67f;
	GLfloat blue = 0.33f;
	// Set up vertex data (and buffer(s)) and attribute pointers
	//        Coords			     Colors		                Texture			    Normals
 	//    X      Y      Z  ||  R      G      B    Alpha  ||  TextU  TextV || LightX LightY LightZ
	 GLfloat vertex_data[] = {

		-0.5f, -0.5f, 0.5f,   red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //0
		 0.5f, -0.5f, 0.5f,   red,   green, blue,  1.0f,      0.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //1
         0.5f,  0.5f, 0.5f,   red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, 1.0f, //2
        -0.5f,  0.5f, 0.5f,   red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, 1.0f, //3

		-0.5f, -0.5f, -0.5f,  red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, -1.0f, //4
		 0.5f, -0.5f, -0.5f,  red,   green, blue,  1.0f,      0.0f, 0.0f,	  0.0f,  0.0f, -1.0f, //5
         0.5f,  0.5f, -0.5f,  red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, -1.0f, //6
        -0.5f,  0.5f, -0.5f,  red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, -1.0f  //7
    };

	 GLuint indexes[] = {
		0, 1, 2,   // Front
		0, 2, 3,
		5, 4, 7,   // Back
		5, 7, 6,
		4, 0, 3,   // Left
		4, 3, 7,
		1, 5, 6,   // Right
		1, 6, 2,
		3, 2, 6,   // Top
		3, 6, 7,
		1, 0, 4,   // Bottom
		1, 4, 5
	 };

	 string texture_files[] = {
		 "Textures/steel.jpg",
		 "Textures/Olaf.jpg"
	 };

	 // loop through the vertex data provided.  Note the "12" is the current number of elements in the data that
	 // are being processed.
	 int num_elems = 12;  // the current number of elements in the data

	 // Find the nodes related to the faces based upon connectivity indexes
	 // Loop through the index data.  Assumes three nodes per triangle for now
 	 int num_faceindex_elems = 3;		// the number of nodes per face
	 int f_max = (sizeof(indexes)/(num_faceindex_elems*sizeof(GLuint))); // computes the number of faces defined
	 printf("\nNumber of faces, f_max: %i", f_max);
	
	 vector<VertexData> face_vertices;			// stores the vertex data
	 // Loop once for each defined face
	 for(int f=0;f<f_max; f++)
	 {
		 //printf("\n=================================================================");
		 //printf("\nFace #: %i",f);
		 // =====  VERTEX DATA ========
		 VertexData face_vertex;
		 glm::vec3 A, B, C, vAB, vAC, normal_vec ;		// vectors for computing normals
		 face_vertices.resize(0);						// clear existing face_vertices vector
		 face_vertices.reserve(num_faceindex_elems);	// set the size of the vertices vector

		 GLuint face_node_number0 = (indexes[f*num_faceindex_elems+0]);  // node A from index
		 GLuint face_node_number1 = (indexes[f*num_faceindex_elems+1]);  // node B from index
		 GLuint face_node_number2 = (indexes[f*num_faceindex_elems+2]);  // node C# from index
		 
		 // For nodes A-B-C -- in that order for a triangular mesh
		 A = glm::vec3(vertex_data[(face_node_number0*num_elems+0)], vertex_data[(face_node_number0*num_elems+1)], vertex_data[(face_node_number0*num_elems+2)]);
		 B = glm::vec3(vertex_data[(face_node_number1*num_elems+0)], vertex_data[(face_node_number1*num_elems+1)], vertex_data[(face_node_number1*num_elems+2)]);
		 C = glm::vec3(vertex_data[(face_node_number2*num_elems+0)], vertex_data[(face_node_number2*num_elems+1)], vertex_data[(face_node_number2*num_elems+2)]);
		 vAB = B-A;						// position vector AB
		 vAC = C-A;						// position vector AC
		 normal_vec = glm::normalize(glm::cross(vAB,vAC));	// now compute vector AB x AC
		 //printf("\nCross Product --  x: %f   y: %f   z: %f",normal_vec.x, normal_vec.y, normal_vec.z);

//		 GLfloat temp_area = area_3P(A,B,C);
//		 printf("\nArea:  %f", temp_area);
//		 printf("\n0,0,0.5f inside triangle? %i",point_inside_triangle(glm::vec3(0.0f,0.0f,0.5f), A, B, C));

		 for(int k=0; k<num_faceindex_elems;k++) // loop through each of the index elements
		 {
			 GLuint face_node_number0 = (indexes[f*num_faceindex_elems+k]);  // node # from index
	 		 // record vertices for face nodes
			 face_vertex.Position = glm::vec3(vertex_data[(face_node_number0*num_elems+0)], vertex_data[(face_node_number0*num_elems+1)], vertex_data[(face_node_number0*num_elems+2)]);
			 // record colors for face nodes
			 face_vertex.Color = glm::vec4(vertex_data[(face_node_number0*num_elems+3)],vertex_data[(face_node_number0*num_elems+4)],vertex_data[(face_node_number0*num_elems+5)],vertex_data[(face_node_number0*num_elems+6)]);
			 // record texture coords for face nodes
			 face_vertex.TexCoords = glm::vec2(vertex_data[(face_node_number0*num_elems+7)], vertex_data[(face_node_number0*num_elems+8)]);
			 // record normal vectors for face nodes
//			 face_vertex.Normal = glm::vec3(vertex_data[(face_node_number0*num_elems+9)], vertex_data[(face_node_number0*num_elems+10)], vertex_data[face_node_number0*num_elems+11]);
			 face_vertex.Normal = glm::vec3(normal_vec.x, normal_vec.y, normal_vec.z);


			 face_vertices.push_back(face_vertex);			 // add the vertex to the end of the vertices vector

			 //printf("\nNode#: %i -- Vertex.Position.x: %f",face_node_number0, face_vertex.Position.x);
 			// printf("\nNode#: %i -- Vertex.Position.y: %f",face_node_number0, face_vertex.Position.y);
 			// printf("\nNode#: %i -- Vertex.Position.z: %f",face_node_number0, face_vertex.Position.z);
			 //printf("\nNode#: %i -- Vertex.Color.x: %f",face_node_number0, face_vertex.Color.x);
 			// printf("\nNode#: %i -- Vertex.Color.y: %f",face_node_number0, face_vertex.Color.y);
 			// printf("\nNode#: %i -- Vertex.Color.z: %f",face_node_number0, face_vertex.Color.z);
			 //printf("\nNode#: %i -- Vertex.TexCoords.x: %f",face_node_number0, face_vertex.TexCoords.x);
 			// printf("\nNode#: %i -- Vertex.TexCoords.y: %f",face_node_number0, face_vertex.TexCoords.y);
			 //printf("\nNode#: %i -- Vertex.Normal.x: %f",face_node_number0, face_vertex.Normal.x);
 			// printf("\nNode#: %i -- Vertex.Normal.y: %f",face_node_number0, face_vertex.Normal.y);
	 		// printf("\nNode#: %i -- Vertex.Normal.z: %f",face_node_number0, face_vertex.Normal.z);
			 //printf("\n-----------------------------------------");
		 }

		 // ====== INDEX DATA ======
		 //  Indices for each mesh will be 0, 1, 2 for a triangle, based on the order of the index_data (connectivity)
	 	 vector<GLuint> face_indices;			// stores the index data
		 face_indices.resize(0);				// clear an existing face_indices vector
		 face_indices.reserve(num_faceindex_elems);	// set the size of the indices
		 //printf("\n============== FACE INDEX POSITION ==============================");
		 for(int j=0; j<num_faceindex_elems;j++)
		 {
			 face_indices.push_back(j);
			 //printf("\nFace #: %i  -- Array:  %i,  indices: %i",f,j,j);
		 }

		 // ====== FRAGMENT DATA ======
		 // record textures
	 	 // Loop through the texture information (if present)
		 int k_max = (sizeof(texture_files)/sizeof(string));
		 vector<TextureData> face_textures;		// stores the texture data
		 face_textures.resize(0);				// clear previous face_texture arrays
		 face_textures.reserve(k_max);			// resize the array based on the number of elements
		 //printf("\n============== FACE TEXTURES ========================");
		 for (int k = 0; k < k_max; k++)
		 {
			 TextureData face_texture;
			 face_texture.id = k;
			 face_texture.path = texture_files[k];
			 face_textures.push_back(face_texture);

			 //printf("\nArray:  %i,  id: %i",k,face_textures[k].id);
			 //printf("\nArray:  %i,  path: %s",k,face_textures[k].path.c_str());
		}


		// Now create the mesh based on the data that has been read by calling the mesh constructor in mesh.h
		this->meshes.push_back(Mesh(face_vertices, face_indices, face_textures));
	 }

//	 //printf("\nSize of vertex data:  %i",sizeof(vertex_data));
//	 //printf("\nnum_elems:  %i", num_elems);
//	 //printf("\nsizeof(GLfloat): %i",sizeof(GLfloat));
//
//	 //printf("\nnum_elems*sizeof(GLfloat):  %i",num_elems*sizeof(GLfloat));
//	 //printf("\ni_max = %i:", (sizeof(vertex_data))/(num_elems*sizeof(GLfloat)));
//
//
//	 int i_max = (sizeof(vertex_data))/(num_elems*sizeof(GLfloat)); //  the number of vertex_data entries
//	 vector<VertexData> vertices;		// stores the vertex data
//	 vertices.reserve(i_max);
//	 for (int i = 0; i < i_max; i++)
//	 {
//	 	 VertexData vertex;
////		 vertex = new VertexData;
//		 // add the vertex coords
//		 vertex.Position = glm::vec3(vertex_data[(num_elems*i+0)], vertex_data[(num_elems*i+1)], vertex_data[(num_elems*i+2)]);
//		 //printf("\nElem#1: %f",vertex_data[(num_elems*i+0)]);
//		 //printf("\nVertex.Position: %f",vertex.Position.x);
//		 //printf("\nElem#1: %f",vertex_data[(num_elems*i+1)]);
// 		// printf("\nVertex.Position: %f",vertex.Position.y);
//		 //printf("\nElem#1: %f",vertex_data[(num_elems*i+2)]);
// 		// printf("\nVertex.Position: %f",vertex.Position.z);
//		 // add the vertex color data (RGBA)
//		 vertex.Color = glm::vec4(vertex_data[(num_elems*i+3)],vertex_data[(num_elems*i+4)],vertex_data[(num_elems*i+5)],vertex_data[(num_elems*i+6)]);
//
//		 // add the texture map coords U,V
//		 vertex.TexCoords = glm::vec2(vertex_data[(num_elems*i+7)], vertex_data[(num_elems*i+8)]);
//		 // add the light normal vectors
//		 // This part should be computed from the coordinate data and indices data.  For now, we'll just read it in from the sample data
//		 // But this really needs to be computed from the indices data directly.
//		 vertex.Normal = glm::vec3(vertex_data[(num_elems*i+9)], vertex_data[(num_elems*i+10)], vertex_data[num_elems*i+11]);
//	 	 // add the vertex to the end of the vertices vector
//		 vertices.push_back(vertex);
//
//		 //printf("\n==============VERTEX POSITION ==============================");
//		 //printf("\nSize of vertices: %i",vertices.size());
//	 	// printf("\nArray:  %i,  Position.x: %f",i,vertices[i].Position.x);
//		 //printf("\nArray:  %i,  Position.y: %f",i,vertices[i].Position.y);
//		 //printf("\nArray:  %i,  Position.z: %f",i,vertices[i].Position.z);
//	 }
//	 
//	 // Loop through the index data.  Assumes three nodes per triangle
// 	 int num_index_elems = 1;  // the current number of nodes per triangle
//	 int j_max = (sizeof(indexes)/(num_index_elems*sizeof(GLuint)));
//	 vector<GLuint> indices;			// stores the index data
//	 indices.reserve(j_max);	
//	 printf("\nj_max: %i", j_max);
//
//	 // recording the indices for the mesh
// 	 for (int j = 0; j < j_max; j++)
//	 {
//		 indices.push_back(indexes[j]);
//		 printf("\n============== INDEX POSITION ==============================");
//		 printf("\nArray:  %i,  indices: %i",j,indices[j]);
////		 IndexData index_load;
//		 // uses an ivec3 for integers
////		 index_load.id = 1000;
////		 index_load.Index_value = glm::ivec3(indexes[(num_index_elems*j+0)], indexes[(num_index_elems*j+1)], indexes[(num_index_elems*j+2)]);
////		 index_load.Index_value = glm::vec3(0,1,2);
//		 //index_load.id = 1000;
// 		 //index_load.Index_value.x = 10; 
// 		 //index_load.Index_value.y = 21; 
//  		 //index_load.Index_value.z = 32; 
//		 /*printf("\n================ INDEXES ============================");
//		 printf("\nArray:  %i,  indexes[(num_index_elems*j+0)]: %i",j,indexes[(num_index_elems*j+0)]);
//		 printf("\nArray:  %i,  indexes[(num_index_elems*j+1)]: %i",j,indexes[(num_index_elems*j+1)]);
//		 printf("\nArray:  %i,  indexes[(num_index_elems*j+2)]: %i",j,indexes[(num_index_elems*j+2)]);
//		 printf("\nArray:  %i,  index.Index_value.x: %i",j,index_load.Index_value.x);
//		 printf("\nArray:  %i,  index.Index_value.y: %i",j,index_load.Index_value.y);
//		 printf("\nArray:  %i,  index.Index_value.z: %i",j,index_load.Index_value.z);
//		 indices.push_back(index_load);
//		 printf("\n================ INDEXES ============================");
//		 printf("\nSize of indices: %i",indices.size());
//		 printf("\nArray:  %i,  index_value.id: %i",j,indices[j].id);
//		 printf("\nArray:  %i,  index_value.x: %i",j,indices[j].Index_value.x);
//		 printf("\nArray:  %i,  index_value.y: %i",j,indices[j].Index_value.y);
//		 printf("\nArray:  %i,  index_value.z: %i",j,indices[j].Index_value.z);*/
//	 }
//
//	 // Loop through the texture information (if present)
//
//	 int k_max = (sizeof(texture_files)/sizeof(string));
//	 vector<TextureData> textures;	// stores the texture data
//	 textures.reserve(k_max);
//	 for (int k = 0; k < k_max; k++)
//	 {
//		 TextureData texture;
//		 texture.id = k;
//		 texture.path = texture_files[k];
//		 textures.push_back(texture);
//		 printf("\n============== Textures ========================");
//		 printf("\nArray:  %i,  id: %i",k,textures[k].id);
//		 printf("\nArray:  %i,  path: %s",k,textures[k].path.c_str());
//	 }
//
//	 // Now create the mesh based on the data that has been read by calling the mesh constructor in mesh.h
////	 this->meshes.push_back(Mesh(vertices, indices, textures));

}