#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>					// GLEW

#include "../Headers/ShaderManager.h"	// include our shader manager class
#include "../Headers/SOIL.h"			// include the soil image loader based on stb_image for texture loading

#include <fstream>

bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return ifile != NULL;
}

const char* GL_type_to_string(GLenum type){
	switch(type) {
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
		default: break;
	}
	return "other";
}
void _print_shader_info_log (GLuint shader_index) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
		glGetShaderInfoLog (shader_index, max_length, &actual_length, log);
		printf ("shader info log for GL index %u:\n%s\n", shader_index, log);
}

void _print_programme_info_log(GLuint programme) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog(programme, max_length, &actual_length, log);
	printf ("program info log for GL index %u:\n%s", programme, log);
}

bool is_valid(GLuint programme) {
	glValidateProgram(programme);
	int params = -1;
	glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
	printf("program %i GL_VALIDATE_STATUS = %i\n", programme, params);
	if (GL_TRUE != params) {
		_print_programme_info_log (programme);
		return false;
	}
	return true;
}

void print_all(GLuint programme) {
	printf ("---------------------------------------\nshader programme %i info:\n", programme);
	int params = -1;
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	printf ("GL_LINK_STATUS = %i\n", params);
	glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
	printf ("GL_ATTACHED_SHADERS= %i\n", params);
	glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
	printf ("GL_ACTIVE_ATTRIBUTES=%i\n", params);
	for (GLuint i=0; i<(GLuint)params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib(programme, i, max_length, &actual_length, &size, &type, name);
		if(size>1){
			for(int j=0; j<size; j++) {
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(programme, long_name);
				printf("  %i) type:%s  name:%s  location:%i\n", i, GL_type_to_string(type), long_name, location);
			}
		} else {
			int location = glGetAttribLocation(programme, name);
			printf("  %i) type:%s,  name:%s  location:%i\n", i, GL_type_to_string(type), name, location);
		}
	}
	glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
	printf("GL_ACTIVE_UNIFORMS = %i\n", params);
	for(GLuint i=0; i<(GLuint)params; i++) {
		char name[64];
		int max_length=64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform(programme, i, max_length, &actual_length, &size, &type, name);
		if (size>1){
			for (int j=0; j<size; j++) {
				char long_name[64];
				sprintf(long_name,"%s[%i]", name, j);
				int location = glGetUniformLocation (programme, long_name);
				printf ("  %i) type:%s name:%s  location:%i\n", i, GL_type_to_string(type), long_name, location);
			}
		} else {
			int location = glGetUniformLocation(programme, name);
			printf ("  %i) type:%s name:%s  location:%i\n", i, GL_type_to_string (type), name, location);
		}
	}

	_print_programme_info_log(programme);
}

// This function loads a text file and returns the code for our shaders
std::string ShaderManager::LoadShaderFile(std::string strFile)
{
	// Open the file passed in
	std::ifstream fin(strFile.c_str());

	// Make sure we opened the file correctly
	if ( !fin )
	{
		printf("\nError opening shader file: %s", strFile.c_str());
		return "";
	}
	std::string strLine = "";
	std::string strText = "";

	// Go through and store each line in the text file within a "string" object
	while ( getline(fin, strLine) )
	{
		strText = strText + "\n" + strLine;
	}

	// Close our file
	fin.close();

	// Return the text file's data
	return strText;
}

// constructor for ShaderManager
ShaderManager::ShaderManager()
{
	printf("\nShader Manager default constructor...");

	SetID(1000);								// sets the ShaderManagerID to 1,000;

	// Creat an empty ShaderInfo
	ShaderMemberInfo = new ShaderInfo;				// creates an empty ShaderInfo list
	ShaderMemberInfo->ShaderID = -1;
	ShaderMemberInfo->ShaderType = SHADER_UNDEFINED;
	ShaderMemberInfo->strVertexFilename = "Undefined";
	ShaderMemberInfo->strFragmentFilename = "Undefined";
	ShaderMemberInfo->previous = NULL;
	ShaderMemberInfo->next = NULL;
	ShaderMemberInfo->VertexShaderID = -1;
	ShaderMemberInfo->FragmentShaderID = -1;
	ShaderMemberInfo->ShaderProgramID = -1;
	ShaderMemberInfo->IsBuilt = false;

	// Since nothing is currently stored, the first and last members are pointed to the previous value (NULL);
	firstShaderMemberInfo = ShaderMemberInfo;		// point the first member to the previous value
	lastShaderMemberInfo = ShaderMemberInfo;		// point the last member to the previous value

	// Create an empty TextureInfo
	TextureMemberInfo = new TextureInfo;				
	TextureMemberInfo->TextureID = -1;
	TextureMemberInfo->strTextureFilename = "Undefined";
	TextureMemberInfo->previous = NULL;
	TextureMemberInfo->next = NULL;
	TextureMemberInfo->IsBuilt = false;

	// Since nothing is currently stored, the first and last members are pointed to the previous value (NULL);
	firstTextureMemberInfo = TextureMemberInfo;		// point the first member to the previous value
	lastTextureMemberInfo = TextureMemberInfo;		// point the last member to the previous value

}

// deconstructor for ShaderManager
ShaderManager::~ShaderManager()
{
	printf("\nShader Manager deconstructor...");
	Destroy();
}

int ShaderManager::Initialize()
{
	printf("\nInitializing shader manager...");

	ActiveTexture = NULL;		// indicates that there is no active texture currently loaded;

	// Loads a default shader.  This will be used in the event of a problem with a required shader
	// Possible include this directly into the Intialize() call?
	std::string strvertexfilename = "Shaders/DefaultShader.vertex";
	std::string strfragmentfilename = "Shaders/DefaultShader.fragment";
	AddShader(ShaderMemberInfo, SHADER_VERTEX, strvertexfilename, strfragmentfilename);
	ShaderInfo *temp0 = searchShaderInfo(ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//	ShowShaderDetails(MemberInfo);
	BuildShaderProgram(temp0);

	// Our first actual shader parameters.
	// repeat these lines to load and build a shader prograrm
	strvertexfilename = "Shaders/Shader.vertex";
	strfragmentfilename = "Shaders/Shader.fragment";
	AddShader(ShaderMemberInfo, SHADER_VERTEX, strvertexfilename, strfragmentfilename);
	ShaderInfo *temp = searchShaderInfo(ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//	ShowShaderDetails(MemberInfo);
	BuildShaderProgram(temp);

	// a junk shader for testing the search function
	strvertexfilename = "Shaders/ShaderCopy.vertex";
	strfragmentfilename = "Shaders/ShaderCopy.fragment";
	AddShader(ShaderMemberInfo, SHADER_VERTEX, strvertexfilename, strfragmentfilename);
	ShaderInfo *temp2 = searchShaderInfo(ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//	ShowShaderDetails(MemberInfo);
	BuildShaderProgram(temp2);

	// REPEATED shader loading to test the omission code from the linked list
	// repeat these lines to load and build a shader prograrm
	strvertexfilename = "Shaders/Shader.vertex";
	strfragmentfilename = "Shaders/Shader.fragment";
	AddShader(ShaderMemberInfo, SHADER_VERTEX, strvertexfilename, strfragmentfilename);
	ShaderInfo *temp3 = searchShaderInfo(ShaderMemberInfo, strvertexfilename, strfragmentfilename);
//	printf("\nShowing shader details...");
//	ShowShaderDetails(ShaderMemberInfo);
	BuildShaderProgram(temp3);

	// Load Textures
	std::string	strtexturefilename;
	strtexturefilename = "Textures/container.jpg";
	AddTexture(TextureMemberInfo, strtexturefilename);
	strtexturefilename = "Textures/Olaf.jpg";
	AddTexture(TextureMemberInfo, strtexturefilename);

	TextureInfo *ActiveTexture = searchTextureInfo(TextureMemberInfo, strtexturefilename);
//	printf("\nActiveTexture  ID:  %i", ActiveTexture->TextureID);
//	printf("\nActiveTexture filename:  %s", ActiveTexture->strTextureFilename.c_str());
	BuildTextureProgram(ActiveTexture);

//	ShowTextureDetails(TextureMemberInfo);

	return 0;
}

void ShaderManager::AddShader(struct ShaderInfo *head, int type, std::string strVertexFilename, std::string strFragmentFilename)
{
	printf("\nAdding a shader/texture to the shader manager list...");
//	printf("\nfilename: %s", strFilename.c_str());

	//ShaderInfo *temp = searchShaderInfo(MemberInfo, strvertexfilename, strfragmentfilename);
	// if the shader list already has this pair of files in it, no need to add it again
	if(searchShaderInfo(ShaderMemberInfo, strVertexFilename, strFragmentFilename))
	{
		printf ("\nFound shader.  No need to add another.");
		return;
	} else {
		printf ("\nShader not found, proceeding to add to the list.");
	}

	ShaderInfo *newShader = new ShaderInfo;
	newShader->ShaderID = ((lastShaderMemberInfo->ShaderID)+1);
	newShader->ShaderType = type;
	newShader->strVertexFilename = strVertexFilename.c_str();
	newShader->strFragmentFilename = strFragmentFilename.c_str();
	newShader->VertexShaderID = -1;			// recorded during the linking process in BuildShader method
	newShader->FragmentShaderID = -1;		// recorded during the linking process in BuildShader method
	newShader->ShaderProgramID = -1;		// recorded during the linking process in BuildShader method
	newShader->IsBuilt = false;

	//	(MemberInfo->next)->previous = lastMemberInfo;
	newShader->next = NULL;
	
	ShaderInfo *curShader = head;

	if (head->ShaderID == -1)
	{
//		printf("\nAdding first shader..");
		ShaderMemberInfo = newShader;
		lastShaderMemberInfo = newShader;
		return;
	}
	while (curShader)
	{
//		printf ("\nID: %i      Type:  %i     Filename: %s", curShader->ShaderID, curShader->ShaderType, curShader->strFilename.c_str());
		if(curShader->next == NULL)
		{
			curShader->next = newShader;
			lastShaderMemberInfo = curShader->next;
			return;
		}
		curShader = curShader->next;
	}

	return;
}

int ShaderManager::BuildShaderProgram(struct ShaderInfo *head)
{
	//Test if the vertex shader file exists
	if (!fexists(head->strVertexFilename))
		printf("\nVertex shader file does not exist.  Check the file name in: %s", head->strVertexFilename.c_str());

	//Test if the fragment shader file exists
	if (!fexists(head->strFragmentFilename))
		printf("\nFragment shader file does not exist.  Check the file name in: %s", head->strFragmentFilename.c_str());

	// search the linked list for the ID number in the manager
	if (head->IsBuilt == true)  // if this shader is already built, no need to load or compile the program again.
	{
		//printf("\nShader program is already built, so skipping the rebuild phase.");
		return head->ShaderProgramID;
	} else {
		//printf("\nBuilding shader program since its not already flagged as being built.");
	}
	GLint success;
    GLchar infoLog[512];

	// These will hold the shader's text file data
	std::string strVShader, strFShader;

	// Make sure the user passed in a vertex and fragment shader file
	if ( !head->strVertexFilename.length() || !head->strFragmentFilename.length() )
		return -1;

	// If any of our shader pointers are set, let's free them first
	if ( (head->VertexShaderID) || (head->FragmentShaderID) || (head->ShaderProgramID) )
		Destroy();

	// Reset the last OpenGL error so we can check if down below
	GLenum ErrorCheckValue = glGetError();

	// For vertex shader
	head->VertexShaderID = glCreateShader(GL_VERTEX_SHADER);		// Here we get an Id to our vertex shaders
	strVShader = LoadShaderFile(head->strVertexFilename.c_str());	// Now we load the shaders from the respective files and store it in a string
	const char *szVShader = strVShader.c_str();		// Do a quick switch so we can do a double pointer below
	glShaderSource(head->VertexShaderID, 1, &szVShader, nullptr);	// Now this assigns the shader text file to each shader pointer
	glCompileShader(head->VertexShaderID);		// Now we actually compile the shader code
	
	// Check for compile time errors
    glGetShaderiv(head->VertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(head->VertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", head->VertexShaderID);
		_print_shader_info_log (head->VertexShaderID);
		return false; // or exit or something
    }

	// For fragment shader
	head->FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);	// Here we get an Id to our vertex and fragment shaders	
	strFShader = LoadShaderFile(head->strFragmentFilename.c_str());	// Now we load the shaders from the respective files and store it in a string
	const char *szFShader = strFShader.c_str();		// Do a quick switch so we can do a double pointer below
	glShaderSource(head->FragmentShaderID, 1, &szFShader, nullptr);	// Now this assigns the shader text file to each shader pointer
	glCompileShader(head->FragmentShaderID);		// Now we actually compile the shader code

    // Check for compile time errors
    glGetShaderiv(head->FragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(head->FragmentShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", head->FragmentShaderID);
		_print_shader_info_log (head->FragmentShaderID);
		return false; // or exit or something
	}

	head->ShaderProgramID = glCreateProgram();			// Next we create a program object to represent our shaders
	glAttachShader(head->ShaderProgramID, head->VertexShaderID);	// We attach each shader we just loaded to our program object
	glAttachShader(head->ShaderProgramID, head->FragmentShaderID);
	glLinkProgram(head->ShaderProgramID);		// Our last init function is to link our program object with OpenGL

	// Check for linking errors
    glGetProgramiv(head->ShaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(head->ShaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		fprintf (stderr, "ERROR: could not link shader programme GL index %u\n", head->ShaderProgramID);
		_print_programme_info_log (head->ShaderProgramID);
		return false;
	}

	print_all(head->ShaderProgramID);		// print all the shader info

	// Now check to see if any errors happened in this function
	ErrorCheckValue = glGetError();

	// If there was an error found, print it to the screen and close the OpenGL window.
	if ( ErrorCheckValue != GL_NO_ERROR )
	{
		// Use gluErrorString(ErrorCheckValue) if you want to get the string value of the
		// error, but I removed this since Mac OSX 10.9 (Mavericks) deprecated this function.
		fprintf(stderr, "ERROR: Could not create the shader program with error Id: %d\n", ErrorCheckValue);
		exit(-1);
	}
	head->IsBuilt = true;
	return head->ShaderProgramID;
}

void ShaderManager::ShowShaderDetails(struct ShaderInfo *head)
{
	ShaderInfo *list = head;

	printf("\nShowing details of the shader contents stored by the shader manager...");

	if (head->ShaderID == -1)
	{
		printf("\n...No Shader Info added at this time...");
		return;
	}

	while(list)
	{
		printf("\nMember ID:     %i ", list->ShaderID);
		printf("\nMember Type:   %i ", list->ShaderType);
		printf("\nstrVertexFilename: %s ", list->strVertexFilename.c_str());
		printf("\nstrFragmentFilename: %s ", list->strFragmentFilename.c_str());
		printf("\nVertexShaderID: %i ", list->VertexShaderID);
		printf("\nFragmentShaderID: %i ", list->FragmentShaderID);
		printf("\nShaderProgramID: %i ", list->ShaderProgramID);
		printf("\nIsBuilt?   %s", list->IsBuilt ? "TRUE" : "FALSE");
		printf("\n-------------------------------------------");
		list=list->next;
	}
	return;
}

struct ShaderInfo* ShaderManager::searchShaderInfo(struct ShaderInfo *head, std::string strVertexFile, std::string strFragmentFile) 
{
	ShaderInfo *cur = head;
	while(cur) {
		if((cur->strVertexFilename == strVertexFile) && (cur->strFragmentFilename == strFragmentFile)) return cur;
		cur = cur->next;
	}
	printf("\nNo shader found in the manager combining %s and %s in ShaderManager", strVertexFile.c_str(), strFragmentFile.c_str());
	return NULL;
}


// Adds an item to the shader manager
void ShaderManager::AddTexture(struct TextureInfo *head, std::string strTextureFilename)
{
	printf("\nAdding a texture to the shader manager list...");
//	printf("\nfilename: %s", strFilename.c_str());

	//ShaderInfo *temp = searchShaderInfo(MemberInfo, strvertexfilename, strfragmentfilename);
	// if the shader list already has this pair of files in it, no need to add it again
	if(searchTextureInfo(TextureMemberInfo, strTextureFilename))
	{
		printf ("\nFound texture of same name.  No need to add another.");
		return;
	} else {
		printf ("\nTexture not found, proceeding to add to the list.");
	}

	TextureInfo *newTexture = new TextureInfo;
	newTexture->TextureID = ((lastTextureMemberInfo->TextureID)+1);
	newTexture->strTextureFilename = strTextureFilename.c_str();
	newTexture->IsBuilt = false;

	//	(MemberInfo->next)->previous = lastMemberInfo;
	newTexture->next = NULL;
	
	TextureInfo *curTexture = head;

	if (head->TextureID == -1)
	{
//		printf("\nAdding first shader..");
		TextureMemberInfo = newTexture;
		lastTextureMemberInfo = newTexture;
		return;
	}
	while (curTexture)
	{
//		printf ("\nID: %i      Type:  %i     Filename: %s", curShader->ShaderID, curShader->ShaderType, curShader->strFilename.c_str());
		if(curTexture->next == NULL)
		{
			curTexture->next = newTexture;
			lastTextureMemberInfo = curTexture->next;
			return;
		}
		curTexture = curTexture->next;
	}
	return;
}

// Search the texture linked list for a specified texture file, returning the item
struct TextureInfo* ShaderManager::searchTextureInfo(struct TextureInfo *head, std::string strTextureFile) 
{
	TextureInfo *cur = head;
	while(cur) {
		if(cur->strTextureFilename == strTextureFile) return cur;
		cur = cur->next;
	}
	printf("\nNo texture found in the manager utilizing  %s", strTextureFile.c_str());

	return NULL;   // search not found in list
}

// Builds a texture and does the binding
int ShaderManager::BuildTextureProgram(struct TextureInfo *head)
{
	if(!head->IsBuilt)
	{
		printf("\n--------------------------------------  Inside the build loop -----------------");

		//////////////////
		//  This chunk works...
		////////////////////
	    GLuint texture1;
	    // ====================
	    // Texture 1
		// ====================
	    glGenTextures(1, &texture1);
	    glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	    // Set our texture parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    // Set texture filtering
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    // Load, create texture and generate mipmaps
	    int width, height;
//	    unsigned char* image = SOIL_load_image("Textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		unsigned char* image = SOIL_load_image(head->strTextureFilename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		////////////////////////////////////////////////////
		head->TextureID = texture1;

/*


//		GLuint texture;
//		glGenTextures(1, &texture);
		glGenTextures(1, &head->TextureID);
//		glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
		glBindTexture(GL_TEXTURE_2D, head->TextureID); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);	// unbind the texture to avoid corruption with other objects
		

		if(!LoadTextureFile(head->strTextureFilename))  // loads the image  associated with the texture
		{
			printf("\nERROR: loading texture %s",head->strTextureFilename.c_str());
			return -1;
		}
*/
		head->IsBuilt = true;
		ActiveTexture = head;		// set the active texture to the one just built.
	}

	return 0;
}

// loads a texture... SOIL should do this automatically?
bool ShaderManager::LoadTextureFile(std::string strFile)
{
	//Error checking needed here...

	// Load image, create texture and generate mipmaps
	int width, height;
	std::string strText;
	unsigned char* image = SOIL_load_image(strFile.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	return true;
}

// Shows all the texture items currently known by the shader manager.
void ShaderManager::ShowTextureDetails(struct TextureInfo *head)
{
	printf("\n--------------  Showing Texture Details -----------------");

	TextureInfo *list = head;

	printf("\nShowing details of the texture contents stored by the shader manager...");

	if (head->TextureID == -1)
	{
		printf("\n...No TextureInfo added at this time...");
		return;
	}

	while(list)
	{
		printf("\nTexture ID:     %i ", list->TextureID);
		printf("\nstrFragmentFilename: %s ", list->strTextureFilename.c_str());
		printf("\nIsBuilt?   %s", list->IsBuilt ? "TRUE" : "FALSE");
		printf("\n-------------------------------------------");
		list=list->next;
	}
	return;
}






void ShaderManager::Destroy()
{
	printf("\nINCOMPLETE:: Destroying the manager...");
}