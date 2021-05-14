/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <raylib.h>
#include "Drawables/Drawable.hpp"

namespace Ray {
    class Circle: public Drawable
	{
        public:
            //! @brief Circle constructor
            //! @param topLeftPos position of top-left point (in percentage) 
            //! @param radius radius of the circle(in percentage)
            //! @param Color Color of the circle  
            Circle(Vector2 topLeftPos, int radius, Color color);
            
            //! @brief Circle constructor
            //! @param topLeftX x-position of top-left point (in percentage) 
            //! @param topLeftY y-position of top-left point (in percentage)
            //! @param radius radius of the circle(in percentage)
            //! @param Color Color of the circle  
            Circle(int topLeftX, int topLeftY, int radius, Color color);
            
            //! @brief A default copy constructor
            Circle(const Circle &) = default;

            //! @brief A circle is assignable
            Circle &operator=(const Circle &) = default;

            //! @brief A default destructor
            ~Circle() = default;

            //! @return the radius of the circle
            int getRadius(void) const;

            //! @brief set radius
            Circle &setRadius(int radius) const;

        private:
            //! @brief Radius of the circle (in percentage)
            int _radius;
    };
};

#endif /* !PIXEL_HPP_ */
