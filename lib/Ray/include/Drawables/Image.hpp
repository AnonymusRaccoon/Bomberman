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
#include "Surface.hpp"

namespace Ray
{
    class Image {
        public:
            Image(const std::string &filename);
            Image(const Image &);
            Image();

            Image &operator=(const Image &);
            
            bool load(const std::string &filename);
            bool exportTo(const std::string &outputPath);
            bool unload();

            const ::Image &getImage(void) const;

            ~Image();

            void drawRectangle(const Rectangle &);
            void drawLine(const Line &);
            void drawPoint(const Point &);
            void drawCircle(const Circle &);

        protected:
        private:
            ::Image _image;
    };   
}

#endif /* !IMAGE_HPP_ */
