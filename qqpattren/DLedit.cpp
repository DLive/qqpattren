// DLedit.cpp : 实现文件
//

#include "stdafx.h"
#include "qqpattren.h"
#include "DLedit.h"


// DLedit

IMPLEMENT_DYNAMIC(DLedit, CEdit)

DLedit::DLedit()
{

	m_Bitmap.LoadBitmap(IDB_CLOSEBT);
	m_isDown=FALSE;
	m_needRedraw=FALSE;
	m_selB=m_selE=0;
}

DLedit::~DLedit()
{
}


BEGIN_MESSAGE_MAP(DLedit, CEdit)
//	ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR_REFLECT()
ON_CONTROL_REFLECT(EN_CHANGE, &DLedit::OnEnChange)

ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()

ON_WM_KILLFOCUS()

ON_WM_MOUSEMOVE()

//ON_WM_NCPAINT()
//ON_WM_PAINT()
END_MESSAGE_MAP()



// DLedit 消息处理程序




//BOOL DLedit::OnEraseBkgnd(CDC* pDC)
//{
//	
//	 //TODO: 在此添加消息处理程序代码和/或调用默认值
//	CRect clientrect;
//	GetClientRect(clientrect);
//    if(!m_bkDc.GetSafeHdc()/* || m_isSizing*/)  
//    {
//		m_bkDc.DeleteDC();
//		m_bmpbk.DeleteObject();
//		//CClientDC cdc(GetParent());
//		CDC* cdc;
//		cdc=GetParent()->GetDC();
//		CRect windowrect;
//		GetWindowRect(windowrect);
//		GetParent()->ScreenToClient(&windowrect);
//		CBitmap* m_poldbmpbk;
//        m_bkDc.CreateCompatibleDC(cdc);
//        m_bmpbk.CreateCompatibleBitmap(cdc,clientrect.Width(),clientrect.Height());
//        m_poldbmpbk =m_bkDc.SelectObject(&m_bmpbk);
//        m_bkDc.BitBlt(0,0,clientrect.Width(),clientrect.Height(),cdc,windowrect.left,windowrect.top,SRCCOPY);	
//    }
//    pDC->BitBlt(0,0,clientrect.Width(),clientrect.Height(),&m_bkDc,0,0,SRCCOPY);
//
//	CDC memDC;
//    memDC.CreateCompatibleDC(pDC);
//    memDC.SelectObject(&m_Bitmap);
//    BITMAP m_Bmp;
//    m_Bitmap.GetBitmap(&m_Bmp);
//    CRect rect;
//    GetClientRect(&rect);
//拉伸贴图
//    pDC->StretchBlt(0,0,rect.Width() ,rect.Height(),&memDC,0,0,m_Bmp.bmWidth,m_Bmp.bmHeight,SRCCOPY);
//    memDC.DeleteDC();
//	return TRUE;
//	//return CEdit::OnEraseBkgnd(pDC);
//}



HBRUSH DLedit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何属性
	//pDC->SetBkMode(TRANSPARENT); 
	//pDC->SetTextColor(RGB(0,255,0));
	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
   	//return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	return NULL;
}

void DLedit::OnEnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CEdit::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	//Invalidate();
	//::TRACE0("enchange ");
	//Invalidate();
	// TODO:  在此添加控件通知处理程序代码
}

void DLedit::drawBk(CDC* pDC)
{
	CWindowDC  pc(this);
	CRect clientrect;
	GetClientRect(clientrect);
    if(!m_bkDc.GetSafeHdc() || m_isSizing)  
    {
		m_bkDc.DeleteDC();
		m_bmpbk.DeleteObject();
		CClientDC cdc(GetParent());
		CRect windowrect;
		GetWindowRect(windowrect);
		GetParent()->ScreenToClient(&windowrect);
		CBitmap* m_poldbmpbk;
        m_bkDc.CreateCompatibleDC(&cdc);
        m_bmpbk.CreateCompatibleBitmap(&cdc,clientrect.Width(),clientrect.Height());
        m_poldbmpbk =m_bkDc.SelectObject(&m_bmpbk);
        m_bkDc.BitBlt(0,0,clientrect.Width(),clientrect.Height(),&cdc,windowrect.left,windowrect.top,SRCCOPY);	
    }
    pc.BitBlt(0,0,clientrect.Width(),clientrect.Height(),&m_bkDc,0,0,SRCCOPY);
}



//void DLedit::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	//SetWindowText(_T("asfasdfafasf"));
//	// TODO: 在此处添加消息处理程序代码
//	CEdit::OnPaint();
//	//CString text;
//	//GetWindowText(text);
//	//CDC* pDC=GetDC();
//	//pDC->SetBkMode(1);
//	//pDC->SetTextColor(RGB(0,0,0));
//	//pDC->TextOutW(2,2,text);
//	//drawBk(GetDC());
//}

void DLedit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//UpdateCtrl();
	//Invalidate(0);
	//::TRACE0("LUD ");
	//GetWindowText(m_text);
	////Invalidate();
	//m_isDown=TRUE;
	//RedrawWindow(NULL, NULL,RDW_INVALIDATE | RDW_ERASE );
	//SetCapture();
	//Invalidate();
	this->GetSel(m_selB,m_selE);
	if(m_selB!=m_selE)
	{
	//	RedrawWindow(NULL, NULL,RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);
		//Default();
	}
		//Invalidate();
	CEdit::OnLButtonDown(nFlags, point);
}

void DLedit::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//UpdateCtrl();
	//Invalidate(0);
	//::TRACE0("LUP ");
	//if(m_isDown) 
	//	//ReleaseCapture();
	//m_isDown=FALSE;
	
	CEdit::OnLButtonUp(nFlags, point);
}

//void DLedit::OnEnUpdate()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
//	// 发送该通知，除非重写 CEdit::OnInitDialog()
//	// 函数，将 EM_SETEVENTMASK 消息发送到控件，
//	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。
//	//UpdateCtrl();
//	Invalidate();
//	// TODO:  在此添加控件通知处理程序代码
//	this->GetSel(m_selB,m_selE);
//	//RedrawWindow(NULL, NULL,RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);
//		//Default();
//
//}

void DLedit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	m_needRedraw=TRUE;
	// TODO: 在此处添加消息处理程序代码
}


void DLedit::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if(m_isDown)
	//	//RedrawWindow(NULL, NULL,RDW_INVALIDATE | RDW_ERASE );
	CEdit::OnMouseMove(nFlags, point);
}

//UINT DLedit::OnGetDlgCode()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	//RedrawWindow(NULL, NULL,RDW_INVALIDATE | RDW_ERASE );
//	m_needRedraw=FALSE;
//	//RedrawWindow(NULL, NULL,RDW_INVALIDATE | RDW_ERASE );
//	return CEdit::OnGetDlgCode();
//}

//void DLedit::OnNcPaint()
//{
//	//Default();
//	//UpdateWindow();
//	//CWindowDC dc(this);
//	//this->SendMessage(WM_IME_SETCONTEXT,0x00000001,0xC000000F);
//	//CString str;
//	//GetWindowText(str);
//	//this->OnEraseBkgnd(&dc);
//	//SetWindowText(str);
//	// TODO: 在此处添加消息处理程序代码
//	//if(m_needRedraw)
//		//RedrawWindow(NULL, NULL,RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);
//	CWindowDC dc(this);
//	drawBk(&dc);
//	SetWindowText(L"asdf");
//	CEdit::OnNcPaint();
//}


//void DLedit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	
//	CEdit::OnChar(nChar, nRepCnt, nFlags);
//}

//void DLedit::OnNcPaint()
//{
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CEdit::OnNcPaint()
//}

//void DLedit::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//}
