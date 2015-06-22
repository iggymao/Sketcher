#include "stdafx.h"
#include <iostream>

#include "../Headers/SOIL.h"			// adds the soil library

#include <string>						// Used for our STL string objects
#include <fstream>						// Used for our ifstream object to load text files
//#include "../Headers/Main.h"			// Adds our other program headers
#include "../Headers/Texture.h"			// adds our texture class

void Texture::Initialize()
{
	    // Load and create a texture 
//    GLuint texture1;
//    GLuint texture2;

/*
    // ====================
    // Texture 1
    // ====================
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
*/
}

void Texture::Destroy()
{
	printf("\nDestroying a texture...");
}