// qqpattrenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "qqpattren.h"
#include "qqpattrenDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
enum
{
	MY_BORDER=2,
	MY_CORNER=10, //圆角
	
	BT_SYSTEMY=0,  //系统按钮Y点
	BT_CLOSEX=35, //关闭按钮
	BT_MAXX=65,  //最大化
	BT_MINX=95,	//最小化
	BT_HEADPICX=10,
	BT_HEADPICY=30,
	BT_USTATEX=55,
	BT_USTATEY=32,
	S_USERNAMEX=95,
	S_USERNAMEY=34,
	E_SIGNITUREX=90,
	E_SIGNITUREY=50,
	BT_SYSMENUX=10,//相对左下角
	BT_SYSMENUY=50
};

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CqqpattrenDlg 对话框




CqqpattrenDlg::CqqpattrenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CqqpattrenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	InitData();
}

void CqqpattrenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CqqpattrenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
//	ON_WM_NCCALCSIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZING()
//	ON_WM_NCPAINT()
ON_WM_NCHITTEST()
ON_WM_SETCURSOR()
ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CqqpattrenDlg 消息处理程序
// 初始化数据
void CqqpattrenDlg::InitData(void)
{
	m_bkbmp.LoadBitmapW(IDB_BKBMP);
}

BOOL CqqpattrenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//ShowWindow(SW_MINIMIZE);
	
	CRect cR;
	GetClientRect(&cR);

	m_mixBT.setShadeColor(RGB(44,104,225));
	m_mixBT.SetdelColor(RGB(225,23,243));
	m_mixBT.InitBT(IDB_MIN,_T("最小化"),WS_VISIBLE,CRect(CPoint(cR.right-BT_MINX,BT_SYSTEMY),CSize(30,15)),this,IDMB_MIN);
	
	m_maxBT.setShadeColor(RGB(44,104,225));
	m_maxBT.SetdelColor(RGB(225,23,243));
	m_maxBT.InitBT(IDB_MAX,_T("最大化"),WS_VISIBLE,CRect(CPoint(cR.right-BT_MAXX,BT_SYSTEMY),CSize(30,15)),this,IDMB_MAX);
	
	m_closeBT.setShadeColor(RGB(241,8,41));
	m_closeBT.SetdelColor(RGB(225,23,243));
	m_closeBT.InitBT(IDB_CLOSEBT,_T("关闭"),WS_VISIBLE,CRect(CPoint(cR.right-BT_CLOSEX,BT_SYSTEMY),CSize(30,15)),this,IDMB_CLOSE);
	

	m_headPic.m_margin=1;
	m_headPic.m_bkMode=2;
	m_headPic.m_pressOffset=0;
	m_headPic.SettransColor(RGB(255,255,255));
	m_headPic.InitBT(IDB_HEADPIC,_T("头像"),WS_VISIBLE,CRect(CPoint(BT_HEADPICX,BT_HEADPICY),CSize(40,40)),this,IDMB_HEADPIC);

	m_uStateBT.m_margin=4;
	m_uStateBT.m_bkMode=2;
	m_uStateBT.SettransColor(RGB(255,255,255));
	m_uStateBT.SetdelColor(RGB(226,90,238));
	m_uStateBT.SetborderColor(RGB(185,185,185));
	m_uStateBT.m_salpha=150;
	m_uStateBT.InitBT(IDB_STONLINE,_T("在线"),WS_VISIBLE,CRect(CPoint(BT_USTATEX,BT_USTATEY),CSize(40,40)),this,IDMB_USTATE);

	m_sysMenuBT.m_margin=0;
	m_sysMenuBT.m_btMode=2;
	m_sysMenuBT.m_salpha=200;
	m_sysMenuBT.SetdelColor(RGB(226,90,238));
	m_sysMenuBT.m_forceIstrans=TRUE;
	m_sysMenuBT.m_pressOffset=0;
	m_sysMenuBT.InitBT(IDB_SYSMENU1,IDB_SYSMENU2,IDB_SYSMENU2,_T("菜单"),WS_VISIBLE,CRect(CPoint(BT_SYSMENUX,cR.bottom-BT_SYSMENUY),CSize(30,15)),this,IDMB_SYSMENU);
	
	m_username.Create(_T("DoubleLive"),WS_VISIBLE,CRect(CPoint(S_USERNAMEX,S_USERNAMEY),CSize(100,20)),this,IDMS_USERNAME);
	m_signature.Create(WS_VISIBLE,CRect(CPoint(E_SIGNITUREX,E_SIGNITUREY),CSize(100,22)),this,IDME_SIGNITURE);
	
	m_imglist.Create(40,40,ILC_COLORDDB|ILC_MASK,0,2);
	m_listbmp.LoadBitmapW(IDB_UPIC1);
	m_imglist.Add(&m_listbmp,RGB(0,0,0));
	m_listbmp.DeleteObject();
	m_listbmp.LoadBitmapW(IDB_UPIC2);
	m_imglist.Add(&m_listbmp,RGB(0,0,0));

	m_userlist.Create(WS_VISIBLE|LVS_NOCOLUMNHEADER|LVS_SINGLESEL|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED|LVS_REPORT,CRect(2,80,cR.right-2,cR.bottom-100),this,IDML_USERLIST);
	
	m_userlist.SetExtendedStyle(m_userlist.GetExtendedStyle()| LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
	m_userlist.SetImageList(&m_imglist,LVSIL_SMALL);

	m_userlist.InsertColumn(0,_T(""),LVCFMT_LEFT,120,0);
	m_userlist.InsertColumn(1,_T(""),LVCFMT_LEFT,100,0);

	m_userlist.InsertItem(0,_T("01"),0);
	m_userlist.SetItemText(0,0,_T("双生"));
	m_userlist.SetItemText(0,1,_T("1111111111111112222222"));

	m_userlist.InsertItem(1,_T("02"),1);
	m_userlist.SetItemText(1,0,_T("千里花舞"));
	m_userlist.SetItemText(1,1,_T("22222222222222222"));
	m_userlist.SetItemHeigt(56);
	/*test.m_isDrawText=TRUE;
	
	test.InitBT(IDB_MAX,_T("123"),WS_VISIBLE,CRect(50,50,70,70),this,5001);
	test.setShadeColor(RGB(44,104,225));
	test.SetdelColor(RGB(225,23,243));*/

	

	
	// TODO: 在此添加额外的初始化代码
	//mybt=new DLbutton(IDB_CLOSE,_T("asf"),WS_VISIBLE,CRect(10,10,30,30),this,5000);
	////mybt->setShadeColor(RGB(241,8,41));
	//m_closeBT=new DLbutton(IDB_CLOSEBT,_T("关闭"),WS_VISIBLE,CRect(40,40,50,50),this,5001);
	//m_closeBT->setShadeColor(RGB(241,8,41));
	//m_closeBT->SettransColor(RGB(225,23,243));
	//m_closeBT->SetborderColor(RGB(180,180,180));


	//mybt->Create(_T("asf"),WS_CHILD|WS_VISIBLE,CRect(10,10,30,30),this,5000);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CqqpattrenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CqqpattrenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialog::OnPaint();
		
		//m_bkdc.DeleteDC();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CqqpattrenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CqqpattrenDlg::OnSize(UINT nType, int cx, int cy)
{

	CDialog::OnSize(nType, cx, cy);

	RECT rc; 
	GetWindowRect(&rc);
	
	OffsetRect(&rc,-rc.left,-rc.top);
	if(m_rgn)
		DeleteObject(m_rgn);
	m_rgn=CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,MY_CORNER,MY_CORNER); 
	SetWindowRgn(m_rgn,TRUE);
	// TODO: 在此处添加消息处理程序代码
}


void CqqpattrenDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);//移动窗口
	CDialog::OnLButtonDown(nFlags, point);
}



void CqqpattrenDlg::OnDestroy()
{
	CDialog::OnDestroy();

	m_bkbmp.DeleteObject();
	// TODO: 在此处添加消息处理程序代码
}

BOOL CqqpattrenDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CRect crc,wrc;
	//GetWindowRect(&wrc);
	//CDC* pdc=GetWindowDC();
	//pdc->FrameRgn(CRgn::FromHandle(m_rgn),&CBrush(RGB(10,248,32)),1,1);
	//CDC *pdc=GetWindowDC();
	CRect rc;
	GetWindowRect(&rc);
	CBitmap* poldbmp=NULL;
	m_bkdc.CreateCompatibleDC(pDC);
	m_bkdc.FillRect(&rc,&CBrush(RGB(150,150,150)));
	poldbmp=m_bkdc.SelectObject(&m_bkbmp);
	m_bkdc.SetBkMode(1);
	m_bkdc.DrawTextW(_T("TT1.0"),CRect(9,3,60,20),0);
	
	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&m_bkdc,0,0,SRCCOPY);
	m_bkdc.SelectObject(poldbmp);
	m_bkdc.DeleteDC();
	//return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}

//void CqqpattrenDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
//}

void CqqpattrenDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize=CPoint(230,550);
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CqqpattrenDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}

//void CqqpattrenDlg::OnNcPaint()
//{
//	CDialog::OnNcPaint();
//	
//}

LRESULT CqqpattrenDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//无边框拖动
	CRect rect;
	CRect rect1;
	GetWindowRect(&rect);
	rect1 = rect;
	rect1.DeflateRect(10, 10, -10, -10);
	rect1.NormalizeRect();

	if(point.x <= rect.left+3)
		return HTLEFT;
	else if(point.x >= rect.right-3)
		return HTRIGHT;
	else if(point.y <= rect.top+3)
		return HTTOP;
	else if(point.y >= rect.bottom-3)
		return HTBOTTOM;
	else if(point.x <= rect.left+10 && point.y <= rect.top+10)
		return HTTOPLEFT;
	else if(point.x >= rect.right-10 && point.y <= rect.top+10)
		return HTTOPRIGHT;
	else if(point.x <= rect.left+10 && point.y >= rect.bottom-10)
		return HTBOTTOMLEFT;
	else if(point.x >= rect.right-10 && point.y >= rect.bottom-10)
		return HTBOTTOMRIGHT;
	else if(!rect.IsRectEmpty())
	{
		LRESULT uRet = CWnd::OnNcHitTest(point);
		uRet = (uRet == HTCLIENT) ? HTCAPTION : uRet;
		return uRet;
	}
	else
	{
		return CWnd::OnNcHitTest(point);
	}
	return 0;

	//return CDialog::OnNcHitTest(point);
}

BOOL CqqpattrenDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//无边框拖动
	if(nHitTest == HTCAPTION || nHitTest == HTSYSMENU ||
       nHitTest == HTMENU || nHitTest == HTCLIENT)
   {
       SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
   }
   else if(nHitTest == HTTOP || nHitTest == HTBOTTOM)
   {
       SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
   }
   else if(nHitTest == HTLEFT || nHitTest == HTRIGHT)
   {
       SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
   }
   else if(nHitTest == HTTOPLEFT || nHitTest == HTBOTTOMRIGHT)
   {
       SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
   }
   else if(nHitTest == HTTOPRIGHT || nHitTest == HTBOTTOMLEFT)
   {
       SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
   }
   else
   {
       SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
   }
   return TRUE;
	//return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CqqpattrenDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
   if(nHitTest == HTTOP)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTBOTTOM)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTLEFT)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTRIGHT)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTTOPLEFT)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTTOPRIGHT)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTBOTTOMLEFT)
       SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
   else if(nHitTest == HTBOTTOMRIGHT)
       SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
   else if(nHitTest==HTCAPTION)
		 SendMessage(WM_SYSCOMMAND, SC_MOVE | 4, MAKELPARAM(point.x, point.y));
	//CDialog::OnNcLButtonDown(nHitTest, point);
}
