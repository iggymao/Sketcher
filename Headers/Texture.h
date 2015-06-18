#ifndef _Texture_H
#define _Texture_H

#include <string>										// Used for our STL string objects
#include <fstream>										// Used for our ifstream object to load text files
#include "../Headers/Main.h"

#define MAX_TEXTURE		1

class Texture
{
	public:
		// Create an empty constructor and have the deconstructor release our memory.
		Texture()	{ }
		~Texture()	{ Destroy(); }

		void Initialize();		// initializes the texture

//		Gluint texture[1];		// stores up to MAX_TEXTURES per mesh
//		GLuint texture_qty;					// stores the number of textures in use.  Should be less than MAX_TEXTURES

		GLint textureLocation1;
		// These 2 functions turn on and off our shader, which uses the OpenGL glUseProgram() function
//		void TurnOn()		{ cout << "\nTurning on texture... need a UseProgram call like the shaders?"; }
//		void TurnOff()		{ cout << "\nTurning off texture... need a glUseProgram(0) like the shaders?"; }

		// This releases our memory for our shader
		void Destroy();
};

#endif