/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable
*/

#ifndef ADrawable_HPP_
#define ADrawable_HPP_

#include <raylib.h>
#include <Vector.hpp>
#include "Drawables/Basic/Circle.hpp"
#include "Drawables/Basic/Line.hpp"
#include "Drawables/Basic/Rectangle.hpp"
#include "Drawables/Basic/Point.hpp"

namespace Ray {
    class ADrawable
	{
        public:
            //! @brief ADrawable constructor
            //! @param poition position of top-left point (in percentage)
            //! @param Color Color of the color  
            ADrawable(Vector2 position, Color color);
            //! @brief ADrawable constructor
            //! @param x x-position of top-left point (in percentage) 
            //! @param y y-position of top-left point (in percentage)
            //! @param Color Color of the color  
            ADrawable(int x, int y, Color color);

            //! @brief A default copy constructor
            ADrawable(const ADrawable &) = default;

            //! @brief A default destructor
            virtual ~ADrawable() = 0;

            //! @return the top-left position of the ADrawable
            const Vector2 &getPosition(void) const;

            //! @return the color of the ADrawable
            const Color &getColor(void) const;

            //! @brief set Top-left position
            ADrawable &setPosition(const Vector2 &position);
            
            //! @brief set Top-left position
            ADrawable &setPosition(int x, int y);
            
            //! @brief set color
            ADrawable &setColor(const Color &color) const;

        private:
            //! @brief Top-left position (in percentage)
            Vector2 _position;
            //! @brief Color of the ADrawable
            Color _color;

    };
};

#endif /* !ADrawable_HPP_ */
