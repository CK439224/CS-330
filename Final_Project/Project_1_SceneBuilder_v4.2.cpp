//**************************************************
// This Class is used as a single location where the
// shape builder functions are located.
// *************************************************

// Template
//BUILDING A SHAPE:
	//To build a shape, follow the following standard:
	//
	//		GLMesh <glmesh_name>
	//		<glmesh_name>.p = {
	//		red float, green float, blue float, alpha float,
	//		x scale float, y scale float, z scale float,
	//		x rotation degrees float, 1.0f, 0.0f, 0.0f,
	//		y rotation degrees float, 0.0f, 1.0f, 0.0f,
	//		z rotation degrees float, 0.0f, 0.0f, 1.0f,
	//		x translate float, y translate float, z translate float,
	//		x texture scale float, y texture scale float
	//		};
	//		<glmesh_name>.texFilename = "textures\\[filename.filetype]";
	//		<glmesh_name>.length = float;
	//		<glmesh_name>.height = float;
	//		<glmesh_name>.radius = float;
	//		<glmesh_name>.number_of_sides = float;
	//		ShapeBuilder::<ShapeBuilderMethod>(<glmesh_name>);
	//		**OR**
	//		ShapeBuilder::<ShapeBuild "Rainbow" Shape>(<glmesh_name>, rand() % 100 + 1);
	//		scene.push_back(<glmesh_name>);
	//
	//
	//
	// </summary>
	// <param name="scene"></param>



#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;


void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{




	// seed the rand() function once
	srand(time(nullptr));


	//********************************************************************************
	// DESK
	GLMesh plan_gMesh01;
	plan_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		20.0f, 2.0f, 10.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		90.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		1.0f, 0.0f, 0.0f,						// translate x, y, z
		1.0f, 1.0f
	};
	plan_gMesh01.texFilename = "textures\\table.jpeg";
	ShapeBuilder::UBuildPlane(plan_gMesh01);
	scene.push_back(plan_gMesh01);

	//********************************************************************************
	// Phone
	// Phone Body
	GLMesh cube_gMesh01;
	cube_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		1.0f, 0.10f, 2.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		-120.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		-1.0f, 0.254f, 6.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	cube_gMesh01.texFilename = "textures\\phoneCase.jpg";
	ShapeBuilder::UBuildCube(cube_gMesh01);
	scene.push_back(cube_gMesh01);


	// Phone Screen
	GLMesh plan_gMesh02;
	plan_gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		0.98f, 2.0f, 1.99f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		-120.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		-1.0f, 0.364f, 6.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	plan_gMesh02.texFilename = "textures\\phoneScreen.jpg";
	ShapeBuilder::UBuildPlane(plan_gMesh02);
	scene.push_back(plan_gMesh02);

	//********************************************************************************
	//Notebook
	//Paper
	GLMesh cube_gMesh02;
	cube_gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		6.0f, 0.25f, 5.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,					// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		-0.5f, 0.002f, 6.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	cube_gMesh02.texFilename = "textures\\notebookPaper.jpg";
	ShapeBuilder::UBuildCube(cube_gMesh02);
	scene.push_back(cube_gMesh02);

	//Back Cover
	GLMesh plan_gMesh03;
	plan_gMesh03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		6.0f, 0.25f, 5.05f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,					// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		-0.5f, 0.001f, 6.02f,					// translate x, y, z
		1.0f, 1.0f
	};
	plan_gMesh03.texFilename = "textures\\notebookCover.jpg";
	ShapeBuilder::UBuildPlane(plan_gMesh03);
	scene.push_back(plan_gMesh03);

	//Front Cover
	GLMesh plan_gMesh04;
	plan_gMesh04.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		6.0f, 0.25f, 5.05f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,					// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		-0.5f, 0.253f, 6.02f,					// translate x, y, z
		1.0f, 1.0f
	};
	plan_gMesh04.texFilename = "textures\\notebookCover.jpg";
	ShapeBuilder::UBuildPlane(plan_gMesh04);
	scene.push_back(plan_gMesh04);

	// Notebook binding
	GLMesh cyl_gMesh01;
	cyl_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		1.0f, 1.0f, 1.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		90.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		-3.499f, -0.374f, 4.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	cyl_gMesh01.length = 5.998f;	cyl_gMesh01.radius = 0.125f;	cyl_gMesh01.number_of_sides = 50.0f;
	cyl_gMesh01.texFilename = "textures\\notebookCover.jpg";
	ShapeBuilder::UBuildCylinder(cyl_gMesh01);
	scene.push_back(cyl_gMesh01);

	//********************************************************************************
// Computer
//Bottom cube
	GLMesh cube_gMesh03;
	cube_gMesh03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		9.0f, 0.25f, 6.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		90.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		0.0f, 0.0f, -4.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	cube_gMesh03.texFilename = "textures\\laptopColor.jpg";
	ShapeBuilder::UBuildCube(cube_gMesh03);
	scene.push_back(cube_gMesh03);

	//KeyBoard Plane
	GLMesh plan_gMesh05;
	plan_gMesh05.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		9.0f, 0.1f, 6.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		-90.0f, 0.0f, 1.0f, 0.0f,					// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		0.0f, 0.251f, -4.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	plan_gMesh05.texFilename = "textures\\keyboard1.jpg";
	ShapeBuilder::UBuildPlane(plan_gMesh05);
	scene.push_back(plan_gMesh05);

	//Monitor Cube
	GLMesh cube_gMesh04;
	cube_gMesh04.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		8.999f, 0.25f, 6.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		90.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		60.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		4.51f, 2.6f, -4.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	cube_gMesh04.texFilename = "textures\\laptopColor.jpg";
	ShapeBuilder::UBuildCube(cube_gMesh04);
	scene.push_back(cube_gMesh04);

	//KeyBoard Plane
	GLMesh plan_gMesh06;
	plan_gMesh06.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		8.998f, 0.25f, 5.90f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		-90.0f, 0.0f, 1.0f, 0.0f,					// y amount of rotation, rotate x, y, z
		60.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		4.30f, 2.75f, -4.5f,					// translate x, y, z
		1.0f, 1.0f
	};
	plan_gMesh06.texFilename = "textures\\screen1.jpg";
	ShapeBuilder::UBuildPlane(plan_gMesh06);
	scene.push_back(plan_gMesh06);

	//********************************************************************************
	// Speaker
	// Speaker Main Body
	GLMesh cyl_gMesh02;
	cyl_gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		1.0f, 1.0f, 1.0f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		0.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		3.5f, 0.25f, 2.0f,					// translate x, y, z
		1.0f, 1.0f
	};
	cyl_gMesh02.length = 4.5f;	cyl_gMesh02.radius = 0.75f;	cyl_gMesh02.number_of_sides = 50.0f;
	cyl_gMesh02.texFilename = "textures\\speakerMesh.jpg";
	ShapeBuilder::UBuildCylinder(cyl_gMesh02);
	scene.push_back(cyl_gMesh02);

	// Speaker Button Microphone
	GLMesh cube_gMesh05;
	cube_gMesh05.p = {
		1.0f, 1.0f, 1.0f, 1.0f,					// color r, g, b a
		3.3f, 0.1f, 0.2f,						// scale x, y, z
		0.0f, 1.0f, 0.0f, 0.0f,					// x amount of rotation, rotate x, y, z
		90.0f, 0.0f, 1.0f, 0.0f,				// y amount of rotation, rotate x, y, z
		0.0f, 0.0f, 0.0f, 1.0f,					// z amount of rotation, rotate x, y, z
		4.0f, 1.4f, 4.25f,					// translate x, y, z
		1.0f, 1.0f
	};
	cube_gMesh05.texFilename = "textures\\speakerButtons1.jpg";
	ShapeBuilder::UBuildCube(cube_gMesh05);
	scene.push_back(cube_gMesh05);
	
}



