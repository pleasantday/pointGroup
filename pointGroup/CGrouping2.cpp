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
		// point�� member ã�Ƴֱ�
		for( int i = 0; i < m_vp->size(); ++i )
		{
			if( (*m_vp)[i]->sector > -1 )	// sector�� ������ point�� member�� ã�� �ʿ� ����.
				continue;

			for( int j = 0; j < m_vp->size(); ++j )
			{
				if( i == j )	// �ڱ� �ڽ� ���� �ʱ�
					continue;

				if( (*m_vp)[j]->sector > -1 )	// sector�� ������ point�� member�� ���� �ʿ� ����.
					continue;

				if( Distance( (*m_vp)[i], (*m_vp)[j] ) < m_range )
					(*m_vp)[i]->member.push_back( (*m_vp)[j] );
			}
		}

		// ���� ���� ����� ����  point ã��
		Point* maxPt = nullptr;
		int memCnt = 0;
		for( int i = 0; i < m_vp->size(); ++i )
		{
			if( (*m_vp)[i]->sector > -1 )	// sector�� ������ point�� ����
				continue;

			if( (*m_vp)[i]->member.size() > memCnt )
			{
				maxPt = (*m_vp)[i];
				memCnt = maxPt->member.size();
			}
		}

		if( memCnt == 0 )	// ���� ū ������� 0�̸� ����
		{
			// member�� 0�� point�� sector id �ο�
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

		// point�� point�� member�� sector id �ο�
		maxPt->sector = m_sectorCnt;
		maxPt->type = "CORE";
		for( int i = 0; i < maxPt->member.size(); ++i )
		{
			maxPt->member[i]->sector = m_sectorCnt;
			maxPt->member[i]->type = "BORDER";
		}
		++m_sectorCnt;

		// sector id�� �ο����� ���� point���� member vector�� clear
		for( int i = 0; i < m_vp->size(); ++i )
		{
			if( (*m_vp)[i]->sector > -1 )
				continue;

			(*m_vp)[i]->member.clear();
		}
	}
}