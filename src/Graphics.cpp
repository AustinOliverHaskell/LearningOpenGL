#include "glHeader.h"
#include "Graphics.h"
#include "shapeData.h"
#include "Cube.h"
#include "Plane.h"
#include "Controls.h"
#include "defs.h"
#include "FileLoader.h"

using namespace glm;

Graphics::Graphics(std::string name)
{
	windowName = name;

	// Initialise GLFW
	if(!glfwInit())
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	// These two lines make sure that the current API client is a compatable version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

	// Specifies which openGl profile to create context for openGL, openGl 3 in this case
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Graphics::~Graphics()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void Graphics::openWindow()
{
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, windowName.c_str(), NULL, NULL);

	// Check to make sure that the window handle was created succesfully
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Graphics::setupGL()
{
	Controls * controls = new Controls(window);
	FileLoader * fileLoader = new FileLoader();

	fileLoader->openFile("./obj/cube.obj");

	// White background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);

	// Compile shaders
	GLuint shaders = loadShaders("./shaders/SimpleVertexShader.vertexshader", "./shaders/SimpleFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	// MVP = Model, View, and Projection
	GLuint MatrixID = glGetUniformLocation(shaders, "MVP");

	glm::mat4 Model  = translate(glm::mat4(), vec3(0.0f, -1.01f, 0.0f));
	glm::mat4 Model2 = translate(glm::mat4(), vec3(-2.0f, -1.01f, -2.0f));
	glm::mat4 Model3 = scale(glm::mat4(), vec3(8.0f, 0.0f, 8.0f));
	//Model3 = translate(Model3, vec3(0.0f, -1.0f, 0.0f));
	// Our ModelViewProjection : multiplication of our 3 matrices

	Cube * cube = new Cube();
	Plane * plane = new Plane();

	do {
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		controls->computeMatrices();

		// Use our shader
		glUseProgram(shaders);


		glm::mat4 MVP2 = controls->getProjectionMatrix() * controls->getViewMatrix() * Model2;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
		cube->draw();

		glm::mat4 MVP = controls->getProjectionMatrix() * controls->getViewMatrix() * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		cube->draw();


		// Draw a plane
		glm::mat4 MVP3 = controls->getProjectionMatrix() * controls->getViewMatrix() * Model3;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
		plane->draw();

		// cube->getMatrix();
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );


	// Cleanup VBO
	delete cube;
	delete plane;
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(shaders);
}



