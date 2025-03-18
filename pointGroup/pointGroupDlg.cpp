
// pointGroupDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "pointGroup.h"
#include "pointGroupDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx( IDD_ABOUTBOX )
{
}

void CAboutDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CAboutDlg, CDialogEx )
END_MESSAGE_MAP()


// CpointGroupDlg 대화 상자



CpointGroupDlg::CpointGroupDlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_POINTGROUP_DIALOG, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );

	m_ptInfo = false;
	m_gpInfo = false;
	m_drawVP = &m_vp2;
}

void CpointGroupDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CpointGroupDlg, CDialogEx )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CpointGroupDlg 메시지 처리기

BOOL CpointGroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT( (IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX );
	ASSERT( IDM_ABOUTBOX < 0xF000 );

	CMenu* pSysMenu = GetSystemMenu( FALSE );
	if( pSysMenu != nullptr )
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString( IDS_ABOUTBOX );
		ASSERT( bNameValid );
		if( !strAboutMenu.IsEmpty() )
		{
			pSysMenu->AppendMenu( MF_SEPARATOR );
			pSysMenu->AppendMenu( MF_STRING, IDM_ABOUTBOX, strAboutMenu );
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon( m_hIcon, TRUE );			// 큰 아이콘을 설정합니다.
	SetIcon( m_hIcon, FALSE );		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	srand( time( NULL ) );

	for( int i = 0; i < 200; ++i )
	{
		Point* tmp = new Point;
		tmp->id = i;
		m_vp.push_back( tmp );

		Point* tmp2 = new Point;
		tmp2->id = tmp->id;
		tmp2->x = tmp->x;
		tmp2->y = tmp->y;
		m_vp2.push_back( tmp2 );
	}

	CGrouping gp( m_vp, RANGE, MEMBERCNT );
	gp.Run();
	CGrouping2 gp2( m_vp2, RANGE );
	gp2.Run();

	// pen init
	m_pen[0].CreatePen( PS_SOLID, 3, RGB( 255, 255, 255 ) );
	for( int i = 1; i < PENCOUNT; ++i )
	{
		m_pen[i].CreatePen( PS_SOLID, 3, RGB( rand() % 255, rand() % 255, rand() % 255 ) );
	}

	MoveWindow( 0, 0, 1100, 1100 );

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CpointGroupDlg::OnSysCommand( UINT nID, LPARAM lParam )
{
	if( (nID & 0xFFF0) == IDM_ABOUTBOX )
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand( nID, lParam );
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CpointGroupDlg::OnPaint()
{
	if( IsIconic() )
	{
		CPaintDC dc( this ); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage( WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0 );

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( &rect );
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
		CPaintDC dc1( this );
		DrawRange( dc1 );
		if( m_gpInfo )
			DrawGroupingInfo( dc1 );

		for( int i = 0; i < m_drawVP->size(); ++i )
		{
			DrawPoint( dc1, (*m_drawVP)[i] );
		}

		CDialogEx::OnPaint();
	}
}

void CpointGroupDlg::DrawPoint( CPaintDC& dc, const Point* pp )
{
	CPen* oldPen = nullptr;

	//	CPen pen[3];
	//	pen[0].CreatePen( PS_SOLID, 3, RGB( 255, 0, 0 ) );
	//	pen[1].CreatePen( PS_SOLID, 3, RGB( 0, 255, 0 ) );
	//	pen[2].CreatePen( PS_SOLID, 3, RGB( 0, 0, 255 ) );
	//
	//
	//	// line
	//	if( pp->type.compare("CORE") == 0 )
	//		oldPen = dc.SelectObject( &pen[0] );
	//	else if( pp->type.compare( "BORDER" ) == 0  )
	//		oldPen = dc.SelectObject( &pen[1] );
	//	else if( pp->type.compare( "NOISE" ) == 0 )
	//		oldPen = dc.SelectObject( &pen[2] );

	oldPen = dc.SelectObject( &m_pen[pp->sector] );

	dc.MoveTo( pp->x - POINTSIZE, pp->y );
	dc.LineTo( pp->x + POINTSIZE, pp->y );
	dc.MoveTo( pp->x, pp->y - POINTSIZE );
	dc.LineTo( pp->x, pp->y + POINTSIZE );
	dc.SelectObject( oldPen );

	// text
	dc.SetTextColor( RGB( 0, 0, 0 ) );
	dc.SetBkColor( RGB( 128, 68, 0 ) );
	dc.SetBkMode( TRANSPARENT );   // 텍스트 배경을 투명하게 설정
	CString tmp;
	if( m_ptInfo )
		tmp.Format( L"NO:%d", pp->id );
	else
		tmp.Format( L"G%d", pp->sector );
	dc.TextOut( pp->x + 3, pp->y + 3, tmp );
}

void CpointGroupDlg::DrawRange( CPaintDC& dc )
{
	dc.Ellipse( m_mousePt.x - RANGE, m_mousePt.y - RANGE, m_mousePt.x + RANGE, m_mousePt.y + RANGE );
}

void CpointGroupDlg::DrawGroupingInfo( CPaintDC& dc )
{
	dc.SetTextColor( RGB( 255, 0, 0 ) );
	dc.SetBkColor( RGB( 128, 68, 0 ) );
	dc.SetBkMode( TRANSPARENT );   // 텍스트 배경을 투명하게 설정
	CString tmp;
	tmp.Format( L"RANGE : %.1f", RANGE );
	dc.TextOut( m_mousePt.x + 5, m_mousePt.y + 5 + RANGE, tmp );
	tmp.Format( L"MEMBER : %d", MEMBERCNT );
	dc.TextOut( m_mousePt.x + 5, m_mousePt.y + 20 + RANGE, tmp );
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CpointGroupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CpointGroupDlg::OnMouseMove( UINT nFlags, CPoint point )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mousePt = point;
	Invalidate( TRUE );
	CDialogEx::OnMouseMove( nFlags, point );
}


void CpointGroupDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptInfo = !m_ptInfo;
	Invalidate( TRUE );
	CDialogEx::OnLButtonDown( nFlags, point );
}


void CpointGroupDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_gpInfo = !m_gpInfo;
	Invalidate( TRUE );
	CDialogEx::OnRButtonDown( nFlags, point );
}


BOOL CpointGroupDlg::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( zDelta > 0 )
		m_drawVP = &m_vp;
	else if( zDelta < 0 )
		//m_drawVP = &m_vp2;

		Invalidate( TRUE );
	return CDialogEx::OnMouseWheel( nFlags, zDelta, pt );
}
