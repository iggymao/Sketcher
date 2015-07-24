#ifndef _DrawingShapes_H
#define _DrawingShapes_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// GL Includes
#include <GL\glew.h>									// Used for the OpenGL types like GLuint
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Headers/Mesh.h"

// draws a line of length centered at (0,0,0)
class CLine : public Mesh2
{
public:
	// constructor
	CLine() {printf("\nDefault constructor for CLine..");}
	CLine(GLfloat length) {
//		printf("\nLine length: %f",length);
		setMeshData();
		draw_type = GL_LINES;
	}
	~CLine() { ;}					// deconstructor
	CLine(const CLine & rhs) { ;}	// copy constructor

	void Draw()
	{   
		// Draw mesh
        glBindVertexArray(VAO);			// uses the VAO stored in the Mesh2 c;ass
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

// draws a grid of lines centered at (0,0,0)
class CGrid : public CLine
{
public:
	// constructor
	//	:  qty_x = # of z-lines along the x-axis
	//	:  qty_z = # of x-lines along the z-axis
	//  :  space_x = spacing between z-direction lines
	//  :  space_z = spacing between x-direction lines
	CGrid(GLuint qty_x, GLfloat spacing_x, GLuint qty_z, GLfloat spacing_z) {
		this->qty_x = qty_x;
		this->qty_z = qty_z;
		this->spacing_x = spacing_x; 
		this->spacing_z = spacing_z;
		this->length_x = (GLfloat)((qty_z) * spacing_x);
		this->length_z = (GLfloat)((qty_x) * spacing_z);

		MakeGridData();				// create the grid data
		setMeshData(vertices, indices, textures);	// sets the mesh data and creates the VAO and VBO in Mesh2
	}
	~CGrid() { ;}					// deconstructor
	CGrid(const CGrid & rhs) { ;}	// copy constructor

	void UpdateGrid(){printf("\nINCOMPLETE!!!  routine to update the grid dimensions");}		// routine to update an existing grid based on changed parameters

	GLfloat SetQty(GLuint qty1, GLuint qty2) {this->qty_x=qty1; this->qty_z=qty2;}
	GLfloat SetSpacing(GLfloat spacing1, GLfloat spacing2) {this->spacing_x=spacing1; this->spacing_z=spacing2;}
	GLfloat GetSpacing() {return this->spacing_x;}

	// create the vertex_data, index_data, texture_data for the grid 
	// calculates the data for line grids a grid in the XZ plane for now
	void MakeGridData();

private:
	GLuint qty_x, qty_z;			// number of lines in grid, x- and y- direction
	GLfloat spacing_x, spacing_z;		// spacing between grid lines, x- and y- direction
	GLfloat length_x, length_z;		// length of grid line system
};

/*
class CPrism: public Mesh
{
public:
	CPrism(GLfloat length, GLfloat length);
	const int draw_type = GL_TRIANGLES;
};

class CSphere: public Mesh
{
public:
	CSphere(GLfloat radius);
	const int draw_type = GL_TRIANGLES;
};

class CCone: public Mesh
{
public:
	CCone(GLfloat radius, GLfloat length);
	const int draw_type = GL_TRIANGLES;
};

class CModelLoader: public Mesh
{
public:
	CModelLoader(std::string filename) {  printf("\nINCOMPLETE MODEL LOADER");}
	const int draw_type = GL_TRIANGLES;
};

class CAisc: public CPrism
{
public:
	CAisc(std::string section_name, GLfloat length, const int draw_type)
		: CPrism(length, draw_type);
	static const int draw_type = GL_TRIANGLES;
};

class CRectangle: public CPrism
{
public:
	CRectangle(GLfloat width, GLfloat height, GLfloat length, const int draw_type) 
		: CPrism(length, draw_type);
	const int draw_type = GL_TRIANGLES;
};

class CCylinder: public CPrism
{
public:
	CCylinder(GLfloat radius, GLfloat length, const int draw_type)
		: CPrism(length, draw_type);
	const int draw_type = GL_TRIANGLES;
};

class CWshape: public CAisc
{
public:
	CWshape(Mesh mesh_shape, GLfloat length, const int draw_type)
		: CPrism(length, draw_type);
	const int draw_type = GL_TRIANGLES;
};

class CChannelshape: public CAisc
{
public:
	CChannelshape(Mesh mesh_shape, GLfloat length, const int draw_type)
		: CPrism(length, draw_type);
	const int draw_type = GL_TRIANGLES;
};

class CAngleshape: public CAisc
{
public:
	CChannelshape(Mesh mesh_shape, GLfloat length, const int draw_type)
		: CPrism(length, draw_type);
	const int draw_type = GL_TRIANGLES;
};
*/
#endif
