#include "Ball.h"

Ball::Ball(const Vec2& in_pos, const Vec2& in_vel)
	:
	pos(in_pos),
	vel(in_vel)
{
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

bool Ball::WallBounce(const RectF& walls)
{
	if (GetRect().left <= walls.left)
	{
		pos.x += walls.left - GetRect().left;
		BounceX();
	}
	else if (GetRect().right >= walls.right)
	{
		pos.x -= GetRect().right - walls.right;
		BounceX();
	}
	if (GetRect().top <= walls.top)
	{
		pos.y += walls.top - GetRect().top;
		BounceY();
	}
	else if (GetRect().bottom >= walls.bottom)
	{
		pos.y -= GetRect().bottom - walls.bottom;
		BounceY();
	}
	return GetRect().left <= walls.left || GetRect().right >= walls.right || GetRect().top <= walls.top || GetRect().bottom >= walls.bottom;
}

void Ball::BounceX()
{
	vel.x = -vel.x;
}

void Ball::BounceY()
{
	vel.y = -vel.y;
}
RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

const Vec2 Ball::GetVel() const
{
	return vel;
}

void Ball::Draw(Graphics& gfx) const
{
	const int x = (int)pos.x;
	const int y = (int)pos.y;
	const int r = (int)radius;
	gfx.DrawCircle(x, y, r, Colors::Yellow);
}
