//Written by Vito(DevVitoP)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#ifndef OUTPUT_MESSAGE
	#define OUTPUT_MESSAGE(str,...) wprintf(str __VA_OPT__(,) __VA_ARGS__)
#endif

//string中找find,-1:未找到,否则返回string中第一次出现的数组下标
//注：如何string是动态的，请每次将末尾(find长度-1)个单位保留在下一次开头
int kmp_char(char *string,char *find);
int kmp_wchar(wchar_t *string,wchar_t *find);

void kmp_next_val_char_visiable(char *s,int length);//char,next,next_val可视化
void kmp_next_val_wchar_visiable(wchar_t *s,int length);//wchar,next,next_val可视化


