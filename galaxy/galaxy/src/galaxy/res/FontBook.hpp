///
/// FontBook.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_FONTBOOK_HPP_
#define GALAXY_FONTBOOK_HPP_

#include <protostar/res/ResourceCache.hpp>
#include <qs/text/Font.hpp>

///
/// Core namespace.
///
namespace galaxy
{
	///
	/// Resource manager for fonts.
	///
	class FontBook final : public pr::ResourceCache<qs::Font>
	{
	public:
		///
		/// Default constructor.
		///
		FontBook() noexcept = default;

		///
		/// JSON constructor.
		///
		/// \param json JSON file to load.
		///
		explicit FontBook(std::string_view json);

		///
		/// Copy constructor.
		///
		FontBook(const FontBook&) noexcept = delete;

		///
		/// Move constructor.
		///
		FontBook(FontBook&&) noexcept = delete;

		///
		/// Copy assignment operator.
		///
		FontBook& operator=(const FontBook&) noexcept = delete;

		///
		/// Move assignment operator.
		///
		FontBook& operator=(FontBook&&) noexcept = delete;

		///
		/// Destructor.
		///
		virtual ~FontBook();

		///
		/// Create FontBook from JSON.
		///
		/// \param json JSON file to load.
		///
		void create_from_json(std::string_view json);

		///
		/// Clean up.
		///
		void clear() override;
	};
} // namespace galaxy

#endif