///
/// Panel.hpp
/// starlight
///
/// Created by reworks on 14/09/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_PANEL_HPP_
#define STARLIGHT_PANEL_HPP_

#include <allegro5/allegro_color.h>

#include "sl/ui/Widget.hpp"

namespace sl
{
	///
	/// A UI Panel holds and positions UI widgets on it.
	///
	class Panel final
	{
	public:
		///
		/// Primitives Constructor.
		///
		/// \param bounds Dimension of the panel.
		/// \param colour Colour of the panel. Can be transparent or opaque.
		///
		Panel(const sl::Rect<int>& bounds, const ALLEGRO_COLOR colour);

		///
		/// Image Constructor.
		///
		/// \param bounds Dimension of the panel.
		/// \param image Background image to use.
		///
		Panel(const sl::Rect<int>& bounds, const std::string& image);

		///
		/// Destructor.
		///
		~Panel() noexcept;

		///
		/// Add a new widget to the Panel.
		///
		/// \param args Arguments for widget to construct.
		///
		/// \return Returns pointer to newly created widget.
		///
		template<typename WidgetType, typename... Args>
		WidgetType* add(Args&&... args);

		///
		/// Remove a widget.
		///
		/// \param id ID of widget to remove. Get by calling widget->id().
		///
		void remove(unsigned int id);

		///
		/// Update the panel and widgets.
		///
		/// \param dt Delta Time.
		///
		void update(const double dt);

		///
		/// Render panel and widgets.
		///
		void render();

		///
		/// Set visibility of panel and subsiquently all widgets.
		///
		/// \param isVisible True if visible.
		///
		void setVisibility(const bool isVisible);

		///
		/// Destroy all widgets.
		///
		void clear();

	private:
		///
		/// Primary Constructor.
		///
		Panel() = delete;

	private:
		///
		/// ID Counter;
		///
		unsigned int m_counter;

		///
		/// Is the panel currently visible. I.e. being rendered.
		///
		bool m_isVisible;

		///
		/// Dimensions of the panel, relative to the screen.
		///
		sl::Rect<int> m_bounds;

		///
		/// Background of the panel. Full colour or image.
		///
		ALLEGRO_BITMAP* m_background;

		///
		/// Collection of widgets on the panel.
		///
		std::unordered_map<unsigned int, std::unique_ptr<Widget>> m_widgets;
	};

	template<typename WidgetType, typename... Args>
	inline WidgetType* Panel::add(Args&&... args)
	{
		// Forward arguments to std::vector's construct in place method.
		m_widgets.emplace(m_counter, std::make_unique<WidgetType>(std::forward<Args>(args)...));
		Widget* ref = m_widgets[m_counter].get();
		if (!ref)
		{
			LOG_S(FATAL) << "Failed to retrieve widget just emplaced... assumed id: " << m_counter;
		}
		
		// Set offset and id.
		ref->setOffset(m_bounds.m_x, m_bounds.m_y);
		ref->m_id = m_counter;

		// Increment counter for next widget.
		++m_counter;

		// Then return a pointer to object placed.
		return dynamic_cast<WidgetType*>(ref);
	}
}

#endif