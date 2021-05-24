/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Model
*/

#include "Model/Model.hpp"
#include "Exceptions/RayError.hpp"

RAY::Model::Model(const std::string &filename):
	_model(LoadModel(filename.c_str()))
{
}

RAY::Model::Model(const Mesh &mesh):
	_model(LoadModelFromMesh(mesh))
{
}

RAY::Model::~Model()
{
	this->unload();
}

bool RAY::Model::load(const std::string &filename)
{
	this->_model = LoadModel(filename.c_str());
	return true;
}

bool RAY::Model::load(const Mesh &mesh)
{
	this->_model = LoadModelFromMesh(mesh);
	return true;
}

bool RAY::Model::unload()
{
	UnloadModel(this->_model);
	return true;
}

bool RAY::Model::unloadKeepMeshes()
{
	UnloadModelKeepMeshes(_model);
	return true;
}

bool RAY::Model::setAnimation(const RAY::ModelAnimation &animation)
{
	if (!IsModelAnimationValid(this->_model, animation))
		throw RAY::Exception::NotCompatibleError("The animation is not compatible with the model");
	UpdateModelAnimation(this->_model, animation, animation.getFrameCounter());
	return true;
}

bool RAY::Model::setTextureToMaterial(RAY::Model::MaterialType materialType, const RAY::Texture &texture)
{
	SetMaterialTexture(&this->_model.materials[materialType], materialType, texture);
	return true;
}

RAY::Model::operator ::Model() const
{
	return this->_model;
}

int RAY::Model::getBoneCount() const
{
	return this->_model.boneCount;
}