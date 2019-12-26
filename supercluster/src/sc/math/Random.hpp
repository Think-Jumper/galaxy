///
/// Random.hpp
/// supercluster
///
/// Refer to LICENSE.txt for more details.
///

#ifndef SUPERCLUSTER_RANDOM_HPP_
#define SUPERCLUSTER_RANDOM_HPP_

#include <random>

///
/// Core namespace.
///
namespace sc
{
	///
	/// Credits: http://stackoverflow.com/a/32907541.
	///
	template<typename T>
	using conditional_distribution = std::conditional_t<std::is_integral<T>::value, std::uniform_int_distribution<T>, std::conditional_t<std::is_floating_point<T>::value, std::uniform_real_distribution<T>, void>>;

	///
	/// Generate a random number of type T.
	///
	/// \param min Minimum number inclusive.
	/// \param max Maximum number inclusive.
	///
	/// \return Returns type T.
	///
	template<typename T>
	inline T random(const T min, const T max)
	{
		// Make sure is arimthmatic.
		static_assert(std::is_arithmetic<T>::value);

		// Restricts to one thread, so each thread gets a random device.
		thread_local static std::random_device rd;
		thread_local static std::mt19937 mt(rd());

		conditional_distribution<T> dist(min, max);

		return dist(mt);
	}
}

#endif