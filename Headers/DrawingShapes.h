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

static const int AISC_SHAPE_UNDEFINED	= -1;
static const int AISC_W_SHAPE			= 0;
static const int AISC_S_SHAPE			= 1;
static const int AISC_C_SHAPE			= 2;
static const int AISC_MC_SHAPE			= 3;
static const int AISC_L_SHAPE			= 4;
static const int AISC_LL_SHAPE			= 5;
static const int AISC_HSS_SHAPE			= 6;
static const int AISC_RSS_SHAPE			= 7;




// draws a line of length centered at (0,0,0)
class CLine : public Mesh2
//class CLine : public ModelManager
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
//class CGrid : public ModelManager
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
class CPrism: public Mesh2
{
public:
	CPrism(GLfloat length, GLfloat length);
	const int draw_type = GL_TRIANGLES;
};

class CSphere: public Mesh2
{
public:
	CSphere(GLfloat radius);
	const int draw_type = GL_TRIANGLES;
};

class CCone: public Mesh2
{
public:
	CCone(GLfloat radius, GLfloat length);
	const int draw_type = GL_TRIANGLES;
};

class CModelLoader: public Mesh2
{
public:
	CModelLoader(std::string filename) {  printf("\nINCOMPLETE MODEL LOADER");}
	const int draw_type = GL_TRIANGLES;
};
*/
class CAisc
{
public:
	CAisc(std::string section_name, GLfloat length, const int draw_type) {printf("CAisc shape constructor based on strings...");}
//		: CPrism(length, draw_type);
	CAisc(int aisc_shape, GLfloat depth, GLfloat bf, GLfloat tf, GLfloat tw, GLfloat length)
	{
		this->aisc_shape = aisc_shape;
		this->depth = depth;
		this->bf = bf;
		this->tf = tf; 
		this->tw = tw;
		this->length = length;

		void MakeGridData(int aisc_shape, GLfloat depth, GLfloat bf, GLfloat tf, GLfloat tw, GLfloat length);
	}
	static const int draw_type = GL_TRIANGLES;

	void MakeGridData(int aisc_shape, GLfloat depth, GLfloat bf, GLfloat tf, GLfloat tw, GLfloat length);

	/* accessors to private data */
	int GetShape() {return this->aisc_shape;}
	GLfloat GetDepth() {return this->depth;}
	GLfloat GetFlangeWidth() {return this->bf;}
	GLfloat GetFlangeThickness() {return this->tf;}
	GLfloat GetWebThickness() {return this->tw;}
	GLfloat GetLength() {return this->length;}

private:
	int aisc_shape;				// a designator for the aisc shape as defined in DrawingShapes.h
	GLfloat depth;				// depth "d"
	GLfloat bf;					// flange width, "bf"
	GLfloat tf;					// flange thickness, "tf"
	GLfloat tw;					// web thickness
	GLfloat length;				// length of the prism.  Should be moved up into the Prism abstract class?
};

/*
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
