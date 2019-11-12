#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create Witch with given bottom left corner, length and color
	Mesh* CreateWitch(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	// Create pillar with given bottom left corner, length and color
	Mesh* CreatePillar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

}

