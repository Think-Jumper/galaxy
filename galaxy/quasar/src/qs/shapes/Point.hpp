///
/// Point.hpp
/// quasar
///
/// Refer to LICENSE.txt for more details.
///

#ifndef QUASAR_POINT_HPP_
#define QUASAR_POINT_HPP_

#include <protostar/graphics/Colour.hpp>

#include "qs/core/Transform.hpp"
#include "qs/core/VertexData.hpp"

///
/// Core namespace.
///
namespace qs
{
	///
	/// Point graphic definition.
	///
	class Point final : public qs::VertexData, public qs::Transform
	{
	public:
		///
		/// Constructor.
		///
		Point() noexcept;

		///
		/// Constructor.
		///
		/// \param x X position.
		/// \param y Y position.
		/// \param size Size of the point.
		/// \param colour Colour.
		///
		Point(const float x, const float y, const unsigned int size, pr::Colour& colour);

		///
		/// Copy constructor.
		///
		Point(const Point&) noexcept = delete;

		///
		/// Move constructor.
		///
		Point(Point&&) noexcept = default;

		///
		/// Copy assignment operator.
		///
		Point& operator=(const Point&) noexcept = delete;

		///
		/// Move assignment operator.
		///
		Point& operator=(Point&&) noexcept = default;

		///
		/// Destructor.
		///
		virtual ~Point() noexcept = default;

		///
		/// Create the point.
		///
		/// \param x X position.
		/// \param y Y position.
		/// \param size Size of the point.
		/// \param colour Colour.
		///
		void create(const float x, const float y, const unsigned int size, pr::Colour& colour);

		///
		/// Bind as active VA.
		///
		void bind() noexcept;

		///
		/// Unbind as active VA.
		///
		void unbind() noexcept;

		///
		/// Get size of point.
		///
		/// \return Const integer.
		///
		[[nodiscard]] const int get_size() const noexcept;

	private:
		///
		/// Size of point.
		///
		int m_size;
	};
} // namespace qs

#endif