/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Window
*/

#include "Window.hpp"

#include <utility>
#include "Controllers/Mouse.hpp"

RAY::Window &RAY::Window::getInstance(int width, int height, const std::string &title, unsigned flags, bool openNow)
{
	static RAY::Window window(width, height, title, flags, openNow);

	return window;
}

RAY::Window::Window(int width, int height, std::string title, unsigned flags, bool openNow):
	_dimensions(width, height),
	_title(std::move(title)),
	_isOpen(openNow),
	_flags(flags),
	_drawingState(IDLE), _displayState(NONE)
{
	if (openNow)
		this->open();
}

bool RAY::Window::open(void)
{
	if (this->_flags) {
		SetConfigFlags(this->_flags);
	}
	InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
	this->_isOpen = true;
	return true;
}

bool RAY::Window::shouldClose(void) const
{
	return WindowShouldClose();
}

void RAY::Window::close(void)
{
	CloseWindow();
}

bool RAY::Window::isFocused(void) const
{
	return IsWindowFocused();
}

const RAY::Vector2 &RAY::Window::getDimensions(void) const
{
	return this->_dimensions;
}

void RAY::Window::setVisibleCursor(bool visible)
{
	if (visible)
		ShowCursor();
	else
		HideCursor();
}

void RAY::Window::enableCursor(bool enable)
{
	if (enable)
		EnableCursor();
	else
		DisableCursor();
}

bool RAY::Window::cursorIsVisible(void) const
{
	return !IsCursorHidden();
}

RAY::Vector2 RAY::Window::getCursorPosition(void) const
{
	return RAY::Controller::Mouse::getCursorPosition();
}

void RAY::Window::setFPS(unsigned int fps)
{
	SetTargetFPS(fps);
}

void RAY::Window::clear(const RAY::Color &color)
{
	ClearBackground(color);
}

void RAY::Window::setDrawingState(enum RAY::Window::drawingState state)
{
	if (state == this->_drawingState)
		return;
	switch (state)
	{
	case DRAWING:
		BeginDrawing();
		break;
	case IDLE:
		EndDrawing();
		break;
	}
	this->_drawingState = state;
}

void RAY::Window::useCamera(RAY::Camera::Camera2D &camera)
{
	this->_displayState = RAY::Window::TWO_DIMENSIONNAL;
	BeginMode2D(camera);
}

void RAY::Window::useCamera(RAY::Camera::Camera3D &camera)
{
	this->_displayState = RAY::Window::THREE_DIMENSIONNAL;
	BeginMode3D(camera);
}

void RAY::Window::unuseCamera(void)
{
	switch (this->_displayState)
	{
	case THREE_DIMENSIONNAL:
		EndMode3D();
		break;
	case TWO_DIMENSIONNAL:
		EndMode2D();
		break;
	default:
		break;
	}
	this->_displayState = NONE;
}

void RAY::Window::setTitle(const std::string &title)
{
	this->_title = title;
}

void RAY::Window::draw(RAY::Drawables::IDrawable &drawable)
{
	drawable.drawOn(*this);
}

void RAY::Window::draw(const RAY::Texture &texture, const Vector2 &position, const Color &tint)
{
	DrawTexture(texture, position.x, position.y, tint);
}

void RAY::Window::draw(const Mesh &mesh, const Material &material, const Matrix &transform)
{
	DrawMesh(mesh, material, transform);
}

void RAY::Window::setIcon(RAY::Image &img)
{
	SetWindowIcon(img);
}