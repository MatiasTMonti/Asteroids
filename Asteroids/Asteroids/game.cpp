#include "game.h"

#include "raylib.h"

#include "meteors.h"
#include "spaceship.h"
#include "app.h"
#include "powerups.h"

using namespace app;
using namespace	spaceship;
using namespace	meteors;
using namespace powerups;

namespace app
{
	namespace game
	{
		extern bool victory = false;
		extern bool gameOver = false;
		static char text[] = "CLICK DER: Acelerar, CLICK IZQ: Disparar";
		static int sizeText;
		static float textPositionX;
		static float textPositionY;

		//Imagenes y texturas
		static Image backImage;
		static Texture2D backTexture;

		//Boton pausa
		static Rectangle btnPause1;
		static Rectangle btnPause2;
		static Color colorRect;
		static Vector2 mousePoint;

		static bool init;

		void InitValues()
		{
			sizeText = (GetScreenWidth() * 20) / 1600;
			textPositionX = GetScreenWidth() * 0.01f;
			textPositionY = GetScreenHeight() * 0.97f;

			backImage = LoadImage("../res/gameBackground.png");

			//init boton pausa
			btnPause1.x = GetScreenWidth() * 0.96f;
			btnPause1.y = GetScreenHeight() * 0.02f;
			btnPause1.height = (GetScreenWidth() * 40) / 1600;
			btnPause1.width = (GetScreenWidth() * 15) / 1600;
			btnPause2.x = GetScreenWidth() * 0.975f;
			btnPause2.y = GetScreenHeight() * 0.02f;
			btnPause2.height = (GetScreenWidth() * 40) / 1600;
			btnPause2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;

			backTexture = LoadTextureFromImage(backImage);

			InitPowerUps();
			InitMeteors();
			InitSpaceship();
		}


		static void Input()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, btnPause1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, btnPause2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}

		}

		static void Update()
		{

			UpdatePowerUps();
			UpdateSpaceship();
			UpdateMeteors();
		}

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void Draw()
		{
			ClearBackground(BLANK);
			DrawTexture(backTexture, 0, 0, WHITE);

			DrawPowerUps();
			DrawSpaceship();
			DrawMeteors();

			DrawRectangleRec(btnPause1, colorRect);
			DrawRectangleRec(btnPause2, colorRect);
			DrawText(text, textPositionX, textPositionY, sizeText, RED);
		}

		void ResetValues()
		{
			InitValues();
			gameOver = false;
		}

		void UnloadGameplay()
		{
			UnloadPowerUps();
			UnloadMeteors();
			UnloadSpaceship();
			UnloadTexture(backTexture);
			UnloadImage(backImage);
		}
	}
}