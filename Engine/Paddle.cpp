#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Draw(Graphics & gfx)
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);
}

void Paddle::DoWallCollision(const RectF & walls)
{
	RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}

bool Paddle::DoBallCollision(Ball & ball)
{
	if (GetRect().IsOverlappingWith(ball.GetRect()) && !ballColided)
	{
		Vec2 ballPos = ball.GetPosition();
		const RectF rect = GetRect();
		if ((std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - pos).x)))
		{
			ball.ReboundY();
		}
		else if (ballPos.x >= rect.left && ballPos.x <= rect.right)
		{
			ball.ReboundY();
		}
		else {
			ball.ReboundX();
		}
		ballColided = true;
		return true;
	}
	return false;
}

void Paddle::Update(Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

void Paddle::ResedBallColided()
{
	ballColided = false;
}
