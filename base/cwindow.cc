#include "cwindow.h"
namespace cui {

CuiWindow::CuiWindow() {

}

CuiWindow::~CuiWindow() {

}

LRESULT CuiWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  //Paint Controls.
}

LRESULT CuiWindow::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  // Paint Backbround.
}

LRESULT CuiWindow::OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {

}

HWND CuiWindow::GetCuiWnd()
{
  return hwnd_;
}

CuiWindow* CuiWindow::GetWindow(int uCode)
{
  CuiWindow* pRet = NULL;
  switch(uCode)
  {
  case CW_FIRSTCHILD:
    break;
  }
  return pRet;
}

BOOL CuiWindow::IsDisabled(BOOL bCheckParent/*=FALSE*/)
{
//   if (bCheckParent) return m_dwState & WndState_Disable;
//   else return m_bDisable;
}

void CuiWindow::EnableWindow(BOOL bEnable, BOOL bUpdate/* = FALSE */) {
}


}