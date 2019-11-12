#include "Laborator3.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 240;
	translateY = 450;
	velocity = 0;
	fall = true;
	score = 0;
	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	ok = 0;
	// initialize angularStep
	angularStep = 0;

	x_pillar1 = 400;
	x_pillar2 = 2.5 * x_pillar1;
	y_pillar1 = 0;
	y_scale_pillar1 = 2;
	y_scale_pillar2 = 2;

	Mesh* witch = Object2D::CreateWitch("witch", corner, squareSide, glm::vec3(1, 0, 0));
	AddMeshToList(witch);
	
	Mesh* pillar1 = Object2D::CreatePillar("pillar1", corner, squareSide, glm::vec3(0, 1, 0), true);
	AddMeshToList(pillar1);

	Mesh* pillar2 = Object2D::CreatePillar("pillar2", corner, squareSide, glm::vec3(1, 1, 0), true);
	AddMeshToList(pillar2);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{

	glm::ivec2 resolution = window->GetResolution();

	if (translateY < 20 || translateY > 690) {
		GAME_OVER = true;
	}
	if (GAME_OVER == false) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translateX, translateY);
		modelMatrix *= Transform2D::Scale(4.3, 4.3);
		modelMatrix *= Transform2D::Rotate(angularStep);

		RenderMesh2D(meshes["witch"], shaders["VertexColor"], modelMatrix);

		//primul stalp
		x_pillar1 -= 4;
		if (x_pillar1 < -100) {
			x_pillar1 = resolution.x;
			y_scale_pillar1 = rand() % 4 + 1.5;
		}
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar1, y_pillar1);
		modelMatrix *= Transform2D::Scale(0.5, y_scale_pillar1);

		RenderMesh2D(meshes["pillar1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar1, 160 + y_scale_pillar1 * 100);
		modelMatrix *= Transform2D::Scale(0.5, 7 - y_scale_pillar1);

		RenderMesh2D(meshes["pillar1"], shaders["VertexColor"], modelMatrix);
		//end primul stalp

		x_pillar2 -= 4;
		if (x_pillar2 < -100) {
			x_pillar2 = resolution.x;
			y_scale_pillar2 = rand() % 5 + 1.5;
		}

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar2, y_pillar2);
		modelMatrix *= Transform2D::Scale(0.5, y_scale_pillar2);

		RenderMesh2D(meshes["pillar2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar2, 160 + y_scale_pillar2 * 100);
		modelMatrix *= Transform2D::Scale(0.5, 7 - y_scale_pillar2);

		RenderMesh2D(meshes["pillar2"], shaders["VertexColor"], modelMatrix);
	}
	else {   //GAME_OVER == true
		cout << "FINAL SCORE IS: " << score << endl;
		cout << "GAME OVER";

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar1, y_pillar1);
		modelMatrix *= Transform2D::Scale(0.5, y_scale_pillar1);

		RenderMesh2D(meshes["pillar1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar1, 160 + y_scale_pillar1 * 100);
		modelMatrix *= Transform2D::Scale(0.5, 7 - y_scale_pillar1);

		RenderMesh2D(meshes["pillar1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar2, y_pillar2);
		modelMatrix *= Transform2D::Scale(0.5, y_scale_pillar2);

		RenderMesh2D(meshes["pillar2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_pillar2, 160 + y_scale_pillar2 * 100);
		modelMatrix *= Transform2D::Scale(0.5, 7 - y_scale_pillar2);

		RenderMesh2D(meshes["pillar2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translateX - 5, translateY);
		modelMatrix *= Transform2D::Scale(4.3, 4.3);

		RenderMesh2D(meshes["witch"], shaders["VertexColor"], modelMatrix);
		Sleep(2000);
		exit(0);
	}
	if (x_pillar1 == translateX || x_pillar2 == translateX) {
		score++;
		cout << "Score is: " << score << endl;
	}

	for (int i = -5; i < 10; i++) { 
		if ((x_pillar1 == translateX + 4 * i) && (translateY - 24 < y_scale_pillar1 * 100)) {
			GAME_OVER = true;
		}
		if ((x_pillar1 == translateX + 4 * i) && (translateY + 30 > y_scale_pillar1 * 100 + 160)) {
			GAME_OVER = true;
		}
		if ((x_pillar2 == translateX + 4 * i) && (translateY - 24 < y_scale_pillar2 * 100)) {
			GAME_OVER = true;
		}
		if ((x_pillar2 == translateX + 4 * i) && (translateY + 30 > y_scale_pillar2 * 100 + 160)) {
			GAME_OVER = true;
		}
	}

}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	if (GAME_OVER == false) {
		if (fall) {
			velocity += acceleration * deltaTime;
			translateY -= velocity;
			if (angularStep > -1.5)
				angularStep -= deltaTime;
		}
		else {
			if (angularStep < 0.15)
				angularStep += 8 * deltaTime;
			if (angularStep > 0.15)
				fall = true;
		}
	}
}


void Laborator3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		fall = false;
		velocity = 0;
		translateY += 50;
	}
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{

}
