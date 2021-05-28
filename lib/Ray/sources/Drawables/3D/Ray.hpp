/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Ray in a three-dimensionnal space
	class Ray: public ADrawable3D
	{
		public:
			//! @brief Ray constructor
			//! @param startPosition position of top-left point  
			//! @param direction direction of the ray
			//! @param Color Color of the line  
			Ray(const Vector3 &startPosition, const Vector3 &direction, const Color &color);

			//! @brief A default copy constructor
			Ray(const Ray &) = default;

			//! @brief A line is assignable
			Ray &operator=(const Ray &) = default;

			//! @brief A default destructor
			~Ray() override = default;



			//! @return the end position of the line
			const Vector3 &getDirection(void) const;

			//! @brief Set end position
			Ray &setDirection(const Vector3 &direction);

			//! @brief Draw point on window
			void drawOn(RAY::Window &) override;

			//! @brief Get the bounding box
			BoundingBox getBoundingBox(void) const override;
		private:
			Vector3 _direction;
	};
};

#endif /* !PIXEL_HPP_ */
