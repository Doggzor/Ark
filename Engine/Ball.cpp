#include "Ball.h"

Ball::Ball(const Vec2& in_pos, const Vec2& in_vel, float in_speed)
	:
	pos(in_pos),
	vel(in_vel),
	speed(in_speed)
{
}

void Ball::Update(const RectF& paddle, float dt)
{
	if (bLaunched)
	{
		const Vec2 dir = ((pos + vel) - pos).GetNormalized();
		pos += dir * speed * dt;
	}
	else
		pos = Vec2((paddle.GetCenter().x + (paddle.right - paddle.left) / 5.0f), paddle.top - radius);
}

void Ball::launch()
{
	bLaunched = true;
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
void Ball::SetVX(float vx)
{
	vel.x = vx;
}
void Ball::SetPX(float px)
{
	pos.x = px;
}
void Ball::SetPY(float py)
{
	pos.y = py;
}
RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

const Vec2 Ball::GetVel() const
{
	return vel;
}

float Ball::GetRadius() const
{
	return radius;
}

void Ball::Draw(Graphics& gfx) const
{
	const int x = (int)pos.x;
	const int y = (int)pos.y;
	const int r = (int)radius;
	gfx.DrawCircle(x, y, r, Colors::Yellow);
}
