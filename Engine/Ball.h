#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
class Ball
{
public:
	Ball(const Vec2& in_pos, const Vec2& in_vel, float in_speed);
	void Update(const RectF& paddle, float dt);
	void launch();
	bool WallBounce(const RectF& walls);
	void BounceX();
	void BounceY();
	void SetVX(float vx);
	void SetPX(float px);
	void SetPY(float py);
	RectF GetRect() const;
	const Vec2 GetVel() const;
	float GetRadius() const;
	void Draw(Graphics& gfx) const;
private:
	Vec2 pos;
	Vec2 vel;
	float speed;
	static constexpr float radius = 7;
	bool bLaunched = false;
};

