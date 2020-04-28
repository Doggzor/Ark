#pragma once
#include "Graphics.h"
#include "Ball.h"
#include "Vec2.h"
class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect, Color c);
	void BallCollision(Ball& ball);
	void Draw(Graphics& gfx) const;
private:
	RectF rect;
	static constexpr float padding = 1.0f;
	Color c;
	bool destroyed = false;
};

