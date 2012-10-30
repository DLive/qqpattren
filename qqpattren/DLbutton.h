#pragma once


// DLbutton

class DLbutton : public CButton
{
	DECLARE_DYNAMIC(DLbutton)

public:
	DLbutton();
	virtual ~DLbutton();
	//�Զ�������
	BOOL m_btDown;//��ť������

	CFont m_TextFont;
	LOGFONT   lf; 
	BOOL m_isDrawText;//�Ƿ���ʾ����

	CBitmap m_forebmp;//ǰ��ͼƬ
	CBitmap m_hotbmp; //�ȵ�ͼ
	CBitmap m_downbmp;//����ͼ
	COLORREF m_transColor;//͸��ɫ
	COLORREF m_delColor; //ͼƬȥ����ɫ
	CSize m_foresz;//ǰ��ͼƬ�ߴ�
	int m_margin;//�߾�
	int m_bmpX;//��ͼλ��X
	int m_bmpY;//ͬ��
	BOOL m_bOver; //����Ƿ��ڰ�ť֮��
	BOOL m_bkIsdraw;//�����Ƿ����
	BOOL m_isSizing;//�Ƿ�ı��˳ߴ�
	CDC memDc; //
	
	CDC m_bkDc;//����DC
	void PaintBk(CDC* pDC);
	CBitmap m_bmpbk;
	CBitmap* m_poldbmpbk;

	CDC m_sDC;//����DC
	BYTE m_salpha;//����ͱ���͸����
	BOOL m_forceIstrans;
	COLORREF m_shadeColorB;//����ɫ��ʼ
	COLORREF m_shadeColorE;//����ɫ����

	COLORREF m_borderColor;

	UINT m_bkMode;//����ģʽ 1.���䱳�� 2.͸������   Ĭ��Ϊ1
	UINT m_btMode; //Ĭ��Ϊ1��2����̬ͼƬģʽ
	int m_pressOffset; //���°�ť��ƫ��  Ĭ��Ϊ1

	void drawShadeBk(CRect rc,CDC* pDc,BYTE alpha);//������ɫ
	void setShadeColor(COLORREF rgbB,COLORREF rgbE=RGB(255,255,255));//���ý���ɫ
	void DrawAlphaRect(CDC   *pDC,CRect&   r,COLORREF   clr,unsigned   char   alpha);//��͸������
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg   LRESULT   OnMouseLeave(   WPARAM   wp, LPARAM   lp   );
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	//����ͼƬȥ��ɫ
	void SetdelColor(COLORREF color);
	//�豸͸��ɫ
	void SettransColor(COLORREF color);
	// ���ñ߿���ɫ
	BOOL SetborderColor(COLORREF color);
	// ��ʼ����ť
	void InitBT(UINT bmpID,LPCTSTR lpCapition,DWORD dwStyle,RECT rect,CWnd* pParentWnd,UINT btID);

	//��̬ͼ��ʼ��
	void InitBT(UINT bmpNormalID,UINT bmpFocuseID,UINT bmpSelectID,LPCTSTR lpCapition,DWORD dwStyle,RECT rect,CWnd* pParentWnd,UINT btID);
};


