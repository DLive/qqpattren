// qqpattrenDlg.h : 头文件
//

#pragma once
#include "DLbutton.h"
#include "DLstatic.h"
#include "DLedit.h"
#include "DLlist.h"
// CqqpattrenDlg 对话框
class CqqpattrenDlg : public CDialog
{
// 构造
public:
	CqqpattrenDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQPATTREN_DIALOG };
	
	//定义系统按钮
	DLbutton m_closeBT;
	DLbutton m_maxBT;
	DLbutton m_mixBT;
	DLbutton test;
	DLbutton m_uStateBT;
	DLbutton m_sysMenuBT;

	DLstatic m_username;
	DLedit m_signature;
	DLbutton m_headPic;

	CBitmap m_bkbmp;//背景图片
	CDC m_bkdc;//背景DC
	DLlist m_userlist;

	CImageList m_imglist;
	CBitmap m_listbmp;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
// 实现
protected:
	HICON m_hIcon;
	
	HRGN m_rgn;//窗口区域 
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 初始化数据
	void InitData(void);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
//	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
