#pragma once
#include "Vec2.h"
class RectF
{
public:
	RectF() = default;
	RectF(float top, float bottom, float left, float right);
	RectF(const Vec2& topleft, const Vec2& bottomright);
	RectF(const Vec2& topleft, float width, float height);
	static RectF FromCenter(const Vec2& center, float halfwidth, float halfheight);
	bool isColliding(const RectF& rect) const;
	RectF GetShrunk(float offset) const;
	Vec2 GetCenter() const;

	float top;
	float bottom;
	float left;
	float right;

};

