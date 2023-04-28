#pragma once
#include "stdafx.h"

struct Vector2
{
	float x;
	float y;

	Vector2() : x(0.f), y(0.f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vector2(float _right) : x(_right), y(_right) {}
	Vector2(int _right) : x((float)_right), y((float)_right) {}
	//Vector2(const Vector2&& _right) :x(_right.x), y(_right.y) {/**/}
	Vector2(const Vector2& rhs) :x(rhs.x), y(rhs.y) {}
	void operator =(Vector2 _right)		{ x = _right.x; y = _right.y; }

	bool operator ==(Vector2 _right)	{ return (x == _right.x && y == _right.y); }
	bool operator !=(Vector2 _right)	{ return !(*this == _right); }

	void operator +=(Vector2 _right)	{ x += _right.x; y += _right.y; }
	void operator -=(Vector2 _right)	{ x -= _right.x; y -= _right.y; }
	void operator *=(Vector2 _right)	{ x *= _right.x; y *= _right.y; }
	void operator *=(float _right)		{ x *= _right; y *= _right; }
	friend Vector2 operator *=(float _left, Vector2 _right) { return Vector2(_left*_right.x, _left*_right.y); }
	void operator /=(Vector2 _right)	{ assert(_right.x != 0 || _right.y != 0); x /= _right.x; y /= _right.y; }
	void operator /=(float _right)		{ assert(_right != 0); x /= _right; y /= _right; }

	Vector2 operator +(Vector2 _right)	{ return Vector2(x + _right.x, y + _right.y); }
	Vector2 operator -(Vector2 _right)	{ return Vector2(x - _right.x, y - _right.y); }
	Vector2 operator *(Vector2 _right)	{ return Vector2(x * _right.x, y * _right.y); }
	Vector2 operator *(float _right)	{ return Vector2(x * _right, y * _right); }
	friend Vector2 operator*(float _left, Vector2 _right) { return _right * _left; };
	Vector2 operator /(Vector2 _right)	{ assert(_right.x != 0 || _right.y != 0);  return Vector2(x / _right.x, y / _right.y); }
	Vector2 operator /(float _right)	{ assert(_right != 0);	return Vector2(x / _right, y / _right); }

	Vector2 Normalize()					{ return Vector2(x / Length(), y / Length()); }
	float Dot(Vector2 _right)			{ return x * _right.x + y * _right.y; }
	static float Dot(Vector2 _left, Vector2 _right) { return _left.x * _right.x + _left.y * _left.y; }
	float Length()						{ return sqrt(x * x + y * y); }
	float LengthSquared()				{ return x * x + y * y; }
	static float Distance(Vector2 _left, Vector2 _right)			{ return (_left - _right).Length(); }
	static float DistanceSquared(Vector2 _left, Vector2 _right)	{ return (_left - _right).LengthSquared(); }

	Vector2 Clamp(const Vector2 _min, const Vector2 _max)
	{
		Vector2 ret = *this;
		(x <= _min.x) ? (x = _min.x) : ((x > _max.x) ? (x = _max.x) : x);
		(y <= _min.y) ? (y = _min.y) : ((y > _max.y) ? (y = _max.y) : y);
		return ret;
	}

	static void Clamp(Vector2 _min, Vector2 _max, Vector2 _ret)
	{
		(_ret.x <= _min.x) ? (_ret.x = _min.x) : ((_ret.x > _max.x) ? (_ret.x = _max.x) : _ret.x);
		(_ret.y <= _min.y) ? (_ret.y = _min.y) : ((_ret.y > _max.y) ? (_ret.y = _max.y) : _ret.y);
	}
	
	static Vector2 Lerp(Vector2 _left, Vector2 _right, float t)
	{
		Vector2 ret;
		t = (t > 1.f) ? 1.f : ((t < 0.f) ? 0.f : t);
		ret.x = _left.x + t * (_right.x - _left.x);
		ret.y = _left.y + t * (_right.y - _left.y);
		return ret;
	}

	static Vector2 Reflect(Vector2 _incidence, Vector2 _normal)
	{
		return _incidence - 2.f * Dot(_incidence, _normal) * _normal;
	}

	static Vector2 Up()	{ return Vector2(0.f, -1.f); }
	static Vector2 Down()	{ return Vector2(0.f, 1.f); }
	static Vector2 Right() { return Vector2(1.f, 0.f); }
	static Vector2 Left()	{ return Vector2(-1.f, 0.f); }

	static Vector2 UnitX() { return Vector2(1.f, 0.f); }
	static Vector2 UnitY() { return Vector2(0.f, 1.f); }

	static Vector2 Zero()	{ return Vector2(0.f, 0.f); }
	static Vector2 One()	{ return Vector2(1.f, 1.f); }
};