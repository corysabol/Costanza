#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include "../Dependencies/glm/glm/glm.hpp"

struct VertexFormat {

	// First vertex attribute
	glm::vec3 position;

	VertexFormat( const glm::vec3 &pos ) {
		position = pos;
	}

};

#endif