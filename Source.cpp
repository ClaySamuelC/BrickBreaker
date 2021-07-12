#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

bool isCollided(olc::vd2d& aPos, olc::vd2d& aRad, olc::vd2d& bPos, olc::vd2d& bRad)
{
	return (
		(aPos.x + aRad.x < bPos.x - bRad.x &&
		aPos.y + aRad.y < bPos.y - bRad.y) ||
		(aPos.x - aRad.x > bPos.x + bRad.x &&
		aPos.y - aRad.y > bPos.y + bRad.y)
	);
}

class BrickBreaker : public olc::PixelGameEngine
{
public:
	BrickBreaker()
	{
		sAppName = "BrickBreaker";
	}

	olc::vi2d fieldSize = { 400, 600 };
	
	olc::vd2d playerPos = { fieldSize.x / 2, fieldSize.y * 0.9 };
	olc::vd2d ballPos = { fieldSize.x / 2, fieldSize.y / 2 };
	olc::vd2d ballVel = { 0, 100.0f };

	olc::vd2d playerSize = { 80.0, 32.0 };

	olc::vd2d playerRadius = { playerSize.x / 2, playerSize.y / 2 };
	olc::vd2d ballRadius = { 5, 5 };
	
	float playerVel = 500.0f;

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Input
		if (GetKey(olc::LEFT).bHeld)
		{
			playerPos.x -= (playerVel * double(fElapsedTime));
		}
		if (GetKey(olc::RIGHT).bHeld)
		{
			playerPos.x += (playerVel * double(fElapsedTime));
		}

		// Game Logic
		ballPos += ballVel * fElapsedTime;

		// Collisions
		if (playerPos.x - playerRadius.x < 0)
			playerPos.x = playerRadius.x;
		if (playerPos.x + playerRadius.x >= fieldSize.x)
			playerPos.x = fieldSize.x - playerRadius.x - 1;
		if (isCollided(ballPos, ballRadius, playerPos, playerRadius))
			playerVel = -playerVel;

		// Draw
		Clear(olc::GREY);
		FillRect(playerPos - playerRadius, playerSize, olc::YELLOW);
		FillCircle(ballPos, 10, olc::BLACK);

		return true;
	}
};


int main()
{
	BrickBreaker demo;
	if (demo.Construct(demo.fieldSize.x, demo.fieldSize.y, 1, 1))
		demo.Start();

	return 0;
}
