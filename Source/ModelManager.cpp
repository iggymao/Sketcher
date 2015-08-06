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
#include "../Headers/DrawingShapes.h"

//#include "../utils/MathUtils.h"			// generic math functions

class Mesh;			// forward declaration

void ModelManager::Initialize(int type)
{
	// If its an AISC model, we don't need to initialize the data as that is down in the AISC constructor already
	//if(type == MODEL_LOAD_AISC)
	//	return;

	/*
	this->aisc_data.aisc_label = "Undefined";
	this->aisc_data.depth = -1;						
	this->aisc_data.flange_width = -1;				
	this->aisc_data.flange_thick = -1;				
	this->aisc_data.web_thick = -1;
	this->aisc_data.length = 0;

	Mesh2::draw_type = GL_TRIANGLES; 
	*/
}

ModelManager::ModelManager(int model_type)
{
	printf("\nModel Manager constructor...");
	switch(model_type)
	{
		case MODEL_LOAD_MODEL:
		{
			Initialize(model_type);			// call the default constructor to preload the data thats not needed
			printf("\nLoading model...");
			loadModel();
			break;
		}
		case MODEL_LOAD_GRID:
		{
			// Not currently used
			printf("\nNON-FUNCTIONAL: Loading grid case...");
			break;
		}
		case MODEL_LOAD_COORDSYS:
		{
			printf("\nLoading coordinate system...");
			break;
		}
		//case MODEL_LOAD_AISC:
		//{
			//printf("\nLoading an AISC shape...");
			//loadAISC();
			break;
		//}
		default:
		{
			printf("\nUnknown model type...");
			break;
		}
	}
}

// for AISC shapes.  Will read the aisc_shape string and then lookup the relevant dimensions.  For now it just loads a default set of data
ModelManager::ModelManager(std::string aisc_shape)
{
	/*
	// we'll need to rewrite this function to load data from a database...but to test for now
	this->aisc_data.aisc_label = aisc_shape;
	this->aisc_data.depth = 10.0f/12.0f;						
	this->aisc_data.flange_width = 8.0f/12.0f;				
	this->aisc_data.flange_thick = 0.25f/12.0f;				
	this->aisc_data.web_thick = 0.1875f/12.0f;
	this->aisc_data.length = 96.0f/12.0f;

	loadAISC();  // calls the aisc shape creation function now that the aisc_shape is declared and the data is loaded
	*/
}

// Draws all the meshes known by the model
void ModelManager::Draw()
{
	//printf("\nDrawing from within ModelManager");
	for(GLuint i=0; i < this->meshes.size(); i++)
	{
//		printf("\nmeshes.size(): %i",meshes.size());
		this->meshes[i]->Draw();
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

// This is the routine to load a model, whether it be from a basic format as current
// or for future loads from a more expansive system such as ASSIMP or Blender or 3DSMax
// For now it just loads a cube.
void ModelManager::processMesh()
{
	GLfloat red = 1.0f;
	GLfloat green = 0.67f;
	GLfloat blue = 0.33f;
	// Data for a default unit cube sentered at (0,0,0)
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

		Mesh2 *newmesh = new Mesh2(face_vertices, face_indices, face_textures, draw_type);
	    this->meshes.push_back(newmesh);
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

// routine to create a standard AISC shape.  For now it does a simple I-beam shape.
// With a quick swap of vertices, Z, C, WT, and other sections can be quickly drawn.
// As of 8/3/15, routine does not draw fillets or allow for more detailed refinement.
/*
void ModelManager::loadAISC() 
{
	printf("\nLoading the AISC data");
	
	GLfloat len = 1;
	GLfloat d = 1;
	GLfloat bf = .1;
	GLfloat tf = .1;
	GLfloat tw = .1;
	GLfloat web_ht = (GLfloat)(d-2.0*tf);
	//GLfloat len = this->aisc_data.length;
	//GLfloat d = this->aisc_data.depth;
	//GLfloat bf = this->aisc_data.flange_width;
	//GLfloat tf = this->aisc_data.flange_thick;
	//GLfloat tw = this->aisc_data.web_thick;
	//GLfloat web_ht = (GLfloat)(d-2.0*tf);

	GLfloat red = 0.5f;
	GLfloat green = 0.5f;
	GLfloat blue = 0.5f;

	// Data for a default unit cube sentered at (0,0,0)
	// Set up vertex data (and buffer(s)) and attribute pointers
	//        Coords						Colors		                Texture			    Normals
 	//    X      Y      Z  ||			R      G      B    Alpha  ||  TextU  TextV || LightX LightY LightZ
	 GLfloat vertex_data[] = {
		 // For the start end
		 0.0f,	 0.0f,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //0
		-0.5*tw, 0.0f,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //1
		-0.5*tw, 0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //2
		-0.5*bf, 0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //3
		-0.5*bf, 0.5*d,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //4
		-0.5*tw, 0.5*d,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //5
		 0.0f,	 0.5*d,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //6
		 0.5*tw, 0.5*d,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //7
 		 0.5*bf, 0.5*d,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //8
		 0.5*bf, 0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //9
		 0.5*tw, 0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //10
 		 0.5*tw, 0.0f,		 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //11
		 0.5*tw, -0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //12
 		 0.5*bf, -0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //13
 		 0.5*bf, -0.5*d,	 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //14
		 0.5*tw, -0.5*d,	 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //15
		 0.0f,	 -0.5*d,	 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //16	 
	 	-0.5*tw, -0.5*d,	 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //17
		-0.5*bf, -0.5*d,	 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //18
		-0.5*bf, -0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //19
		-0.5*tw, -0.5*web_ht, 0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //20

		// for the far end
		 0.0f,	 0.0f,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //21
		-0.5*tw, 0.0f,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //22
		-0.5*tw, 0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //23
		-0.5*bf, 0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //24
		-0.5*bf, 0.5*d,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //25
		-0.5*tw, 0.5*d,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //26
		 0.0f,	 0.5*d,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //27
		 0.5*tw, 0.5*d,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //28
 		 0.5*bf, 0.5*d,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //29
		 0.5*bf, 0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //30
		 0.5*tw, 0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //31
 		 0.5*tw, 0.0f,		 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //32
		 0.5*tw, -0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //33
 		 0.5*bf, -0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //34
 		 0.5*bf, -0.5*d,	 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //35
		 0.5*tw, -0.5*d,	 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //36
		 0.0f,	 -0.5*d,	 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //37	 
	 	-0.5*tw, -0.5*d,	 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //38
		-0.5*bf, -0.5*d,	 -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //39
		-0.5*bf, -0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //40
		-0.5*tw, -0.5*web_ht, -0.5*len,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //41

	 };

	 GLuint indexes[] = {
		// for the start end
		0, 2, 1,   
		0, 10, 2,
		0, 11, 10,
		2, 4, 3,
		2, 5, 4,
		2, 6, 5,
		2, 10, 6,
		6, 10, 7,
		7, 10, 8,
		8, 10, 9,
		0, 1, 20,
		0, 20, 12,
		0, 12, 11,
		12, 14, 13,
		12, 15, 14,
		12, 16, 15,
		12, 20, 16,
		16, 20, 17,
		17, 20, 18,
		18, 20, 19,
		// for the far end
		21, 22, 23,
		21, 23, 31,
		21, 31, 32,
		23, 24, 25,
		23, 25, 26,
		23, 26, 27,
		23, 27, 31,
		27, 28, 31,
		28, 29, 31,
		31, 29, 30,
		21, 41, 22,
		21, 33, 41,
		21, 32, 33,
		33, 34, 35,
		33, 35, 36,
		33, 36, 37,
		37, 38, 41,
		38, 39, 41,
		39, 40, 41,
		// side elements
		1, 23, 22,
		1, 2,  23,
		2, 24, 23,
		2, 3,  24,
		3, 25, 24,
		3, 4,  25,
		4, 26, 25,
		4, 5,  26,
		5, 27, 26,
		5, 6,  27,
		6, 28, 27,
		6, 7,  28,
		7, 29, 28,
		7, 8,  29,
		8, 30, 29,
		8, 9,  30,
		9, 31, 30,
		9, 10, 31,
		10, 32, 31,
		10, 11, 32,
		11, 33, 32,
		11, 12, 33,
		12, 34, 33,
		12, 13, 34,
		13, 35, 34,
		13, 14, 35,
		14, 36, 35,
		14, 15, 36,
		15, 37, 36,
		15, 16, 37,
		16, 38, 37,
		16, 17, 38,
		17, 39, 38,
		17, 18, 39,
		18, 40, 39,
		18, 19, 40,
		19, 41, 40,
		19, 20, 41,
		20, 22, 41,
		20, 1,  22, 
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
		 }

			 //printf("\nArray:  %i,  id: %i",k,face_textures[k].id);
			 //printf("\nArray:  %i,  path: %s",k,face_textures[k].path.c_str());
		
		Mesh2 *newmesh = new Mesh2(face_vertices, face_indices, face_textures, draw_type);
	    this->meshes.push_back(newmesh);
	 }
}
*/