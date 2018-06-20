///
/// Sol2enttWorkaround.cpp
/// starlight
///
/// Created by reworks on 17/02/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include "sl/libs/loguru/loguru.hpp"

#include "Sol2enttWorkaround.hpp"

namespace sl
{
	void Sol2enttWorkaround::setRegistry(entt::DefaultRegistry* registry)
	{
		if (!registry)
		{
			LOG_S(ERROR) << "Tried to set a nullptr registry!";
		}
		else
		{
			m_registry = registry;
		}
	}

	entt::DefaultRegistry::entity_type Sol2enttWorkaround::create()
	{
		return m_registry->create();
	}

	void Sol2enttWorkaround::destroy(entt::DefaultRegistry::entity_type entity)
	{
		m_registry->destroy(entity);
	}
}