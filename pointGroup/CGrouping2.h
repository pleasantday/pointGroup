#pragma once
#include "Point.h"

using namespace std;

class CGrouping2
{
	double m_range;
	int m_sectorCnt;
	vector<Point*>* m_vp;

	double Distance( const Point* p1, const Point* p2 );

public:
	CGrouping2( vector<Point*>& _vp, double _range );

	void Run();
};

