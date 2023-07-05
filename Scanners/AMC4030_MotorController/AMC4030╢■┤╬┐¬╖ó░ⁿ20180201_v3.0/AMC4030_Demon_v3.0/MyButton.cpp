// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()

END_MESSAGE_MAP()



// CMyButton 消息处理程序
/*
void CMyButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::SendMessage(this->GetParent()->m_hWnd,WM_THREADMSG, SBUTTON_DOWN,(LPARAM)this->m_hWnd);  
	CButton::OnLButtonDown(nFlags, point);
}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
::SendMessage(this->GetParent()->m_hWnd,WM_THREADMSG, SBUTTON_UP,(LPARAM)this->m_hWnd); 
	CButton::OnLButtonUp(nFlags, point);
}
*/


BOOL CMyButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	 switch(message)  
    {  
    case WM_LBUTTONDOWN:  
       // ::SendMessage(this->GetParent()->m_hWnd,WM_THREADMSG+1, SBUTTON_DOWN,(LPARAM)this->m_hWnd);  
		::SendMessage(this->GetParent()->m_hWnd,SBUTTON_DOWN,1,(LPARAM)this->m_hWnd);  
        break;  
    case WM_LBUTTONUP:  
      //  ::SendMessage(this->GetParent()->m_hWnd, SBUTTON_UP,(LPARAM)this->m_hWnd);  
		  ::SendMessage(this->GetParent()->m_hWnd, SBUTTON_UP,0,(LPARAM)this->m_hWnd);  
        break;  
    default:  
        break;  
    }  
	return CButton::OnWndMsg(message, wParam, lParam, pResult);
}
