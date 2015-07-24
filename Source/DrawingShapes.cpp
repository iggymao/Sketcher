#include "stdafx.h"

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

#include "../Headers/DrawingShapes.h"

// create the vertex_data, index_data, texture_data for the grid 
// creates a grid in the XZ plane for now
void CGrid::MakeGridData()
{
	GLfloat y_elev = 0.0f;
	//vector<VertexData> v_data;
	vertices.reserve(2*(this->qty_x+this->qty_z));	// reserve data for lines in both x- and y- directions
	//vector<GLuint> i_data;
	indices.reserve(2*(this->qty_x+this->qty_z));
	//vector<TextureData> t_data;
	
	GLfloat lower_x = (GLfloat)(-0.5*(this->qty_x * this->spacing_x));
	GLfloat lower_z = (GLfloat)(-0.5*(this->qty_z * this->spacing_z));
	GLuint last_index_end;
	
	VertexData temp_vertex;
	temp_vertex.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // set the color black
	temp_vertex.TexCoords = glm::vec2(0.0f, 0.0f);			// default tex coords
	temp_vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);		// no normal for lighting

	// for x-direction
	for(unsigned int i = 0; i<(qty_x+1);i++)
	{
		//1st end point
		temp_vertex.Position = glm::vec3(lower_x, y_elev, lower_z+i*this->spacing_z);
//		vdata.push_back(temp_vertex);
		vertices.push_back(temp_vertex);
		//2nd end point
		temp_vertex.Position = glm::vec3(lower_x + this->length_x, y_elev, lower_z+i*this->spacing_z);
		vertices.push_back(temp_vertex);
		// set the indices (two points per line)
		indices.push_back(2*i);
		indices.push_back(2*i+1);
		last_index_end = 2*i+1;
	}

	last_index_end++;		// need to increment to continue the numbering for the other direction
	
	// for orthogonal direction
	for(unsigned int j = 0; j<(qty_z+1);j++)
	{
		//1st end point
		temp_vertex.Position = glm::vec3(lower_x+j*this->spacing_x, y_elev, lower_z);
		vertices.push_back(temp_vertex);
		//2nd end point
		temp_vertex.Position = glm::vec3(lower_x+j*this->spacing_x, y_elev, lower_z+this->length_z);
		vertices.push_back(temp_vertex);
		// set the indices (two points per line)
		indices.push_back(last_index_end+2*j);
		indices.push_back(last_index_end+2*j+1);
	}

	// no textures
	TextureData temp_tex;
	temp_tex.id = -1;
	temp_tex.path = " ";
	textures.push_back(temp_tex);
}