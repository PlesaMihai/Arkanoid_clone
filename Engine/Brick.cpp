#include "Brick.h"

Brick::Brick(const RectF & rect_in, Color color_in)
	:
	rect(rect_in),
	color(color_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect, color);
	}
}

bool Brick::DoCollision(Ball& ball)
{
	if (!destroyed && ball.GetRect().IsOverlappingWith(rect))
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}
	return false;
}
