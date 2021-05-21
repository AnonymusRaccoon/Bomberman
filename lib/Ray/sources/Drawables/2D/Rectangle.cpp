/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Rectangle
*/

#include "Drawables/2D/Rectangle.hpp"
#include <cmath>

RAY::Drawables::Drawables2D::Rectangle::Rectangle(const Vector2 &position, const Vector2 &dimensions, const Color &color):
	ADrawable2D(position, color), _dimensions(dimensions)
{

}

RAY::Drawables::Drawables2D::Rectangle::Rectangle(int x, int y, int width, int height, const Color &color):
	ADrawable2D(x, y, color), _dimensions(width, height)
{

}

const RAY::Vector2 &RAY::Drawables::Drawables2D::Rectangle::getDimensions(void)
{
	return this->_dimensions;
}

RAY::Drawables::Drawables2D::Rectangle &RAY::Drawables::Drawables2D::Rectangle::setDimensions(const Vector2 &dimensions)
{
	this->_dimensions = dimensions;
	return *this;
}

RAY::Drawables::Drawables2D::Rectangle &RAY::Drawables::Drawables2D::Rectangle::setDimensions(int x, int y)
{
	this->_dimensions.x = x;
	this->_dimensions.y = y;
	return *this;
}

void RAY::Drawables::Drawables2D::Rectangle::drawOn(RAY::Window &)
{
	DrawRectangleV(this->_position, this->_dimensions, this->_color);
}

void RAY::Drawables::Drawables2D::Rectangle::drawOn(RAY::Image &image)
{
	ImageDrawRectangleV(image, this->_position, this->_dimensions, this->_color);
}
