#pragma once


namespace luled
{

struct Quaternion
{
	float x, y, z, w;
};

struct Vector3
{
	float x, y, z;
};

struct Matrix3
{
	float m[3][3];
};

struct Matrix4
{
	float m[4][4];

};


class Plane
{
public:
	Plane();
	~Plane();
private:


};


}