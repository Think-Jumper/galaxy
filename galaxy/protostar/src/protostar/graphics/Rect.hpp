///
/// Rect.hpp
/// protostar
///
/// Refer to LICENSE.txt for more details.
///

#ifndef PROTOSTAR_RECT_HPP_
#define PROTOSTAR_RECT_HPP_

#include <compare>

#include "protostar/system/Concepts.hpp"

///
/// Core namespace.
///
namespace pr
{
	///
	/// Represents a rectangle object.
	///
	template<is_arithmetic Type>
	class Rect final
	{
	public:
		///
		/// Default constructor.
		///
		Rect() noexcept;

		///
		/// Argument constructor.
		///
		/// \param x X value.
		/// \param y Y value.
		/// \param width Width value.
		/// \param height Height value.
		///
		Rect(const Type x, const Type y, const Type width, const Type height) noexcept;

		///
		/// Copy constructor.
		///

		Rect(const Rect&) noexcept = default;
		///
		/// Move constructor.
		///
		Rect(Rect&&) noexcept = default;

		///
		/// Copy assignment operator.
		///
		Rect& operator=(const Rect&) noexcept = default;

		///
		/// Move assignment operator.
		///
		Rect& operator=(Rect&&) noexcept = default;

		///
		/// Default destructor.
		///
		~Rect() noexcept = default;

		///
		/// Does the rectangle contain the point (x, y).
		///
		/// \param x X coordinate.
		/// \param y Y coordinate.
		///
		/// \return True if contains the point.
		///
		[[nodiscard]] bool contains(const Type x, const Type y) noexcept;

		///
		/// Does the rectangle contain another rectangle.
		///
		/// \param b Rectangle to check.
		///
		/// \return Returns true if the rectangle is completely inside, not on the edge.
		///
		[[nodiscard]] bool contains(const Rect<Type>& b) noexcept;

		///
		/// \brief Do the rectangles a and b overlap.
		///
		/// Credits: https://stackoverflow.com/a/306379
		///
		/// \param b Second rectangle to test.
		///
		/// \return Returns true if there is an overlap.
		///
		[[nodiscard]] bool overlaps(const Rect<Type>& b) noexcept;

		///
		/// Spaceship operator.
		///
		auto operator<=>(const Rect&) const = default;

		///
		/// X position.
		///
		Type m_x;

		///
		/// Y position.
		///
		Type m_y;

		///
		/// Width of rectangle.
		///
		Type m_width;

		///
		/// Height of rectangle.
		///
		Type m_height;

	private:
		///
		/// Private function to determine if value is in range. Inclusive.
		/// Credits: https://stackoverflow.com/a/306379
		///
		/// \param value Value to check if in the min-max range.
		/// \param min Lower range.
		/// \param max Upper range.
		///
		/// \return True if value is inbetween min and max. Inclusive.
		///
		[[nodiscard]] bool value_in_range(const Type value, const Type min, const Type max) noexcept;
	};

	template<is_arithmetic Type>
	inline Rect<Type>::Rect() noexcept
	    : m_x {0}, m_y {0}, m_width {0}, m_height {0}
	{
	}

	template<is_arithmetic Type>
	inline Rect<Type>::Rect(const Type x, const Type y, const Type width, const Type height) noexcept
	    : m_x {x}, m_y {y}, m_width {width}, m_height {height}
	{
	}

	template<is_arithmetic Type>
	inline bool Rect<Type>::contains(const Type x, const Type y) noexcept
	{
		// Checks if the rectangle contains the point (x, y) using some basic math.
		return ((x > m_x) && (x < (m_x + m_width)) && (y > m_y) && (y < (m_y + m_height)));
	}

	template<is_arithmetic Type>
	inline bool Rect<Type>::contains(const Rect<Type>& b) noexcept
	{
		// Checks if the rectangle contains another rectangle using math.
		return ((b.m_x + b.m_width) < (m_x + m_width) && (b.m_x) > (m_x) && (b.m_y) > (m_y) &&
			(b.m_y + b.m_height) < (m_y + m_height));
	}

	template<is_arithmetic Type>
	inline bool Rect<Type>::overlaps(const Rect<Type>& b) noexcept
	{
		// Check for overlaps using math.
		bool x = value_in_range(m_x, b.m_x, b.m_x + b.m_width) || value_in_range(b.m_x, m_x, m_x + m_width);

		bool y =
		    value_in_range(m_y, b.m_y, b.m_y + b.m_height) || value_in_range(b.m_y, m_y, m_y + m_height);

		return x && y;
	}

	template<is_arithmetic Type>
	inline bool Rect<Type>::value_in_range(const Type value, const Type min, const Type max) noexcept
	{
		// Check if a value is between min and max - i.e. in range.
		return (value >= min) && (value <= max);
	}
} // namespace pr

#endif