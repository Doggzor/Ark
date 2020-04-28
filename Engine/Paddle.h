#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"
#include "Ball.h"
#include "Keyboard.h"
class Paddle
{
public:
	Paddle(const Vec2& pos, float halfwidth, float halfheight, float speed);
	void Update(const Keyboard& kbd, const RectF& walls, float dt);
	void BallCollision(Ball& ball) const;
	RectF GetRect() const;
	void Draw(Graphics& gfx) const;
private:
	Vec2 pos;
	float halfwidth;
	float halfheight;
	Color padC = Colors::White;
	static constexpr float wingwidth = 15.0f;
	Color wingC = Colors::Red;
	float speed;

};

