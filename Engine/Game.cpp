/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(320.0f, 350.0f), Vec2(-300.f, -300.0f)),
	walls(0.0f, float(gfx.ScreenWidth), 0.0f, float(gfx.ScreenHeight)),
	soundPad(L"Sounds\\arkpad.wav"),
	brckSound(L"Sounds\\arkbrick.wav"),
	paddle(Vec2(300.0f, 500.0f), 75.0f, 15.0f)
{
	int i = 0;
	Color colorArray[] = {Colors::Red, Colors::Blue, Colors::Green, Colors::Magenta};

	const Vec2 topLeft(40.0f, 40.0f);
	for (int y = 0; y < brickRows; y++)
	{
		for (int x = 0; x < brickCols; x++)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), colorArray[y]);
			i++;
		}
	}
}

void Game::Go()
{
	
	float elapsedTime = ft.Mark();
	gfx.BeginFrame();	
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (!gameOver)
	{
		ball.Update(dt);
		paddle.Update(wnd.kbd, dt);
		paddle.DoWallCollision(walls);

		float lowestLength = 0;
		int colIndex = 0;
		float current;
		for (int i = 0; i < nBrickMax; i++)
		{
			if (bricks[i].CheckCollision(ball))
			{
				current = (ball.GetPosition() - bricks[i].GetPostion()).GetLengthSq();
				if (lowestLength == 0 || current < lowestLength)
				{
					lowestLength = current;
					colIndex = i;
				}
			}
		}

		if (lowestLength != 0)
		{
			bricks[colIndex].DoCollision(ball);
			brckSound.Play();
			paddle.ResedBallColided();
		}

		const int ballWallColResult = ball.DoWallCollision(walls);

		if (ballWallColResult == 1)
		{
			soundPad.Play();
			paddle.ResedBallColided();
		}
		else if(ballWallColResult == 2){
			gameOver = true;
		}
		if (paddle.DoBallCollision(ball))
		{
			soundPad.Play();
		}
	}
}

void Game::ComposeFrame()
{
	if (!gameOver)
	{
		ball.Draw(gfx);
		paddle.Draw(gfx);
	}
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
}
