/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable3D
*/

#include "Drawables/ADrawable3D.hpp"

RAY::Drawables::Drawables3D::ADrawable3D::ADrawable3D(const RAY::Vector3 &position, const RAY::Color &color):
	_position(position), _color(color)
{

}

const RAY::Color &RAY::Drawables::Drawables3D::ADrawable3D::getColor(void) const
{
	return this->_color;
}

RAY::Drawables::Drawables3D::ADrawable3D &RAY::Drawables::Drawables3D::ADrawable3D::setColor(const RAY::Color &color)
{
	this->_color = color;
	return *this;
}


const RAY::Vector3 &RAY::Drawables::Drawables3D::ADrawable3D::getPosition(void) const
{
	return this->_position;
}


RAY::Drawables::Drawables3D::ADrawable3D &RAY::Drawables::Drawables3D::ADrawable3D::setPosition(const RAY::Vector3 &position)
{
	this->_position = position;
	return *this;
}