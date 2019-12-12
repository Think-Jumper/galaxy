///
/// Layer.cpp
/// starmap
///
/// Refer to LICENSE.txt for more details.
///

#include "nlohmann/json.hpp"

#include "Layer.hpp"

///
/// Core namespace.
///
namespace starmap
{
	Layer::~Layer() noexcept
	{
		m_properties.clear();
	}

	const int Layer::getHeight() const noexcept
	{
		return m_height;
	}

	const int Layer::getID() const noexcept
	{
		return m_id;
	}

	const std::string Layer::getName() const noexcept
	{
		return m_name;
	}

	const double Layer::getOffsetX() const noexcept
	{
		return m_offsetX;
	}

	const double Layer::getOffsetY() const noexcept
	{
		return m_offsetY;
	}

	const double Layer::getOpacity() const noexcept
	{
		return m_opacity;
	}

	Layer::Layer() noexcept
		:m_height(0), m_id(0), m_name(""), m_offsetX(0.0), m_offsetY(0.0), m_opacity(0.0)
	{
	}

	Layer::Layer(const nlohmann::json& json)
		:m_height(0), m_id(0), m_name(""), m_offsetX(0.0), m_offsetY(0.0), m_opacity(0.0)
	{
		m_height = json.at("height");
		m_id = json.at("id");
		m_name = json.at("name");
		m_offsetX = json.at("offsetx");
		m_offsetY = json.at("offsety");
		m_opacity = json.at("opacity");

		if (json.count("properties") > 0)
		{
			auto propArray = json.at("properties");
			std::for_each(propArray.begin(), propArray.end(), [&](const nlohmann::json& property)
			{
				m_properties.emplace(property.at("name"), property);
			});
		}
	}
}