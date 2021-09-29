#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx);
	void DoWallCollision(const RectF& walls);
	bool DoBallCollision(Ball& ball);
	void Update(Keyboard& kbd, float dt);
	RectF GetRect() const;
	void ResedBallColided();
private:
	static constexpr float wingWidth = 15.f;
	Color wingColor = Colors::Red;
	Color color = Colors::White;
	float speed = 300.0f;
	float halfWidth;
	float halfHeight;
	bool ballColided = false;
	Vec2 pos;
};