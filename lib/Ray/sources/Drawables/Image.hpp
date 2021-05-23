/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <raylib.h>
#include <string>
#include "Canvas.hpp"
#include "Texture.hpp"
#include "IRessource.hpp"

namespace RAY
{
	namespace Drawables {
		class ADrawable2D;
	}
	class IRessource;
	//! @brief Object representation of a framebuffer
	class Image: public Canvas, public IRessource {
		public:
			//! @brief Create an image, loading a file
			//! @param filename: path to file to load
			explicit Image(const std::string &filename);

			//! @brief Create an image, using data from a texure
			//! @param texture: texture to extract data from
			explicit Image(Texture &texture);

			//! @brief A default copy constructor
			Image(const Image &image) = default;

			//! @brief A default constructor, no ressources loaded
			Image();

			//! @brief An image is assignable
			Image &operator=(const Image &image) = default;
			
			//! @brief Image destructor, will unload ressources
			~Image() override;

			//! @brief load ressources from file
			//! @param filename: path of input
			bool load(const std::string &filename) override;

			//! @brief export to file
			//! @param outputPath: path of output
			bool exportTo(const std::string &outputPath);

			//! @brief unload ressources
			bool unload() override;

			//! @brief get image
			operator ::Image() const;
			operator ::Image *();

			//! @brief draw drawable
			void draw(Drawables::ADrawable2D &);

		private:
			//! @brief Image, really, that's just it...
			::Image _image;
	};   
}

#endif /* !IMAGE_HPP_ */
