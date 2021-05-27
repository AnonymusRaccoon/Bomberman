/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cube
*/

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D {
	//! @brief Cube in a three-dimensionnal space
	class Cube: public ADrawable3D
	{
		public:
			//! @brief Cube constructor
			//! @param position position of the cube 
			//! @param dimensions dimensions of the cube
			//! @param Color Color of the cube  
			Cube(const Vector3 &position, const Vector3 &dimensions, const Color &color);

			
			//! @brief A default copy constructor
			Cube(const Cube &) = default;

			//! @brief A circle is assignable
			Cube &operator=(const Cube &) = default;

			//! @brief A default destructor
			~Cube() override = default;


			//! @return the dimensions of the cube
			const Vector3 &getDimensions(void) const;

			//! @brief set the dimensions of the cube
			Cube &setDimensions(const Vector3 &dimensions);
		
			//! @brief Draw circle on window
			void drawOn(RAY::Window &) override;

			//! @brief Get the bounding box
			BoundingBox getBoundingBox(void) override;
		private:
			//! @brief Dimensions of the cube
			Vector3 _dimensions;
	};
}

#endif /* !CUBE_HPP_ */
