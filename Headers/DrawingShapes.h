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
#include "../Headers/ModelManager.h"

#include "../utils/MathUtils.cpp"

static const int AISC_SHAPE_UNDEFINED	= -1;
static const int AISC_W_SHAPE			= 0;
static const int AISC_S_SHAPE			= 1;
static const int AISC_C_SHAPE			= 2;
static const int AISC_MC_SHAPE			= 3;
static const int AISC_L_SHAPE			= 4;
static const int AISC_LL_SHAPE			= 5;
static const int AISC_HSS_SHAPE			= 6;
static const int AISC_RSS_SHAPE			= 7;

struct AISCData{
	std::string aisc_label;		// the label for the shape W10x33, C12x20.7, etc...used for lookup of data eventually
	GLfloat depth;				// depth, d
	GLfloat flange_width;		// flange width, bf
	GLfloat flange_thick;		// flange thickness, tf
	GLfloat web_thick;			// web thickness of the member,tw
	GLfloat length;
};

class CDrawObjLocData
{
public:
	
	// constructor
	CDrawObjLocData() 
	{
		printf("\nDefault constructor for CDrawingObjects..");
		this->insert_point = glm::vec3(0.0f, 0.0f, 0.0f);
		this->insert_unit_rotation = glm::vec3(1.0f, 1.0f, 1.0f);  // default is about the y-axis
		this->euler_angles = glm::vec3(45.0f, 0.0f, 0.0f);
	}
	CDrawObjLocData(glm::vec3 insert_point, glm::vec3 insert_unit_rotation, glm::vec3 euler_angles) 
	{
		this->insert_point = insert_point;
		this->insert_unit_rotation = glm::normalize(insert_unit_rotation);
		this->euler_angles = euler_angles;			
	}
	~CDrawObjLocData() { ;}								// deconstructor
	CDrawObjLocData(const CDrawObjLocData & rhs) { ;}	// copy constructor

	void SetInsertPoint(glm::vec3 insert_pt) {this->insert_point = insert_pt;}
	glm::vec3 GetInsertPoint() {return this->insert_point;}
	void SetInsertRotation(glm::vec3 insert_rot) {this->insert_unit_rotation = glm::normalize(insert_rot);}
	glm::vec3 GetInsertRotation() {return this->insert_unit_rotation;}
	void SetEulerAngles(glm::vec3 euler) {this->euler_angles = euler;}
	glm::vec3 GetEulerAngles() {return this->euler_angles;}

private:
	glm::vec3 insert_point;			// insertion coordinates (vector from world coords origin to insertion)
	glm::vec3 insert_unit_rotation;	// rotation unit vector relative to <0,0,0> local access
	glm::vec3 euler_angles;			// angles around respective axis <x, y, z>
	//glm::vec3 WindowInfo;		// UNUSED:  a director for multiple windows
};

class CDrawingObjects : public ModelManager, public CDrawObjLocData
{
public:
	static GLuint next_drawingobj_id(){ next_id++; return next_id; }   // to obtain the next drawing object id

	// constructor
	CDrawingObjects() 
	{
//		printf("\nDefault constructor for CDrawingObjects..");
		DrawingObjID = next_drawingobj_id();
		this->IsVisible = true;
		this->IsActiveCursorSnap = false;
		this->IsPicked = false;
	}
	CDrawingObjects(GLfloat length) {
//		printf("\nLine length: %f",length);
		DrawingObjID = next_drawingobj_id();
		this->IsVisible = true;
		this->IsActiveCursorSnap = false;
		this->IsPicked = false;
	}
	CDrawingObjects(glm::vec3 model_loc, glm::vec3 model_rot, glm::vec3 model_euler)
		: CDrawObjLocData(model_loc, model_rot, model_euler) 
	{
		DrawingObjID = next_drawingobj_id();
		this->IsVisible = true;
		this->IsActiveCursorSnap = false;
		this->IsPicked = false;
	}
	~CDrawingObjects() { ;}								// deconstructor
	CDrawingObjects(const CDrawingObjects & rhs) { ;}	// copy constructor

	glm::vec3 bounding_planes[6];
	bool IsVisible;										// should the object be drawn?
	bool IsPicked;										// has the object been selected by clicked?

	/* Virtual methods from the CCursor class */
	virtual void SetRayCast(glm::vec3 ray) {;}
	virtual glm::vec3 GetRayCast() {return glm::vec3(0.0f, 0.0f, 0.0f);}
	virtual void SetWorldCoords(glm::vec3 coords) {;}
	virtual glm::vec3 GetWorldCoords() {return glm::vec3(0.0f, 0.0f, 0.0f);}
	virtual void SetSnapValues(GLfloat val1, GLfloat val2, int plane) {;}  
	virtual glm::vec3 GetSnap() {return glm::vec3(0.0f, 0.0f, 0.0f);}
	bool IsActiveCursorSnap;

	/* Virtual methods from CGrid class */
	virtual void SetQty(GLuint qty1, GLuint qty2) {;}
	virtual void SetSpacing(GLfloat spacing1, GLfloat spacing2) {;}
	virtual GLfloat GetSpacing1() {return 0;}
	virtual GLfloat GetSpacing2() {return 0;}
	virtual int GetPlane() {return XZ_PLANE;}

	/* General virtual methods */
	virtual void Draw() {;}
	virtual void MakeGridData(){;}

	/* class specific methods */
	void RotateObjectData() {;}
	void TranslateObjectData(glm::vec3 trans_amt);
	void ScaleObjectData() {;}

	GLint GetDrawingObjID() {return DrawingObjID;}

private:
	GLint DrawingObjID;			// a number to reference this DrawingObjID
	static GLuint next_id;

};


// draws a line of length centered at (0,0,0)
class CLine : public CDrawingObjects
//class CLine : public ModelManager
{
public:
	// constructor
	//CLine() {printf("\nDefault constructor for CLine..");}
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
		glDrawElements(draw_type, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

// draws a grid of lines centered at (0,0,0)
class CGrid : public CDrawingObjects
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

		draw_type = GL_LINES;

		MakeGridData();				// create the grid data
		setMeshData(vertices, indices, textures);	// sets the mesh data and creates the VAO and VBO in Mesh2
	}
	~CGrid() { ;}					// deconstructor
	CGrid(const CGrid & rhs) { ;}	// copy constructor

	void UpdateGrid(){printf("\nINCOMPLETE!!!  routine to update the grid dimensions");}		// routine to update an existing grid based on changed parameters

	void SetQty(GLuint qty1, GLuint qty2) {this->qty_1=qty1; this->qty_2=qty2;}
	void SetSpacing(GLfloat spacing1, GLfloat spacing2) {this->spacing_1=spacing1; this->spacing_2=spacing2;}
	GLfloat GetSpacing1() {return this->spacing_1;}
	GLfloat GetSpacing2() {return this->spacing_2;}
	int GetPlane() {return this->plane;}

	// create the vertex_data, index_data, texture_data for the grid 
	// calculates the data for line grids a grid in the XZ plane for now
	void MakeGridData();

	void Draw()
	{    
		// now Draw mesh
		for(GLuint i=0; i < this->meshes.size(); i++)
		{
	        glBindVertexArray(meshes[i]->VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(draw_type, meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		return;
	}

private:
	GLuint qty_1, qty_2;			// number of lines in grid, x- and z- direction
	GLfloat spacing_1, spacing_2;	// spacing between grid lines, x- and z- direction
	GLfloat length_1, length_2;		// length of grid line system
	int plane;						// plane orientation of the grid (currently XY, YZ, or XZ as defined in MathUtils.h)
};

// For drawing a rectangle area
class CRectangle: public CDrawingObjects
{
public:
	CRectangle(GLfloat x_len, GLfloat y_len, glm::vec3 model_pos, glm::vec3 model_unit_rot, glm::vec3 model_euler)
		: CDrawingObjects(model_pos, model_unit_rot, model_euler)		// constructor
	{
		this->x_len = x_len;
		this->y_len = y_len;

		draw_type = GL_TRIANGLES;

		MakeGridData();
	}
	~CRectangle() { ;}					// deconstructor
	CRectangle(const CRectangle & rhs) { ;}	// copy constructor

	void MakeGridData();

	void Draw()
	{    
		// now Draw mesh
		for(GLuint i=0; i < this->meshes.size(); i++)
		{
	        glBindVertexArray(meshes[i]->VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(draw_type, meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		return;
	}

private:
	GLfloat x_len;		// x-direction length
	GLfloat y_len;		// y-direction length
};


// For drawing a rectangular right prism
class CRectPrism: public CDrawingObjects
{
public:
	CRectPrism(GLfloat x_len, GLfloat y_len, GLfloat z_len, glm::vec3 model_pos, glm::vec3 model_unit_rot, glm::vec3 model_euler) 
		: CDrawingObjects(model_pos, model_unit_rot, model_euler)		// constructor
	{
		this->x_len = x_len;
		this->y_len = y_len;
		this->z_len = z_len;

		draw_type = GL_TRIANGLES;

		MakeGridData();
	}
	~CRectPrism() { ;}					// deconstructor
	CRectPrism(const CRectPrism & rhs) { ;}	// copy constructor

	void MakeGridData();

	void Draw()
	{    
		// now Draw mesh
		for(GLuint i=0; i < this->meshes.size(); i++)
		{
	        glBindVertexArray(meshes[i]->VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(draw_type, meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		return;
	}

private:
	GLfloat x_len;		// x-direction length
	GLfloat y_len;		// y-direction length
	GLfloat z_len;		// z-direction length
};



/*
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
class CAisc : public CDrawingObjects
{
public:
	// If its an AISC model, we don't need to initialize the data as that is down in the AISC constructor already
	//if(type == MODEL_LOAD_AISC)
	//	return;
	CAisc()
	{
		this->aisc_data.aisc_label = "Undefined";
		this->aisc_data.depth = -1;						
		this->aisc_data.flange_width = -1;				
		this->aisc_data.flange_thick = -1;				
		this->aisc_data.web_thick = -1;
		this->aisc_data.length = 0;
		draw_type = GL_TRIANGLES;
	}

	CAisc(std::string aisc_shape) 
	{
		printf("CAisc shape constructor based on strings...");
		this->aisc_data.aisc_label = aisc_shape;
		this->aisc_data.depth = 10.0f/12.0f;						
		this->aisc_data.flange_width = 8.0f/12.0f;				
		this->aisc_data.flange_thick = 0.25f/12.0f;				
		this->aisc_data.web_thick = 0.1875f/12.0f; 
		this->aisc_data.length = 96.0f/12.0f;
		draw_type = GL_TRIANGLES;

		MakeGridData();
	}

	CAisc(std::string aisc_shape, glm::vec3 model_loc, glm::vec3 model_rot, glm::vec3 model_euler)
		: CDrawingObjects(model_loc, model_rot, model_euler)
	{
		printf("CAisc shape constructor based on strings...");
		this->aisc_data.aisc_label = aisc_shape;
		this->aisc_data.depth = 10.0f/12.0f;						
		this->aisc_data.flange_width = 8.0f/12.0f;				
		this->aisc_data.flange_thick = 0.25f/12.0f;				
		this->aisc_data.web_thick = 0.1875f/12.0f; 
		this->aisc_data.length = 192.0f/12.0f;
		draw_type = GL_TRIANGLES;

		MakeGridData();
	}

	void MakeGridData();
	void Draw()
	{    
		// now Draw mesh
		for(GLuint i=0; i < this->meshes.size(); i++)
		{
	        glBindVertexArray(meshes[i]->VAO);			// uses the VAO stored in the Mesh2 c;ass
			glDrawElements(draw_type, meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		return;
	}

	/* accessors to private data */
	std::string GetShape() {return this->aisc_data.aisc_label;}
	GLfloat GetDepth() {return this->aisc_data.depth;}
	GLfloat GetFlangeWidth() {return this->aisc_data.flange_width;}
	GLfloat GetFlangeThickness() {return this->aisc_data.flange_thick;}
	GLfloat GetWebThickness() {return this->aisc_data.web_thick;}
	GLfloat GetLength() {return this->aisc_data.length;}

	AISCData aisc_data;		// stores the AISC data (if any for the shape)

private:
/*
	int aisc_shape;				// a designator for the aisc shape as defined in DrawingShapes.h
	GLfloat depth;				// depth "d"
	GLfloat bf;					// flange width, "bf"
	GLfloat tf;					// flange thickness, "tf"
	GLfloat tw;					// web thickness
	GLfloat length;				// length of the prism.  Should be moved up into the Prism abstract class?
*/
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
