#pragma once
#include "Point.h"

using namespace std;

class CGrouping
{
	double m_range;
	int m_memCnt;
	int m_sectorCnt;
	int m_sectorStartNum;
	vector<Point*>* m_vp;

	double Distance( const Point* p1, const Point* p2 );
	void Clustering( Point* pp );
	
public:
	CGrouping(vector<Point*>& _vp, double _range, int _memCnt);
	void Run();
};

