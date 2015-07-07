#include "stdafx.h"
#include <iostream>

#include "../Headers/ModelManager.h"
#include "../Headers/Volume.h"

class Volume;			// forward declaration

ModelManager::ModelManager()
{
	printf("\nModel Manager constructor...");
}

void ModelManager::Initialize()
{
	printf("\nCreating the model manager...");
	printf("\nINCOMPLETE:  install initial values");

	// create a test mesh with data
	Volume *testvolume;
	testvolume = new Volume;
	testvolume->Initialize();

	// create a second test mesh with data
	Volume *testvolume2;
	testvolume2 = new Volume;
	testvolume2->Initialize();

	// create a second test mesh with data
	Volume *testvolume3;
	testvolume3 = new Volume;
	testvolume3->Initialize();


}

void ModelManager::AddModel()
{

}

void ModelManager::SearchModel()
{

}

void ModelManager::CreateVAO()	
{
	//printf("\n		Creating a VAO");
	//vao=0;
	//glGenVertexArrays (1, &vao);
	//glBindVertexArray(vao);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, NULL);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glfwSwapBuffers (window);
}

// finds a created VAO to speed up the creation process
void ModelManager::FindVAO()
{
}		

// creates the VBO for a drawing;
void ModelManager::CreateVBO()
{
	printf("\n		Creating a VBO");

	//GLfloat points[] = { 
	//	0.0f, 0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f};

	//vbo=0;
	//	glGenBuffers(1, &vbo);
	//glBindBuffer (GL_ARRAY_BUFFER, vbo);
	//glBufferData (GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);
}	

// finds a created VBO to speed up drawing process
void ModelManager::FindVBO()
{

}

// creates the EBO from the volume / mesh data
void ModelManager::CreateEBO()
{

}

// finds a created EBO
void ModelManager::FindEBO()
{
	
}		

// renders the model
void ModelManager::RenderModel()
{

}	

// destroy the model manager
void ModelManager::Destroy()
{

}		