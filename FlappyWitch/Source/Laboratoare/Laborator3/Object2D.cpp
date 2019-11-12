#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateWitch(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-1, 11, 0), glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(1, 8, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(2, 6, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(1.5, 5.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(2, 5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(2.5, 2.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(3, 5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(2.5, 4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(1, 4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(0, 4, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1, 3, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-2, 1, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-3, -1, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-3, -2, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-2.5, -2.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1, -2, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1, -2.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-2, -3, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-4, -3.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-4.5, -3.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-5, -3, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-6.5, -4, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-13, -3, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-13.5, -5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-13, -7, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-12, -8.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-10, -7, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-7, -5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-6, -4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-4.5, -5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-4.5, -4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-3.5, -4, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1.5, -3.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1, -4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1.5, -5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-2, -5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-2.5, -4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-3.5, -4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-4.5, -6, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-5.5, -8, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-4, -7, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-2, -6, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(2, -5.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4, -4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4.5, -4, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4, -3.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(3.5, -2.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(7, -2, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(13, -0.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(13, 0.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(11, 0, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(9, -0.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(6, -0.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4, 0, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(3.5, 1, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(3.5, 3, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5, 3, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4.5, 4, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5.5, 3.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(6, 4.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(7, 5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(6.5, 5.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5.5, 6, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5, 7, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5.5, 7.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5.5, 8, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(5, 7.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4.5, 7.5, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(4, 8, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(2, 9, 0), glm::vec3(1, 0.4f, 0.3f)),
		VertexFormat(glm::vec3(-1, 11, 0), glm::vec3(1, 0.4f, 0.3f)),
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices;
	for (unsigned short i = 0; i < 72; i++) {
		indices.push_back(i);
	}
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreatePillar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* pillar = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		pillar->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	pillar->InitFromData(vertices, indices);
	return pillar;
}