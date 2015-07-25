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
	//	:  qty_1 = # of perp-lines along the #2-axis
	//	:  qty_2 = # of perp-lines along the #1-axis
	//  :  space_1 = spacing between #2-direction lines
	//  :  space_2 = spacing between #1-direction lines
	CGrid(GLuint qty_1, GLfloat spacing_1, GLuint qty_2, GLfloat spacing_2, const int plane) {
		this->qty_1 = qty_1;
		this->qty_2 = qty_2;
		this->spacing_1 = spacing_1; 
		this->spacing_2 = spacing_2;
		this->length_1 = (GLfloat)((qty_2) * spacing_1);
		this->length_2 = (GLfloat)((qty_1) * spacing_2);
		this->plane = plane;

		MakeGridData(this->GetPlane());				// create the grid data
		setMeshData(vertices, indices, textures);	// sets the mesh data and creates the VAO and VBO in Mesh2
	}
	~CGrid() { ;}					// deconstructor
	CGrid(const CGrid & rhs) { ;}	// copy constructor

	void UpdateGrid(){printf("\nINCOMPLETE!!!  routine to update the grid dimensions");}		// routine to update an existing grid based on changed parameters

	GLfloat SetQty(GLuint qty1, GLuint qty2) {this->qty_1=qty1; this->qty_2=qty2;}
	GLfloat SetSpacing(GLfloat spacing1, GLfloat spacing2) {this->spacing_1=spacing1; this->spacing_2=spacing2;}
	GLfloat GetSpacing1() {return this->spacing_1;}
	GLfloat GetSpacing2() {return this->spacing_2;}
	int GetPlane() {return this->plane;}

	// create the vertex_data, index_data, texture_data for the grid 
	// calculates the data for line grids a grid in the XZ plane for now
	void MakeGridData(int plane);

private:
	GLuint qty_1, qty_2;			// number of lines in grid, x- and z- direction
	GLfloat spacing_1, spacing_2;	// spacing between grid lines, x- and z- direction
	GLfloat length_1, length_2;		// length of grid line system
	int plane;						// plane orientation of the grid (currently XY, YZ, or XZ as defined in MathUtils.h)
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
