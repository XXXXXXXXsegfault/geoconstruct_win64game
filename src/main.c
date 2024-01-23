#include "windows.c"
#include "windef.c"
#include "mem.c"
#include "iformat.c"
#include "rect.c"
#include "font.c"

void *xmalloc(unsigned long size)
{
	void *ptr;
	ptr=malloc(size);
	if(ptr==NULL)
	{
		MessageBoxA(NULL,"Cannot allocate memory","Error",0);
		exit(1);
	}
	return ptr;
}
#define WINW 800
#define WINH 500
#define IS_ZERO(x) ((x)>-0.0000001&&(x)<0.0000001)
#define PI 3.141592653589793
unsigned int pbuf[WINW*WINH];
int mode;
void *hwnd;
int count_levels;
int current_level;
#include "pad.c"
#include "levels.c"
#include "mode0.c"
#include "mode1.c"
#include "mode2.c"

void paint_all(void)
{
	rect(pbuf,WINW,WINH,0,0,WINW,WINH,0xffffff);
	if(mode==0)
	{
		mode0_paint();
	}
	else if(mode==1)
	{
		mode1_paint();
	}
	else if(mode==2)
	{
		mode2_paint();
	}
}
void _WndProc(void);
asm "@_WndProc"
asm "push %r9"
asm "push %r8"
asm "push %rdx"
asm "push %rcx"
asm "call @WndProc"
asm "add $32,%rsp"
asm "ret"
long WndProc(void *hwnd,unsigned int Message,unsigned long wParam,unsigned long lParam)
{
	if(Message==WM_DESTROY)
	{
		PostQuitMessage(0);
		return;
	}
	if(Message==WM_PAINT)
	{
		struct paintstruct ps;
		void *dc,*memdc,*bmp;
		dc=BeginPaint(hwnd,&ps);
		memdc=CreateCompatibleDC(dc);
		bmp=CreateCompatibleBitmap(dc,WINW,WINH);
		SelectObject(memdc,bmp);
		paint_all();
		SetBitmapBits(bmp,sizeof(pbuf),pbuf);
		BitBlt(dc,0,0,WINW,WINH,memdc,0,0,SRCCOPY);
		DeleteObject(bmp);
		DeleteDC(dc);
		EndPaint(hwnd,&ps);
	}
	else if(Message==WM_LBUTTONDOWN)
	{
		if(mode==0)
		{
			mode0_click(LOWORD(lParam),HIWORD(lParam));
		}
		else if(mode==1)
		{
			mode1_click(LOWORD(lParam),HIWORD(lParam));
		}
		else if(mode==2)
		{
			mode2_click(LOWORD(lParam),HIWORD(lParam));
		}
	}
	else if(Message==WM_KEYDOWN)
	{
		if(mode==1)
		{
			mode1_key(wParam);
		}
		else if(mode==2)
		{
			mode2_key(wParam);
		}
	}
	return DefWindowProcA(hwnd,Message,wParam,lParam);
}

int main(int argc,char **argv,void *hInstance)
{
	static struct wndclassex wc;
	struct msg msg;
	SetProcessDPIAware();
	levels_init();
	wc.cbSize=sizeof(wc);
	wc.lpfnWndProc=_WndProc;
	wc.lpszClassName="TEST";
	wc.hInstance=hInstance;
	wc.hbrBackground=(void *)8;
	wc.hCursor=LoadCursorA(NULL,IDC_ARROW);
	wc.hIcon=LoadIconA(NULL,IDI_APPLICATION);
	if(!RegisterClassExA(&wc))
	{
		return 0;
	}
	hwnd=CreateWindowExA(WS_EX_WINDOWEDGE|WS_EX_CLIENTEDGE,"TEST","Geoconstruct",WS_VISIBLE|WS_CAPTION|WS_SYSMENU,
	CW_USEDEFAULT,CW_USEDEFAULT,WINW+10,WINH+39,NULL,NULL,hInstance,NULL);
	if(hwnd==NULL)
	{
		return 0;
	}
	while(GetMessageA(&msg,NULL,0,0)>0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	return msg.wparam;
}
