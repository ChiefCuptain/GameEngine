#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"

#include "Actor.h"
#include "Scene.h"

#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "MathUtil.h"

#include "fmod.hpp"

#include <iostream>
#include <vector>
#include <string>

namespace nu
{
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Quit();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		GameTime& GetTime() { return m_time; }

	private:
		Engine() = default;
	private:
		Input m_input;
		Renderer m_renderer;
		
		GameTime m_time;
	};

}