#include "./h/glHeader.h"
#include "./h/Graphics.h"
#include "./h/shapeData.h"
#include "./h/Cube.h"
#include "./h/Plane.h"
#include "./h/Controls.h"
#include "./h/defs.h"
#include "./h/FileLoader.h"
#include "./h/GraphicDebugger.h"
#include "./h/Model.h"

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

	// White background
	glClearColor(0.4f, 0.4f, 0.6f, 0.0f);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Compile shaders
	GLuint shaders = loadShaders("./shaders/lightShader.vertexshader", "./shaders/lightShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	// MVP = Model, View, and Projection
	GLuint MatrixID      = glGetUniformLocation(shaders, "MVP");
	GLuint ViewMatrixID  = glGetUniformLocation(shaders,   "V");
	GLuint ModelMatrixID = glGetUniformLocation(shaders,   "M");


	mat4 m1 = mat4(1);
	//m1 = rotate(mat4(), 90.0f, vec3(0.0f, 0.0f, 0.0f));
	//m1 = translate(m1, vec3(-5.0f, -5.0f, -5.0f));
	//m1 = scale(mat4(), vec3(0.25f, 0.25f, 0.25f)); 

	glm::mat4 m2 = translate(glm::mat4(), vec3(-2.0f, -1.01f, -2.0f));
	glm::mat4 m3 = translate(glm::mat4(), vec3(8.0f, 0.0f, 8.0f));
	//Model3 = translate(Model3, vec3(0.0f, -1.0f, 0.0f));
	// Our ModelViewProjection : multiplication of our 3 matrices

	// Could wrap this in some kind of "Object Manager", but thats not needed for this assignment
	Model * model = new Model(shaders, "./obj/cube.obj");
	GraphicDebugger * debugger = new GraphicDebugger();
	Model * sphere = new Model(shaders, "./obj/sphere.obj");
	Model * custom = new Model(shaders, "./obj/random_multi_layer_test.obj", true);

	model ->initBuffers();
	sphere->initBuffers();
	custom->initBuffers();

	glUseProgram(shaders);
	GLuint LightID = glGetUniformLocation(shaders, "LightPosition_worldspace");

	// Not changing, no need to put it in the loop like the 
	//  tutorial does.
	glm::vec3 lightPos = glm::vec3(3, 3, 3);

	do {

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		controls->computeMatrices();

		// Use our shader
		glUseProgram(shaders);

		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


		if (glfwGetKey( window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			debugger->showFPS();
		}

		// Get matricies
		mat4 viewMatrix = controls->getViewMatrix();
		mat4 modelMatrix = m1;
		mat4 projectionMatrix = controls->getProjectionMatrix();
		mat4 MVP = projectionMatrix * viewMatrix * m1;


		// Could this be an inline function?
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);


		model->draw();

		modelMatrix = m2;
		MVP = projectionMatrix * viewMatrix * m2;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
		
		sphere->draw();

		modelMatrix = m3;
		MVP = projectionMatrix * viewMatrix * m3;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );


	// Cleanup, each of these objects knows how to clear its own buffers
	delete model;
	delete debugger;

	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(shaders);
}



