//Written by Vito(DevVitoP)
#include "message_window.h"

int main(void){
	HWND hwnd = init_default_message_window();

	OUTPUT_MESSAGE(L"啧,柚子厨真恶心。啧。");
	OUTPUT_MESSAGE(L"\n");
	OUTPUT_MESSAGE(L"阿库西斯教接受所有形式的爱。");
	OUTPUT_MESSAGE(L"\n");
	OUTPUT_MESSAGE(L"蓝色是\"智慧\"的象征，Miku不算。。。");
	OUTPUT_MESSAGE(L"\n");
	OUTPUT_MESSAGE(L"红钻头，黄手套，有点奇怪，再看一遍，");
	OUTPUT_MESSAGE(L"耶？Teto");
	OUTPUT_MESSAGE(L"\n");
	OUTPUT_MESSAGE(L"deco不更，老匹不更，完了，这些p主不是死了吧，");
	OUTPUT_MESSAGE(L"算了，再等等");
	OUTPUT_MESSAGE(L"\n");

	MSG msg;
	while(true){
		if (GetMessageW(&msg,hwnd,0,0) <= 0)break;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	quit_default_message_window(hwnd);
	ExitProcess(0);
	return 0;
}
