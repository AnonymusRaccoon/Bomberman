/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace Ray::Drawable3D {
    class Circle: public ADrawable3D
	{
        public:
            //! @brief Circle constructor
            //! @param centerPosition position of the center 
            //! @param radius radius of the circle(in percentage)
            //! @param Color Color of the circle  
            Circle(Vector3 centerPosition, int radius, Color color);

            
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

            //! @return the position of the center
            const Vector3 &getCenterPos(void) const;

            //! @brief set pos of center 
            Circle &setRadius(Vector3 pos) const;

        private:
            //! @brief Radius of the circle (in percentage)
            int _radius;

            //! @brief position of the center
            Vector3 _centerPos;
    };
};

#endif /* !PIXEL_HPP_ */
