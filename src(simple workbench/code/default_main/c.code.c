//Written by Vito
//the others header in build directory

int main(){

	HWND window_handle = init_default_message_window();
	if (window_handle == NULL)return 1;

	HANDLE cur_thread = GetCurrentThread();
	HANDLE default_main_thread = init_default_main_thread();
	if (cur_thread == NULL || default_main_thread == NULL)return 1;

	MSG msg;
	while (true){
		if (GetMessageW(&msg,window_handle,0,0) <= 0)break;

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
		Sleep(1000/60);
	}

	quit_default_message_window(window_handle);
	CloseHandle(default_main_thread);
	ExitProcess(0);
	return 0;
}
