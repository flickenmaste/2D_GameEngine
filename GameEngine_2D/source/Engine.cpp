// Will Gilstrap - Game Engine
// 1/23/2014

#include <Engine.h>

// Globals
//GLFWwindow * window;
// Keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 1920;
int g_gl_height = 1080;

// Constructor
Engine::Engine()
{
	as::RunApplication();
	tiny::parseDoc("settings.xml");
	tiny2::parseDoc("settings.xml");
	Engine::OpenWindow();
	Engine::RunGame();
}

// Destructor
Engine::~Engine()
{
	glfwTerminate();
}

// error message
void glfw_error_callback (int error, const char* description)
{
	fputs (description, stderr);
	gl_log (description, __FILE__, __LINE__);
}

// open GLFW window
unsigned int Engine::OpenWindow()
{

	char message[256];
	sprintf (message, "starting GLFW %s", glfwGetVersionString () );
	assert (gl_log (message, __FILE__, __LINE__));
	glfwSetErrorCallback (glfw_error_callback);
	
	// Open an OS window using GLFW
	if (!glfwInit())
	{
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// AntiAliasing
	glfwWindowHint (GLFW_SAMPLES, 4);

	// Get the primary monitor
	GLFWmonitor* mon = glfwGetPrimaryMonitor ();

	// THis lets us use the video mode for the monitor we pass
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);

	window = glfwCreateWindow(vmode->width, vmode->height, "Hello Triangle", NULL /* or mon for fscreen */, NULL);
	if (!window)
	{
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwSetWindowSize(window, vmode->width, vmode->height);
	glfwMakeContextCurrent(window);
	// Start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	// Get version info
	const GLubyte* renderer = glGetString (GL_RENDERER);	// Get Renderer string
	const GLubyte* version = glGetString (GL_VERSION); // Version as a string
	printf ("Renderer %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	// Tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST);	// enable depth-testing
	glDepthFunc (GL_LESS);
	// Depth-testing interprets a smaller value as "closer"

}

// Run the game
void Engine::RunGame()
{
	Sprite player;
	mat4 trans;
	player.LoadTexture("face.bmp", trans);
	
	// Draw stuff
	while (!glfwWindowShouldClose (window))
	{
		// Draw FPS
		_update_fps_counter (window);
		
		glViewport (0, 0, g_gl_width, g_gl_height);

		// Wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Draw sprite
		player.DrawTex(trans);
		// Update other events like input handling
		glfwPollEvents ();
		Input::Rotate(window, player, trans);
		Input::Scale(window, player, trans);
		Input::Move(window, player, trans);
		// Put the stuff we've been drawing on the display
		glfwSwapBuffers (window);
	}

}

// A call-back function
void Engine::glfw_window_size_callback (GLFWwindow* window, int width, int height)
{
	g_gl_width = width;
	g_gl_height = height;

	// update any perspective matrices used here
}

// Draw fps
void Engine::_update_fps_counter (GLFWwindow* window) {
	static double previous_seconds = glfwGetTime ();
	static int frame_count;
	double current_seconds = glfwGetTime ();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf (tmp, "opengl @ fps: %.2lf", fps);
		glfwSetWindowTitle (window, tmp);
		frame_count = 0;
	}
	frame_count++;
}