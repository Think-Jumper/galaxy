///
/// RenderTexture.cpp
/// quasar
///
/// Refer to LICENSE.txt for more details.
///

#include <filesystem>

#include <glad/glad.h>
#include <stb_image.h>
#include <pulsar/Log.hpp>
#include <stb_image_write.h>

#include "qs/core/Window.hpp"
#include "qs/core/WindowSettings.hpp"

#include "RenderTexture.hpp"

///
/// Core namespace.
///
namespace qs
{
	RenderTexture::RenderTexture() noexcept
	    : m_projection(1.0f), m_framebuffer(0)
	{
		glGenFramebuffers(1, &m_framebuffer);
	}

	RenderTexture::RenderTexture(const int width, const int height)
	    : m_projection(1.0f), m_framebuffer(0)
	{
		glGenFramebuffers(1, &m_framebuffer);
		create(width, height);
	}

	RenderTexture::RenderTexture(RenderTexture&& rt)
	    : BaseTexture {std::move(rt)}
	{
		this->m_projection  = std::move(rt.m_projection);
		this->m_framebuffer = rt.m_framebuffer;

		rt.m_framebuffer = 0;
	}

	RenderTexture& RenderTexture::operator=(RenderTexture&& rt)
	{
		if (this != &rt)
		{
			BaseTexture::operator=(std::move(rt));
			this->m_projection   = std::move(rt.m_projection);
			this->m_framebuffer  = rt.m_framebuffer;

			rt.m_framebuffer = 0;
		}

		return *this;
	}

	RenderTexture::~RenderTexture() noexcept
	{
		glBindFramebuffer(GL_TEXTURE_2D, 0);
		glDeleteFramebuffers(1, &m_framebuffer);
	}

	void RenderTexture::create(const int width, const int height)
	{
		m_width  = width;
		m_height = height;

		if (m_width < 1)
		{
			m_width = 1;
		}

		if (m_height < 1)
		{
			m_height = 1;
		}

		m_projection = glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);

		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, qs::WindowSettings::s_texture_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, qs::WindowSettings::s_ansio_filtering);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			PL_LOG(PL_FATAL, "Failed to create GL_FRAMEBUFFER!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void RenderTexture::change_size(const int width, const int height)
	{
		glDeleteFramebuffers(1, &m_framebuffer);
		glGenFramebuffers(1, &m_framebuffer);

		create(width, height);
	}

	void RenderTexture::bind() noexcept
	{
		// Bind to framebuffer.
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		glViewport(0, 0, m_width, m_height);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Reset Colour, in prep for rendering.
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderTexture::unbind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTexture::set_projection(const float left, const float right, const float bottom, const float top) noexcept
	{
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

	glm::mat4& RenderTexture::get_proj() noexcept
	{
		return m_projection;
	}
} // namespace qs