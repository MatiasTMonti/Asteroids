#pragma once

#include <raylib.h>

namespace app
{
	namespace powerups
	{
		struct Powerups
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
		};

		void InitPowerUps();
		void UpdatePowerUps();
		void DrawPowerUps();
		void UnloadPowerUps();

		extern float timer;

		extern bool resizeShootActive;
		extern bool nuclearActive;
	}
}