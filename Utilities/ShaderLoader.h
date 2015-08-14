#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include "..\Dependencies\GLEW\glew.h"
#include "..\Dependencies\SDL\SDL.h"
#include "..\Dependencies\SDL\SDL_opengl.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace Utilities {

	class unhingedShaderLoader {

	public:

		unhingedShaderLoader( void ) {}
		~unhingedShaderLoader( void ) {}

		// Creates both shaders and loads them into the program which is used in the rendering loop
		GLuint CreateProgram( char * vertexShaderFilename, char * fragmentShaderFilename );

	private:

		// Extracts vertex and/or fragment shader contents
		std::string ReadShader( char * filename );
		
		// Creates and compiles a vertex or fragment shader
		GLuint CreateShader( GLenum shaderType, std::string source, char * shaderName );

	};

}

#endif