//Written by Vito(DevVitoP)

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define CTM_WM_INIT_WINDOW (WM_USER+1)
#define CTM_WM_INIT_CLASS (WM_USER+2) 
#define CTM_WM_DESTROY_WINDOW (WM_USER+3)
#define CTM_WM_SET_VSCROLL (WM_USER+4)
#define CTM_WM_READ_MESSAGE_LINE (WM_USER+5)

//全局使用默认窗口,init_default_message_window中给值
extern HWND defautlt_message_window;

int malloc_and_post(HWND hwnd , wchar_t *str , ...);//窗口行读入显示
#define OUTPUT_MESSAGE(str,...) malloc_and_post((defautlt_message_window) , (str) __VA_OPT__(,) __VA_ARGS__)

LRESULT message_window_proc(HWND msg_hwnd,unsigned int message,UINT_PTR up,LONG_PTR lp);//消息框架

HWND init_default_message_window(void);//一个自定的默认窗口
int quit_default_message_window(HWND window_handle);//自定窗口退出


