//Written by Vito
#include <windows.h>

#include <shlobj.h>
#include <objbase.h>
#include <commdlg.h>
#include <wchar.h>

//warning:非终端时window_message定义在前
#ifndef OUTPUT_MESSAGE
	#define OUTPUT_MESSAGE(str,...) wprintf((str) __VA_OPT__(,) __VA_ARGS__)
#endif

int choose_which_path_to_output(wchar_t *buffer_path);//目录选择
int choose_which_file_to_input(wchar_t *szFile,wchar_t *init_dir);//文件选择
