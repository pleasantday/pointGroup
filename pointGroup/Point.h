#pragma once
#include <string>
#include <vector>
using namespace std;

enum PointAttribute
{
	NONE = 0,
	CORE,
	BORDER,
	NOISE
};

class Point
{
public:
	int id;
	double x;
	double y;
	int sector;
	string type;
	int attr;
	vector<Point*> member;

	Point()
	{
		double f = rand() % 1000;
		double b = rand() % 1000000;
		x = f + b / 1000000;

		f = rand() % 1000;
		b = rand() % 1000000;
		y = f + b / 1000000;

		sector = 0;
		type = "";
		attr = PointAttribute::NONE;
	}
};