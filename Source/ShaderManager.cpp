#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdio.h>

#include "../Headers/ShaderManager.h"
//#include "../Headers/Shader.h"

#include <fstream>

bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return ifile != NULL;
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

	MemberInfo = new ShaderInfo;				// creates an empty ShaderInfo list
	MemberInfo->ShaderID = -1;
	MemberInfo->ShaderType = SHADER_UNDEFINED;
	MemberInfo->strVertexFilename = "Undefined";
	MemberInfo->strFragmentFilename = "Undefined";
	MemberInfo->previous = NULL;
	MemberInfo->next = NULL;
	MemberInfo->VertexShaderID = -1;
	MemberInfo->FragmentShaderID = -1;
	MemberInfo->ShaderProgramID = -1;
	MemberInfo->IsBuilt = false;

	// Since nothing is currently stored, the first and last members are pointed to the previous value (NULL);
	firstMemberInfo = MemberInfo;		// point the first member to the previous value
	lastMemberInfo = MemberInfo;		// point the last member to the previous value
}

// deconstructor for ShaderManager
ShaderManager::~ShaderManager()
{
	printf("\nShader Manager deconstructor...");
	Destroy();
}

void ShaderManager::Initialize()
{
	printf("\nInitializing shader manager...");
}

void ShaderManager::AddShader(struct ShaderInfo *head, int type, std::string strVertexFilename, std::string strFragmentFilename)
{
	printf("\nAdding a shader/texture to the shader manager list...");
//	printf("\nfilename: %s", strFilename.c_str());

	ShaderInfo *newShader = new ShaderInfo;
	newShader->ShaderID = ((lastMemberInfo->ShaderID)+1);
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
		MemberInfo = newShader;
		lastMemberInfo = newShader;
		return;
	}
	while (curShader)
	{
//		printf ("\nID: %i      Type:  %i     Filename: %s", curShader->ShaderID, curShader->ShaderType, curShader->strFilename.c_str());
		if(curShader->next == NULL)
		{
			curShader->next = newShader;
			lastMemberInfo = curShader->next;
			return;
		}
		curShader = curShader->next;
	}

	return;
}

void ShaderManager::BuildShaderProgram(struct ShaderInfo *head)
{
	//Test if the vertex shader file exists
	if (!fexists(head->strVertexFilename))
		printf("\nVertex shader file does not exist.  Check the file name in: %s", head->strVertexFilename.c_str());

	//Test is the fragment shader file exists
	if (!fexists(head->strFragmentFilename))
		printf("\nFragment shader file does not exist.  Check the file name in: %s", head->strFragmentFilename.c_str());

	// search the linked list for the ID number in the manager

	GLint success;
    GLchar infoLog[512];

	// These will hold the shader's text file data
	std::string strVShader, strFShader;

	// Make sure the user passed in a vertex and fragment shader file
	if ( !head->strVertexFilename.length() || !head->strFragmentFilename.length() )
		return;

	// If any of our shader pointers are set, let's free them first
	if ( head->VertexShaderID || head->FragmentShaderID || head->ShaderProgramID )
		Destroy();

	// Reset the last OpenGL error so we can check if down below
	GLenum ErrorCheckValue = glGetError();

	// Here we get an Id to our vertex and fragment shaders
	head->VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	head->FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

//	cout << "VertexShaderID:  " << VertexShaderID;
//	cout << "FragmentShaderID:  " << FragmentShaderID;

	// Now we load the shaders from the respective files and store it in a string
	strVShader = LoadShaderFile(head->strVertexFilename.c_str());
	strFShader = LoadShaderFile(head->strFragmentFilename.c_str());

//	cout << "strVShader:  " << strVShader;
//	cout << "strFShader: " << strFShader;

	// Do a quick switch so we can do a double pointer below
	const char *szVShader = strVShader.c_str();
	const char *szFShader = strFShader.c_str();

	// Now this assigns the shader text file to each shader pointer
	glShaderSource(head->VertexShaderID, 1, &szVShader, nullptr);
	glShaderSource(head->FragmentShaderID, 1, &szFShader, nullptr);

	// Now we actually compile the shader code
	glCompileShader(head->VertexShaderID);
	    // Check for compile time errors

    glGetShaderiv(head->VertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(head->VertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	glCompileShader(head->FragmentShaderID);
    // Check for compile time errors
    glGetShaderiv(head->FragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(head->FragmentShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	// Next we create a program object to represent our shaders
	head->ShaderProgramID = glCreateProgram();

	// We attach each shader we just loaded to our program object
	glAttachShader(head->ShaderProgramID, head->VertexShaderID);
	glAttachShader(head->ShaderProgramID, head->FragmentShaderID);

	// Our last init function is to link our program object with OpenGL
	glLinkProgram(head->ShaderProgramID);
    // Check for linking errors
    glGetProgramiv(head->ShaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(head->ShaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

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
}

void ShaderManager::ShowDetails(struct ShaderInfo *head)
{
	ShaderInfo *list = head;

	printf("\nShowing details of the contents stored by the shader manager...");

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
	printf("No shader found in the manager combining %s and %s in ShaderManager", strVertexFile.c_str(), strFragmentFile.c_str());
}


void ShaderManager::Destroy()
{
	printf("\nDestroying the manager...");
}