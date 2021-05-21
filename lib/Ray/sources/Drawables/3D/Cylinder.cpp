/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cylinder
*/

#include "Drawables/3D/Cylinder.hpp"


RAY::Drawables::Drawables3D::Cylinder::Cylinder(const Vector3 &position, float radiusTop, float radiusBottom, float height, const Color &color):
	ADrawable3D(color), _topRadius(radiusTop), _bottomRadius(radiusBottom), _height(height), _centerPos(position)

{

}


int RAY::Drawables::Drawables3D::Cylinder::getTopRadius(void) const
{
	return this->_topRadius;
}

RAY::Drawables::Drawables3D::Cylinder &RAY::Drawables::Drawables3D::Cylinder::setTopRadius(float radius)
{
	this->_topRadius = radius;
	return *this;
}

int RAY::Drawables::Drawables3D::Cylinder::getBottomRadius(void) const
{
	return this->_bottomRadius;
}

RAY::Drawables::Drawables3D::Cylinder &RAY::Drawables::Drawables3D::Cylinder::setBottopRadius(float radius)
{
	this->_bottomRadius = radius;
	return *this;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Cylinder::getPosition(void) const
{
	return this->_centerPos;
}

RAY::Drawables::Drawables3D::Cylinder &RAY::Drawables::Drawables3D::Cylinder::setPosition(const Vector3 &position)
{
	this->_centerPos = position;
	return *this;
}

float RAY::Drawables::Drawables3D::Cylinder::getHeight(void) const
{
	return this->_height;
}

RAY::Drawables::Drawables3D::Cylinder &RAY::Drawables::Drawables3D::Cylinder::setHeight(float height)
{
	this->_height = height;
	return *this;
}

void RAY::Drawables::Drawables3D::Cylinder::drawOn(RAY::Window &)
{
	DrawCylinder(this->_centerPos, this->_topRadius, this->_bottomRadius, this->_height, 0, this->_color.getColor());
}
