#pragma once

union vec2
{
	//access by array
	float v[2];

	//access by individual component
	struct { float x, y; };
};

// arithmetic operators
vec2 operator+(const vec2 &lhs, const vec2 &rhs);
vec2 operator-(const vec2 &lhs, const vec2 &rhs);

vec2 operator*(const vec2 &lhs, const float &rhs);
vec2 operator*(const float &lhs, const vec2 &rhs);

vec2 operator/(const vec2 &lhs, const float &rhs);

//Unary negation
vec2 operator-(const vec2 &rhs);

// compound assignment operators
vec2 &operator+=(vec2 &lhs, const vec2 &rhs);
vec2 &operator-=(vec2 &lhs, const vec2 &rhs);
vec2 &operator*=(vec2 &lhs, const float rhs);
vec2 &operator/=(vec2 &lhs, const float rhs);

// logical operators
bool operator==(const vec2 &lhs, const vec2 &rhs);
bool operator!=(const vec2 &lhs, const vec2 &rhs);