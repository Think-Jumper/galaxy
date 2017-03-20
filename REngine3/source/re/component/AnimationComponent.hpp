//
//  AnimationComponent.hpp
//  REngine3
//
//  Created by reworks on 16/08/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//
// Code adapted from here: https://github.com/SFML/SFML/wiki/Source:-AnimatedSprite

#ifndef RENGINE3_ANIMATEDSPRITECOMPONENT_HPP_
#define RENGINE3_ANIMATEDSPRITECOMPONENT_HPP_

#include <SFML/System/Time.hpp>

#include "re/types/Component.hpp"

namespace re
{
	class AnimationComponent : public Component
	{
		friend class AnimationSystem;
	public:
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Default Constructor.
		*/
		AnimationComponent();

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Destructor. Cleans up component.
		*/
		~AnimationComponent() override;

		/*
		* IMPORTS: sol::table from lua script containing component data.
		* EXPORTS: none
		* PURPOSE: Set up the component.
		*/
		void Init(sol::table& table) override;

		/*
		* IMPORTS: animation name
		* EXPORTS: none
		* PURPOSE: Change the active animation
		*/
		void ChangeAnimation(const std::string& animation);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Plays the active animation.
		*/
		void Play();

		/*
		* IMPORTS: animation name
		* EXPORTS: none
		* PURPOSE: Plays a specific animation.
		*/
		void Play(const std::string& animation);
	
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Pauses active animation.
		*/
		void Pause();

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Stops the active animation.
		*/
		void Stop();

		/*
		* IMPORTS: none
		* EXPORTS: boolean value
		* PURPOSE: Is the animation paused or not.
		*/
		bool IsPaused() const;

	private:
		bool m_isPaused;
		sf::Time m_frameTime;
		sf::Time m_currentTime;
		std::size_t m_currentFrame;
		std::string m_activeAnimation;
		std::unordered_map<std::string, std::vector<sf::IntRect>> m_animations;

	public:
		bool m_isLooped;
		sf::IntRect m_currentFrameRect;
	};
}

#endif