#include "Core.h"
#include <GL\glew.h>


Core::Core(int width, int height, const string& title)
{
	m_width = width;
	m_height = height;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	GLenum result = glewInit();
	if (result != GLEW_OK)
		cerr << "Glew failed to initialize!" << endl;
	
	isClosed = false;


	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

}


Core::~Core()
{	
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Core::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Core::Update()
{
	
	
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			isClosed = true;
			break;
		//case SDL_KEYDOWN:	// Keyboard input handling gets called less often then the one in input namespace
		//	switch (e.key.keysym.sym)
		//	{
		//	case SDLK_LEFT: cout << "LEFT" << endl; break;
		//	//case SDLK_UP: cout << "UP" << endl; break;
		//	case SDLK_RIGHT: cout << "RIGHT" << endl; break;
		//	case SDLK_DOWN: cout << "DOWN" << endl; break;
		//	}
		//	break;

		case SDL_MOUSEBUTTONDOWN:	// Mouse input handling only gets called on the initial press
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT: cout << "LEFT MOUSE BUTTON x: " << e.button.x << " + y: " << e.button.y << endl; break;
			case SDL_BUTTON_RIGHT: cout << "RIGHT MOUSE BUTTON x: " << e.button.x << " + y: " << e.button.y << endl; break;
			}
		default:
			break;
		}
	}


	SDL_GL_SwapWindow(m_window);
}

