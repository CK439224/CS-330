#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>

#include "ShapeBuilder.h"

using namespace std;

void ShapeBuilder::UBuildCube(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 1 front left
		-0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 2
		-0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 3

		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 1 front right
		0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 4
		-0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 3


		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 1 right front
		0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 4
		0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 5

		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 1 right back
		0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 6
		0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 5


		0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 6 back left
		-0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 7
		-0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 8

		0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 6 back right
		0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 5
		-0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 8


		-0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 2 left back
		-0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 3
		-0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 8

		-0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 2 left front
		-0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 7
		-0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 8




		-0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 3 top left
		-0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 8
		0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 4

		-0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 8 top right
		0.5f,	1.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 4
		0.5f,	1.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 5

		-0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	// 2 bottom left
		-0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 7
		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 1

		-0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	// 7 bottom right
		0.5f,	0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	// 1
		0.5f,	0.0f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	// 6

	};

	UTranslator(mesh);
}

void ShapeBuilder::UBuildCylinder(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;


	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.5f, 0.0f, c[0],	c[1], c[2],	c[3], 0.5f, 0.125f });			// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,									// x
										0.5f + r * sin(i * sectorStep) ,						// y
										0.0f ,													// z
										c[0], c[1], c[2], c[3],									// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,						// texture x; adding the origin for proper alignment
										(0.125f + (0.125f * sin((i)*sectorStep))) });			// texture y


		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],									// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										(0.125f + (0.125f * sin((i + 1) * sectorStep))) });


	}

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan, top
		v.insert(v.end(), { 0.5f, 0.5f, l, c[0], c[1], c[2], c[3], 0.5f, 0.875f });				// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										l ,														// build this fan the 'l' value away from the other fan
										c[0], c[1], c[2], c[3],									// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,
										0.875f + (0.125f * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],									// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.875f + (0.125f * sin((i + 1) * sectorStep)) });
	}

	constexpr float x = 1.0f;
	float j = 1.0f / (s / x);	// for calculating texture location; change 'x' to increase or decrease how many times the texture wraps around the cylinder
	float k = 0.0f;				// for texture clamping

	// sides
	for (auto i = 1; i < s + 1; i++)
	{
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k ,
										0.25f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k + j ,
										0.75f });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										l ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k + j ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k + j ,
										0.25f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.5f + r * sin(i * sectorStep) ,
										0.0f ,
										c[0], c[1], c[2], c[3],					// color data r g b a
										k,
										0.25f });
		k += j;
	}

	mesh.v = v;
	v.clear();
	UTranslator(mesh);

}


void ShapeBuilder::UBuildPlane(GLMesh& mesh)
{

	mesh.v = {
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// 1
		 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,	// 5
		-0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// 3

		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// 1
		 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,	// 5
		 0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,	// 6


	};


	UTranslator(mesh);

}

void ShapeBuilder::UBuildCircle(GLMesh& mesh)
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };


	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++)
	{
		// triangle fan
		v.insert(v.end(), { 0.5f, 0.5f, 0.0f, c[0],	c[1], c[2],	c[3], 0.5f, 0.5f });		// origin (0.5, 0.5) works best for textures
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,								// x
										0.5f + r * sin(i * sectorStep) ,					// y
										0.0f ,												// z
										c[0],	c[1], 1.0f,	c[3],							// color data r g b a
										0.5f + (r * cos((i)*sectorStep)) ,					// texture x; adding the origin for proper alignment
										0.5f + (r * sin((i)*sectorStep)) });				// texture y
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										0.0f ,
										c[0],	c[1], 1.0f,	c[3],							// color data r g b a
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.5f + (r * sin((i + 1) * sectorStep)) });
	}
	mesh.v = v;
	v.clear();
	UTranslator(mesh);
}




void ShapeBuilder::UTranslator(GLMesh& mesh)
{
	// build the mesh

	constexpr GLuint floatsPerVertex = 3;
	constexpr GLuint floatsPerColor = 4;
	constexpr GLuint floatsPerUV = 2;

	mesh.nIndices = mesh.v.size() / (floatsPerVertex + floatsPerUV + floatsPerColor);

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer

	// use vector instead of array
	glBufferData(
		GL_ARRAY_BUFFER,
		mesh.v.size() * sizeof(float),
		&mesh.v.front(),
		GL_STATIC_DRAW
	); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	constexpr GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV + floatsPerColor);

	// Create Vertex Attribute Pointers
	// location
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// scale the object
	mesh.scale = glm::scale(glm::vec3(mesh.p[4], mesh.p[5], mesh.p[6]));

	const glm::mat4 rot = glm::mat4(1.0f);

	// rotate the object (x, y, z) (0 - 6.4, to the right)
	mesh.xrotation = glm::rotate(rot, glm::radians(mesh.p[7]), glm::vec3(mesh.p[8], mesh.p[9], mesh.p[10]));
	mesh.yrotation = glm::rotate(rot, glm::radians(mesh.p[11]), glm::vec3(mesh.p[12], mesh.p[13], mesh.p[14]));
	mesh.zrotation = glm::rotate(rot, glm::radians(mesh.p[15]), glm::vec3(mesh.p[16], mesh.p[17], mesh.p[18]));


	// move the object (x, y, z)
	mesh.translation = glm::translate(glm::vec3(mesh.p[19], mesh.p[20], mesh.p[21]));

	mesh.model = mesh.translation * mesh.xrotation * mesh.zrotation * mesh.yrotation * mesh.scale;

	mesh.gUVScale = glm::vec2(mesh.p[22], mesh.p[23]);		// scales the texture

}