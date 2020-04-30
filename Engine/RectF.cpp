#include "RectF.h"

RectF::RectF(float top, float bottom, float left, float right)
	:
	top(top),
	bottom(bottom),
	left(left),
	right(right)
{
}

RectF::RectF(const Vec2& topleft, const Vec2& bottomright)
	:
	RectF(topleft.y, bottomright.y, topleft.x, bottomright.x)
{
}

RectF::RectF(const Vec2& topleft, float width, float height)
	:
	RectF(topleft.y, topleft.y + height, topleft.x, topleft.x + width)
{
}

RectF RectF::FromCenter(const Vec2& center, float halfwidth, float halfheight)
{
	return RectF(center.y - halfheight, center.y + halfheight, center.x - halfwidth, center.x + halfwidth);
}

bool RectF::isColliding(const RectF& rect) const
{
	return top < rect.bottom && bottom > rect.top && left < rect.right && right > rect.left;
}

RectF RectF::GetShrunk(float offset) const
{
	return RectF(top + offset, bottom - offset, left + offset, right - offset);
}

Vec2 RectF::GetCenter() const
{
	return Vec2((left + right) / 2.0f, (top + bottom) / 2.0f);
}
