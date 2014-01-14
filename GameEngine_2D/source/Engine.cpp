// Will Gilstrap - Game Engine
// 1/14/2013

#include <Engine.h>

bool g_bWindowClosed = false; 
bool g_bFullscreen = false;
char * a_pWindowTitle = "Game";

int GLFWCALL Engine::windowCloseListener() 
{ 
	g_bWindowClosed = true; 
	return 0; 
}

int Engine::openWindow()
{
	//We need to call glfwInit() to init GLFW if this returns a value other than 
	// 0 we have been unable to create a window or OpenGL context 
	if( !glfwInit() ) 
	{ 
		return -1; 
	} 
	//This is a Window hint to tell GLFW that we do not wish to allow our window to 
	//be resizeable
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE); 
	//This is the call to GLFW to open our window 
	glfwOpenWindow( 1024, 768, // resolution 
		8,8,8,8, // bits per colour channel (RGBA)
		24, // depth bits 
		8, // stencil bits 
		(g_bFullscreen)? GLFW_FULLSCREEN:GLFW_WINDOW); 
	//Here we are setting the title for our window 
	glfwSetWindowTitle((a_pWindowTitle != NULL)? a_pWindowTitle : "GLFW Window"); 
	glfwSwapInterval(0); 
	//set listeners for window events such as close window 
	//windowCloseListener is a static function that will be called when the close 
	//button on the window is clicked  
	glfwSetWindowCloseCallback(&windowCloseListener); 
	//………Insert this into the main.cpp example given in the setting up GLFW section 
	// start GLEW 
	if (glewInit() != GLEW_OK) 
	{ 
		// OpenGL didn't start-up! shutdown GLFW and return an error code 
		glfwTerminate(); 
		return -1; 
	} 

	//Set the clear colour for OpenGL 
	glClearColor( 0.f, 0.4f, 0.65f, 1.f); 
	glColor4f( 0.f, 0.f, 0.f, 1.f ); 
	//As we're going to draw in 2D set up an orthographic projection. 
	//This type of projection has no perspective. This projection is set up so 
	//that one pixel on the screen is one unit in 
	//world co-ordinates 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	//Older versions of OpenGL allow you to set up a view matrix with the following 
	//call. 
	//this function is no longer supported in more recent versions of OpenGL 
	glOrtho( 0.f, 1024, 768, 0.f, 0.f, 100.f ); 
	//Enable some Blending. 
	glEnable(GL_BLEND); 
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

	glEnable(GL_DEPTH); 
	glDepthFunc(GL_LEQUAL);
}

unsigned int Engine::LoadTexture(const char* a_szTexture, unsigned int a_uiFormat /* = GL_RGBA */)
{ 
	FIBITMAP* pBitmap = nullptr; 

	// check the file signature and deduce its format and load it 
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(a_szTexture, 0); 
	if (fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) 
	{ 
		pBitmap = FreeImage_Load(fif, a_szTexture); 
	} 

	if (pBitmap == nullptr) 
	{ 
		printf("Error: Failed to load image '%s'!\n", a_szTexture);
		printf(a_szTexture);
		return 0; 
	} 

	// optionally get the image width and height 
	//if (a_uiWidth != nullptr) 
	//*a_uiWidth = FreeImage_GetWidth(pBitmap); 
	//if (a_uiHeight != nullptr) 
	//*a_uiHeight = FreeImage_GetHeight(pBitmap); 

	// force the image to RGBA 
	unsigned int bpp = FreeImage_GetBPP(pBitmap); 
	//if( a_uiBPP != nullptr ) 
	bpp = bpp/8; 

	FREE_IMAGE_COLOR_TYPE fi_colourType = FreeImage_GetColorType(pBitmap); 
	if (fi_colourType != FIC_RGBALPHA ) 
	{ 
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(pBitmap); 
		FreeImage_Unload(pBitmap); 
		pBitmap = ndib; 
		bpp = FreeImage_GetBPP(pBitmap); 
		fi_colourType = FreeImage_GetColorType(pBitmap); 
	} 

	// get the pixel data 
	BYTE* pData = FreeImage_GetBits(pBitmap); 

	// try to determine data type of file (bytes/floats) 
	FREE_IMAGE_TYPE fit = FreeImage_GetImageType(pBitmap); 
	GLenum eType = (fit == FIT_RGBF || fit == FIT_FLOAT) ? 
GL_FLOAT:GL_UNSIGNED_BYTE; 

	// create GL texture 
	GLuint textureID = -1; 
	glGenTextures( 1, &textureID ); 
	glBindTexture( GL_TEXTURE_2D, textureID ); 
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
		FreeImage_GetWidth(pBitmap), 
		FreeImage_GetHeight(pBitmap), 0, 
		a_uiFormat, eType, pData); 

	// specify default filtering and wrapping 
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); 
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	// unbind texture 
	glBindTexture( GL_TEXTURE_2D, 0 ); 

	// delete data 
	FreeImage_Unload(pBitmap); 

	return textureID; 
} 