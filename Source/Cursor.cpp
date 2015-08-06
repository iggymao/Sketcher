#include "stdafx.h"
#include <iostream>

#include <GL/glew.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Headers/Mesh.h"
#include "../Headers/Cursor.h"

#include "../utils/MathUtils.cpp"

//#include "../utils/MathUtils.h"

void CCursor::SetSnapValues(GLfloat val1, GLfloat val2, int plane)
{
	GLfloat xval, yval, zval;

	switch(plane)
	{
		case YZ_PLANE:
		{
			xval = 0.0f;
			yval = val1;
			zval = val2;
			break;
		}
		case XZ_PLANE:
		{
			xval = val1;
			yval = 0.0f;
			zval = val2;
			break;
		}
		case XY_PLANE:
		{
			xval = val1;
			yval = val2;
			zval = 0.0f;
			break;
		}
		default:
		{
			xval = 0.1f;
			yval = 0.1f;
			zval = 0.1f;
			printf("\nUndefined plane detected.  Must be XZ_PLANE, YZ_PLANE, or XY_PLANE.");
			return;
		}
	}
	this->SnapValueX = xval;
	this->SnapValueY = yval;
	this->SnapValueZ = zval;
}

// Creates the mesh for the cursor model.  For now it makes a cube shape, but ultimately 
// It should be changeable with other models (such as selected shapes for moving, newly added models to screen, etc.).
void CCursor::MakeGridData()
{
	printf("\nMakingCursorModel...");
		// For now, we'll load a simple cube to test
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
		Mesh2 *newmesh = new Mesh2(face_vertices, face_indices, face_textures, draw_type);
	    this->meshes.push_back(newmesh);
//		meshes.push_back(newmesh);
	 }
//	 return meshes;

}

/*
// sets the openGL properties for the cursor
void Cursor::setupCursor(int width, int height, Shader shader, Camera camera, int draw_type)
{
		GLint lightPosLoc    = glGetUniformLocation(shader.Program, "light.position");
        GLint viewPosLoc     = glGetUniformLocation(shader.Program, "viewPos");
        glUniform3f(lightPosLoc,    0.0f, 0.0f, 0.0f);		// set to 0,0,0
        glUniform3f(viewPosLoc,     camera.Position.x, camera.Position.y, camera.Position.z);
        // Set lights properties
        glm::vec3 lightColor;
		// Variable light Color code
        //lightColor.x = (GLfloat)(sin(glfwGetTime() * 2.0f));
        //lightColor.y = (GLfloat)(sin(glfwGetTime() * 0.7f));
        //lightColor.z = (GLfloat)(sin(glfwGetTime() * 1.3f));
		lightColor.x = 1.0f;		// red color
		lightColor.y = 1.0f;		// green color
		lightColor.z = 1.0f;		// blue color

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence
        glUniform3f(glGetUniformLocation(shader.Program, "light.ambient"),  ambientColor.x, ambientColor.y, ambientColor.z);
        glUniform3f(glGetUniformLocation(shader.Program, "light.diffuse"),  diffuseColor.x, diffuseColor.y, diffuseColor.z);
        glUniform3f(glGetUniformLocation(shader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
        // Set material properties
        glUniform3f(glGetUniformLocation(shader.Program, "material.ambient"),   1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(shader.Program, "material.diffuse"),   1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(shader.Program, "material.specular"),  0.5f, 0.5f, 0.5f); // Specular doesn't have full effect on this object's material
        glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 32.0f);

		IsCreatedCursor = true;
}
*/

// stores the six planes that create a bounding cube around the object
	// plane 1 = <xmin, 0.0f, 0.0f>
	// plane 2 = <xmax, 0.0f, 0.0f>
	// plane 3 = <0.0f, ymin, 0.0f>
	// plane 4 = <0.0f, ymax ,0.0f>
	// plane 5 = <0.0f, 0.0f, zmin>
	// plane 6 = <0.0f, 0.0f, zmax> 



// Needs to account for a translated, rotated meshes in the rendering function somehow
//void CCursor::CreateBoundingBox(vector<Mesh2*> temp)
//{
//	GLfloat temp_valx, temp_valy, temp_valz;
//
//	GLfloat xmin = temp[0]->vertices[0].Position.x;
//	GLfloat xmax = temp[0]->vertices[0].Position.x;
//	GLfloat ymin = temp[0]->vertices[0].Position.y;
//	GLfloat ymax = temp[0]->vertices[0].Position.y;
//	GLfloat zmin = temp[0]->vertices[0].Position.z;
//	GLfloat zmax = temp[0]->vertices[0].Position.z;
//
//	// search for x-min
//	for (unsigned int i=0; i < temp.size(); i++)
//	{
//		for(int j=0; j<3; j++)  // look through each of the three nodes in a triangle mesh face
//		{
//			// For x-planes
//			temp_valx = temp[i]->vertices[j].Position.x;
//			if (temp_valx < xmin)
//				xmin = temp_valx;
//			if (temp_valx > xmax)
//				xmax = temp_valx;
//
//			// For y-planes
//			temp_valy = temp[i]->vertices[j].Position.y;
//			if (temp_valy < ymin)
//				ymin = temp_valy;	
//			if (temp_valy > ymax)
//				ymax = temp_valy;
//
//			// For y-planes
//			temp_valz = temp[i]->vertices[j].Position.z;
//			if (temp_valz < zmin)
//				zmin = temp_valz;
//			if (temp_valz > zmax)
//				zmax = temp_valz;
//		}
//	}
//	printf("\nBounding box:  \nxmin: %f \nxmax: %f,\nymin: %f,\nymax: %f,\nzmin: %f,\nzmax: %f", xmin, xmax, ymin, ymax, zmin, zmax);
//	boundary.push_back(glm::vec3(xmin, 0.0f, 0.0f));
//	boundary.push_back(glm::vec3(xmax, 0.0f, 0.0f));
//	boundary.push_back(glm::vec3(0.0f, ymin, 0.0f));
//	boundary.push_back(glm::vec3(0.0f, ymax, 0.0f));
//	boundary.push_back(glm::vec3(0.0f, 0.0f, zmin));
//	boundary.push_back(glm::vec3(0.0f, 0.0f, zmax));
//}