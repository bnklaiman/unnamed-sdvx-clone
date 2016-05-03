#pragma once
#include "VectorMath.hpp"

// GUI space rectangle with bottom as y+height
template<typename T>
class RectangleBase
{
public:
	typedef VectorMath::VectorBase<T, 2> VectorType;
	VectorType pos;
	VectorType size;
	RectangleBase() = default;
	RectangleBase(T left, T top, T right, T bottom)
	{
		pos = VectorType(left, top);
		size = VectorType(right - left, bottom - top);
	}
	RectangleBase(const VectorType& pos, const VectorType& size)
		: pos(pos), size(size)
	{
	}
	T Left() const
	{
		return pos.x;
	}
	T Top() const
	{
		return pos.y;
	}
	T Bottom() const
	{
		return pos.y + size.y;
	}
	T Right() const
	{
		return pos.x + size.x;
	}
	// Moves the edges of this rectangle inward or outward
	RectangleBase Offset(float amount) const
	{
		RectangleBase newRect = *this;
		VectorType newSize = newRect.size + VectorType(amount);
		if(newSize.x < 0)
			newSize.x = 0;
		if(newSize.y < 0)
			newSize.y = 0;

		VectorType halfDelta = (newSize - newRect.size);
		newRect.pos -= halfDelta;
		newRect.size += halfDelta * 2;
		return newRect;
	}
	// Moves the upper and lower edges of this rectangle inward or outward
	RectangleBase OffsetY(float amount) const
	{
		RectangleBase newRect = *this;
		VectorType newSize = newRect.size + VectorType(0, amount);
		if(newSize.y < 0)
			newSize.y = 0;

		VectorType halfDelta = (newSize - newRect.size);
		newRect.pos -= halfDelta;
		newRect.size += halfDelta * 2;
		return newRect;
	}
	// Moves the upper and lower edges of this rectangle inward or outward
	RectangleBase OffsetX(float amount) const
	{
		RectangleBase newRect = *this;
		VectorType newSize = newRect.size + VectorType(amount, 0);
		if(newSize.x < 0)
			newSize.x = 0;

		VectorType halfDelta = (newSize - newRect.size);
		newRect.pos -= halfDelta;
		newRect.size += halfDelta * 2;
		return newRect;
	}
};

// Same as a normal rectangle but this one has the top as y+height aka world space
template<typename T>
class RectangleBase3D : public RectangleBase<T>
{
public:
	using RectangleBase::RectangleBase;
	RectangleBase3D() = default;
	RectangleBase3D(const RectangleBase<T>& other)
	{
		pos = other.pos; 
		size = other.size;
	};
	RectangleBase3D(T left, T top, T right, T bottom)
	{
		pos = VectorType(left, bottom);
		size = VectorType(right - left, top - bottom);
	}
	T Top() const
	{
		return pos.y + size.y;
	}
	T Bottom() const
	{
		return pos.y;
	}
};

typedef RectangleBase<float> Rect;
typedef RectangleBase<int32> Recti;
typedef RectangleBase3D<float> Rect3D;
typedef RectangleBase3D<int32> Recti3D;