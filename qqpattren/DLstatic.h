#pragma once


// DLstatic

class DLstatic : public CStatic
{
	DECLARE_DYNAMIC(DLstatic)

public:
	DLstatic();
	virtual ~DLstatic();

	CDC m_bkDc; //����DC
	CBitmap m_bmpbk;
	BOOL m_isSizing;  //�Ƿ�ı��С

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


