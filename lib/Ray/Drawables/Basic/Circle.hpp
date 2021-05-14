/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include <raylib.h>
#include "Drawables/Drawable.hpp"

namespace Ray {
    struct Circle: public Drawable
	{
        int radius;
    };
};

#endif /* !PIXEL_HPP_ */
