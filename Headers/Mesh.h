#ifndef _Mesh_H
#define _Mesh_H

#define GLM_FORCE_RADIANS								// Make sure GLM is using radians instead of degrees

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
//#include "../Headers/ShaderManager.h"					// Include the shader manager for the ShaderInfo class
//#include "../Headers/Shader.h"

// vertex data assigned to a given mesh
struct VertexData {
	glm::vec3 Position;
	glm::vec4 Color;
    glm::vec2 TexCoords;
	glm::vec3 Normal;
};

// texture data assigned to a given mesh
struct TextureData {
	GLint id;
	string path;
};

//// indices for each triangle mesh
//struct IndexData
//{
//	GLuint id;
//	glm::ivec3 Index_value;
//};

class Mesh2
{
public:
	static GLuint next_mesh_id(){  next_id++; 	return next_id;	} 	// to obtain the next mesh number

	/* Functions */
	// constructor
	Mesh2() {
		printf("\nMesh2 constructor.");
		//MeshID = next_mesh_id();
	}
	Mesh2(vector<VertexData> vert, vector<GLuint> ind, vector<TextureData> tex)
	{
		MeshID = next_mesh_id();
		printf("\nMesh::next_id++ %i",Mesh2::next_id);
		printf("\nSetting mesh for cursor....");
		this->vertices = vert;
		this->indices = ind;
		this->textures = tex;
		this->setupMesh();
	}

	// copy constructor
	Mesh2(const Mesh2 & rhs) { }

	// deconstructor
	~Mesh2() { }

	void setMeshData() {
		printf("\nSetting Data....");
		MeshID = next_mesh_id();
	}
	void setMeshData(vector<VertexData> vert, vector<GLuint> ind, vector<TextureData> tex)
	{
		MeshID = next_mesh_id();
		this-> vertices = vert;
		this-> indices = ind;
		this-> textures = tex;

		this->setupMesh();
	}

	GLuint GetMeshID() {return MeshID;}					// retrieves the Mesh's ID number
//	void SetMeshID(GLuint id_num) {this->MeshID = id_num;}	// stores the Mesh's ID number

	void Draw(GLuint draw_type) {
////		printf("\nDrawing Mesh2.");
//        glBindVertexArray(this->VAO);
////		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
//		glDrawElements(draw_type, this->indices.size(), GL_UNSIGNED_INT, 0);
//
//		glBindVertexArray(0);
	}

	GLuint draw_type;		// a marker for the type of opengl drawing to be done...GL_LINES, GL_TRIANGLES, etc..

// need tom make this protected somehow
public:
	GLuint MeshID;			// A number to reference the meshID once they are created
	static GLuint next_id;

	/* Mesh Data */
	vector<VertexData> vertices;
	vector<GLuint> indices;
	vector<TextureData> textures;
	/* Render data */
	GLuint VAO, VBO, EBO, IBO;
	/* Functions */
	void setupMesh() 
	{
//		printf("\nInside Mesh2 setupMesh.");
			// Create buffers/arrays
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);
        glBindVertexArray(this->VAO);
        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexData), &this->vertices[0], GL_STATIC_DRAW);  
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
        // Set the vertex attribute pointers
        // Vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)0);
        // Vertex Colors
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, Color));
		//printf("\nColor Offset: %i",offsetof(VertexData, Color));
		// Vertex Texture Coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, TexCoords));
		//printf("\nColor Offset: %i",offsetof(VertexData, TexCoords));
		// Vertex Normals
        glEnableVertexAttribArray(3);	
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, Normal));
		//printf("\nColor Offset: %i",offsetof(VertexData, Normal));

		glBindVertexArray(0); // clear the VAO
	}

};  // end class



// The Mesh class to handle initializing, rendering and destroying of a 3D object
class Mesh
{
public:
	static GLuint next_mesh_id(){  next_id++; 	return next_id;	} ;	// to obtain the next mesh number
	/* Functions */
	// constructor
	Mesh(vector<VertexData> vertices, vector<GLuint> indices, vector<TextureData> textures)
	{
		MeshID = next_mesh_id();
//		printf("\nMesh::next_id++ %i",Mesh::next_id);

		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		this->setupMesh();
	}

	GLuint GetMeshID() {return MeshID;}					// retrieves the Mesh's ID number
//	void SetMeshID(GLuint id_num) {this->MeshID = id_num;}	// stores the Mesh's ID number

	void Draw(int draw_type) 
    {
		
		//GLuint shader_program = shader.ShaderProgramID;
  //      // Bind appropriate textures
  //      GLuint diffuseNr = 1;
  //      GLuint specularNr = 1;
  //      for(GLuint i = 0; i < this->textures.size(); i++)
  //      {
  //          glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
  //          // Retrieve texture number (the N in diffuse_textureN)
  //          stringstream ss;
  //          string number;
  //          string name = this->textures[i].type;
  //          if(name == "texture_diffuse")
  //              ss << diffuseNr++; // Transfer GLuint to stream
  //          else if(name == "texture_specular")
  //              ss << specularNr++; // Transfer GLuint to stream
  //          number = ss.str(); 
  //          // Now set the sampler to the correct texture unit
  //          glUniform1f(glGetUniformLocation(shader_program, (name + number).c_str()), i);
  //          // And finally bind the texture
  //          glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
  //      }
  //      
  //      // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
  //      glUniform1f(glGetUniformLocation(shader_program, "material.shininess"), 16.0f);

        // Draw mesh
        glBindVertexArray(this->VAO);

//		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		glDrawElements(draw_type, this->indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

        //// Always good practice to set everything back to defaults once configured.
        //for (GLuint i = 0; i < this->textures.size(); i++)
        //{
        //    glActiveTexture(GL_TEXTURE0 + i);
        //    glBindTexture(GL_TEXTURE_2D, 0);
        //}

    }

private:
	GLuint MeshID;			// A number to reference the meshID once they are created
	static GLuint next_id;

	/* Mesh Data */
	vector<VertexData> vertices;
	vector<GLuint> indices;
	vector<TextureData> textures;
	/* Render data */
	GLuint VAO, VBO, EBO, IBO;
	/* Functions */
	void setupMesh()
	{
	// Create buffers/arrays
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);
        glBindVertexArray(this->VAO);
        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexData), &this->vertices[0], GL_STATIC_DRAW);  
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
        // Set the vertex attribute pointers
        // Vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)0);
        // Vertex Colors
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, Color));
		//printf("\nColor Offset: %i",offsetof(VertexData, Color));
		// Vertex Texture Coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, TexCoords));
		//printf("\nColor Offset: %i",offsetof(VertexData, TexCoords));
		// Vertex Normals
        glEnableVertexAttribArray(3);	
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, Normal));
		//printf("\nColor Offset: %i",offsetof(VertexData, Normal));

		glBindVertexArray(0); // clear the VAO
	}

	



//
//private:
//	GLuint MeshID;					// Stores an ID for the mesh
//	static GLuint next_id;
//public:
////	GLuint MeshID;	
//	GLuint GetMeshID() {return MeshID;}
//	static GLuint next_mesh_id(){	next_id++; 	return next_id;	} ;	// to obtain the next mesh number
//	GLuint MeshType;					// Stores the type of Mesh as defined in Application.h
//	GLuint VertexNumber;				// Stores the last Vertex number
//
//	VertexInfo *MeshVertexInfo;			// a linked list to the vertex information for a specific node
//	VertexInfo *firstVertexInfo;		// point the first member to the previous value
//	VertexInfo *lastVertexInfo;		// point the last member to the previous value
//
//	IndexInfo *MeshIndexInfo;			// a linked list to the index information for the nodal connectivity
//	IndexInfo *firstIndexInfo;			// point the first member to the previous value
//	IndexInfo *lastIndexInfo;		// point the last member to the previous value
//
//	Mesh();								// mesh constructor
//	~Mesh() {Destroy();}				// mesh deconstructor
//
//	void Initialize();		// initialize a mesh member
//
//	// adds a new VertexInfo to the MeshVertexInfo linked list returning the automatically generated NODE number
//	// to be used in the AddMeshIndex parameter?
//	// This will need a better method, but is functional for preliminary testing.
//	GLuint AddMeshVertex(VertexInfo *head, GLfloat x, GLfloat y, GLfloat z, GLfloat red, GLfloat green, GLfloat blue, GLfloat u, GLfloat v);	
//	void AddMeshIndex(IndexInfo *head, int index_val);	// adds a new IndexInfo to the MeshIndexInfo linked list 
//
//	// methods to show contents of the index and vertex pointer lists.
//	void ShowMeshVertexDetails(VertexInfo *head);
//	void ShowMeshIndexDetails(IndexInfo *head);
//	//	vector<GLfloat> vertex_data;		// create a vector to store the vertex information
////	vector<GLfloat> vertex_buffer_data; // create a vector of g_vertex_buffer_data to store the vertex data in a std::vector container
////	vector<GLuint> vertex_index_data;	// create a vector for the index data in a std::vector container.
//
//	std::string strVertexFile;			// The name of the shader file to be used with the associated mesh
//	std::string strFragmentFile;		// The name of the fragment file to be used with the associated mesh
//	std::string strTextureFile;
//
//	void Destroy();
//	//	int TargetWindow;					// Target window for the rendering
////
////	vector<GLfloat> g_vertex_buffer_data;   // create a vector of g_vertex_buffer_data to store the vertex data in a std::vector container
////	
//
////	// to create a Mesh in a specific window (WindowNum) and of a particular type (as defined in Mesh.h);
////	// param1:  width of the object
////	// param2:  height of the object
////	// param3:  depth of the object
////	void CreateMesh(int WindowNum, int ObjectType, GLfloat param1, GLfloat param2, GLfloat param3);		
////	int MeshSize;			// stores the number of meshes that make up the volume
////
////	bool TextureAlreadyLoaded;
////	// These are created to standardize the index properties used for vertex properties.
////	static const GLuint kVertexIndex = 0;				// This is for the x,y,z vertices
////	static const GLuint kColorIndex = 1;				// This is for the r,g,b,a colors
////	static const GLuint kTextureIndex = 2;				// This is for the u,v texture coordinates
////	static const GLuint kNormalIndex = 3;				// This is for the x,y,z normals
////
////
////	// Set the scale of our mesh to 100% by default
////	Mesh();  // the default constructor will create a simple triangle of 3 nodes (9 elements)
////	//Mesh()		{ Scale = vec3(1.0f, 1.0f, 1.0f); }
////
////	~Mesh()	{ DestroyMesh(); }
////
////	// Takes in a list of x,y,z vertices and vertex length to create the VBO and VAO's from,
////	// as well as the text file locations for the vertex and fragment shaders to load.
//////	void Initialize(Vertex3 vertices[], int length, std::string strVertex, std::string strFragment);
//////	void Initialize(AppWindow **WinID_array, Mesh **MemberMesh, int num_mesh );
////
////	// This draws the Mesh to the backbuffer
//////	void RenderMesh(AppWindow **WinID_array, Mesh **MemberMesh, int num_mesh, int num_VAO, int num_VBO);
//////	void RenderMesh(Mesh **MemberMesh);
////
////	// Create the getter and setters for the mesh's position
//////	vec3 GetPosition() { return Position; }
//////	void SetPosition(vec3 position) { Position = position; }
////
////	// Create the getter and setters for the mesh's rotation
//////	vec3 GetRotation() { return Rotation; }
//////	void SetRotation(vec3 rotation) { Rotation = rotation; }
////
////	// Create the getter and setters for the mesh's scale
//////	vec3 GetScale() { return Scale; }
//////	void SetScale(vec3 scale) { Scale = scale; }
////
////	// This cleans up the VBO and VAO's
//////	void DestroyMesh();
////
//////protected:
////
////	Vertex3 *Vertices;									// The list of the vertices
//////	GLint VerticesLength;								// The length of the vertices
//////	GLuint VertexBufferID;								// The VBO Id stored by the VAO
//////	GLuint VertexArrayID;								// The VAO Id to bind when drawing
////
//////	vec3 Position;										// The mesh's position
//////	vec3 Rotation;										// The mesh's rotation
//////	vec3 Scale;											// The mesh's scale
////
////	// Our shader object to initialize and run the shaders
////	Shader Shader;
////
////	// Our texture object to initialize and run the texture routines
////	Texture Texture;
};
#endif
