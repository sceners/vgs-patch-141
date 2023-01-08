//-----------------------------------------------------------------------------
#include"main.h"
#include"gauge.h"
#include"crc32.h"
//-----------------------------------------------------------------------------
HINSTANCE	hInstance;
const char	progname[]="Written by hEX :-)";
const char	VGSClassName[]="PatchVGS";
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hprev,LPSTR lpCmdLine,int wCmdShow) {
hInstance=hInst;
InitCRC32();
InitGauge(hInst);
RegClassVGS();
DialogBoxParam(hInst,(LPSTR)100,0,MainDlgProc,0);
return 0;
}
//-----------------------------------------------------------------------------
void  CALLBACK RegClassVGS(void) {
WNDCLASS	wc;
wc.style=CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
wc.lpfnWndProc=DefDlgProc;
wc.cbClsExtra=0;
wc.cbWndExtra=DLGWINDOWEXTRA;
wc.hInstance=hInstance;
wc.hIcon=LoadIcon(hInstance,(LPSTR)100);
wc.hCursor=LoadCursor(0,(LPSTR)IDC_ARROW);
wc.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
wc.lpszMenuName=0;
wc.lpszClassName=VGSClassName;
RegisterClass(&wc);
}
//-----------------------------------------------------------------------------
const char	FileName[]="Connectix VGS.exe";
const DWORD	crc32File=0xB9FFDFB8,FileSize=843776;
const BYTE	ssec00[]={0xE8,0xAF,0x0D,0x00,0x00,0x90},
		ssec01[]={0x8B,0x2D,0x60,0x31,0x40,0x00,0xC6,0x80,0x4A,0x24,0x03,0x00,0x03,0xC3};
HWND	hMainDlg,hGauge;
HANDLE	hFile;
char	crcFileBuf[4096];
//-----------------------------------------------------------------------------
LRESULT CALLBACK MainDlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam) {
DWORD	cbwrite;
switch (uMsg) {
case	WM_INITDIALOG:
	hMainDlg=hWnd;
	hGauge=GetDlgItem(hWnd,1000);
	break;
case	WM_COMMAND:
	switch ((WORD)wParam) {
	case	1:
		hFile=CreateFile(FileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,0,
			OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
		if (hFile!=INVALID_HANDLE_VALUE) {
		   if (FileSize==GetFileSize(hFile,0)) {
		      if (crc32File==VerifyCRC()) {
			 SetFilePointer(hFile,0x1C4C,0,FILE_BEGIN);
			 WriteFile(hFile,ssec00,sizeof(ssec00),&cbwrite,0);
			 SetFilePointer(hFile,0x2A00,0,FILE_BEGIN);
			 WriteFile(hFile,ssec01,sizeof(ssec01),&cbwrite,0);
			 MessageBox(hWnd,"Done.",progname,MB_ICONASTERISK);
		      } else MessageBox(hWnd,"Inccorect file Crc32!",progname,MB_ICONHAND);
		   } else MessageBox(hWnd,"Inccorect file size!",progname,MB_ICONHAND);
		   CloseHandle(hFile);
		} else MessageBox(hWnd,"I could\'t find file!",progname,MB_ICONHAND);
		break;
	case	2:
		EndDialog(hWnd,0);
		break;
	}
	break;
case	WM_CLOSE:
	EndDialog(hWnd,0);
	break;
}
return 0;
}
//-----------------------------------------------------------------------------
DWORD CALLBACK VerifyCRC(void) {
DWORD	dw,readed,allreaded;
WORD	last,current;
dw=(DWORD)-1;
last=0;
for (allreaded=0;;) {
    ReadFile(hFile,crcFileBuf,sizeof(crcFileBuf),&readed,0);
    allreaded+=readed;
    current=100*allreaded/FileSize;
    if (last!=current) {
       SendMessage(hGauge,GM_SETPOS,current,0);
       UpdateWindow(hMainDlg);
    last=current;
    }
    if (!readed) break;
    dw=CRC32(dw,crcFileBuf,readed);
}
    SendMessage(hGauge,GM_SETPOS,100,0);
return ~dw;
}
