/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include <iostream>
#include "Runner/Runner.hpp"

// Dependencies of the demo
#include "Camera/Camera3D.hpp"
#include "Controllers/Keyboard.hpp"
#include "Drawables/2D/Text.hpp"
#include "Drawables/Image.hpp"
#include "Drawables/3D/Grid.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/3D/Circle.hpp"
#include "Model/Model.hpp"
#include "Model/ModelAnimations.hpp"
#include "System/Renderer/Renderer3DSystem.hpp"
#include "Component/Drawable/Drawable3DComponent.hpp"
#include "System/Renderer/RenderScreenSystem.hpp"
#include "Vector/Vector3.hpp"
#include "Window.hpp"
#include "TraceLog.hpp"
#include "Wal.hpp"

const std::vector<std::string>textures = {
	"black", "blue", "pink", "red", "white", "yellow"
};

std::string get_full_path(const std::string &color)
{
	std::string path = "assets/player/";

	path += color;
	path += ".png";
	return path;
}

int demo()
{
	WAL::Wal wal;
	const int screenWidth = 800;
	const int screenHeight = 450;
	auto iterator = textures.begin();
	const std::string modelPath = "assets/player/player.obj";
	const std::string texturePath = "assets/player/blue.png";
	//const std::string animationPath = "assets/guy.iqm";
	RAY::TraceLog::setLevel(LOG_WARNING);
	RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "Bidibidibop", FLAG_WINDOW_RESIZABLE);
	RAY::Image icon("assets/icon.png");
	window.setIcon(icon);
	RAY::Model model(modelPath);
	RAY::Camera::Camera3D camera(RAY::Vector3(10.0f, 10.0f, 10.0f),
	                             RAY::Vector3(0.0f, 0.0f, 0.0f),
	                             RAY::Vector3(0.0f, 1.0f, 0.0f),
	                             45.0f, CAMERA_PERSPECTIVE
	);
	WAL::Entity entityPlayer("roger");
	RAY::Drawables::Drawables3D::Circle circle({30, 30, 30}, 50, 0XFFFFFFF, {0, 0, 0}, 0);
	BBM::Drawable3DComponent<RAY::Drawables::Drawables3D::Circle> circleComponent(entityPlayer, circle);

	BBM::Renderer3DSystem<RAY::Drawables::Drawables3D::Circle> circleSystem(window);

	BBM::RenderScreenSystem<RAY::Camera::Camera3D> renderSystem(window, camera);

	wal.addSystem(circleSystem);
	entityPlayer.addComponent(circleComponent);

	RAY::Texture texture(get_full_path(*iterator));
	//RAY::ModelAnimations animations(modelPath);
	RAY::Drawables::Drawables3D::Grid grid(10, 1.0f);
	RAY::Drawables::Drawables2D::Text instructionText("PRESS SPACE to PLAY MODEL ANIMATION", 10, {10, 20} , MAROON);
	model.setTextureToMaterial(MAP_DIFFUSE, texture);

	RAY::Vector3 position(0.0f, 0.0f, 0.0f);			// Set model position

	camera.setMode(CAMERA_FREE); // Set free camera mode

	float y_rotation = 0;
	window.setFPS(60);

	wal.run<int>([](WAL::Wal &wal, int) {});

	window.close();

	return 0;
}


void usage(const std::string &bin)
{
	std::cout << "Bomberman." << std::endl
		<< "\tUsage: " << bin << " [options]" << std::endl
		<< "Options:" << std::endl
		<< "\t-h:\tPrint this help message" << std::endl;
}

int main(int argc, char **argv)
{
	if (argc == 2 && std::string(argv[1]) == "-h") {
		usage(argv[0]);
		return 1;
	}
	return demo();
	return BBM::run();
}
