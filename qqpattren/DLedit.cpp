// DLedit.cpp : ʵ���ļ�
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



// DLedit ��Ϣ�������




//BOOL DLedit::OnEraseBkgnd(CDC* pDC)
//{
//	
//	 //TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
//������ͼ
//    pDC->StretchBlt(0,0,rect.Width() ,rect.Height(),&memDC,0,0,m_Bmp.bmWidth,m_Bmp.bmHeight,SRCCOPY);
//    memDC.DeleteDC();
//	return TRUE;
//	//return CEdit::OnEraseBkgnd(pDC);
//}



HBRUSH DLedit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	//pDC->SetBkMode(TRANSPARENT); 
	//pDC->SetTextColor(RGB(0,255,0));
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
   	//return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	return NULL;
}

void DLedit::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CEdit::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	//Invalidate();
	//::TRACE0("enchange ");
	//Invalidate();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
//	// ���͸�֪ͨ��������д CEdit::OnInitDialog()
//	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
//	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�
//	//UpdateCtrl();
//	Invalidate();
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	this->GetSel(m_selB,m_selE);
//	//RedrawWindow(NULL, NULL,RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);
//		//Default();
//
//}

void DLedit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	m_needRedraw=TRUE;
	// TODO: �ڴ˴������Ϣ����������
}


void DLedit::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if(m_isDown)
	//	//RedrawWindow(NULL, NULL,RDW_INVALIDATE | RDW_ERASE );
	CEdit::OnMouseMove(nFlags, point);
}

//UINT DLedit::OnGetDlgCode()
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
//	// TODO: �ڴ˴������Ϣ����������
//	//if(m_needRedraw)
//		//RedrawWindow(NULL, NULL,RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);
//	CWindowDC dc(this);
//	drawBk(&dc);
//	SetWindowText(L"asdf");
//	CEdit::OnNcPaint();
//}


//void DLedit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	
//	CEdit::OnChar(nChar, nRepCnt, nFlags);
//}

//void DLedit::OnNcPaint()
//{
//	// TODO: �ڴ˴������Ϣ����������
//	// ��Ϊ��ͼ��Ϣ���� CEdit::OnNcPaint()
//}

//void DLedit::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//}
