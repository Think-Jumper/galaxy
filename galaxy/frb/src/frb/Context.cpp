///
/// Context.cpp
/// frb
///
/// Refer to LICENSE.txt for more details.
///

#include <pulsar/Log.hpp>

#include "frb/detail/Error.hpp"

#include "Context.hpp"

///
/// Core namespace.
///
namespace frb
{
	Context::Context()
	    : m_device {nullptr}, m_context {nullptr}
	{
		// Make sure error code is default flagged.
		alGetError();

		m_device = alcOpenDevice(alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER));
		if (!m_device)
		{
			PL_LOG(PL_FATAL, frb::parse_error("Failed to create OpenAL device."));
		}

		m_context = alcCreateContext(m_device, nullptr);
		if (!m_context)
		{
			PL_LOG(PL_FATAL, frb::parse_error("Failed to create OpenAL context."));
		}

		if (!alcMakeContextCurrent(m_context))
		{
			PL_LOG(PL_FATAL, frb::parse_error("Failed to make OpenAL context current."));
		}
	}

	Context::~Context()
	{
		// Cleanup.
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);

		m_context = nullptr;
		m_device  = nullptr;
	}

	void Context::set_doppler_factor(const float factor)
	{
		if (factor < 0)
		{
			throw std::runtime_error("Cannot have a negative doppler factor.");
		}
		else
		{
			alDopplerFactor(factor);
			if (alGetError() != AL_NO_ERROR)
			{
				PL_LOG(PL_ERROR, frb::parse_error("Unable to set context doppler factor."));
			}
		}
	}

	void Context::set_speed_of_sound(const float speed)
	{
		if (speed < 0)
		{
			throw std::runtime_error("Cannot have a negative speed of sound.");
		}
		else
		{
			alSpeedOfSound(speed);
			if (alGetError() != AL_NO_ERROR)
			{
				PL_LOG(PL_ERROR, frb::parse_error("Unable to set context sound speed."));
			}
		}
	}

	void Context::set_listener_gain(const float gain)
	{
		if (gain < 0)
		{
			throw std::runtime_error("Cannot have a negative audio gain multiplier.");
		}
		else
		{
			alListenerf(AL_GAIN, gain);
			if (alGetError() != AL_NO_ERROR)
			{
				PL_LOG(PL_ERROR, frb::parse_error("Unable to set listener AL_GAIN."));
			}
		}
	}

	void Context::set_listener_position(const float x, const float y, const float z)
	{
		alListener3f(AL_POSITION, x, y, z);
		if (alGetError() != AL_NO_ERROR)
		{
			PL_LOG(PL_ERROR, frb::parse_error("Unable to set listener AL_POSITION."));
		}
	}

	void Context::set_listener_velocity(const float x, const float y, const float z)
	{
		alListener3f(AL_VELOCITY, x, y, z);
		if (alGetError() != AL_NO_ERROR)
		{
			PL_LOG(PL_ERROR, frb::parse_error("Unable to set listener AL_VELOCITY."));
		}
	}

	void Context::set_listener_orientation(const float atX, const float atY, const float atZ, const float upX, const float upY, const float upZ)
	{
		const float arr[6] = {atX, atY, atZ, upX, upY, upZ};
		alListenerfv(AL_ORIENTATION, arr);
		if (alGetError() != AL_NO_ERROR)
		{
			PL_LOG(PL_ERROR, frb::parse_error("Unable to set listener AL_ORIENTATION."));
		}
	}
} // namespace frb