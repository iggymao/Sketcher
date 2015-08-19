#include "stdafx.h"

// GL Includes
#include <GL\glew.h>									// Used for the OpenGL types like GLuint

#include "../Headers/GUIElements.h"

//#include "../Headers/DrawingShapes.h"					// includes our drawing shape information

// forward declaration
//glm::vec3 PixeltoScreenCoords(glm::ivec3 pixel_coords, GLuint width, GLuint height);		// convert pixel coords to screen coords
//glm::ivec3 ScreentoPixelCoords(glm::vec3 pixel_coords, GLuint width, GLuint height);		// convert screen coords to pixel coords

GLuint CGUIElementButton::next_id = -1;			// set the initial value at the start of the program


// Draws the button
void CGUIElementButton::Draw()
{
	/*
	// Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left  
         0.5f, -0.5f, 0.0f, // Right 
         0.0f,  0.5f, 0.0f  // Top   
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    // Render
    // Clear the colorbuffer
//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT);

     // Draw our first triangle
     glBindVertexArray(VAO);
     glDrawArrays(GL_TRIANGLES, 0, 3);
     glBindVertexArray(0);
*/
	// now Draw mesh
	for(GLuint i=0; i < this->meshes.size(); i++)
	{
		//printf("------------------------------------");
		//printf("\n		Printing mesh #: %i",i);
		//printf("\n		   Button MeshID: %i", this->meshes[i]->GetMeshID());
		//printf("\n		   Button VAO #:  %i", this->meshes[i]->VAO);
		//printf("\n		   Button indices size #:  %i", this->meshes[i]->indices.size());
		//printf("\n		   Draw_type:  %i", this->meshes[i]->draw_type);

	    glBindVertexArray(this->meshes[i]->VAO);			// uses the VAO stored in the Mesh2 class
//		glDrawElements(this->meshes[i]->draw_type, this->meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, this->meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	return;
}

// Stores the vertices of the four corners of the buttons, and extracts the 
// maximum/minimum of each of the x- and y-coords.
void CGUIElementButton::SetButtonCornerPts()
{
	glm::vec3 corner1 = (*(this->meshes[0])).vertices[0].Position;  //lower left
	glm::vec3 corner2 = (*(this->meshes[0])).vertices[1].Position;  //lower right
	glm::vec3 corner3 = (*(this->meshes[0])).vertices[2].Position;  //upper right
	glm::vec3 corner4 = (*(this->meshes[1])).vertices[2].Position;  //upper left

	this->xmin = corner1.x;
	this->xmax = corner3.x;
	this->ymin = corner1.y;
	this->ymax = corner3.y;

	this->CornerPts.push_back(corner1);
	this->CornerPts.push_back(corner2);
	this->CornerPts.push_back(corner3);
	this->CornerPts.push_back(corner4);
}

void CGUIElementButton::ShowButtonCornerPts()
{
	printf("\n====================================");
	printf("\nCorner1:   x: %f    y: %f    z: %f", this->CornerPts[0].x, this->CornerPts[0].y, this->CornerPts[0].z);
	printf("\nCorner2:   x: %f    y: %f    z: %f", this->CornerPts[1].x, this->CornerPts[1].y, this->CornerPts[1].z);
	printf("\nCorner3:   x: %f    y: %f    z: %f", this->CornerPts[2].x, this->CornerPts[2].y, this->CornerPts[2].z);
	printf("\nCorner4:   x: %f    y: %f    z: %f", this->CornerPts[3].x, this->CornerPts[3].y, this->CornerPts[3].z);
}

CGUILayoutHUD::CGUILayoutHUD(GLuint win_width, GLuint win_height)
{
	this->WinHt = win_height;
	this->WinWidth = win_width;
	this->WinAspectRatio = (GLfloat) win_width / win_height;

	// set the default button dimensions
	// BUG!!! this pixel code does not work...produces a NEGATIVE height for the button for some reason, which I suspect reverse the
	// winding order and renders it because we've hidden back faces via CULL faces.
	this->pixel_button_dims = glm::vec3(60.0f, 60.0f, 0.0f);		// button dimensions (in pixels) -- (width, height, thick(not used = 0) )
	glm::vec3 half_pixel_button_dims = glm::vec3(0.5f*pixel_button_dims.x, 0.5f*pixel_button_dims.y, 0.0f);
	this->pixel_button_gap = glm::vec3(5.0f, 5.0f, 0.0f);			// gap measured in pixels between adjacent buttons (x, y, z)
	this->button_dims = glm::vec3(
		(pixel_button_dims.x) / (this->WinWidth),
		(pixel_button_dims.y) / (this->WinHt), 
		0.0f);
	glm::vec3 half_button_dims = glm::vec3(0.5f*button_dims.x, 0.5f*button_dims.y, 0.0f);

	//printf("\nButton_dims (pixel):   x:  %f    y: %f    z: %f",pixel_button_dims.x, pixel_button_dims.y, pixel_button_dims.z);
	//printf("\nHalf Button_dims (pixel):   x:  %f    y: %f    z: %f",half_pixel_button_dims.x, half_pixel_button_dims.y, half_pixel_button_dims.z);
	//printf("\nButton_dims (screen):   x:  %f    y: %f    z: %f",button_dims.x, button_dims.y, button_dims.z);
	this->button_gap = glm::vec3(
		(pixel_button_gap.x) / (this->WinWidth),
		(pixel_button_gap.y) / (this->WinHt), 
		0.0f);

	//printf("\nButton_gap (pixel):   x:  %f    y: %f    z: %f",pixel_button_gap.x, pixel_button_gap.y, pixel_button_gap.z);
	//printf("\nButton_gap (screen):   x:  %f    y: %f    z: %f",button_gap.x, button_gap.y, button_gap.z);
	//printf("\n------------------------------------------------------");

	for(unsigned int i = 0; i < NUM_BUTTONS; i++)
	{
		//printf("\ni (GLfloat) = %i", i);
		//printf("\ni (GLfloat) = %f", ((GLfloat)i));
		// Button1
		// measure the insert point in pixels (origin 0,0 is measured at the upper left of the window
		// ...or (-1.0,1.0 in screen coords).  The origin of the button is middel point of the button)
		this->next_pixel_insert_point = glm::vec3(
			(GLfloat)(pixel_button_gap.x+half_pixel_button_dims.x), 
			(GLfloat)(pixel_button_gap.y+half_pixel_button_dims.y+(pixel_button_dims.y+pixel_button_gap.y)*((GLfloat)i)),
			0.0f);
		//printf("\nNext point Initial (pixels):   x: %f    y: %f    z: %f",this->next_pixel_insert_point.x, this->next_pixel_insert_point.y, this->next_pixel_insert_point.z);
		this->next_insert_point = glm::vec3(((GLfloat)(next_pixel_insert_point.x) / ((GLfloat)(this->WinWidth)))-1.0f, (1.0f-((GLfloat)(next_pixel_insert_point.y)) / ((GLfloat)(this->WinHt))),0.0f);
		//printf("\nNext point Initial (screen):   x: %f    y: %f    z: %f",this->next_insert_point.x, this->next_insert_point.y, this->next_insert_point.z);

		glm::vec3 model_pos = glm::vec3(this->next_insert_point.x, this->next_insert_point.y, this->next_insert_point.z);
		//printf("\nInsert point button #%i:   x: %f    y: %f    z: %f",i,model_pos.x, model_pos.y, model_pos.z);
		glm::vec3 model_unit_rot = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 model_euler = glm::vec3(0.0f, 0.0f, 0.0f);
		CGUIElementButton *element = new CGUIElementButton(this->button_dims, model_pos, model_unit_rot, model_euler);
		element->TranslateObjectData(model_pos);
		element->SetButtonCornerPts();   // Must follow the TranslateObjectData function once the coords are set for button, store the corner points in the element
		element->ShowButtonCornerPts();
		GUIMembers.push_back(element);
	}
}

void CGUILayoutHUD::Draw(Shader shader)
{
	//printf("\nPrinting LayoutHUD.");
	
	GLfloat aspect = this->WinAspectRatio;

	shader.Use();		// turn on the shader

	// Camera/View transformation -- needed to match the original view and projection matrices for normal rendering
    glm::mat4 view = glm::mat4();	// sets an identity matrix in view	
	glm::mat4 projection = glm::mat4();
	glm::mat4 model = glm::mat4(); 

	// Ortho projection    (-left, right,      -bottom,        top,          near,    far)
	projection = glm::ortho(-aspect, aspect, (GLfloat)-1.0f, (GLfloat)1.0f, -1.0f, 1.0f);	
	// projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	// model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 0.3f, 0.5f));

	// Get the uniform locations
    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	GLint viewLoc  = glGetUniformLocation(shader.Program, "view");
	GLint projLoc  = glGetUniformLocation(shader.Program, "projection");
	GLint HUDIDLoc  = glGetUniformLocation(shader.Program, "HUDColor");
		
	// Pass the matrices to the shader
	//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//  model = glm::translate(model, GUIMembers[i]->GetInsertPoint());  // translate (or set at the insertion point)
	//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	for (unsigned int i = 0; i < this->GUIMembers.size(); i++)
	{
		// model = glm::mat4();  // sets an identity matrix into model
		//printf("\n==========================================");
		//printf("\nPrinting GUI Member #: %i",i);
		glUniform3f(HUDIDLoc, 0.1f * GLfloat(i), 0.0f, 0.0f);	// change the color of the objects that are on the highlighted list
		this->GUIMembers[i]->Draw();
	}
}

// A routine to define what happens when the CLICK is performed on a GUI HUD object.
// - GUIMember_num = ID number of the GUI object
// - Mouse_x = pixel x-coords of the point on the screen that was clicked
// - Mouse_y = pixel y-coords of the point on the screen that was clicked 
void CGUILayoutHUD::OnClick(GLuint GUIMember_num, GLfloat pixel_mouse_x, GLfloat pixel_mouse_y)
{
	bool click = false;

	GLfloat mouse_x = (-1.0f + 2.0f*(pixel_mouse_x / (GLfloat)(this->WinWidth)));
	GLfloat mouse_y = ( 1.0f - 2.0f*(pixel_mouse_y / (GLfloat)(this->WinHt)));

	for(unsigned int i = 0; i < this->GUIMembers.size(); i++)
	{
		// find coords of button -- xmin, xmax, ymin, ymax
		GLfloat x_lower = (this->GUIMembers[i]->xmin);
		GLfloat x_upper = (this->GUIMembers[i]->xmax);
		GLfloat y_lower = (this->GUIMembers[i]->ymin);
		GLfloat y_upper = (this->GUIMembers[i]->ymax);

		//printf("\nmouse_x: %f      mouse_y: %f", mouse_x, mouse_y);
		//printf("\nx_lower: %f   x_upper: %f   y_lower: %f   y_upper: %f", x_lower, x_upper, y_lower, y_upper);
		//if(mouse_x > x_lower)
		//	printf("\nX > X_LOWER:  Button successfully clicked");
		//if(mouse_x < x_upper)
		//	printf("\nX < X_UPPER:	Button successfully clicked");
		//if(mouse_y > y_lower)
		//	printf("\nY > Y_LOWER:	Button successfully clicked");
		//if(mouse_y < y_upper)
		//	printf("\nY < Y_UPPER:	Button successfully clicked");

		// compare to mouse click points
		if((mouse_x > x_lower) && (mouse_x < x_upper) && (mouse_y > y_lower) && (mouse_y < y_upper))
		{
			click = true;
			break;
		} 
	}  // end for
	if(click)
		printf("\nButton successfully clicked");
	else
		printf("\nButton missed");
}
//
//// Conversions for pixel to screen coords
//// Screen coords:  -1.0 < x < +1.0 , -1.0 < y < +1.0 -- origin (0,0) at center of window
//// Pixel coords:  0 < X < ScreenWidth, 0 < Y < ScreenHeight -- origin (0,0) at upper left corner of window
//glm::vec3 PixeltoScreenCoords(glm::ivec3 pixel_coords, GLuint width, GLuint height)
//{
//	glm::vec3 screen_coords;
//	screen_coords.x = (pixel_coords.x - 0.5f * width) * (2.0f / width);
//	screen_coords.y = (pixel_coords.y - 0.5f * height) * (-2.0f / height);
//	screen_coords.z = 0.0f;
//	return screen_coords;
//}
//
//// Screen coords:  -1.0 < x < +1.0 , -1.0 < y < +1.0 -- origin (0,0) at center of window
//// Pixel coords:  0 < X < ScreenWidth, 0 < Y < ScreenHeight -- origin (0,0) at upper left corner of window
//glm::ivec3 ScreentoPixelCoords(glm::vec3 screen_coords, GLuint width, GLuint height)
//{
//	glm::ivec3 pixel_coords;
//	pixel_coords.x = (GLuint)((0.5f * width) * (screen_coords.x + 1.0f));
//	pixel_coords.y = (GLuint)((0.5f * height) * (1.0f - screen_coords.y));
//	pixel_coords.z = 0;
//	return pixel_coords; 
//}
