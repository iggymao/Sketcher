#ifndef _ShaderManager_H
#define _ShaderManager_H

//#include "../Headers/Main.h"			// include our main application header file
//#include "../Headers/Shader.h"

#include <GL/glew.h>  // Include GLEW for the GLuint, GLbool variable calls

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

struct TextureInfo
{
	GLuint TextureID;
	std::string strTextureFilename;
	TextureInfo *next;				// point to the next TextureItem
	TextureInfo *previous;			// point to the previous TextureItem
	bool IsBuilt;					// store a boolean to tell us if the texture has already been loaded
};

// This class creates a shader manager to load and  handles all shaders and textures needed by the model,
// recording an ID and information for each. 
class ShaderManager
{
	public:
		ShaderManager();	// default constructor
		~ShaderManager();	// deconstructor
	
		// Shader info linked list
		ShaderInfo *ShaderMemberInfo;				// a linked list of all members
		ShaderInfo *firstShaderMemberInfo;			// a pointer to the first member
		ShaderInfo *lastShaderMemberInfo;			// a pointer to the last member 

		// Texture info linked list
		TextureInfo *TextureMemberInfo;				// a linked list of all members
		TextureInfo *firstTextureMemberInfo;			// a pointer to the first member
		TextureInfo *lastTextureMemberInfo;			// a pointer to the last member 
		TextureInfo *ActiveTexture;					// contains the most recently loaded Texture

		void SetID(int id_num) { ShaderManagerID = id_num; }
		int GetID() { return ShaderManagerID;}
	
		int Initialize();		// Initializes the shader manager

		// adds an entry to the shader manager
		void AddShader(struct ShaderInfo *head, int type, std::string strVertexFilename, std::string strFragmentFilename);		// Adds an item to the shader manager
		// search for a ShaderInfo entry based the frag and vert file name.
		struct ShaderInfo *searchShaderInfo(struct ShaderInfo *ShaderMemberInfo, std::string strVertexFile, std::string strFragmentFile) ;
		int BuildShaderProgram(struct ShaderInfo *head); // Build the shader program for the record referenced by *head;
		std::string LoadShaderFile(std::string strFile);  // loads a fragment/vertex shader from file
		void ShowShaderDetails(struct ShaderInfo *head);		// Shows all the shader items currently known by the shader manager.

		// adds an entry to the shader manager
		void AddTexture(struct TextureInfo *head, std::string strTextureFilename);	// Adds an item to the shader manager
		// search for a ShaderInfo entry based the frag and vert file name.
//		struct TextureInfo *searchTextureInfo(struct TextureInfo *TextureMemberInfo, std::string strTextureFilename) ;
		struct TextureInfo *searchTextureInfo(struct TextureInfo *TextureMemberInfo, std::string strTextureFilename) ;

		int BuildTextureProgram(struct TextureInfo *head); // Builds a texture for the record referenced by *head;
		bool LoadTextureFile(std::string strFile);  // loads a texture and returns the image file
		void ShowTextureDetails(struct TextureInfo *head); // Shows all the texture items currently known by the shader manager.

		void Destroy();			// destroys our shader manager

	private:
		int ShaderManagerID;
};

#endif