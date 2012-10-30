#pragma once
// DLlist

class DLlist : public CListCtrl
{
	DECLARE_DYNAMIC(DLlist)

public:
	DLlist();
	virtual ~DLlist();

	int m_itemHeight;    //���
	int m_textTopMargin; //���ֱ߾�
	int m_textRightMargin;
	int m_textLeftMargin;
	int m_imgLeftMargin;
	int m_oldHotItem;  //�ϵ��ȵ���
	int m_hotItem;
	CRect m_colRc1,m_colRc2;
	mutable int m_oldRTip,m_oldCTip;
	int m_oldTip;
	CDC memDc;   //drawitem����
	CBitmap bmp,*pob;
	CFont m_font;
	
	int getSubItemHitTest(CPoint pt,int iItem) const;//�ж��������һ��
	void SetItemHeigt(int nHeight);
protected:
	DECLARE_MESSAGE_MAP()
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnLvnHotTrack(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
//	afx_msg void OnLvnGetInfoTip(NMHDR *pNMHDR, LRESULT *pResult);
};


