//
/// Algorithm.hpp
/// protostar
///
/// Refer to LICENSE.txt for more details.
///

#ifndef PROTOSTAR_ALGORITHM_HPP_
#define PROTOSTAR_ALGORITHM_HPP_

#include <optional>
#include <vector>

#include "protostar/system/Concepts.hpp"

///
/// Core namespace.
///
namespace pr
{
	///
	/// Calc normalized value from range.
	///
	/// \param val Value to divide by max.
	/// \param max Value representing 1.0f.
	///
	/// \return Normalized float.
	///
	template<is_arithmetic Type>
	inline float normalize(const Type val, const Type max) noexcept
	{
		return (static_cast<float>(val) / static_cast<float>(max));
	}

	template<typename Type>
	inline std::optional<decltype(std::vector<Type>::iterator)> contains(const std::vector<Type>& cont, const Type val)
	{
		auto found = std::find(cont.begin(), cont.end(), val);
		if (found != cont.end())
		{
			return std::make_optional(found);
		}
		else
		{
			return std::nullopt;
		}
	}
} // namespace pr

#endif