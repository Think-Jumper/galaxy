///
/// SandboxLayer.cpp
/// sandbox_tests
///
/// Refer to LICENSE.txt for more details.
///

#include <galaxy/core/ServiceLocator.hpp>
#include <galaxy/systems/RenderSystem.hpp>
#include <galaxy/components/SpriteComponent.hpp>
#include <qs/core/Renderer.hpp>
#include <galaxy/components/ShaderComponent.hpp>
#include <galaxy/flags/EnabledFlag.hpp>
#include <galaxy/res/ShaderBook.hpp>
#include <galaxy/fs/FileSystem.hpp>

#include "SandboxLayer.hpp"

///
/// Core namespace.
///
namespace sb
{
	SandboxLayer::SandboxLayer()
	{
		set_name("sandbox_layer");
		m_window = SL_HANDLE.window();
		m_world  = SL_HANDLE.world();

		auto vs = galaxy::FileSystem::s_root + galaxy::FileSystem::s_shaders + "particle.vs";
		auto fs = galaxy::FileSystem::s_root + galaxy::FileSystem::s_shaders + "particle.fs";
		m_shader.load_path(vs, fs);

		// create and set texture
		auto tex = galaxy::FileSystem::s_root + galaxy::FileSystem::s_textures + "particle_demo.png";
		m_particle_gen.create(tex, 100.0f, 100.0f);
		m_particle_gen.define("default", {0, 0, 16, 16});
		m_particle_gen.configure("default");
		m_particle_gen.gen_circular("default", 200, 100.0f, 0.5f, 0.5f);

		pr::Colour c = {0, 0, 0, 255};
		m_point.create(0, 0, 10, c);
		m_point.set_pos(200, 150);

		m_circle.create(0, 0, 20, 50, c);
		m_circle.set_pos(150, 150);
	}

	SandboxLayer::~SandboxLayer()
	{
		m_world  = nullptr;
		m_window = nullptr;
	}

	void SandboxLayer::events()
	{
		if (glfwGetKey(m_window->gl_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			m_window->close();
		}

		/*
		auto pos = m_window->get_cursor_pos();
		if (glfwGetMouseButton(m_window->gl_window(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{
			m_particle_gen.update_emitter(pos.x, pos.y);
			m_particle_gen.gen_circular("default", 200, 100.0f, 0.5f, 0.5f);
		}
		*/

		m_world->events();
	}

	void SandboxLayer::update(const double dt)
	{
		m_world->update(dt);
		m_particle_gen.update(dt, 0.01f);
	}

	void SandboxLayer::render(qs::Camera& camera)
	{
		// set shader
		m_shader.bind();
		m_shader.set_uniform("u_cameraProj", camera.get_proj());
		m_shader.set_uniform("u_cameraView", camera.get_transform());
		SL_HANDLE.renderer()->draw_particles(m_particle_gen, m_shader);

		auto* ps = SL_HANDLE.shaderbook()->get("point");
		ps->bind();
		ps->set_uniform("u_cameraProj", camera.get_proj());
		ps->set_uniform("u_cameraView", camera.get_transform());
		SL_HANDLE.renderer()->draw_point(m_point, *ps);

		SL_HANDLE.renderer()->draw_circle(m_circle, *ps);

		//m_world->get_system<galaxy::RenderSystem>()->render(camera);
	}
} // namespace sb