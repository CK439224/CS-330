//---------------------------------------------------
//
// Christopher King
// CS-330 Comp Graphic and Visualization
// 7-1 Final Project
//
//
//---------------------------------------------------


#include "ShapeBuilder.h"
#include "Mesh.h"
#include "SceneBuilder.h"
#include "shader.h"

// image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// shader program macros
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

//window title
const char* const WINDOW_TITLE = "Christopher King : 7-1 Final Project";

//window width, height
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

struct GLightMesh {
	GLuint vao;				// Light VAO
	GLuint vbo;				// Light VBO
	GLuint nVertices;		// Light indices
};

GLightMesh spotLightMesh;
GLightMesh keyLightMesh;
ShapeBuilder builder;

//main window
GLFWwindow* gWindow = nullptr;

//shader program
GLuint gShaderProgram;
GLuint gLightProgramId;

// scene vector for drawing shapes
vector<GLMesh> scene;

// variable to handle ortho change
bool perspective = false;


// camera
//Camera gCamera(glm::vec3(0.0f, 1.5f, 5.0f));
Camera gCamera(glm::vec3(-5.0f, 4.5f, -0.3f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, -30.0f);

float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;


// timing
float gDeltaTime = 0.0f; // time between current frame and last frame
float gLastFrame = 0.0f;

// Light color, position, and scale
glm::vec3 gSpotLightColor(1.0f, 1.0f, 1.0f);
glm::vec3 gSpotLightPosition(0.0f, 30.0f, 10.0f);
glm::vec3 gSpotLightScale(0.1f);


// Light color, position, and scale
glm::vec3 gSpotLightColor2(1.0f, 1.0f, 1.0f);
glm::vec3 gSpotLightPosition2(0.0f, 30.0f, -10.0f);
glm::vec3 gSpotLightScale2(0.1f);

bool gSpotLightOrbit = true;

//initialize program
bool UInitialize(int, char* [], GLFWwindow** window);
//set window size
void UResizeWindow(GLFWwindow* window, int width, int height);
//process user input
void UProcessInput(GLFWwindow* window);
//render graphics
void URender(vector<GLMesh> scene);
//compile shaders
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);
//free up memory
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);
void UDestroyTexture(GLuint textureId);

// build shapes
void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildPlane(GLMesh& mesh, vector<float> properties);
void UBuildCircle(GLMesh& mesh, vector<float> properties, float radius);


// keyboard and mouse input
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// texture create
bool UCreateTexture(const char* filename, GLuint& textureId);
//void UCreateLightMesh(GLightMesh& lightMesh);


// Vertex Shader Source Code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position;	// Vertex data from Vertex Attrib Pointer 0
layout(location = 1) in vec3 normal;		// Normal data from Vertex Attrib Pointer 1
layout(location = 2) in vec2 textureCoordinate;  // Texture data from Vertex Attrib Pointer 2

out vec3 vertexFragmentPos;				// variable to transfer to fragment shader
out vec3 vertexNormal;					// variable to transfer normals data to the fragment shader
out vec2 vertexTextureCoordinate;		// variable to transfer texture data to the fragment shader

//uniform mat4 shaderTransform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
	vertexFragmentPos = vec3(model * vec4(position, 1.0f));
	vertexNormal = mat3(transpose(inverse(model))) * normal;
	vertexTextureCoordinate = textureCoordinate;

}
);

// Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,

	in vec3 vertexFragmentPos;
in vec3 vertexNormal;
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 keyLightColor;
uniform vec3 lightPos;
uniform vec3 keyLightPos;
uniform vec3 viewPosition;

uniform sampler2D uTexture;
uniform vec2 uvScale;

void main()
{
	//Calculate Ambient lighting*/
	float spotStrength = 0.0000001f; // Set ambient or global lighting strength
	float keyStrength = 0.0000005f; // Set ambient or global lighting strength
	vec3 spot = spotStrength * lightColor; // Generate ambient light color
	vec3 key = keyStrength * keyLightColor;

	//Calculate Diffuse lighting*/
	vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
	vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
	vec3 keyLightDirection = normalize(keyLightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube

	float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
	float keyImpact = max(dot(norm, keyLightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light

	vec3 diffuse = impact * lightColor; // Generate diffuse light color
	vec3 keyDiffuse = keyImpact * keyLightColor;

	//Calculate Specular lighting*/
	float specularIntensity = 0.4f; // Set specular light strength
	float highlightSize = 16.0f; // Set specular highlight size
	vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
	vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
	//Calculate specular component
	float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
	vec3 specular = specularIntensity * specularComponent * lightColor * 0.03;
	vec3 keySpecular = specularIntensity * specularComponent * keyLightColor * 0.03;

	// Texture holds the color to be used for all three components
	vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

	// Calculate phong result
	vec3 phong = (spot + key + diffuse + keyDiffuse + specular /*+ objectColor*/) * textureColor.xyz;

	fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU

}
);

// Light Shader Source Code
const GLchar* lampVertexShaderSource = GLSL(440,

	layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
}
);

// Light Fragment Shader Source Code
const GLchar* lampFragmentShaderSource = GLSL(440,

	out vec4 fragmentColor; // For outgoing light color to the GPU

void main()
{
	fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
}
);



// OpenGL expects 0.0 coordinate on the y-axis to be on the bottom side of the image
// but images usually have 0.0 at the top of the y-axis. Due to this, the following
// code is to flip the image virtically and right side up.
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
	for (int j = 0; j < height / 2; ++j)
	{
		int index1 = j * width * channels;
		int index2 = (height - 1 - j) * width * channels;

		for (int i = width * channels; i > 0; --i)
		{
			unsigned char tmp = image[index1];
			image[index1] = image[index2];
			image[index2] = tmp;
			++index1;
			++index2;
		}
	}
}



//main
int main(int argc, char* argv[])
{

	//check if initialized correctly
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;


	SceneBuilder::UBuildScene(scene);

	//build shader 
	if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
		gShaderProgram))
		return EXIT_FAILURE;


	for (auto& m : scene)
	{
		if (!UCreateTexture(m.texFilename, m.textureId))
		{
			cout << "Failed to load texture " << m.texFilename << endl;
			//cin.get();
			return EXIT_FAILURE;

		}

		if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
			gShaderProgram))
			//cout << "Fail 2" << endl;	cin.get();

			return EXIT_FAILURE;
	}

	if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLightProgramId))
		return EXIT_FAILURE;

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	glUseProgram(gShaderProgram);
	// Set the texture as texture unit 0
	glUniform1i(glGetUniformLocation(gShaderProgram, "uTexture"), 0);

	//rendering loop
	while (!glfwWindowShouldClose(gWindow))
	{
		// color of window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// DeltaTime is used to smooth out the camera movement
		float currentFrame = glfwGetTime();
		gDeltaTime = currentFrame - gLastFrame;
		gLastFrame = currentFrame;

		//process user input
		UProcessInput(gWindow);

		//render frame
		URender(scene);

		glfwPollEvents();
	}

	// Release mesh as it is no longer needed
	for (auto& m : scene)
	{
		UDestroyMesh(m);
	}

	scene.clear();

	// Release shaderProgram as it is no longer needed
	UDestroyShaderProgram(gShaderProgram);

	//exit
	exit(EXIT_SUCCESS);

}






// functions
// initialize and build shaders
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	// Glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	// glad: load all OpenGL function pointers
	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}

	return true;
}
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
	//error reporting
	int success = 0;
	char infoLog[512];

	//create shader program object
	programId = glCreateProgram();

	//create vertex and frag shader obj
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//get shader source
	glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

	//compile vertex shader
	glCompileShader(vertexShaderId);


	//check for errors
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	//compile frag shader
	glCompileShader(fragmentShaderId);

	//check for errors
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	//shaders compiled, attach to shader program object from above
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	//link the program object
	glLinkProgram(programId);

	//check for linking errors
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glUseProgram(programId);

	return true;
}

// process user input and windows changes
void UProcessInput(GLFWwindow* window)
{


	// exit program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCamera.ProcessKeyboard(UP, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		gCamera.ProcessKeyboard(DOWN, gDeltaTime);


	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (!perspective) {
			perspective = true;
		}
		else {
			perspective = false;
		}
	}

}
void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (gFirstMouse)
	{
		gLastX = xpos;
		gLastY = ypos;
		gFirstMouse = false;
	}

	float xoffset = xpos - gLastX;
	float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

	gLastX = xpos;
	gLastY = ypos;

	gCamera.ProcessMouseMovement(xoffset, yoffset);
}
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// change camera speed by mouse scroll
	gCamera.ProcessMouseScroll(yoffset);
}
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "Left mouse button pressed" << endl;
		else
			cout << "Left mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "Middle mouse button pressed" << endl;
		else
			cout << "Middle mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "Right mouse button pressed" << endl;
		else
			cout << "Right mouse button released" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}

// render the scene
void URender(vector<GLMesh> scene)
{
	/*
	// Borrowed from the Tutorial; animates the Spot Light to circle around the scene
	constexpr float angularVelocity = glm::radians(45.0f);
	if (gSpotLightOrbit)
	{
		glm::vec4 newPosition = glm::rotate(angularVelocity * gDeltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(gSpotLightPosition, 1.0f);
		gSpotLightPosition.x = newPosition.x;
		gSpotLightPosition.y = newPosition.y;
		gSpotLightPosition.z = newPosition.z;
	}
	*/

	//Shader lightingShader("shaderfiles/6.multiple_lights.vs", "shaderfiles/6.multiple_lights.fs");
	//Shader lightCubeShader("shaderfiles/6.light_cube.vs", "shaderfiles/6.light_cube.fs");

	// Enable z-depth
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// transform the camera (x, y, z)
	glm::mat4 view = gCamera.GetViewMatrix();

	// create perspective projection (fov, aspect ratio, near plane, far plane)
	glm::mat4 projection;
	if (!perspective)
	{
		// perspective view (default)
		projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	}
	else
		// orthographic view
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);


	// loop to draw each shape individually
	for (auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		// activate vbo's
		glBindVertexArray(mesh.vao);

		// set shader
		glUseProgram(gShaderProgram);

		// gets and passes transform matrices to shader program
		GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
		GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
		GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// Reference matrix uniforms from the shape shader program for the shape color, light color, light position, and camera position
		GLint objectColorLoc = glGetUniformLocation(gShaderProgram, "objectColor");

		// Spotlight
		GLint lightColorLoc = glGetUniformLocation(gShaderProgram, "lightColor");
		GLint lightPositionLoc = glGetUniformLocation(gShaderProgram, "lightPos");

		// Key light
		GLint keyLightColorLoc = glGetUniformLocation(gShaderProgram, "keyLightColor");
		GLint keyLightPositionLoc = glGetUniformLocation(gShaderProgram, "keyLightPos");

		// Camera view
		GLint viewPositionLoc = glGetUniformLocation(gShaderProgram, "viewPosition");

		// Pass color, light, and camera data to the shape shader 
		glUniform3f(objectColorLoc, mesh.p[0], mesh.p[1], mesh.p[2]);

		// Spot Light
		glUniform3f(lightColorLoc, gSpotLightColor.r, gSpotLightColor.g, gSpotLightColor.b);
		glUniform3f(lightPositionLoc, gSpotLightPosition.x, gSpotLightPosition.y, gSpotLightPosition.z);

		// Key Light
		glUniform3f(keyLightColorLoc, gSpotLightColor2.r, gSpotLightColor2.g, gSpotLightColor2.b);
		glUniform3f(keyLightPositionLoc, gSpotLightPosition2.x, gSpotLightPosition2.y, gSpotLightPosition2.z);


		const glm::vec3 cameraPosition = gCamera.Position;
		glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);


		GLint UVScaleLoc = glGetUniformLocation(gShaderProgram, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(mesh.gUVScale));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.textureId);

		// Draws the shape
		glDrawArrays(GL_TRIANGLES, 0, mesh.nIndices);

	}


	// Draw the Spot Light
	glUseProgram(gLightProgramId);
	glBindVertexArray(spotLightMesh.vao);

	// Light location and Scale
	glm::mat4 model = glm::translate(gSpotLightPosition) * glm::scale(gSpotLightScale);

	// Matrix uniforms from the Light Shader program
	GLint modelLoc = glGetUniformLocation(gLightProgramId, "model");
	GLint viewLoc = glGetUniformLocation(gLightProgramId, "view");
	GLint projLoc = glGetUniformLocation(gLightProgramId, "projection");

	// Matrix data
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw the light
	glDrawArrays(GL_TRIANGLES, 0, spotLightMesh.nVertices);



	// Draw the Key Light
	glUseProgram(gLightProgramId);
	glBindVertexArray(keyLightMesh.vao);

	// Light location and Scale
	model = glm::translate(gSpotLightPosition2) * glm::scale(gSpotLightScale2);

	// Matrix uniforms from the Light Shader program
	modelLoc = glGetUniformLocation(gLightProgramId, "model");
	viewLoc = glGetUniformLocation(gLightProgramId, "view");
	projLoc = glGetUniformLocation(gLightProgramId, "projection");

	// Matrix data
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw the light
	glDrawArrays(GL_TRIANGLES, 0, keyLightMesh.nVertices);

	// deactivate vao's
	glBindVertexArray(0);
	glUseProgram(0);

	// swap front and back buffers
	glfwSwapBuffers(gWindow);

}

// clean-up methods
void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
}
void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}


bool UCreateTexture(const char* filename, GLuint& textureId)
{
	int width, height, channels;
	unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
	if (image)
	{
		flipImageVertically(image, width, height, channels);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		else if (channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			cout << "Not implemented to handle image with " << channels << " channels" << endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

		return true;
	}

	// Error loading the image
	return false;
}
void UDestroyTexture(GLuint textureId)
{
	glGenTextures(1, &textureId);
}

