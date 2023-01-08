//------------------------------------------------------------
#ifndef	_GAUGE_H
#define	_GAUGE_H
//------------------------------------------------------------
#include<windows.h>
#define	GM_SETPOS		(WM_USER+2)
int CALLBACK InitGauge(HINSTANCE);
LRESULT CALLBACK GaugeClassProc(HWND,UINT,WPARAM,LPARAM);
void	CALLBACK GaugePaintProc(HDC,RECT*,UINT);
//------------------------------------------------------------
#endif
//------------------------------------------------------------