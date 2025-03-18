
// pointGroupDlg.h: 헤더 파일
//

#pragma once
#include "CGrouping.h"
#include "CGrouping2.h"

#define RANGE 50.f
#define MEMBERCNT 3
#define POINTSIZE 5.f
#define PENCOUNT 200

// CpointGroupDlg 대화 상자
class CpointGroupDlg : public CDialogEx
{
	// 생성입니다.
public:
	CpointGroupDlg( CWnd* pParent = nullptr );	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POINTGROUP_DIALOG };
#endif

protected:
	virtual void DoDataExchange( CDataExchange* pDX );	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// point 저장 vector, 같은 point를 가진다
	vector<Point*> m_vp;
	vector<Point*> m_vp2;
	CPen m_pen[PENCOUNT];

	vector<Point*>* m_drawVP;	// 그릴때 사용

	CPoint m_mousePt;	// 마우스 좌표 저장용

	bool m_ptInfo;	// point 정보 id/sector num
	bool m_gpInfo;	// 그룹 조건 정보 on/ff

	void DrawPoint( CPaintDC& dc, const Point* pp );	// 점 그리기
	void DrawRange( CPaintDC& dc );			// 그룹 조건 범위 원 그리기
	void DrawGroupingInfo( CPaintDC& dc );	// 그룹 조건 정보 text 그리기

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
};
