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
	bool DoCollision(Ball& ball);
private:
	RectF rect;
	Color color;
	bool destroyed = false;
};