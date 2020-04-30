#include "Brick.h"

Brick::Brick(const RectF& rect, Color c)
	:
	rect(rect),
	c(c)
{
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return (!destroyed && rect.isColliding(ball.GetRect()));
}

void Brick::ExecutekBallCollision(Ball& ball)
{
	if (CheckBallCollision(ball))
	{
		const Vec2 ballcenter = ball.GetRect().GetCenter();
		if (ballcenter.x > rect.left && ballcenter.x < rect.right
			|| signbit(ball.GetVel().x) == signbit((ballcenter - GetCenter()).x)) ball.BounceY();
		else ball.BounceX();
		destroyed = true;
	}
}

Vec2 Brick::GetCenter() const
{
	return Vec2(rect.GetCenter());
}

void Brick::Draw(Graphics& gfx) const
{
	if(!destroyed) gfx.DrawRect(rect.GetShrunk(padding), c);
}
