#pragma once

#include <raylib.h>

namespace app
{
	namespace powerup
	{
		struct Meteor
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
		};

		void InitMeteors();
		void UpdateMeteors();
		void DrawMeteors();
		void UnloadMeteors();

		extern bool pauseSoundExplosion;
	}
}
