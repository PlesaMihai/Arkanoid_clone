#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Ball.h"
#include "Graphics.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, Color color_in);
	void Draw(Graphics& gfx) const;
	bool CheckCollision(const Ball& ball) const;
	void DoCollision(Ball& ball);
	RectF GetRect() const;
	Vec2 GetPostion() const;
private:
	static constexpr float padding = 1.0f;
	RectF rect;
	Color color;
	bool destroyed = false;
};