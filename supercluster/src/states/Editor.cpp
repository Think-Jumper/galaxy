///
/// Editor.cpp
/// supercluster
///
/// Refer to LICENSE.txt for more details.
///

#include <qs/core/Window.hpp>
#include <galaxy/core/ServiceLocator.hpp>

#include "../layers/ECSLayer.hpp"
//#include "../layers/GUILayer.hpp"
#include "../layers/ImGuiLayer.hpp"

#include "Editor.hpp"

namespace sc
{
	Editor::Editor()
	{
		m_camera.create(0.0f, SL_HANDLE.window()->get_width(), SL_HANDLE.window()->get_height(), 0.0f);
	}

	void Editor::on_push()
	{
		m_layers.add<ECSLayer>();
		//m_layers.add<GUILayer>();
		m_layers.add<ImGuiLayer>();
	}

	void Editor::on_pop()
	{
		m_layers.clear();
	}

	void Editor::events()
	{
		m_layers.events();
	}

	void Editor::update(const double dt)
	{
		m_camera.update(dt);
		m_layers.update(dt);
	}

	void Editor::render()
	{
		m_layers.render(m_camera);
	}
} // namespace sc