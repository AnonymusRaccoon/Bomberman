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

namespace Ray
{
    class Image: public Canvas {
        public:
            //! @brief Create an image, loading a file
            //! @param filename: path to file to load
            Image(const std::string &filename);

            //! @brief A default copy constructor
            Image(const Image &);

            //! @brief A default constructor, no ressources loaded
            Image();

            //! @brief An image is assignable
            Image &operator=(const Image &) = default;
            
            //! @brief Image destructor, will unload ressources
            ~Image();

            //! @brief load ressources from file
            //! @param filename: path of input
            bool load(const std::string &filename);

            //! @brief export to file
            //! @param outputPath: path of output
            bool exportTo(const std::string &outputPath);

            //! @brief unload ressources
            bool unload();

            //! @brief get image
            const ::Image &getImage(void) const;


            //! @brief draw rectangle
            void draw(const Rectangle &);

            //! @brief draw line
            void draw(const Line &);

            //! @brief draw point
            void draw(const Point &);

            //! @brief draw circle
            void draw(const Circle &);

        protected:
        private:
            //! @brief Image, really, that's just it...
            ::Image _image;
    };   
}

#endif /* !IMAGE_HPP_ */
