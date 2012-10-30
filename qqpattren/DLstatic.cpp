// DLstatic.cpp : ʵ���ļ�
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



// DLstatic ��Ϣ�������



BOOL DLstatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO:  �ڴ˸��� DC ���κ�����
	/* if( nCtlColor == CTLCOLOR_STATIC )
    {
       pDC->SetBkMode(TRANSPARENT);
       hbr = (HBRUSH)GetStockObject( NULL_BRUSH );
    }*/
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

HBRUSH DLstatic::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT); 
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}
