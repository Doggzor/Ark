#include "Paddle.h"

Paddle::Paddle(const Vec2& pos, float halfwidth, float halfheight, float speed)
	:
	pos(pos),
	halfwidth(halfwidth),
	halfheight(halfheight),
	speed(speed)
{
}

void Paddle::Update(const Keyboard& kbd, const RectF& walls, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT)) pos.x -= speed * dt;
	if (kbd.KeyIsPressed(VK_RIGHT)) pos.x += speed * dt;
	if (GetRect().left <= walls.left) pos.x += walls.left - GetRect().left;
	if (GetRect().right >= walls.right) pos.x -= GetRect().right - walls.right;
}

void Paddle::BallCollision(Ball& ball) const
{
	if (GetRect().isColliding(ball.GetRect()) && ball.GetVel().y > 0.0f) ball.BounceY();
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfwidth, halfheight);
}

void Paddle::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetRect(), wingC);
	gfx.DrawRect(RectF::FromCenter(pos, halfwidth - wingwidth, halfheight), padC);
}
