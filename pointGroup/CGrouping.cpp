#include "pch.h"
#include "CGrouping.h"

CGrouping::CGrouping( vector<Point*>& _vp, double _range, int _memCnt )
{
	m_vp = &_vp;
	m_range = _range;
	m_memCnt = _memCnt;
	m_sectorCnt = 0;
	m_sectorStartNum = m_sectorCnt;
}

double CGrouping::Distance( const Point* p1, const Point* p2 )
{
	return sqrt( pow( p1->x - p2->x, 2 ) + pow( p1->y - p2->y, 2 ) );
}

void CGrouping::Clustering( Point* pp )
{
	if( pp->member.size() == 0 )	// member�� ���� Point�� �ٽ� member ã�� �ʿ����
	{
		for( auto iter2 = m_vp->begin(); iter2 != m_vp->end(); ++iter2 )
		{
			if( pp->id == (*iter2)->id )	// �ڽ��� member�� ���� �ʴ´�
				continue;

			if( Distance( pp, (*iter2) ) < m_range )
				pp->member.push_back( (*iter2) );

		}
	}

	// type and sector setting
	if( pp->member.size() >= m_memCnt )
	{
		pp->type = "CORE";

		if( pp->sector < m_sectorStartNum )	// ���� sector�� ���� ���
			pp->sector = m_sectorCnt++;

		for( int i = 0; i < pp->member.size(); ++i )
		{
			pp->member[i]->sector = pp->sector;
			if( pp->member[i]->type.compare( "CORE" ) != 0 )
				pp->member[i]->type = "BORDER";
		}

		for( int i = 0; i < pp->member.size(); ++i )
			if( pp->member[i]->member.size() < m_memCnt )	// member�� CORE�� �ƴϸ�
				Clustering( pp->member[i] );
	}
	else	// member���� ä���� ���� == CORE �ƴ�
	{
		if( pp->sector >= m_sectorStartNum )	// �Ҽ� ����
			pp->type = "BORDER";
		else
			pp->type = "NOISE";
	}
}

void CGrouping::Run()
{
	for( int i = 0; i < m_vp->size(); ++i )
		Clustering( (*m_vp)[i] );
}