#include "stdafx.h"
#include <iostream>

#include <GL/glew.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Headers/Mesh.h"
#include "../Headers/Cursor.h"

//#include "../utils/MathUtils.h"

// Creates the mesh for the cursor model.  For now it makes a cube shape, but ultimately 
// It should be changeable with other models (such as selected shapes for moving, newly added models to screen, etc.).
void CCursor::MakeCursorModel()
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
		Mesh2 *newmesh = new Mesh2(face_vertices, face_indices, face_textures);
	    this->meshes.push_back(newmesh);
//		this->meshes.push_back(Mesh2(face_vertices, face_indices, face_textures));
//		this->meshes.push_back(Mesh2(vertices, indices, textures));
	 }

}


/*
// loads the cursor geometry
void Cursor::loadCursor()
{
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

	 printf("\nLoading cursor..");
	 printf("\nNumber of faces, f_max: %i", f_max);
	
	 //vector<VertexData> face_vertices;			// stores the vertex data
	 // Loop once for each defined face
	 for(int f=0;f<f_max; f++)
	 {
		 //printf("\n=================================================================");
		 //printf("\nFace #: %i",f);
		 // =====  VERTEX DATA ========
		 VertexData face_vertex;
		 glm::vec3 A, B, C, vAB, vAC, normal_vec ;		// vectors for computing normals
//		 vertices.resize(0);						// clear existing face_vertices vector
		 vertices.reserve(num_faceindex_elems);	// set the size of the vertices vector

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
			 vertices.push_back(face_vertex);			 // add the vertex to the end of the vertices vector

			 printf("\nNode#: %i -- Vertex.Position.x: %f",face_node_number0, face_vertex.Position.x);
 			 printf("\nNode#: %i -- Vertex.Position.y: %f",face_node_number0, face_vertex.Position.y);
 			 printf("\nNode#: %i -- Vertex.Position.z: %f",face_node_number0, face_vertex.Position.z);
			 printf("\nNode#: %i -- Vertex.Color.x: %f",face_node_number0, face_vertex.Color.x);
 			 printf("\nNode#: %i -- Vertex.Color.y: %f",face_node_number0, face_vertex.Color.y);
 			 printf("\nNode#: %i -- Vertex.Color.z: %f",face_node_number0, face_vertex.Color.z);
			 printf("\nNode#: %i -- Vertex.TexCoords.x: %f",face_node_number0, face_vertex.TexCoords.x);
 			 printf("\nNode#: %i -- Vertex.TexCoords.y: %f",face_node_number0, face_vertex.TexCoords.y);
			 printf("\nNode#: %i -- Vertex.Normal.x: %f",face_node_number0, face_vertex.Normal.x);
 			 printf("\nNode#: %i -- Vertex.Normal.y: %f",face_node_number0, face_vertex.Normal.y);
	 		 printf("\nNode#: %i -- Vertex.Normal.z: %f",face_node_number0, face_vertex.Normal.z);
			 printf("\n-----------------------------------------");
		 }

		 // ====== INDEX DATA ======
		 //  Indices for each mesh will be 0, 1, 2 for a triangle, based on the order of the index_data (connectivity)
	 	 //vector<GLuint> face_indices;			// stores the index data
//		 indices.resize(0);				// clear an existing face_indices vector
		 indices.reserve(num_faceindex_elems);	// set the size of the indices
		 //printf("\n============== FACE INDEX POSITION ==============================");
		 for(int j=0; j<num_faceindex_elems;j++)
		 {
			 indices.push_back(j);
			 printf("\nFace #: %i  -- Array:  %i,  indices: %i",f,j,j);
		 }

		 // ====== FRAGMENT DATA ======
		 // record textures
	 	 // Loop through the texture information (if present)
		 int k_max = (sizeof(texture_files)/sizeof(string));
		 //vector<TextureData> face_textures;		// stores the texture data
//		 textures.resize(0);				// clear previous face_texture arrays
		 textures.reserve(k_max);			// resize the array based on the number of elements
		 //printf("\n============== FACE TEXTURES ========================");
		 for (int k = 0; k < k_max; k++)
		 {
			 TextureData face_texture;
			 face_texture.id = k;
			 face_texture.path = texture_files[k];
			 textures.push_back(face_texture);
		}

		// Now create the mesh based on the data that has been read by calling the mesh constructor in mesh.h
//		setMeshData(vertices, indices, textures);

//		this->meshes.push_back(Mesh(face_vertices, face_indices, face_textures));
		this->meshes.push_back(Mesh2(vertices, indices, textures));
	 }

}
*/

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

/*
// draws the cursor shapes on the screen
void Cursor::DrawCursor(int width, int height, Shader shader, Camera camera, int draw_type)
{

		// now draw the pointer
//		for(GLuint i=0; i < meshes.size(); i++)
		{
//			printf("\nmeshes.size(): %i",meshes.size());
//			this->meshes[i].Draw(draw_type);
					// Draw mesh
	        glBindVertexArray(VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		return;
}
*/