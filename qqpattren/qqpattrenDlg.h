// qqpattrenDlg.h : ͷ�ļ�
//

#pragma once
#include "DLbutton.h"
#include "DLstatic.h"
#include "DLedit.h"
#include "DLlist.h"
// CqqpattrenDlg �Ի���
class CqqpattrenDlg : public CDialog
{
// ����
public:
	CqqpattrenDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQPATTREN_DIALOG };
	
	//����ϵͳ��ť
	DLbutton m_closeBT;
	DLbutton m_maxBT;
	DLbutton m_mixBT;
	DLbutton test;
	DLbutton m_uStateBT;
	DLbutton m_sysMenuBT;

	DLstatic m_username;
	DLedit m_signature;
	DLbutton m_headPic;

	CBitmap m_bkbmp;//����ͼƬ
	CDC m_bkdc;//����DC
	DLlist m_userlist;

	CImageList m_imglist;
	CBitmap m_listbmp;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	
// ʵ��
protected:
	HICON m_hIcon;
	
	HRGN m_rgn;//�������� 
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// ��ʼ������
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
