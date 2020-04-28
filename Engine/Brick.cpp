#include "Brick.h"

Brick::Brick(const RectF& rect, Color c)
	:
	rect(rect),
	c(c)
{
}

void Brick::BallCollision(Ball& ball)
{
	if (!destroyed && rect.RectF::isColliding(ball.GetRect()))
	{
		ball.BounceY();
		destroyed = true;
	}
}

void Brick::Draw(Graphics& gfx) const
{
	if(!destroyed) gfx.DrawRect(rect.GetShrunk(padding), c);
}
