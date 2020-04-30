#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
class Ball
{
public:
	Ball(const Vec2& in_pos, const Vec2& in_vel);
	void Update(float dt);
	bool WallBounce(const RectF& walls);
	void BounceX();
	void BounceY();
	RectF GetRect() const;
	const Vec2 GetVel() const;
	void Draw(Graphics& gfx) const;
private:
	Vec2 pos;
	Vec2 vel;
	static constexpr float radius = 7;
};

