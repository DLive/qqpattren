#pragma once


// DLedit

class DLedit : public CEdit
{
	DECLARE_DYNAMIC(DLedit)

public:
	DLedit();

	virtual ~DLedit();
	
	CDC m_bkDc; //����DC
	CBitmap m_bmpbk;
	BOOL m_isSizing;  //�Ƿ�ı��С
	CBitmap m_Bitmap;
	BOOL m_isDown;
	CString m_text;
	int m_selB;//ѡ���ı���ʼ
	int m_selE;//ѡ���ı�����
	void drawBk(CDC* pDC);
	BOOL m_needRedraw;
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
//	virtual void PreSubclassWindow();
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnEnChange();
	//afx_msg void OnPaint();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnKillFocus(CWnd* pNewWnd);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

};


