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

//Function
vec3 min(vec3 a, vec3 b);
vec3 max(vec3 a, vec3 b);
float magnitude(const vec3 v);
vec3 normal(const vec3 v);
vec3 normalize(vec3 &v);
float dot(const vec3 &v1, const vec3 &v2);
//Use this for two points
float distance(vec3 &v1, vec3 &v2);
vec3 &clamp(vec3 &v, const vec3 &min, const vec3 &max);

vec3 cross(const vec3 &v, const vec3 &w);