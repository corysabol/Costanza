#include "..\Dependencies\GLEW\glew.h"
#include "..\Dependencies\SDL\SDL.h"
#include "..\Dependencies\SDL\SDL_opengl.h"

#include "..\Utilities\ShaderLoader.h"

#include <iostream>
#include <stdio.h>
#include <string>

#define			WINDOW_TITLE					"Costanza"

// Window dimensions
#define			WINDOW_WIDTH					800
#define			WINDOW_HEIGHT					600

// The window that we will render to
SDL_Window *	globalWindow					= NULL;

// The surface contained by the window
SDL_Surface *	globalSurface					= NULL;

// OpenGL context
SDL_GLContext	globalContext;

// Render flag
bool			globalRenderQuad				= true;

// Graphics program
GLuint			program							=  0;
GLint			globalVertexPos2DLocation		= -1;
GLuint			globalVAO						=  0;
GLuint			globalIBO						=  0;

// Prototypes for RenderScene() and HandleShaders() functions because I am lazy
void RenderScene( void );

bool HandleShaders();



bool Init() {

	bool success = true; // Initialization flag

	// Initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	} else {

		// Use OpenGL 4.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		// Turn on Double Buffering with a 24 bit depth buffer
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );

		// Create window
		globalWindow = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL |
			SDL_WINDOW_SHOWN
		);

		if ( globalWindow == NULL ) {
			printf( "Window was not created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {

			// Create context
			globalContext = SDL_GL_CreateContext( globalWindow );

			if ( globalContext == NULL ) {
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {

				// Make the newly created OpenGL context current
				SDL_GL_MakeCurrent( globalWindow, globalContext );

				// Configure GLEW to make use of features in OpenGL 3.0+
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();

				if ( glewError != GLEW_OK ) {
					printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
					success = false;
				} else {

					// Synchronize the buffer swap with the monitor's vertical retrace
					if ( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
						printf( "Warning: Unable to set Vsync! SDL Error: %s\n", SDL_GetError() );
						success = false;
					} else {

						// Initialize OpenGL
						if ( !HandleShaders() ) {
							printf( "Unable to initialize OpenGL!\n" );
							success = false;
						}

					}

				}

			}

		}

	}

	return success;

}

bool HandleShaders() {

	bool success = true; // Initialization flag

	glEnable( GL_DEPTH_TEST );

	// Load and Compile Shaders
	Utilities::unhingedShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram( "Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl" );

	glGenVertexArrays( 1, &globalVAO );
	glBindVertexArray( globalVAO );

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	return success;

}

void Run() {

	if ( !Init() ) {
		printf( "Failed to initialize!\n" );
	} else {

		// Render triangle
		RenderScene();

		// Wait five seconds
		SDL_Delay( 5000 );

	}

}

void RenderScene( void ) {

	glClearColor( 1.0f, 0.0f, 0.0f, 1.0f ); // Clear red
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Use the created program
    glUseProgram( program );
 
    // Draw 3 vertices as triangles
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    // Swap the buffers
    SDL_GL_SwapWindow( globalWindow );

}

void Close() {

	// Deallocate program
	glDeleteProgram( program );

	// Destroy the window
	SDL_DestroyWindow( globalWindow );

	// Eliminate dangling reference
	globalWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();

}

int main( int argc, char * argv[] ) {

	Run();

	// OpenGL version control support
	if ( glewIsSupported( "GL_VERSION_4_5" ) ) {
		std::cout << "GLEW Version is 4.5" << std::endl;
	} else {
		std::cout << "GLEW 4.5 not supported" << std::endl;
	}

	Close();

	return 0;

}
