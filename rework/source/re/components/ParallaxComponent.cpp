//
//  ParallaxComponent.cpp
//  rework
//
//  Created by reworks on 29/08/2017.
//  Copyright (c) 2017 reworks. All rights reserved.
//

#include <map>

#include "entityx/Entity.h"
#include "imgui/imgui_impl_a5.h"

#include "ParallaxComponent.hpp"

namespace re
{
	ParallaxComponent::ParallaxComponent(ex::Entity& e, sol::table& table)
	{
		// Get key-value pairs from table
		std::map<std::string, sol::table> kvp;
		table.for_each([&](std::pair<sol::object, sol::object> pair) {
			kvp.insert({ pair.first.as<std::string>(), pair.second.as<sol::table>() });
		});

		for (auto& it : kvp)
		{
			m_pb.emplace_back(it.second.get<std::string>("atlasName"), it.second.get<float>("x"), it.second.get<float>("y"), it.second.get<float>("speed"), it.second.get<int>("layer"));
		}
	}

	ParallaxComponent::~ParallaxComponent()
	{
	}

	void ParallaxComponent::debug()
	{
		ImGui::Text("Edit the script to make changes.");

		ImGui::Spacing();

		ImGui::Text("This is done because alot of parallax stuff changes dynamically.");
	}
}