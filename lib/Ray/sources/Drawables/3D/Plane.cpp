/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Line
*/

#include "Drawables/3D/Plane.hpp"

RAY::Drawables::Drawables3D::Plane::Plane(const Vector3 &position, const Vector2 &dimensions, const Color &color):
	ADrawable3D(color), _position(position), _dimensions(dimensions)
{

}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Plane::getPosition(void) const
{
	return this->_position;
}

RAY::Drawables::Drawables3D::Plane &RAY::Drawables::Drawables3D::Plane::setPosition(const Vector3 &Position)
{
	this->_position = Position;
	return *this;
}

const RAY::Vector2 &RAY::Drawables::Drawables3D::Plane::getDimensions(void) const
{
	return this->_dimensions;
}

RAY::Drawables::Drawables3D::Plane &RAY::Drawables::Drawables3D::Plane::setDimensions(const Vector2 &dimensions)
{
	this->_dimensions = dimensions;
	return *this;
}

void RAY::Drawables::Drawables3D::Plane::drawOn(RAY::Window &)
{
	DrawPlane(this->_position, this->_dimensions, this->_color);
}
