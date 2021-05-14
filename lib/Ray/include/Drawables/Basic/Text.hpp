/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "Drawables/Drawable.hpp"
#include <string>

namespace Ray {
    class Text: public Drawable
	{
        public:
            Text(const std::string &text, int fontSize, Vector2 position, Color);
            Text(const std::string &text, int fontSize, int x, int y, Color);
            Text(const Text &);

            Text &operator=(const Text &);

            ~Text() = default;

            const std::string &getString(void);
            int getFontSize(void);

            Text &setText(const std::string &text);
            Text &setFontSize(int size);


            bool collide(const Text &);
            bool collide(const Line &);
            bool collide(const Point &);
            bool collide(const Circle &);
        private:
            std::string _text;
            int _size;
    };
};


#endif /* !TEXT_HPP_ */
