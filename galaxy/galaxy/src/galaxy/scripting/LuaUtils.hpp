///
/// LuaUtils.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_LUAUTILS_HPP_
#define GALAXY_LUAUTILS_HPP_

///
/// Core namespace.
///
namespace galaxy
{
	///
	/// Namespace that contains useful functions for interacting with Lua.
	///
	namespace Lua
	{
		///
		/// Registers custom library usertypes with sol. Called for you by Application class.
		///
		void register_types();
	} // namespace Lua
} // namespace galaxy

#endif