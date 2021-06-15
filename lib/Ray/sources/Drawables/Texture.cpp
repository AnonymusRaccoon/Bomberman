/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Texture
*/

#include "Drawables/Texture.hpp"
#include "Drawables/2D/Rectangle.hpp"
#include "Drawables/Image.hpp"

namespace RAY {

	Cache<::Texture> Texture::_texturesCache(LoadTexture, UnloadTexture); 

	Texture::Texture(const std::string &filename, bool lonely, float scale, float rotation):
		Rectangle(Vector2(0, 0), Vector2(0, 0), WHITE, scale, rotation),
		_texture(_texturesCache.fetch(filename, lonely)),
		_resourcePath(filename)
	{
		this->_dimensions = Vector2(this->_texture->width, this->_texture->height);
	}

	Texture::Texture(const Image &image):
		Rectangle(Vector2(0, 0), Vector2(0, 0), WHITE),
		_texture(std::make_shared<::Texture>(LoadTextureFromImage(image))),
		_resourcePath()
	{
	}

	Texture &Texture::use(const std::string &filename)
	{
		if (this->_resourcePath == filename)
			return *this;
		this->_texture = this->_texturesCache.fetch(filename);
		this->_resourcePath = filename;
		return *this;
	}

	Texture::operator ::Texture() const
	{
		return *this->_texture;
	}

	void Texture::drawOn(RAY::Window &)
	{
		DrawTextureEx(*this, this->_position, 0, this->_scale, this->_color);
	}
}
