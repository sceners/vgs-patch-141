//------------------------------------------------------------
#include"gauge.h"
//------------------------------------------------------------
const char GaugeClassName[]="Gauge";
//------------------------------------------------------------
int CALLBACK InitGauge(HINSTANCE hInst) {
WNDCLASS wc;
ZeroMemory(&wc,sizeof(wc));
wc.style=CS_HREDRAW|CS_CLASSDC|CS_VREDRAW;
wc.lpfnWndProc=GaugeClassProc;
wc.cbWndExtra=sizeof(WORD);
wc.hInstance=hInst;
wc.hCursor=LoadCursor(0,IDC_ARROW);
wc.hbrBackground=GetStockObject(WHITE_BRUSH);
wc.lpszClassName=GaugeClassName;
 return RegisterClass(&wc);
}
//------------------------------------------------------------
LRESULT CALLBACK GaugeClassProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam) {
PAINTSTRUCT pt;
RECT	rc;
HBITMAP	hBTM;
HDC	hdc,memDC,oldDC;
UINT	percent;
switch (uMsg) {
case	GM_SETPOS:
	percent=GetWindowWord(hWnd,0);
	if (percent>100) percent=100;
	if (((UINT)wParam)>100) wParam=100;
	if (wParam!=percent) {
	   GetClientRect(hWnd,&rc);
	   SetWindowWord(hWnd,0,(WORD)wParam);
	   InvalidateRect(hWnd,&rc,0);
	   SendMessage(GetParent(hWnd),WM_COMMAND,
		(WPARAM)GetWindowLong(hWnd,GWL_ID),(LPARAM)hWnd);
	}
	return (LRESULT)percent;
case	WM_PAINT:
	hdc=BeginPaint(hWnd,&pt);
	GetClientRect(hWnd,&rc);
	percent=GetWindowWord(hWnd,0);
	if (percent>100) percent=100;
	memDC=CreateCompatibleDC(hdc);
	hBTM=CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
	oldDC=SelectObject(memDC,hBTM);
	FillRect(memDC,&rc,(HBRUSH)GetClassLong(hWnd,GCL_HBRBACKGROUND));
	GaugePaintProc(memDC,&rc,percent);
	FrameRect(memDC,&rc,GetStockObject(BLACK_BRUSH));
	BitBlt(hdc,pt.rcPaint.left,pt.rcPaint.top,pt.rcPaint.right,pt.rcPaint.bottom,
		memDC,pt.rcPaint.left,pt.rcPaint.top,SRCCOPY);
	SelectObject(memDC,oldDC);
	DeleteObject(hBTM);
	DeleteObject(memDC);
	EndPaint(hWnd,&pt);
	break;
}
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
//------------------------------------------------------------
const char PercentFmt[]="%d %%";
//------------------------------------------------------------
void	CALLBACK GaugePaintProc(HDC hdc,RECT *rc,UINT percent) {
char	buf[6];
HBITMAP	hBTM;
HBRUSH	hbr;
HDC	memDC,oldDC;
RECT	rcRB;
UINT	cbStr;
SIZE	ssize;
memDC=CreateCompatibleDC(hdc);
hBTM=CreateCompatibleBitmap(hdc,rc->right,rc->bottom);
oldDC=SelectObject(memDC,hBTM);
FillRect(memDC,rc,GetStockObject(BLACK_BRUSH));
hbr=CreateSolidBrush(0xFF);
rcRB=*rc;
rcRB.right=rcRB.right*percent/100;
FillRect(hdc,&rcRB,hbr);
DeleteObject(hbr);
cbStr=wsprintf(buf,PercentFmt,percent);
GetTextExtentPoint(hdc,buf,cbStr,&ssize);
SetBkMode(memDC,TRANSPARENT);
SetTextColor(memDC,0xFFFFFF^0xFF);
TextOut(memDC,(rc->right-ssize.cx)/2,(rc->bottom-ssize.cy)/2,buf,cbStr);
BitBlt(hdc,rc->left,rc->top,rc->right,rc->bottom,memDC,rc->left,rc->top,SRCINVERT);
SelectObject(memDC,oldDC);
DeleteObject(hBTM);
DeleteObject(memDC);
}
//------------------------------------------------------------
