//-----------------------------------------------------------------------------
#ifndef	_MAIN_H
#define	_MAIN_H
//-----------------------------------------------------------------------------
#include<windows.h>
//-----------------------------------------------------------------------------
LRESULT CALLBACK MainDlgProc(HWND,UINT,WPARAM,LPARAM);
void  CALLBACK RegClassVGS(void);
DWORD CALLBACK VerifyCRC(void);
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------