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

#include "../utils/MathUtils.cpp"
// create the vertex_data, index_data, texture_data for the grid 
// creates a grid in the XZ plane for now

void CAisc::MakeGridData(int aisc_shape, GLfloat depth, GLfloat bf, GLfloat tf, GLfloat tw, GLfloat length)
{
	printf("\nMaking vertex and index data for CAisc");
}

void CGrid::MakeGridData(int plane)
{
	GLfloat x_elev1, y_elev1, z_elev1;		// for storing our plane coordinates
	GLfloat x_elev2, y_elev2, z_elev2;		// for storing our plane coordinates

	//vector<VertexData> v_data;
	vertices.reserve(2*(this->qty_1+this->qty_2));	// reserve data for lines in both directions
	//vector<GLuint> i_data;
	indices.reserve(2*(this->qty_1+this->qty_2));
	//vector<TextureData> t_data;
	VertexData temp_vertex;
	temp_vertex.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // set the color black
	temp_vertex.TexCoords = glm::vec2(0.0f, 0.0f);			// default tex coords
	temp_vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);		// no normal for lighting
	
	GLfloat lower_1 = (GLfloat)(-0.5*(this->qty_1 * this->spacing_1));
	GLfloat lower_2 = (GLfloat)(-0.5*(this->qty_2 * this->spacing_2));
	GLuint last_index_end;
	
	// for x-direction
	for(unsigned int i = 0; i<(qty_1+1);i++)
	{
		switch(plane)
		{
			case YZ_PLANE:
			{
				x_elev1 = 0.0f;
				y_elev1 = lower_1;
				z_elev1 = lower_2+i*this->spacing_2;

				x_elev2 = 0.0f;
				y_elev2 = lower_1 + this->length_1;
				z_elev2 = lower_2+i*this->spacing_2;
				break;
			}
			case XZ_PLANE:
			{
				x_elev1 = lower_1;
				y_elev1 = 0.0f;
				z_elev1 = lower_2+i*this->spacing_2;
				
				x_elev2 = lower_1 + this->length_1;
				y_elev2 = 0.0f;
				z_elev2 = lower_2+i*this->spacing_2;
				break;
			}
			case XY_PLANE:
			{
				x_elev1 = lower_1;
				y_elev1 = lower_2+i*this->spacing_2;
				z_elev1 = 0.0f;

				x_elev2 = lower_1 + this->length_1;
				y_elev2 = lower_2+i*this->spacing_2;
				z_elev2 = 0.0f;

				break;
			}
			default:
			{
				x_elev1 = 0.0f;
				x_elev2 = 0.0f;
				y_elev1 = 0.0f;
				y_elev2 = 0.0f;
				z_elev1 = 0.0f;
				z_elev2 = 0.0f;
				printf("\nUndefined plane detected.  Must be XZ_PLANE, YZ_PLANE, or XY_PLANE.");
				return;
			}
		}
		//printf("\nx1: %f, y1: %f, z1: %f",x_elev1, y_elev1, z_elev1);
		//printf("\nx2: %f, y2: %f, z2: %f",x_elev2, y_elev2, z_elev2);


		//1st end point
		temp_vertex.Position = glm::vec3(x_elev1, y_elev1, z_elev1);
//		vdata.push_back(temp_vertex);
		vertices.push_back(temp_vertex);
		//2nd end point
		temp_vertex.Position = glm::vec3(x_elev2, y_elev2, z_elev2);
		vertices.push_back(temp_vertex);
		// set the indices (two points per line)
		indices.push_back(2*i);
		indices.push_back(2*i+1);
		last_index_end = 2*i+1;
	}

	last_index_end++;		// need to increment to continue the numbering for the other direction
	
	// for orthogonal direction
	for(unsigned int j = 0; j<(qty_2+1);j++)
	{
		switch(this->plane)
		{
			case YZ_PLANE:
			{
				x_elev1 = 0.0f;
				y_elev1 = lower_1+j*this->spacing_1;
				z_elev1 = lower_2;

				x_elev2 = 0.0f;
				y_elev2 = lower_1+j*this->spacing_1;
				z_elev2 = lower_2+this->length_2;
				break;
			}
			case XZ_PLANE:
			{
				x_elev1 = lower_1+j*this->spacing_1;
				y_elev1 = 0.0f;
				z_elev1 = lower_2;

				x_elev2 = lower_1+j*this->spacing_1;
				y_elev2 = 0.0f;
				z_elev2 = lower_2+this->length_2;
				break;
			}
			case XY_PLANE:
			{
				x_elev1 = lower_1+j*this->spacing_1;
				y_elev1 = lower_2;
				z_elev1 = 0.0f;

				x_elev2 = lower_1+j*this->spacing_1;
				y_elev2 = lower_2+this->length_2;
				z_elev2 = 0.0f;
				break;
			}
			default:
			{
				x_elev1 = 0.0f;
				x_elev2 = 0.0f;
				y_elev1 = 0.0f;
				y_elev2 = 0.0f;
				z_elev1 = 0.0f;
				z_elev2 = 0.0f;
				printf("\nUndefined plane detected.  Must be XZ_PLANE, YZ_PLANE, or XY_PLANE.");
				return;
			}
		}
		//1st end point
		temp_vertex.Position = glm::vec3(x_elev1, y_elev1, z_elev1);
		vertices.push_back(temp_vertex);
		//2nd end point
		temp_vertex.Position = glm::vec3(x_elev2, y_elev2, z_elev2);
		vertices.push_back(temp_vertex);
		/*printf("\n-----------------------------------------");
		printf("\nx1: %f, y1: %f, z1: %f",x_elev1, y_elev1, z_elev1);
		printf("\nx2: %f, y2: %f, z2: %f",x_elev2, y_elev2, z_elev2);*/

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