///
/// Command.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_COMMAND_HPP_
#define GALAXY_COMMAND_HPP_

///
/// Core namespace.
///
namespace galaxy
{
	///
	/// A command is basically a request in an object oriented form.
	/// Similar to a callback, but with more potential.
	/// You can use it for example, to give multiple "actors" the ability to do the same thing.
	/// You can use it for other useful things, like returning it from a function when something happens, then processing whatever command there is.
	///
	class Command
	{
	public:
		///
		/// Default virtual destructor.
		///
		virtual ~Command() noexcept = default;

		///
		/// Execute the command.
		///
		/// \return bool Return true if successful, false if not.
		///
		virtual bool exec() = 0;

		///
		/// Reverse the command's actions. Undo them.
		///
		/// \return bool Return true if successful, false if not.
		///
		virtual bool undo() = 0;

	protected:
		///
		/// Default constructor.
		///
		Command() noexcept = default;

		///
		/// Copy constructor.
		///
		Command(const Command&) noexcept = default;

		///
		/// Move constructor.
		///
		Command(Command&&) noexcept = default;

		///
		/// Copy assignment operator.
		///
		Command& operator=(const Command&) noexcept = default;

		///
		/// Move assignment operator.
		///
		Command& operator=(Command&&) noexcept = default;
	};
} // namespace galaxy

#endif