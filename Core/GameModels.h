#ifndef GAMEMODELS_H
#define GAMEMODELS_H

#include "../Dependencies/GLEW/glew.h"
#include "../Dependencies/SDL/SDL.h"
#include "../Dependencies/SDL/SDL_opengl.h"

#include "VertexFormat.h"

#include <vector>
#include <map>

struct Model {

	unsigned int vao; // Vertex Array Object
	std::vector<unsigned int> vbos; // Vertex Buffer Objects

	Model() {}

};

class GameModels {

public:

	GameModels();
	~GameModels();

	void CreateTriangleModel( const std::string &gameModelName );
	void DeleteModel( const std::string &gameModelName );

	unsigned int GetModel( const std::string &gameModelName );

private:

	std::map<std::string, Model> GameModelList; // For storing our models

};

#endif