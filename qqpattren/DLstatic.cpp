// DLstatic.cpp : 实现文件
//

#include "stdafx.h"
#include "DLstatic.h"


// DLstatic

IMPLEMENT_DYNAMIC(DLstatic, CStatic)

DLstatic::DLstatic()
{

}

DLstatic::~DLstatic()
{
}

BEGIN_MESSAGE_MAP(DLstatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// DLstatic 消息处理程序



BOOL DLstatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
    pDC->BitBlt(0,0,clientrect.Width(),clientrect.Height(),&m_bkDc,0,0,SRCCOPY);
	return TRUE;
}

HBRUSH DLstatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	/* if( nCtlColor == CTLCOLOR_STATIC )
    {
       pDC->SetBkMode(TRANSPARENT);
       hbr = (HBRUSH)GetStockObject( NULL_BRUSH );
    }*/
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

HBRUSH DLstatic::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  在此更改 DC 的任何属性
	pDC->SetBkMode(TRANSPARENT); 
	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}
