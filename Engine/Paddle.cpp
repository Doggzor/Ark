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

void Paddle::BallCollision(Ball& ball)
{
	RectF rect = GetRect();
	if (!bCoolDown && rect.isColliding(ball.GetRect()))
	{
		const Vec2 ballcenter = ball.GetRect().GetCenter();
		if (ballcenter.x > rect.left && ballcenter.x < rect.right
			|| signbit(ball.GetVel().x) == signbit((ballcenter - pos).x)) ball.BounceY();
		else ball.BounceX();
		bCoolDown = true;
	}
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

void Paddle::ResetCoolDown()
{
	bCoolDown = false;
}
