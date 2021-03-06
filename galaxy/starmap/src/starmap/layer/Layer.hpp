///
/// Layer.hpp
/// starmap
///
/// Refer to LICENSE.txt for more details.
///

#ifndef STARMAP_LAYER_HPP_
#define STARMAP_LAYER_HPP_

#include <robin_hood.h>

#include "starmap/types/Property.hpp"

///
/// Core namespace.
///
namespace starmap
{
	///
	/// Represents a tile/object/image/group layer.
	///
	class Layer
	{
	public:
		///
		/// Destructor.
		///
		virtual ~Layer() noexcept;

		///
		/// Get row count. Same as map height for fixed-size maps.
		///
		/// \return Height as a const int.
		///
		[[nodiscard]] const int get_height() const noexcept;

		///
		/// Get id - unique across all layers.
		///
		/// \return Height as a const int.
		///
		[[nodiscard]] const int get_id() const noexcept;

		///
		/// Get layer name.
		///
		/// \return Name as string.
		///
		[[nodiscard]] std::string get_name() const noexcept;

		///
		/// Horizontal layer offset.
		///
		/// \return Const double.
		///
		[[nodiscard]] const double get_offset_x() const noexcept;

		///
		/// Vertical layer offset.
		///
		/// \return Const double.
		///
		[[nodiscard]] const double get_offset_y() const noexcept;

		///
		/// Opacity of layer.
		///
		/// \return Double between 0 and 1.
		///
		[[nodiscard]] const double get_opacity() const noexcept;

		///
		/// \brief Retrieve property.
		///
		/// You will need to provide the type when retrieving.
		/// DO NOT OVERRIDE THIS METHOD.
		///
		/// \param name Name of the property to retrieve.
		///
		/// \return Property cast as type.
		///
		template<tiled_property Type>
		[[nodiscard]] const Type get_property(std::string_view name) noexcept;

		///
		/// Get X coordinate where layer content starts.
		///
		/// \return Const int.
		///
		[[nodiscard]] const int get_start_x() const noexcept;

		///
		/// Get Y coordinate where layer content starts.
		///
		/// \return Const int.
		///
		[[nodiscard]] const int get_start_y() const noexcept;

		///
		/// Hex-formatted color (#RRGGBB or #AARRGGBB) that is multiplied with any graphics drawn by this layer or any child layers (optional).
		///
		/// \return String.
		///
		[[nodiscard]] std::string get_tint_colour() const noexcept;

		///
		/// Get type of layer.
		///
		/// \return String in format: tilelayer, objectgroup, imagelayer or group.
		///
		[[nodiscard]] std::string get_type() const noexcept;

		///
		/// Get visibility of layer.
		///
		/// \return True if layer is visible.
		///
		[[nodiscard]] const bool is_visible() const noexcept;

		///
		/// Get width of layer.
		///
		/// \return Const int. Column count. Same as map width for fixed-size maps.
		///
		[[nodiscard]] const int get_width() const noexcept;

		///
		/// Get X offset.
		///
		/// \return Const int. Horizontal layer offset in tiles.
		///
		[[nodiscard]] const int get_x() const noexcept;

		///
		/// Get Y offset.
		///
		/// \return Const int. Vertical layer offset in tiles.
		///
		[[nodiscard]] const int get_y() const noexcept;

	protected:
		///
		/// Default constructor.
		///
		Layer() noexcept;

		///
		/// \brief Parse constructor.
		///
		/// Can throw exceptions.
		///
		/// \param json JSON structure containing chunk array from root map.
		///
		explicit Layer(const nlohmann::json& json);

	protected:
		///
		/// Row count. Same as map height for fixed-size maps.
		///
		int m_height;

		///
		/// Incremental id - unique across all layers.
		///
		int m_id;

		///
		/// Name assigned to this layer.
		///
		std::string m_name;

		///
		/// Horizontal layer offset in pixels.
		///
		double m_offset_x;

		///
		/// Vertical layer offset in pixels.
		///
		double m_offset_y;

		///
		/// Value between 0 and 1.
		///
		double m_opacity;

		///
		/// Map of Properties.
		///
		robin_hood::unordered_map<std::string, starmap::Property> m_properties;

		///
		/// X coordinate where layer content starts (for infinite maps).
		///
		int m_start_x;

		///
		/// Y coordinate where layer content starts (for infinite maps).
		///
		int m_start_y;

		///
		/// Hex-formatted color (#RRGGBB or #AARRGGBB) that is multiplied with any graphics drawn by this layer or any child layers (optional).
		///
		std::string m_tint_colour;

		///
		/// Type of layer in string.
		///
		std::string m_type;

		///
		/// Whether layer is shown or hidden in editor.
		///
		bool m_visible;

		///
		/// Column count. Same as map width for fixed-size maps.
		///
		int m_width;

		///
		/// Horizontal layer offset in tiles.
		///
		int m_x;

		///
		/// Vertical layer offset in tiles.
		///
		int m_y;
	};

	template<tiled_property Type>
	inline const Type Layer::get_property(std::string_view name) noexcept
	{
		const auto str = static_cast<std::string>(name);
		return m_properties[str].get<Type>();
	}
} // namespace starmap

#endif