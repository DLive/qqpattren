#pragma once


// DLbutton

class DLbutton : public CButton
{
	DECLARE_DYNAMIC(DLbutton)

public:
	DLbutton();
	virtual ~DLbutton();
	//自定义数据
	BOOL m_btDown;//按钮被按下

	CFont m_TextFont;
	LOGFONT   lf; 
	BOOL m_isDrawText;//是否显示文字

	CBitmap m_forebmp;//前景图片
	CBitmap m_hotbmp; //热点图
	CBitmap m_downbmp;//按下图
	COLORREF m_transColor;//透明色
	COLORREF m_delColor; //图片去除颜色
	CSize m_foresz;//前景图片尺寸
	int m_margin;//边距
	int m_bmpX;//贴图位置X
	int m_bmpY;//同上
	BOOL m_bOver; //鼠标是否在按钮之上
	BOOL m_bkIsdraw;//背景是否填充
	BOOL m_isSizing;//是否改变了尺寸
	CDC memDc; //
	
	CDC m_bkDc;//背景DC
	void PaintBk(CDC* pDC);
	CBitmap m_bmpbk;
	CBitmap* m_poldbmpbk;

	CDC m_sDC;//渐变DC
	BYTE m_salpha;//渐变和背景透明度
	BOOL m_forceIstrans;
	COLORREF m_shadeColorB;//渐变色开始
	COLORREF m_shadeColorE;//渐变色结束

	COLORREF m_borderColor;

	UINT m_bkMode;//背景模式 1.渐变背景 2.透明背景   默认为1
	UINT m_btMode; //默认为1　2　三态图片模式
	int m_pressOffset; //按下按钮的偏移  默认为1

	void drawShadeBk(CRect rc,CDC* pDc,BYTE alpha);//画渐变色
	void setShadeColor(COLORREF rgbB,COLORREF rgbE=RGB(255,255,255));//设置渐变色
	void DrawAlphaRect(CDC   *pDC,CRect&   r,COLORREF   clr,unsigned   char   alpha);//画透明矩形
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

	//设置图片去除色
	void SetdelColor(COLORREF color);
	//设备透明色
	void SettransColor(COLORREF color);
	// 设置边框颜色
	BOOL SetborderColor(COLORREF color);
	// 初始化按钮
	void InitBT(UINT bmpID,LPCTSTR lpCapition,DWORD dwStyle,RECT rect,CWnd* pParentWnd,UINT btID);

	//三态图初始化
	void InitBT(UINT bmpNormalID,UINT bmpFocuseID,UINT bmpSelectID,LPCTSTR lpCapition,DWORD dwStyle,RECT rect,CWnd* pParentWnd,UINT btID);
};


