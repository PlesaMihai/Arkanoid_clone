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
		gfx.DrawRect(rect.GetExpanded(-padding), color);
	}
}

bool Brick::CheckCollision(const Ball & ball) const
{
	if (!destroyed)
	{
		if (ball.GetRect().IsOverlappingWith(rect))
		{
			return true;
		}
	}
	return false;
}

void Brick::DoCollision(Ball& ball)
{
	if (!destroyed)
	{
		Vec2 ballPos = ball.GetPosition();
		if ((std::signbit(ball.GetVelocity().x) == std::signbit( (ballPos - GetPostion()).x)))
		{
			ball.ReboundY();
		}else if (ballPos.x >= rect.left && ballPos.x <= rect.right)
		{
			ball.ReboundY();
		}
		else {
			ball.ReboundX();
		}
		destroyed = true;
	}
}

RectF Brick::GetRect() const
{
	return rect;
}

Vec2 Brick::GetPostion() const
{
	return rect.GetCenter();
}
