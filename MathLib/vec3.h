#pragma once

union vec3
{
	float v[3];
	struct { float x, y, z; };

	float &operator[](int index);
	float operator[](int index) const;
};

//Arithmetic Operators
vec3 operator+(const vec3 &lhs, const vec3 &rhs);
vec3 operator-(const vec3 &lhs, const vec3 &rhs);

vec3 operator*(const vec3 &lhs, const float &rhs);
vec3 operator*(const float &lhs, const vec3 &rhs);

vec3 operator/(const vec3 &lhs, const float &rhs);

//Unary negation
vec3 operator-(const vec3 &lhs);

// compound assignment operators
vec3 &operator+=(vec3 &lhs, const vec3 &rhs);
vec3 &operator-=(vec3 &lhs, const vec3 &rhs);
vec3 &operator*=(vec3 &lhs, const float rhs);
vec3 &operator/=(vec3 &lhs, const float rhs);

// logical operators
bool operator==(const vec3 &lhs, const vec3 &rhs);
bool operator!=(const vec3 &lhs, const vec3 &rhs);