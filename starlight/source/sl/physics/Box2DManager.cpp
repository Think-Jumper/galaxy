///
///  Box2DManager.cpp
///  starlight
///
///  Created by reworks on 12/11/2016.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#include "sl/cosl/World.hpp"
#include "sl/services/ServiceLocator.hpp"
#include "sl/components/PhysicsComponent.hpp"

#include "Box2DManager.hpp"

namespace sl
{
	Box2DManager::Box2DManager(float32 gravity)
	{
		m_world = std::make_unique<b2World>(b2Vec2(0.0, gravity));
	}

	Box2DManager::~Box2DManager()
	{
		m_collisionFunctions.clear();

		auto physicsView = World::get()->m_registery.view<PhysicsComponent>();
		physicsView.each<PhysicsComponent>([this](entt::Entity entity, PhysicsComponent& pc)
		{
			if (pc.m_body)
			{
				if (pc.m_body->GetFixtureList())
				{
					for (b2Fixture* f = pc.m_body->GetFixtureList(); f; f = f->GetNext())
					{
						if (f)
						{
							if (f->GetUserData())
							{
								std::string* data = static_cast<std::string*>(f->GetUserData());

								if (data)
								{
									delete data;
								}
							}
						}
					}
				}
			}

			m_world->DestroyBody(pc.m_body);
		});
	}

	void Box2DManager::clean()
	{
		m_collisionFunctions.clear();
	}
}