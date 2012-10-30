// DLbutton.cpp : 实现文件
//

#include "stdafx.h"
#include "DLbutton.h"


// DLbutton

IMPLEMENT_DYNAMIC(DLbutton, CButton)

DLbutton::DLbutton()
{
	m_bOver=FALSE;
	m_bkIsdraw=FALSE;
	m_isSizing=FALSE;
	m_btDown=FALSE;
	m_forceIstrans=FALSE;//前景是否透明
	m_margin=0;
	m_shadeColorB=NULL;
	m_shadeColorE=NULL;
	
	m_isDrawText=FALSE;

	m_salpha=150;
	m_transColor=NULL;
	m_borderColor=NULL;
	m_delColor=NULL;

	m_bkMode=1;
	m_btMode=1;

	m_pressOffset=1;
	                                          //定义字体结构
	lf.lfWeight=FW_NORMAL;                                   //字体磅数=10  
	lf.lfCharSet=134;
	lf.lfHeight=-95;
	//lf.lfHeight=-150;
	lf.lfWidth=0;                                     //字体宽度(旋转后的字体高度)=20  
	lf.lfUnderline=FALSE;                       //无下划线
    lf.lfStrikeOut=FALSE;                       //无删除线
    lf.lfItalic=FALSE;                             //非斜体
    lf.lfEscapement=0;                       //字体显示角度=270°  
    //lf.lfCharSet=DEFAULT_CHARSET;       //使用缺省字符集
    wcscpy(lf.lfFaceName,_T("Arial")); 
	lf.lfOutPrecision= OUT_STROKE_PRECIS; 
	lf.lfClipPrecision= CLIP_STROKE_PRECIS; 
	lf.lfQuality = DRAFT_QUALITY; 
	lf.lfPitchAndFamily= VARIABLE_PITCH|FF_MODERN; 
	m_TextFont.CreatePointFontIndirect(&lf);
}

DLbutton::~DLbutton()
{
	m_bmpbk.DeleteObject();
	if(m_bkMode==2)
	{
		m_hotbmp.DeleteObject();
		m_downbmp.DeleteObject();
	}
	m_bkDc.DeleteDC();
	m_sDC.DeleteDC();
}


BEGIN_MESSAGE_MAP(DLbutton, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// DLbutton 消息处理程序

// 初始化按钮
void DLbutton::InitBT(UINT bmpID,LPCTSTR lpCapition,DWORD dwStyle,RECT rect,CWnd* pParentWnd,UINT btID)
{
		//得到图片的尺寸
	m_forebmp.LoadBitmapW(bmpID);
	BITMAP bm;
	m_forebmp.GetBitmap(&bm);
	m_foresz=m_forebmp.GetBitmapDimension();
	m_foresz.SetSize(bm.bmWidth,bm.bmHeight);

	int textLen;
	textLen=m_isDrawText?wcslen(lpCapition):0;//判断并取值字符长度

	rect.right=rect.left+m_foresz.cx+2*m_margin+textLen*12;//计算按钮区域
	rect.bottom=rect.top+m_foresz.cy+2*m_margin;
	this->Create( lpCapition,dwStyle,rect,pParentWnd,btID);
}
void DLbutton::InitBT(UINT bmpNormalID,UINT bmpFocuseID,UINT bmpSelectID,LPCTSTR lpCapition,DWORD dwStyle,RECT rect,CWnd* pParentWnd,UINT btID)
{
	m_forebmp.LoadBitmapW(bmpNormalID);
	m_hotbmp.LoadBitmapW(bmpFocuseID);
	m_downbmp.LoadBitmapW(bmpSelectID);
	BITMAP bm;
	m_forebmp.GetBitmap(&bm);
	m_foresz=m_forebmp.GetBitmapDimension();
	m_foresz.SetSize(bm.bmWidth,bm.bmHeight);

	int textLen;
	textLen=m_isDrawText?wcslen(lpCapition):0;//判断并取值字符长度

	rect.right=rect.left+m_foresz.cx+2*m_margin+textLen*12;//计算按钮区域
	rect.bottom=rect.top+m_foresz.cy+2*m_margin;
	this->Create( lpCapition,dwStyle,rect,pParentWnd,btID);
}
void DLbutton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}
 LRESULT  DLbutton::OnMouseLeave(   WPARAM   wp, LPARAM   lp   )
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bOver=FALSE;
	Invalidate(TRUE);
	//CButton::OnMouseLeave();
	return 0;
}

void DLbutton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if(!m_bOver)
	{
		m_bOver=TRUE;
		Invalidate(TRUE);

		TRACKMOUSEEVENT		csTME;
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE;
		csTME.hwndTrack = m_hWnd;
		::_TrackMouseEvent(&csTME);
	}
	
	//CButton::OnMouseMove(nFlags, point);
}

void DLbutton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
	// TODO:  添加您的代码以绘制指定
	
	CRect btrc;
	btrc=lpDrawItemStruct->rcItem;
	
	CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);
	pdc->SetBkMode(TRANSPARENT);
	
	memDc.CreateCompatibleDC(pdc);
	//memDc.FillSolidRect(&btrc,pdc->GetBkColor());
	//memDc.SetBkColor(pdc->GetBkColor());
	//if(!m_btDown)
	PaintBk(pdc);
	CBitmap* poldbmp=NULL;
	if(m_bOver)
	{
		if(m_btMode==1)
		{
			if(m_bkMode==1 && m_shadeColorB!=NULL)
				this->drawShadeBk(btrc,pdc,m_salpha);  //渐变背景
			else if(m_bkMode==2)
				DrawAlphaRect(pdc,btrc,m_transColor,m_salpha);//透明背景
		}
		else if(m_btMode==2 && !m_btDown)
		{
			poldbmp=memDc.SelectObject(&m_hotbmp);
		}
	}

	
	//判断按钮是否按下 并设置图片坐标
	if(m_btDown)
		m_bmpY=m_bmpX=m_margin+m_pressOffset;
	else
		m_bmpY=m_bmpX=m_margin;

	//画前景图
	if(m_btDown)
	{
		if(m_btMode==2){
			poldbmp=memDc.SelectObject(&m_downbmp);
		}else if(m_btMode==1){
				poldbmp=memDc.SelectObject(&m_forebmp);
		}
	}
	else
	{
		if(m_btMode==2 &&!m_bOver)
			poldbmp=memDc.SelectObject(&m_forebmp);
		else if(m_btMode==1)
			poldbmp=memDc.SelectObject(&m_forebmp);
	}	
	//是否输出文字
	if(m_isDrawText)
	{
		CString bb;
		CFont* poldpen;
		this->GetWindowTextW(bb);
		poldpen=pdc->SelectObject(&m_TextFont);
		CRect tRc=lpDrawItemStruct->rcItem;
		CRect centerRect = tRc;
		memDc.DrawText(bb, -1, tRc, DT_WORDBREAK | DT_LEFT| DT_CALCRECT);
		tRc.OffsetRect(tRc.left+m_margin+m_foresz.cx, (centerRect.Height() - tRc.Height())/2);
		memDc.DrawTextW(bb,&tRc,DT_WORDBREAK | DT_VCENTER|DT_LEFT);
		memDc.SelectObject(poldpen);
	}
	//贴图
	if(m_forceIstrans)
	{
		CDC mem2;
		mem2.CreateCompatibleDC(pdc);
		CBitmap dbmp;
		dbmp.CreateCompatibleBitmap(pdc,btrc.Width(),btrc.Height());
		mem2.SelectObject(&dbmp);
		PaintBk(&mem2);
		if(m_delColor)
			mem2.TransparentBlt(m_bmpX,m_bmpY,m_foresz.cx,m_foresz.cy,&memDc,0,0,m_foresz.cx,m_foresz.cy,m_delColor);
		else
			mem2.BitBlt(m_bmpX,m_bmpY,m_foresz.cx,m_foresz.cy,&memDc,0,0,SRCCOPY);

		BLENDFUNCTION   bf;   
		bf.BlendOp   =   AC_SRC_OVER;   
	    bf.BlendFlags   =   0;   
	    bf.SourceConstantAlpha   =   m_salpha;   
	    bf.AlphaFormat   =   0;
		pdc->AlphaBlend(0,0,btrc.Width(),btrc.Height(),&mem2,0,0,btrc.Width(),btrc.Height(),bf);
		mem2.DeleteDC();
	}
	else
	{
		if(m_delColor)
 			pdc->TransparentBlt(m_bmpX,m_bmpY,m_foresz.cx,m_foresz.cy,&memDc,0,0,m_foresz.cx,m_foresz.cy,m_delColor);
		else
			pdc->BitBlt(m_bmpX,m_bmpY,m_foresz.cx,m_foresz.cy,&memDc,0,0,SRCCOPY);
	}
	memDc.SelectObject(poldbmp);
	memDc.DeleteDC();
	
	DeleteObject(memDc);
}

//画透明背景
void DLbutton::DrawAlphaRect(CDC   *pDC,CRect& r,COLORREF   clr,unsigned char alpha)
  {   
	  CDC   memdc;   
	  memdc.CreateCompatibleDC(pDC);   
	  CBitmap   bmp,*pOldBitmap;   
	  bmp.CreateCompatibleBitmap(pDC,r.Width(),r.Height());
	  
	  HRGN roundr=CreateRoundRectRgn(r.left,r.top,r.right,r.bottom,2,2);
	  pDC->SelectClipRgn(CRgn::FromHandle(roundr));
	  pOldBitmap   =   memdc.SelectObject(&bmp);   
	  memdc.FillSolidRect(0,0,r.Width(),r.Height(),clr);

	  if(m_borderColor!=NULL)
	  {
		  CBrush border;
		  border.CreateSolidBrush(m_borderColor);
		  memdc.FrameRgn(CRgn::FromHandle(roundr),&border,1,1);
	  }

	  BLENDFUNCTION   bf;   
	  bf.BlendOp   =   AC_SRC_OVER;   
	  bf.BlendFlags   =   0;   
	  bf.SourceConstantAlpha   =   alpha;   
	  bf.AlphaFormat   =   0;
	  pDC->AlphaBlend(r.left,r.top,r.Width(),r.Height(),&memdc,0,0,r.Width(),r.Height(),bf);
	  
	  memdc.DeleteDC();
	  bmp.DeleteObject();
  }  



BOOL DLbutton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*if(!m_bkIsdraw)
	{
		m_bkIsdraw=TRUE;
		PaintBk(pDC);
	}*/
	//return CButton::OnEraseBkgnd(pDC);
	return TRUE;
}

void DLbutton::PaintBk(CDC* pDC)
{
	CClientDC cdc(GetParent());
    CRect clientrect;
    CRect windowrect;
    GetClientRect(clientrect);
    GetWindowRect(windowrect);
    GetParent()->ScreenToClient(&windowrect);

    if(!m_bkDc.GetSafeHdc() || m_isSizing)  
    {
		m_bkDc.DeleteDC();
		m_bmpbk.DeleteObject();
        m_bkDc.CreateCompatibleDC(&cdc);
        m_bmpbk.CreateCompatibleBitmap(&cdc,clientrect.Width(),clientrect.Height());
        m_poldbmpbk =m_bkDc.SelectObject(&m_bmpbk);
        m_bkDc.BitBlt(0,0,clientrect.Width(),clientrect.Height(),&cdc,windowrect.left,windowrect.top,SRCCOPY);	
		//m_bkDc.SelectObject(m_poldbmpbk);
    }
    pDC->BitBlt(0,0,clientrect.Width(),clientrect.Height(),&m_bkDc,0,0,SRCCOPY);
} // End of PaintBk
void DLbutton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btDown=TRUE;
	CButton::OnLButtonDown(nFlags, point);
}

void DLbutton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btDown=FALSE;
	CButton::OnLButtonUp(nFlags, point);
}

void DLbutton::setShadeColor(COLORREF rgbB,COLORREF rgbE)
{
	m_shadeColorB=rgbB;
	m_shadeColorE=rgbE;
}
//画渐变色
void DLbutton::drawShadeBk(CRect rc,CDC* pDc,BYTE alpha)
{	
	  BLENDFUNCTION   bf;   
	  bf.BlendOp   =   AC_SRC_OVER;   
	  bf.BlendFlags   =   0;   
	  bf.SourceConstantAlpha   = alpha;   
	  bf.AlphaFormat   =   0;
	
	 if(!m_sDC.GetSafeHdc())
	 {
	 	int nWidth =rc.Width();
		int nHeight =rc.Height();
		CRect rectangle;

		int BR=GetRValue(m_shadeColorB);
		int BG=GetGValue(m_shadeColorB);
		int BB=GetBValue(m_shadeColorB);
		
		int ER=GetRValue(m_shadeColorE);
		int EG=GetGValue(m_shadeColorE);
		int EB=GetBValue(m_shadeColorE);
		
		int Rs=(ER-BR)/nHeight;
		int Gs=(EG-BG)/nHeight;
		int Bs=(EB-BB)/nHeight;
		
		if(Rs==0)
			Rs=ER>BR?1:-1;
		if(Gs==0)
			Gs=EG>BG?1:-1;
		if(Bs==0)
			Bs=EB>BB?1:-1;

		int R,G,B;

	     CBitmap   bmp,*pOldBitmap;   
	     m_sDC.CreateCompatibleDC(pDc);   
	
	     bmp.CreateCompatibleBitmap(pDc,rc.Width(),rc.Height());
	     pOldBitmap=m_sDC.SelectObject(&bmp);


		for(int i = 0;i < nHeight;i++ )
		{
			if(Rs>=0)
				R=(BR+i*Rs)>ER?ER:(BR+i*Rs);
			else
				R=(BR+i*Rs)<ER?ER:(BR+i*Rs);

			if(Gs>=0)
				G=(BG+i*Gs)>EG?EG:(BG+i*Gs);
			else
				G=(BG+i*Gs)<EG?EG:(BG+i*Gs);
			if(Bs>=0)
				B=(BB+i*Bs)>EB?EB:(BB+i*Bs);
			else
				B=(BB+i*Bs)<EB?EB:(BB+i*Bs);

			rectangle.SetRect(0, i,nWidth,i+1);
			m_sDC.FillSolidRect(&rectangle, RGB(R,G,B));
		}
		bmp.DeleteObject();
	  if(m_borderColor!=NULL)
	  {
		  CBrush border;
		  border.CreateSolidBrush(m_borderColor);
		  m_sDC.FrameRect(rc,&border);
	  }

	  
	}
	pDc->AlphaBlend(rc.left,rc.top,rc.Width(),rc.Height(),&m_sDC,0,0,rc.Width(),rc.Height(),bf);  
}

//设置透明色
void DLbutton::SettransColor(COLORREF color)
{
	m_transColor=color;
}

// 设置边框颜色
BOOL DLbutton::SetborderColor(COLORREF color)
{
	m_borderColor=color;
	return 0;
}
void DLbutton::SetdelColor(COLORREF color)
{
	m_delColor=color;
}

