#ifndef _MathUtils_H
#define _MathUtils_H

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const int X_PLANE = 0; // for the YZ plane
static const int Y_PLANE = 1; // for the XZ plane
static const int Z_PLANE = 2; // for the XY plane

// forward declaration
GLfloat area_3P(glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3);
GLfloat area_2V(glm::vec3 A_vector, glm::vec3 B_vector);
int point_inside_triangle(glm::vec3 check_point, glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3);

// Compute the area bounded by three points
GLfloat area_3P(glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3)
{
	GLfloat area;
	glm::vec3 vec1, vec2;
	vec1 = (point_2 - point_1);
	vec2 = (point_3 - point_1);
	area = area_2V(vec1, vec2);
	return area;
}

// Compute the area given two input vec3
GLfloat area_2V(glm::vec3 A_vector, glm::vec3 B_vector)
{
	GLfloat area;
	glm::vec3 cross_product = glm::cross(A_vector, B_vector);
	area = (GLfloat)(0.5 * glm::length(cross_product));
	return area;
}

// Check if a point is inside a triangular region (bounded by two vectors)
// returns 0 if the point is inside the triangle (or on the boundary)
// returns 1 if the point is outside the triangle
int point_inside_triangle(glm::vec3 check_point, glm::vec3 point_1, glm::vec3 point_2, glm::vec3 point_3)
{
	GLfloat Area_tot, Area1, Area2, Area3;
	Area_tot = area_3P(point_1, point_2, point_3);
	Area1 = area_3P(check_point, point_1, point_2);
	Area2 = area_3P(check_point, point_2, point_3);
	Area3 = area_3P(check_point, point_3, point_1);

	if (Area_tot == (Area1+Area2+Area3))
		return 0;
	
	return 1;
}

// Find where a line (casted ray) interests a specified plane (X=0, Y=0, or Z=0) for now
glm::vec3 ray_intersect_plane(glm::vec3 camera_loc, glm::vec3 ray, int plane)
{
	glm::vec3 intersect_point;
	GLfloat t, x=0, y=0, z=0;
	// the intersect plane of interest -- in this case the z = 0 plane
	switch(plane)
	{
		case X_PLANE:
			t = ((x-camera_loc.x) / ray.x);
			break;
		case Y_PLANE:
			t = ((y-camera_loc.y) / ray.y);
			break;
		case Z_PLANE:
			t = ((z-camera_loc.z) / ray.z);
			break;
		default:
			printf("\nNon X, Y, or Z, plane declared");
			return glm::vec3(NULL, NULL, NULL);
	}
	
	printf("\nt-parameter = %f",t);
	x = camera_loc.x + t * ray.x;
	y = camera_loc.y + t * ray.y;
	z = camera_loc.z + t * ray.z;
	intersect_point = glm::vec3(x, y, z);
	return intersect_point;
}

#endif