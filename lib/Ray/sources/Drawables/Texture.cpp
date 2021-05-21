/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#include "Drawables/Texture.hpp"

RAY::Texture::Texture(const std::string &filename):
    _texture(LoadTexture(filename.c_str()))
{
}

RAY::Texture::Texture(const Image &image):
    _texture(LoadTextureFromImage(image))
{

}

RAY::Texture::Texture()
{

}

RAY::Texture::~Texture()
{
    UnloadTexture(this->_texture);
}

bool RAY::Texture::load(const std::string &filename)
{
    this->_texture = LoadTexture(filename.c_str());
    return true;
}

bool RAY::Texture::unload()
{
    UnloadTexture(this->_texture);
    return true;
}

Image RAY::Texture::toImage(void) const
{
    return GetTextureData(_texture);
}

const ::Texture &RAY::Texture::getTexture(void) const
{
    return this->_texture;
}

bool RAY::Texture::unload()
{
	UnloadTexture(this->_texture);
	return true;
}