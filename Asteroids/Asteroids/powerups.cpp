#include "powerups.h"

#include <cmath>

#include "spaceship.h"
#include "game.h"
#include "app.h"

using namespace app;
using namespace game;
using namespace spaceship;
using namespace powerups;

namespace app
{
	namespace powerups
	{
		static const int amount = 1;
		static Powerups resizeShoot[amount];
		static Powerups nuclear[amount];
		static int powerupSpeed;
		static const float speedBoost = 100.0f;
		static int initialCorrection = 150;

		//Imagenes
		static Image resizeShootImage;
		static Texture2D resizeShootTexture;
		static Image nuclearImage;
		static Texture2D nuclearTexture;

		//Escalar la textura
		static float resizeShootScale;
		static Vector2 resizeShootScalePos;
		static float nuclearScale;
		static Vector2 nuclearScalePos;

		bool resizeShootActive = false;
		bool nuclearActive = false;

		static int scaleAux = 1600;

		void InitPowerUps()
		{
			resizeShootImage = LoadImage("../res/shoot.png");
			resizeShootTexture = LoadTextureFromImage(resizeShootImage);
			nuclearImage = LoadImage("../res/nuclear.png");
			nuclearTexture = LoadTextureFromImage(nuclearImage);

			float posx, posy;
			float velx, vely;

			bool correctRange = false;
			resizeShootActive = false;
			nuclearActive = false;

			powerupSpeed = 1;

			for (int i = 0; i < amount; i++)
			{
				posx = GetRandomValue(0, GetScreenWidth());

				while (!correctRange)
				{
					if (posx > GetScreenWidth() / 2 - initialCorrection && posx < GetScreenWidth() / 2 + initialCorrection) posx = GetRandomValue(0, GetScreenWidth());
					else correctRange = true;
				}

				correctRange = false;

				posy = GetRandomValue(0, GetScreenHeight());

				while (!correctRange)
				{
					if (posy > GetScreenHeight() / 2 - initialCorrection && posy < GetScreenHeight() / 2 + initialCorrection)  posy = GetRandomValue(0, GetScreenHeight());
					else correctRange = true;
				}

				resizeShoot[i].position = { posx, posy };

				correctRange = false;
				velx = GetRandomValue(-powerupSpeed, powerupSpeed);
				vely = GetRandomValue(-powerupSpeed, powerupSpeed);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = GetRandomValue(-powerupSpeed, powerupSpeed);
						vely = GetRandomValue(-powerupSpeed, powerupSpeed);
					}
					else correctRange = true;
				}

				resizeShoot[i].speed = { velx, vely };
				resizeShoot[i].radius = (10 * GetScreenWidth()) / scaleAux;
				resizeShoot[i].active = true;
				resizeShoot[i].color = BLUE;
			}

			for (int i = 0; i < amount; i++)
			{
				posx = GetRandomValue(0, GetScreenWidth());

				while (!correctRange)
				{
					if (posx > GetScreenWidth() / 2 - initialCorrection && posx < GetScreenWidth() / 2 + initialCorrection) posx = GetRandomValue(0, GetScreenWidth());
					else correctRange = true;
				}

				correctRange = false;

				posy = GetRandomValue(0, GetScreenHeight());

				while (!correctRange)
				{
					if (posy > GetScreenHeight() / 2 - initialCorrection && posy < GetScreenHeight() / 2 + initialCorrection)  posy = GetRandomValue(0, GetScreenHeight());
					else correctRange = true;
				}

				nuclear[i].position = { posx, posy };

				correctRange = false;
				velx = GetRandomValue(-powerupSpeed, powerupSpeed);
				vely = GetRandomValue(-powerupSpeed, powerupSpeed);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = GetRandomValue(-powerupSpeed, powerupSpeed);
						vely = GetRandomValue(-powerupSpeed, powerupSpeed);
					}
					else correctRange = true;
				}

				nuclear[i].speed = { velx, vely };
				nuclear[i].radius = (10 * GetScreenWidth()) / scaleAux;
				nuclear[i].active = true;
				nuclear[i].color = BLUE;
			}

			resizeShootScale = (GetScreenWidth() * 1.0f) / scaleAux;
			resizeShootScalePos = { (resizeShootScale * resizeShootImage.width) / 2 ,(resizeShootScale * resizeShootImage.height) / 2 };

			nuclearScale = (GetScreenWidth() * 1.0f) / scaleAux;
			nuclearScalePos = { (nuclearScale * nuclearImage.width) / 2 ,(nuclearScale * nuclearImage.height) / 2 };
		}

		void UpdatePowerUps()
		{
			if (!gameOver)
			{
				for (int a = 0; a < amount; a++)
				{
					if (CheckCollisionCircles({ ship.collider.x, ship.collider.y }, ship.collider.z, resizeShoot[a].position, resizeShoot[a].radius) && resizeShoot[a].active)
					{
						resizeShoot[a].active = false;
						resizeShootActive = true;
					}
				}

				for (int a = 0; a < amount; a++)
				{
					if (CheckCollisionCircles({ ship.collider.x, ship.collider.y }, ship.collider.z, nuclear[a].position, nuclear[a].radius) && nuclear[a].active)
					{
						nuclear[a].active = false;
						nuclearActive = true;
					}
				}

				for (int i = 0; i < amount; i++)
				{
					if (resizeShoot[i].active)
					{
						resizeShoot[i].position.x += resizeShoot[i].speed.x * GetFrameTime() * speedBoost;
						resizeShoot[i].position.y += resizeShoot[i].speed.y * GetFrameTime() * speedBoost;

						if (resizeShoot[i].position.x > GetScreenWidth() + resizeShoot[i].radius) resizeShoot[i].position.x = -(resizeShoot[i].radius);
						else if (resizeShoot[i].position.x < 0 - resizeShoot[i].radius) resizeShoot[i].position.x = GetScreenWidth() + resizeShoot[i].radius;
						if (resizeShoot[i].position.y > GetScreenHeight() + resizeShoot[i].radius) resizeShoot[i].position.y = -(resizeShoot[i].radius);
						else if (resizeShoot[i].position.y < 0 - resizeShoot[i].radius) resizeShoot[i].position.y = GetScreenHeight() + resizeShoot[i].radius;
					}
				}

				for (int i = 0; i < amount; i++)
				{
					if (nuclear[i].active)
					{
						nuclear[i].position.x += nuclear[i].speed.x * GetFrameTime() * speedBoost;
						nuclear[i].position.y += nuclear[i].speed.y * GetFrameTime() * speedBoost;

						if (nuclear[i].position.x > GetScreenWidth() + nuclear[i].radius) nuclear[i].position.x = -(nuclear[i].radius);
						else if (nuclear[i].position.x < 0 - nuclear[i].radius) nuclear[i].position.x = GetScreenWidth() + nuclear[i].radius;
						if (nuclear[i].position.y > GetScreenHeight() + nuclear[i].radius) nuclear[i].position.y = -(nuclear[i].radius);
						else if (nuclear[i].position.y < 0 - nuclear[i].radius) nuclear[i].position.y = GetScreenHeight() + nuclear[i].radius;
					}
				}
			}
		}

		void DrawPowerUps()
		{
			for (int i = 0; i < amount; i++)
			{
				if (resizeShoot[i].active)
				{
					DrawCircleV(resizeShoot[i].position, resizeShoot[i].radius, DARKGRAY);
					DrawTextureEx(resizeShootTexture, { resizeShoot[i].position.x - resizeShootScalePos.x,resizeShoot[i].position.y - resizeShootScalePos.y }, 0, resizeShootScale, WHITE);
				}
				else DrawCircleV(resizeShoot[i].position, resizeShoot[i].radius, BLANK);
			}

			for (int i = 0; i < amount; i++)
			{
				if (nuclear[i].active)
				{
					DrawCircleV(nuclear[i].position, nuclear[i].radius, DARKGRAY);
					DrawTextureEx(nuclearTexture, { nuclear[i].position.x - nuclearScalePos.x,nuclear[i].position.y - nuclearScalePos.y }, 0, nuclearScale, WHITE);
				}
				else DrawCircleV(nuclear[i].position, nuclear[i].radius, BLANK);
			}
		}

		void UnloadPowerUps()
		{
			UnloadTexture(resizeShootTexture);
			UnloadImage(resizeShootImage);
			UnloadTexture(nuclearTexture);
			UnloadImage(nuclearImage);
		}
	}
}