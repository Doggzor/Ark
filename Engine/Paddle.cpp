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
		const float dist = (ball.GetRect().GetCenter().x - pos.x) / halfwidth; //Distance from place of impact to the center of the paddle
		if (ballcenter.x + ball.GetRadius() / 2.0f > rect.left && ballcenter.x - ball.GetRadius() / 2.0f < rect.right) //Ball bouncing off the top of the paddle
		{
			ball.SetVX(dist * 1.5f);
			ball.BounceY();
		}
		else //Ball bouncing off the sides of the paddle
		{
			ball.SetVX(dist);
			if (ballcenter.x < pos.x) ball.SetPX(rect.left - ball.GetRadius()); //Set ball x to be the same as left side of the paddle 
			else if (ballcenter.x > pos.x) ball.SetPX(rect.right + ball.GetRadius()); //Set ball x to be the same as right side of the paddle
		}
		bCoolDown = true;
	}
	if (ball.bHitBottom)
	{
		--nLives;
		ball.bHitBottom = false;
		if (nLives <= 0) bGameOver = true;
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

void Paddle::DrawLives(Graphics& gfx) const
{
	const float lifeHalfWidth = 30.0f;
	const float lifeHalfHeight = 6.0f;
	const float lifeWingWidth = 9.0f;
	const Vec2 life1Pos(15.0f + lifeHalfWidth, 570.0f + lifeHalfHeight);
	const RectF life1Rect(RectF::FromCenter(life1Pos, lifeHalfWidth, lifeHalfHeight));
	if (nLives >= 3)
	{
		gfx.DrawRect(life1Rect, wingC);
		gfx.DrawRect(RectF::FromCenter(life1Pos, lifeHalfWidth - lifeWingWidth, lifeHalfHeight), padC);
		const Vec2 life2Pos(15.0f + lifeHalfWidth, 570.0f - lifeHalfHeight * 3);
		const RectF life2Rect(RectF::FromCenter(life2Pos, lifeHalfWidth, lifeHalfHeight));
		gfx.DrawRect(life2Rect, wingC);
		gfx.DrawRect(RectF::FromCenter(life2Pos, lifeHalfWidth - lifeWingWidth, lifeHalfHeight), padC);
		const Vec2 life3Pos(15.0f + lifeHalfWidth, 570.0f - lifeHalfHeight * 7);
		const RectF life3Rect(RectF::FromCenter(life3Pos, lifeHalfWidth, lifeHalfHeight));
		gfx.DrawRect(life3Rect, wingC);
		gfx.DrawRect(RectF::FromCenter(life3Pos, lifeHalfWidth - lifeWingWidth, lifeHalfHeight), padC);
	}
	else if (nLives == 2)
	{
		gfx.DrawRect(life1Rect, wingC);
		gfx.DrawRect(RectF::FromCenter(life1Pos, lifeHalfWidth - lifeWingWidth, lifeHalfHeight), padC);
		const Vec2 life2Pos(15.0f + lifeHalfWidth, 570.0f - lifeHalfHeight * 3);
		const RectF life2Rect(RectF::FromCenter(life2Pos, lifeHalfWidth, lifeHalfHeight));
		gfx.DrawRect(life2Rect, wingC);
		gfx.DrawRect(RectF::FromCenter(life2Pos, lifeHalfWidth - lifeWingWidth, lifeHalfHeight), padC);
	}
	else if (nLives == 1)
	{
		gfx.DrawRect(life1Rect, wingC);
		gfx.DrawRect(RectF::FromCenter(life1Pos, lifeHalfWidth - lifeWingWidth, lifeHalfHeight), padC);
	}
}

void Paddle::ResetCoolDown()
{
	bCoolDown = false;
}
