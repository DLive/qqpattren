// DLlist.cpp : 实现文件
//

#include "stdafx.h"
#include "qqpattren.h"
#include "DLlist.h"


// DLlist

IMPLEMENT_DYNAMIC(DLlist, CListCtrl)

DLlist::DLlist()
{
	m_textTopMargin=4;
	m_textRightMargin=6;
	m_textLeftMargin=4;
	m_itemHeight=0;
	m_oldHotItem=-1;
	m_font.CreateFontW(-12,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));
	m_imgLeftMargin=5;
}

DLlist::~DLlist()
{
}


BEGIN_MESSAGE_MAP(DLlist, CListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_MEASUREITEM_REFLECT()
	ON_NOTIFY_REFLECT(LVN_HOTTRACK, &DLlist::OnLvnHotTrack)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()



// DLlist 消息处理程序

void DLlist::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_itemHeight>0)
	{
		lpMeasureItemStruct->itemHeight =m_itemHeight;
	}
}
void DLlist::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void DLlist::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	/*CPoint picPt; 
        picPt.x = rcCell.left+(rcCell.Width()-32)/2; 
        picPt.y = rcCell.top+(rcCell.Height()-32)/2; 
        m_imagelist.Draw ( pDC, rItem.iImage, picPt, uFormat );*/
	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SetBkMode(TRANSPARENT);
	CRect itemRc=lpDrawItemStruct->rcItem;
	CRect rc;
	GetClientRect(&rc);

	memDc.CreateCompatibleDC(pDC);	
	bmp.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
	pob=memDc.SelectObject(&bmp);
	memDc.FillSolidRect(rc,RGB(255,255,255));   //填充为白色
	memDc.SetBkMode(TRANSPARENT);

	WCHAR	lpBuffer[256];
	//TCHAR lpBuffer[256];
	memset(lpBuffer,0,256);
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE ;
	lvi.iItem = lpDrawItemStruct->itemID ; 
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));
	
	//判断状态 并绘背景
	if(lpDrawItemStruct->itemID==m_hotItem && !(lpDrawItemStruct->itemState&ODS_SELECTED))
	{
		memDc.FillSolidRect(itemRc,RGB(248,255,169));
		//memDc.FillRect(itemRc,&CBrush(RGB(248,255,169)));
		
	}
	if(lpDrawItemStruct->itemState&ODS_SELECTED)
	{
		memDc.FillSolidRect(itemRc,RGB(173,180,253));
		//memDc.FillRect(itemRc,&CBrush(RGB(173,180,253)));
	}
	//画图标
	IMAGEINFO img;
	GetImageList(LVSIL_SMALL)->GetImageInfo(lvi.iImage,&img);

	CPoint pt;
	pt.x=itemRc.left+m_imgLeftMargin;
	pt.y=itemRc.top+(itemRc.Height()- (img.rcImage.bottom-img.rcImage.top) )/2;
	HRGN roundr=CreateRoundRectRgn(pt.x,pt.y,pt.x+img.rcImage.right,pt.y+img.rcImage.bottom,2,2);
	memDc.SelectClipRgn(CRgn::FromHandle(roundr));
	this->GetImageList(LVSIL_SMALL)->Draw(&memDc,lvi.iImage,pt,ILD_TRANSPARENT);
	memDc.SelectClipRgn(NULL);
	//画文字
	if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{

		LV_COLUMN lvc;
		::ZeroMemory(&lvc, sizeof(lvc));
		lvc.mask = LVIF_TEXT|LVIF_PARAM|LVCF_WIDTH | LVCF_FMT;
		lvc.pszText=lpBuffer;
		lvc.cchTextMax = sizeof(lpBuffer);

		memDc.SelectObject(m_font);
		TEXTMETRIC metric;
		memDc.GetTextMetrics(&metric);
		for(int i=0;this->GetColumn(i,&lvc);i++)
		{
			
			
			if(i==0)
			{	
				lvi.iSubItem=0;
				VERIFY(GetItem(&lvi));
				CRect rc;
				rc.left=img.rcImage.right+m_textLeftMargin+m_imgLeftMargin;
				rc.top=itemRc.top+m_textTopMargin;
				rc.bottom=rc.top+metric.tmHeight;
				rc.right=itemRc.right-m_textRightMargin;
				
				//保存第一列区域
				m_colRc1.left=rc.left;
				m_colRc1.top=m_textTopMargin;
				m_colRc1.bottom=m_colRc1.top+metric.tmHeight;
				m_colRc1.right=itemRc.right-m_textRightMargin;

				memDc.SetTextColor(RGB(0,0,0));
				memDc.DrawText(lpBuffer,_tcslen(lpBuffer),rc,DT_LEFT|DT_NOPREFIX|DT_SINGLELINE|DT_NOCLIP|DT_END_ELLIPSIS);
			}
			if(i==1)
			{
				lvi.iSubItem=1;
				VERIFY(GetItem(&lvi));
				CRect rc;
				rc.left=img.rcImage.right+m_textLeftMargin+m_imgLeftMargin;
				rc.top=itemRc.top+m_textTopMargin+metric.tmHeight+2;
				rc.bottom=rc.top+metric.tmHeight;
				rc.right=itemRc.right-m_textRightMargin;

				m_colRc2.left=rc.left;
				m_colRc2.top=m_textTopMargin+metric.tmHeight+2;
				m_colRc2.bottom=m_colRc2.top+metric.tmHeight;
				m_colRc2.right=rc.right;

				memDc.SetTextColor(RGB(100,100,100));
				
				memDc.DrawText(lpBuffer,_tcslen(lpBuffer),rc,DT_LEFT|DT_NOPREFIX|DT_SINGLELINE|DT_NOCLIP|DT_END_ELLIPSIS);
			}
		}
		memDc.SelectStockObject(SYSTEM_FONT);

	}
	pDC->BitBlt(itemRc.left,itemRc.top,itemRc.Width(),itemRc.Height(),&memDc,itemRc.left,itemRc.top,SRCCOPY);
	memDc.SelectObject(pob);
	memDc.DeleteDC();
	bmp.DeleteObject();
	//this->GetImageList(LVSIL_SMALL)->GetImageInfo(lvi.iImage,&img);
	
	//CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
	// TODO:  添加您的代码以绘制指定项
}

void DLlist::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	//GetToolTips()->Activate(FALSE);
	VERIFY( EnableToolTips(TRUE) );
	CListCtrl::PreSubclassWindow();
}

void DLlist::OnLvnHotTrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}

void DLlist::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int olditem=this->GetSelectionMark();
	CListCtrl::OnLButtonDown(nFlags, point);
	if(olditem!=GetSelectionMark())
		Update(olditem);
}

void DLlist::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LVHITTESTINFO lvinfo;
    lvinfo.pt = point;
    lvinfo.flags = LVHT_ABOVE;
	int hotItem=HitTest(&lvinfo);
	if(hotItem!=m_oldHotItem && hotItem!=-1)
	{
		m_hotItem=hotItem;
		Update(m_oldHotItem);
		Update(hotItem);
		m_oldHotItem=hotItem;
	}
	
	TRACKMOUSEEVENT		csTME;
	csTME.cbSize = sizeof(csTME);
	csTME.dwFlags = TME_LEAVE;
	csTME.hwndTrack = m_hWnd;
	csTME.dwHoverTime=NULL;
	::_TrackMouseEvent(&csTME);

	CListCtrl::OnMouseMove(nFlags, point);
}

void DLlist::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetHotItem(-1);
	Update(m_oldHotItem);
	m_oldHotItem=-1;
	m_hotItem=-1;
	CListCtrl::OnMouseLeave();
}
void DLlist::SetItemHeigt(int nHeight) //高置行高(别忘了在.h里添加void SetRowHeigt(int nHeight) ；)
{
	 m_itemHeight = nHeight;

	 CRect rcWin;
	 GetWindowRect(&rcWin);
	 WINDOWPOS wp;
	 wp.hwnd = m_hWnd;
	 wp.cx = rcWin.Width();
	 wp.cy = rcWin.Height();
	 wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	 SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
INT_PTR DLlist::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: 在此添加专用代码和/或调用基类

	LVHITTESTINFO lvinfo;

	lvinfo.pt	= point;
	int iItem=HitTest(&lvinfo);
	UINT nFlags =   lvinfo.flags;
	int iSubItem=getSubItemHitTest(point,iItem);
	if( iSubItem<0)
		return -1;
	if(m_oldRTip==iItem && m_oldCTip==iSubItem)
		return -1;
	//TRACE1("%d  ",pTI->uId);
	m_oldRTip=iItem;
	m_oldCTip=iSubItem;

	if(nFlags&LVHT_ONITEMLABEL && iSubItem>=0)
	{
		CRect rc;
		GetClientRect(&rc);
		//m_oldRTip=iItem;
		//m_oldCTip=iSubItem;
	
		pTI->hwnd = m_hWnd;
		pTI->uFlags=TTF_IDISHWND|TTF_SUBCLASS;
		//TRACE1("%d  ",iSubItem);
		pTI->uId =(UINT)(iItem*100+iSubItem);  //值不一样，提示内容就会要求改变
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->rect=rc;
		//	TRACE1("%d  ",pTI->uId);
		return pTI->uId;
	}
	return -1;
	
	//return CListCtrl::OnToolHitTest(point, pTI);
}
int DLlist::getSubItemHitTest(CPoint pt,int iItem) const
{
	if(iItem<0)
	return -1;

	CRect iRc;
	this->GetItemRect(iItem,iRc,LVIR_BOUNDS);
	
	CRect rc;
	rc=m_colRc1;
	rc.OffsetRect(iRc.left,iRc.top);
	int subItem=-1;
	if(rc.PtInRect(pt))
		return 0;
	rc=m_colRc2;
	rc.OffsetRect(iRc.left,iRc.top);
	if(rc.PtInRect(pt))
		return 1;

	return -1;
	
}

BOOL DLlist::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ){
	//Handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
	if( (pNMHDR->idFrom == (UINT)m_hWnd) &&
		 ( ((pNMHDR->code == TTN_NEEDTEXTA) && (pTTTA->uFlags & TTF_IDISHWND)) ||
         ((pNMHDR->code == TTN_NEEDTEXTW) && (pTTTW->uFlags & TTF_IDISHWND)) ) ){
      return FALSE;
	}
	
	*pResult = 0;
	
	const MSG* pMessage = GetCurrentMessage();
	ASSERT ( pMessage );
	CPoint pt;
	//::GetCursorPos(&pt);
	pt = pMessage->pt; //Get the point from the message
	ScreenToClient( &pt );
    
	LVHITTESTINFO lvinfo;
	lvinfo.pt	= pt;
	int iItem=HitTest(&lvinfo);
	UINT nFlags =   lvinfo.flags;
	int iSubItem=getSubItemHitTest(pt,iItem);

	//CString tt;
	//GetToolTips()->GetWindowTextW(tt);
	//TRACE1("__%s__",tt);
	if((nFlags & LVHT_ONITEMLABEL) && m_oldRTip==iItem &&m_oldCTip==iSubItem )
	{
		CString text,tt;
		
		/*GetToolTips()->GetText(tt,this);
		TRACE1("_TT_%s_",tt);*/
		text=this->GetItemText(iItem,iSubItem);

		//_tcscpy(pTTTW->lpszText,text);
		  #ifndef _UNICODE
			  if (pNMHDR->code == TTN_NEEDTEXTA)
				  lstrcpyn(pTTTA->szText, text, 80);
			  else
				  _mbstowcsz(pTTTW->szText, text, 80);
		  #else
			  if (pNMHDR->code == TTN_NEEDTEXTA)
				  _wcstombsz(pTTTA->szText, text, 80);
			  else
				  lstrcpyn(pTTTW->szText, text, 80);
		  #endif
			 // TRACE1("__%d__",pNMHDR->idFrom);
		return TRUE;
	}

	return TRUE;  //表示已处理(自己理解的，未验证）
}
