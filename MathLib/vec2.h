#pragma once

union vec2
{
	//access by array
	float v[2];

	//access by individual component
	struct { float x, y; };

	//access to vec2 by index
	float &operator[](int x);
	float operator[](int x) const;
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

//Function
vec2 min(vec2 a, vec2 b);
vec2 max(vec2 a, vec2 b);
float magnitude(const vec2 v);
vec2 normal(const vec2 v);
vec2 normalize(vec2 &v);
float dot(const vec2 &v1, const vec2 &v2);
//Use this for two points
float distance(vec2 &v1, vec2 &v2);

vec2 perpendicular(const vec2 &v, bool clockwise);
vec2 projection(const vec2 &A, const vec2 &B);


//cross product
//vec3 cross(vec3 &v1, vec3 &v2);

//A from 0.0 to 1.0
vec2 lerp(vec2 start, vec2 end, float a);
vec2 clamp(vec2 &v, const vec2 &min, const vec2 &max);

vec2 degreeToVector(float d, float m);
float VectorToDegree(vec2 vec);