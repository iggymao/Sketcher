#ifndef _ShaderManager_H
#define _ShaderManager_H

//#include "../Headers/Main.h"			// include our main application header file
//#include "../Headers/Shader.h"
//Include GLEW  
#include <GL/glew.h>  // for the GLuint, GLbool variable calls
//Include GLFW  
//#include <GLFW/glfw3.h> 

//Used in our manager routine to identify the types of shaders and or textures
#define SHADER_UNDEFINED -1			// the default value used at creation time
#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2
#define SHADER_TESSELATION 3
#define SHADER_OTHER 4
#define SHADER_TEXTURE 5

// linked list showing Shader information (Type of Shader, Type of Texture, etc.)
struct ShaderInfo
{
	int ShaderID;					// unique identifier for each shader
	int ShaderType;					// stores the type of the shader as described in ShaderManager.h
	std::string strVertexFilename;		// stores the name and location of the vertex shader files being read.
	std::string strFragmentFilename;	// stores the name and location of the fragment shader files being read.
	ShaderInfo *next;				// point to the next ShaderItem
	ShaderInfo *previous;			// point to the previous ShaderItem

	GLuint VertexShaderID;			// stores the VertexShaderID from the BuildShader method
	GLuint FragmentShaderID;		// stores the FragmentShaderID from the BuildShader method
	GLuint ShaderProgramID;			// store the ShaderProgramID after the linking is complete
	bool IsBuilt;					// store a boolean to tell us if the program has been compiled
};

// This class creates a shader manager to load and  handles all shaders and textures needed by the model,
// recording an ID and information for each. 
class ShaderManager
{
	public:
		ShaderManager();	// default constructor
		~ShaderManager();	// deconstructor
	
		ShaderInfo *MemberInfo;				// a linked list of all members
		ShaderInfo *firstMemberInfo;			// a pointer to the first member
		ShaderInfo *lastMemberInfo;			// a pointer to the last member 
		
		void SetID(int id_num) { ShaderManagerID = id_num; }
		int GetID() { return ShaderManagerID;}
	
		void Initialize();		// Initializes the shader manager

		// adds an entry to the shader manager
		void AddShader(struct ShaderInfo *head, int type, std::string strVertexFilename, std::string strFragmentFilename);		// Adds an item to the shader manager
		// search for a ShaderInfo entry based the frag and vert file name.
		struct ShaderInfo *searchShaderInfo(struct ShaderInfo *MemberInfo, std::string strVertexFile, std::string strFragmentFile) ;

		void BuildShaderProgram(struct ShaderInfo *head); // Build the shader program for the record referenced by *head;
		std::string LoadShaderFile(std::string strFile);  // loads a fragment/vertex shader from file

		void ShowDetails(struct ShaderInfo *head);		// Shows all the items currently known by the shader manager.

		void Destroy();			// destroys our shader manager

	private:
		int ShaderManagerID;
};

#endif