#include "pch.h"
#include "CGrouping2.h"

CGrouping2::CGrouping2( vector<Point*>& _vp, double _range )
{
	m_vp = &_vp;
	m_range = _range;
	m_sectorCnt = 0;
}

double CGrouping2::Distance( const Point* p1, const Point* p2 )
{
	return sqrt( pow( p1->x - p2->x, 2 ) + pow( p1->y - p2->y, 2 ) );
}

void CGrouping2::Run()
{
	while( 1 )
	{
		// point에 member 찾아넣기
		for( int i = 0; i < m_vp->size(); ++i )
		{
			if( (*m_vp)[i]->sector > -1 )	// sector가 정해진 point는 member를 찾을 필요 없다.
				continue;

			for( int j = 0; j < m_vp->size(); ++j )
			{
				if( i == j )	// 자기 자신 넣지 않기
					continue;

				if( (*m_vp)[j]->sector > -1 )	// sector가 정해진 point는 member에 넣을 필요 없다.
					continue;

				if( Distance( (*m_vp)[i], (*m_vp)[j] ) < m_range )
					(*m_vp)[i]->member.push_back( (*m_vp)[j] );
			}
		}

		// 가장 많은 멤버를 가진  point 찾기
		Point* maxPt = nullptr;
		int memCnt = 0;
		for( int i = 0; i < m_vp->size(); ++i )
		{
			if( (*m_vp)[i]->sector > -1 )	// sector가 정해진 point는 제외
				continue;

			if( (*m_vp)[i]->member.size() > memCnt )
			{
				maxPt = (*m_vp)[i];
				memCnt = maxPt->member.size();
			}
		}

		if( memCnt == 0 )	// 가장 큰 멤버수가 0이면 종료
		{
			// member가 0인 point들 sector id 부여
			for( int i = 0; i < m_vp->size(); ++i )
			{
				if( (*m_vp)[i]->member.size() == 0 )
				{
					(*m_vp)[i]->sector = m_sectorCnt++;
					(*m_vp)[i]->type = "NOISE";
				}
			}
			return;
		}

		// point와 point의 member에 sector id 부여
		maxPt->sector = m_sectorCnt;
		maxPt->type = "CORE";
		for( int i = 0; i < maxPt->member.size(); ++i )
		{
			maxPt->member[i]->sector = m_sectorCnt;
			maxPt->member[i]->type = "BORDER";
		}
		++m_sectorCnt;

		// sector id가 부여되지 않은 point들의 member vector를 clear
		for( int i = 0; i < m_vp->size(); ++i )
		{
			if( (*m_vp)[i]->sector > -1 )
				continue;

			(*m_vp)[i]->member.clear();
		}
	}
}