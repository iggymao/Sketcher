#include "stdafx.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

// GL Includes
#include <GL\glew.h>									// Used for the OpenGL types like GLuint
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/DrawingShapes.h"

#include "../utils/MathUtils.cpp"
// create the vertex_data, index_data, texture_data for the grid 
// creates a grid in the XZ plane for now

GLuint CDrawingObjects::next_id = -1;			// set the initial value at the start of the program


void CAisc::MakeGridData()
{
	printf("\nMaking vertex and index data for CAisc");		
	GLfloat len = this->aisc_data.length;
	GLfloat d = this->aisc_data.depth;
	GLfloat bf = this->aisc_data.flange_width;
	GLfloat tf = this->aisc_data.flange_thick;
	GLfloat tw = this->aisc_data.web_thick;
	GLfloat web_ht = (GLfloat)(d-2.0*tf);

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
		33, 37, 41,
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
		newmesh->parentID = this->GetDrawingObjID();
	    this->meshes.push_back(newmesh);
	 }
}

void CGrid::MakeGridData()
{
	plane = this->plane;
	GLfloat x_elev1, y_elev1, z_elev1;		// for storing our plane coordinates
	GLfloat x_elev2, y_elev2, z_elev2;		// for storing our plane coordinates

	//vector<VertexData> v_data;
	vertices.reserve(2*(this->qty_1+this->qty_2));	// reserve data for lines in both directions
	//vector<GLuint> i_data;
	indices.reserve(2*(this->qty_1+this->qty_2));
	//vector<TextureData> t_data;
	VertexData temp_vertex;
	temp_vertex.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // set the color black
	temp_vertex.TexCoords = glm::vec2(0.0f, 0.0f);			// default tex coords
	temp_vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);		// no normal for lighting
	
	GLfloat lower_1 = (GLfloat)(-0.5*(this->qty_1 * this->spacing_1));
	GLfloat lower_2 = (GLfloat)(-0.5*(this->qty_2 * this->spacing_2));
	GLuint last_index_end;
	
	// for x-direction
	for(unsigned int i = 0; i<(qty_1+1);i++)
	{
		switch(plane)
		{
			case YZ_PLANE:
			{
				x_elev1 = 0.0f;
				y_elev1 = lower_1;
				z_elev1 = lower_2+i*this->spacing_2;

				x_elev2 = 0.0f;
				y_elev2 = lower_1 + this->length_1;
				z_elev2 = lower_2+i*this->spacing_2;
				break;
			}
			case XZ_PLANE:
			{
				x_elev1 = lower_1;
				y_elev1 = 0.0f;
				z_elev1 = lower_2+i*this->spacing_2;
				
				x_elev2 = lower_1 + this->length_1;
				y_elev2 = 0.0f;
				z_elev2 = lower_2+i*this->spacing_2;
				break;
			}
			case XY_PLANE:
			{
				x_elev1 = lower_1;
				y_elev1 = lower_2+i*this->spacing_2;
				z_elev1 = 0.0f;

				x_elev2 = lower_1 + this->length_1;
				y_elev2 = lower_2+i*this->spacing_2;
				z_elev2 = 0.0f;

				break;
			}
			default:
			{
				x_elev1 = 0.0f;
				x_elev2 = 0.0f;
				y_elev1 = 0.0f;
				y_elev2 = 0.0f;
				z_elev1 = 0.0f;
				z_elev2 = 0.0f;
				printf("\nUndefined plane detected.  Must be XZ_PLANE, YZ_PLANE, or XY_PLANE.");
				return;
			}
		}
		//printf("\nx1: %f, y1: %f, z1: %f",x_elev1, y_elev1, z_elev1);
		//printf("\nx2: %f, y2: %f, z2: %f",x_elev2, y_elev2, z_elev2);


		//1st end point
		temp_vertex.Position = glm::vec3(x_elev1, y_elev1, z_elev1);
//		vdata.push_back(temp_vertex);
		vertices.push_back(temp_vertex);
		//2nd end point
		temp_vertex.Position = glm::vec3(x_elev2, y_elev2, z_elev2);
		vertices.push_back(temp_vertex);
		// set the indices (two points per line)
		indices.push_back(2*i);
		indices.push_back(2*i+1);
		last_index_end = 2*i+1;
	}

	last_index_end++;		// need to increment to continue the numbering for the other direction
	
	// for orthogonal direction
	for(unsigned int j = 0; j<(qty_2+1);j++)
	{
		switch(this->plane)
		{
			case YZ_PLANE:
			{
				x_elev1 = 0.0f;
				y_elev1 = lower_1+j*this->spacing_1;
				z_elev1 = lower_2;

				x_elev2 = 0.0f;
				y_elev2 = lower_1+j*this->spacing_1;
				z_elev2 = lower_2+this->length_2;
				break;
			}
			case XZ_PLANE:
			{
				x_elev1 = lower_1+j*this->spacing_1;
				y_elev1 = 0.0f;
				z_elev1 = lower_2;

				x_elev2 = lower_1+j*this->spacing_1;
				y_elev2 = 0.0f;
				z_elev2 = lower_2+this->length_2;
				break;
			}
			case XY_PLANE:
			{
				x_elev1 = lower_1+j*this->spacing_1;
				y_elev1 = lower_2;
				z_elev1 = 0.0f;

				x_elev2 = lower_1+j*this->spacing_1;
				y_elev2 = lower_2+this->length_2;
				z_elev2 = 0.0f;
				break;
			}
			default:
			{
				x_elev1 = 0.0f;
				x_elev2 = 0.0f;
				y_elev1 = 0.0f;
				y_elev2 = 0.0f;
				z_elev1 = 0.0f;
				z_elev2 = 0.0f;
				printf("\nUndefined plane detected.  Must be XZ_PLANE, YZ_PLANE, or XY_PLANE.");
				return;
			}
		}
		//1st end point
		temp_vertex.Position = glm::vec3(x_elev1, y_elev1, z_elev1);
		vertices.push_back(temp_vertex);
		//2nd end point
		temp_vertex.Position = glm::vec3(x_elev2, y_elev2, z_elev2);
		vertices.push_back(temp_vertex);
		/*printf("\n-----------------------------------------");
		printf("\nx1: %f, y1: %f, z1: %f",x_elev1, y_elev1, z_elev1);
		printf("\nx2: %f, y2: %f, z2: %f",x_elev2, y_elev2, z_elev2);*/

		// set the indices (two points per line)
		indices.push_back(last_index_end+2*j);
		indices.push_back(last_index_end+2*j+1);
	}

	// no textures
	TextureData temp_tex;
	temp_tex.id = -1;
	temp_tex.path = " ";
	textures.push_back(temp_tex);

	Mesh2 *newmesh = new Mesh2(vertices, indices, textures, draw_type);
	newmesh->parentID = this->GetDrawingObjID();
    this->meshes.push_back(newmesh);
}

void CRectPrism::MakeGridData()
{
	GLfloat x = (GLfloat)(0.5*x_len);
	GLfloat y = (GLfloat)(0.5*y_len);
	GLfloat z = (GLfloat)(0.5*z_len);

	GLfloat red = 1.0f;
	GLfloat green = 0.67f;
	GLfloat blue = 0.33f;
	// Data for a default unit cube sentered at (0,0,0)
	// Set up vertex data (and buffer(s)) and attribute pointers
	//        Coords			     Colors		                Texture			    Normals
 	//    X      Y      Z  ||  R      G      B    Alpha  ||  TextU  TextV || LightX LightY LightZ
	 GLfloat vertex_data[] = {
		-x,		-y,	 z,			red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //0
		 x,		-y,	 z,			red,   green, blue,  1.0f,      0.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //1
         x,		 y,	 z,			red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, 1.0f, //2
        -x,		 y,	 z,			red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, 1.0f, //3

		-x,		-y,	 -z,		red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, -1.0f, //4
		 x,		-y,	 -z,		red,   green, blue,  1.0f,      0.0f, 0.0f,	  0.0f,  0.0f, -1.0f, //5
         x,		 y,	 -z,		red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, -1.0f, //6
        -x,		 y,	 -z,		red,   green, blue,  1.0f,      1.0f, 1.0f,	  0.0f,  0.0f, -1.0f  //7
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
		newmesh->parentID = this->GetDrawingObjID();
	    this->meshes.push_back(newmesh);
	 }
}

void CRectangle::MakeGridData()
{
	GLfloat x = (GLfloat)(0.5*this->x_len);
	GLfloat y = (GLfloat)(0.5*this->y_len);
	GLfloat z = (GLfloat) 0.0f;
//	printf("\nX: %f    Y: %f     Z: %f",x, y, z);
//	getchar();

	GLfloat red = 1.0f;
	GLfloat green = 0.67f;
	GLfloat blue = 0.33f;
	// Data for a default unit cube sentered at (0,0,0)
	// Set up vertex data (and buffer(s)) and attribute pointers
	//        Coords			     Colors		                Texture			    Normals
 	//    X      Y      Z  ||  R      G      B    Alpha  ||  TextU  TextV || LightX LightY LightZ
	 GLfloat vertex_data[] = {
		-x,		-y,	 z,			red,   green, blue,  1.0f,	  1.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //0
		 x,		-y,	 z,			red,   green, blue,  1.0f,    0.0f, 0.0f,	  0.0f,  0.0f, 1.0f, //1
         x,		 y,	 z,			red,   green, blue,  1.0f,    1.0f, 1.0f,	  0.0f,  0.0f, 1.0f, //2
        -x,		 y,	 z,			red,   green, blue,  1.0f,    1.0f, 1.0f,	  0.0f,  0.0f, 1.0f, //3
    };

	 GLuint indexes[] = {
		0, 1, 2,   // Front
		0, 2, 3
	 };

	 string texture_files[] = {
		 " "
	 };

	 // loop through the vertex data provided.  Note the "12" is the current number of elements in the data that
	 // are being processed.
	 int num_elems = 12;  // the current number of elements in the data

	 // Find the nodes related to the faces based upon connectivity indexes
	 // Loop through the index data.  Assumes three nodes per triangle for now
 	 int num_faceindex_elems = 3;		// the number of nodes per face
	 int f_max = (sizeof(indexes)/(num_faceindex_elems*sizeof(GLuint))); // computes the number of faces defined
	 //printf("\nNumber of faces, f_max: %i", f_max);
	
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
		 
		 //// For nodes A-B-C -- in that order for a triangular mesh
		 //A = glm::vec3(vertex_data[(face_node_number0*num_elems+0)], vertex_data[(face_node_number0*num_elems+1)], vertex_data[(face_node_number0*num_elems+2)]);
		 //B = glm::vec3(vertex_data[(face_node_number1*num_elems+0)], vertex_data[(face_node_number1*num_elems+1)], vertex_data[(face_node_number1*num_elems+2)]);
		 //C = glm::vec3(vertex_data[(face_node_number2*num_elems+0)], vertex_data[(face_node_number2*num_elems+1)], vertex_data[(face_node_number2*num_elems+2)]);
		 //vAB = B-A;						// position vector AB
		 //vAC = C-A;						// position vector AC
		 //normal_vec = glm::normalize(glm::cross(vAB,vAC));	// now compute vector AB x AC
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
		newmesh->parentID = this->GetDrawingObjID();
	    this->meshes.push_back(newmesh);
	 }
}

void CDrawingObjects::TranslateObjectData(glm::vec3 trans_amt)
{
	for(unsigned int i = 0; i < this->meshes.size();i++)
	{
		printf("\n===================================================");
		printf("\nMesh #:  %i",this->meshes[i]->GetMeshID());
		//This translates the nodes.
		for(unsigned int j=0; j < this->meshes[i]->indices.size(); j++)
		{
			printf("\nBefore:  x: %f   y: %f  z: %f", this->meshes[i]->vertices[j].Position.x, this->meshes[i]->vertices[j].Position.y, this->meshes[i]->vertices[j].Position.z);
			this->meshes[i]->vertices[j].Position = this->meshes[i]->vertices[j].Position + trans_amt;
			printf("\nAfter:  x: %f   y: %f  z: %f", this->meshes[i]->vertices[j].Position.x, this->meshes[i]->vertices[j].Position.y, this->meshes[i]->vertices[j].Position.z);
		
			// Now setup this VAO/VBO again.  Easiest way should be to delete the VAO/VBO etc 
			// from the existing meshes[i] and copy the new one into its place.

			// Delete the old
			glDeleteVertexArrays(1,&(this->meshes[i]->VAO));
			glDeleteBuffers(1,&(this->meshes[i]->VBO));

			// Make the new
			this->meshes[i]->setupMesh();
		}
	}
}