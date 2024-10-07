//Written by Vito(DevVitoP)


#define ICO 0x0001
#define ENOUGH_SPACES MAX_PATH

#define WINDOW_WIDTH 700
#define WINDOW_HIGHT 700

#define LINE_OF_ONE_PAGE 60
#define LINE_HEIGHT 20

//#########EXPOSE#############

#include "message_window.h"
HWND defautlt_message_window = NULL;
//#######EXPOSE END###########

static struct line_list{
	wchar_t line[ENOUGH_SPACES];
	struct line_list *previos_line;
	struct line_list *latter_line;
}line_list;

static void write_into_line_list(wchar_t *buf,struct line_list **fll,struct line_list **prelp);
static void free_line_list(struct line_list **fll) ;

static struct line_list *sync_cur_vscroll_pos_line(int vscroll_pos,struct line_list *all_message_line);
static void show_last_error(void);


int malloc_and_post(HWND hwnd , wchar_t *str , ...){
	if (str == NULL)return 1;
	if (hwnd == NULL)return 1;

	va_list args;
	va_start(args,str);

	wchar_t *line_temp_buffer = (wchar_t *)malloc(sizeof(wchar_t)*ENOUGH_SPACES);//free in message proc
	if (line_temp_buffer == NULL)return 1;

	vswprintf(line_temp_buffer,ENOUGH_SPACES,str,args);
	PostMessageW(hwnd,CTM_WM_READ_MESSAGE_LINE,(UINT_PTR)line_temp_buffer,0);

	va_end(args);
	return 0;
}

LRESULT message_window_proc(HWND msg_hwnd,unsigned int message,UINT_PTR up,LONG_PTR lp){

	static SCROLLINFO vscroll_info;
	static int vscroll_pos = 0;

	static struct line_list *all_message_line = NULL;//HEAD
	static int all_line_number = 0;
	static struct line_list **cur_line = &all_message_line;//for reading

	static struct line_list *cur_vscroll_pos_line = NULL;//同步vscroll_pos

	switch (message){

		case CTM_WM_READ_MESSAGE_LINE:{//#msg_hwnd:(use) #up:(linep) #lp:(nonuse) #ret:(0)

			//write
			if (*cur_line != NULL){
				write_into_line_list((wchar_t *)up,&((**cur_line).latter_line),cur_line);
				cur_line = &((**cur_line).latter_line);
				all_line_number ++;
			}else{
				write_into_line_list((wchar_t *)up,cur_line,NULL);
				all_line_number ++;
			}
			

			//sync
			if (vscroll_pos <= all_line_number - LINE_OF_ONE_PAGE){
				vscroll_pos ++;
				vscroll_info.nPos = vscroll_pos;
			}else if(vscroll_pos == 0){
				vscroll_pos = 1;
			}

			vscroll_info.nMax ++;
			vscroll_info.nMin = 1;
			SetScrollInfo(msg_hwnd,SB_VERT,&vscroll_info,true);

			//sync cur_vscroll_pos_line
			cur_vscroll_pos_line = sync_cur_vscroll_pos_line(vscroll_pos,all_message_line);

			free((wchar_t *)up);//malloc in other thread

			ShowScrollBar(msg_hwnd,SB_VERT,true);
			InvalidateRect(msg_hwnd,NULL,true);
			message_window_proc(msg_hwnd,WM_PAINT,0,0);
			return 0;
		}

		case CTM_WM_INIT_CLASS:{//#msg_hwnd:(nonuse) #up:(class name) #lp:(nonuse) #ret:(0)

			WNDCLASSW cs;
			memset(&cs,0,sizeof(WNDCLASSW));

			wchar_t *cs_name = (wchar_t*)up;
			cs.lpfnWndProc = message_window_proc;
			cs.hInstance = GetModuleHandleW(NULL);
			cs.hIcon = LoadIconW(GetModuleHandleW(NULL),(wchar_t *)(ICO));
			cs.hbrBackground = 0;
			cs.lpszClassName = cs_name;
			RegisterClassW(&cs);

			return 0;
		}

		case CTM_WM_INIT_WINDOW:{//#msg_hwnd:(nonuse) #up:(class name) #lp:(wnd name) #ret:(hwnd)

			HWND main_hwnd;
				main_hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,(wchar_t *)up,(wchar_t *)lp,WS_OVERLAPPEDWINDOW,\
					CW_USEDEFAULT,CW_USEDEFAULT,WINDOW_WIDTH,WINDOW_HIGHT,\
					NULL,NULL,GetModuleHandleW(NULL),NULL);
			ShowWindow(main_hwnd,SW_NORMAL);
			
			return (LRESULT)main_hwnd;
		}

		case CTM_WM_DESTROY_WINDOW:{// #msg_hwnd:(use) #up:(non) #lp:(non) #ret:(DestroyWindow ret)
			free_line_list(&all_message_line);
			return DestroyWindow(msg_hwnd);
		}

		case CTM_WM_SET_VSCROLL:{// #msg_hwnd:(use) #up:(non) #lp:(non) #ret:0
			vscroll_info.cbSize = sizeof (SCROLLINFO);
			vscroll_info.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
			vscroll_info.nMin = 0;
			vscroll_info.nMax = 0;
			vscroll_info.nPage = 30;
			vscroll_info.nPos = 0;
			vscroll_info.nTrackPos = 0;

			return SetScrollInfo(msg_hwnd,SB_VERT,&vscroll_info,true);
		}

		//###############################

		case WM_PAINT:{// #msg_hwnd:(use) #up:(non) #lp:(non) #ret:0

			struct line_list *ptr_line_node = cur_vscroll_pos_line;
			int y_height = LINE_HEIGHT;
			HFONT hfont_default = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

			PAINTSTRUCT ps;
			HDC double_dc = BeginPaint(msg_hwnd,&ps);
			HDC dc = CreateCompatibleDC(double_dc);
			HBITMAP hbitmap = CreateCompatibleBitmap(double_dc,ps.rcPaint.right,ps.rcPaint.bottom);
			HBRUSH hbr_bg = CreateSolidBrush(RGB(13,17,23));
			int old_bk_mode = SetBkMode(dc,TRANSPARENT);

			SelectObject(dc,hbitmap);
			SelectObject(dc,hfont_default);
			SetTextColor(dc,RGB(0x39,0xc5,0xbb));

			FillRect(dc,&(ps.rcPaint),hbr_bg);
			while(ptr_line_node != NULL && y_height < LINE_HEIGHT * LINE_OF_ONE_PAGE){
				TextOutW(dc,LINE_HEIGHT,y_height,(*ptr_line_node).line,wcslen((*ptr_line_node).line));

				ptr_line_node = (*ptr_line_node).latter_line;
				y_height += LINE_HEIGHT;
			}

			BitBlt(double_dc,0,0,ps.rcPaint.right,ps.rcPaint.bottom,dc,0,0,SRCCOPY);
			EndPaint(msg_hwnd,&ps);

			DeleteObject(hbr_bg);
			DeleteObject(hbitmap);
			DeleteDC(dc);
			SetBkMode(double_dc,old_bk_mode);

			return 0;
		}

		case WM_VSCROLL:{
			switch (LOWORD(up)){
				case SB_LINEUP:{
					vscroll_pos = max(vscroll_pos - 1,vscroll_info.nMin);
					break;
				}

				case SB_LINEDOWN:{
					vscroll_pos = min(vscroll_pos + 1,vscroll_info.nMax);
					break;
				}

				case SB_PAGEUP:{
					vscroll_pos = max(vscroll_pos - 1,vscroll_info.nMin);
					break;
				}

				case SB_PAGEDOWN:{
					vscroll_pos = min(vscroll_pos + 1,vscroll_info.nMax);
					break;
				}

				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:
				{
					vscroll_pos = HIWORD(up);  
					break;
				}
			}//end switch

			vscroll_info.nPos = vscroll_pos;
			SetScrollInfo(msg_hwnd,SB_VERT,&vscroll_info,true);

			cur_vscroll_pos_line = sync_cur_vscroll_pos_line(vscroll_pos,all_message_line);//sync cur_vscroll_pos_line
			InvalidateRect(msg_hwnd,NULL,true);
			return 0;
		}

		case WM_MOUSEWHEEL:{
			if ((short)HIWORD(up) > 0){
				vscroll_pos = max(vscroll_pos - 1,vscroll_info.nMin);
			}else{
				vscroll_pos = min(vscroll_pos + 1,vscroll_info.nMax);
			}

			vscroll_info.nPos = vscroll_pos;
			SetScrollInfo(msg_hwnd,SB_VERT,&vscroll_info,true);

			cur_vscroll_pos_line = sync_cur_vscroll_pos_line(vscroll_pos,all_message_line);//sync cur_vscroll_pos_line
			InvalidateRect(msg_hwnd,NULL,true);
			UpdateWindow(msg_hwnd);
			return 0;
		}

		case WM_CLOSE:{
			PostMessageW(msg_hwnd,WM_QUIT,0,0);
			return 0;
		}

		default:{
			return DefWindowProcW(msg_hwnd,message,up,lp);
		}
	
	}//switch end

	return 1;
}

HWND init_default_message_window(void){
	wchar_t *cs_name = L"cs_name";
	wchar_t *window_name = L"(Vito)Log:";
	HWND window_handle;
	message_window_proc(0,CTM_WM_INIT_CLASS,(UINT_PTR)cs_name,0);
	window_handle = (HWND)message_window_proc(0,CTM_WM_INIT_WINDOW,(UINT_PTR)cs_name,(LONG_PTR)window_name);
	if (window_handle == NULL)return NULL;
	message_window_proc(window_handle,CTM_WM_SET_VSCROLL,0,0);

	defautlt_message_window = window_handle;
	return window_handle;
}


int quit_default_message_window(HWND window_handle){
	return message_window_proc(window_handle,CTM_WM_DESTROY_WINDOW,0,0);
}

//#####################################

static struct line_list *sync_cur_vscroll_pos_line(int vscroll_pos,struct line_list *all_message_line){
	if (all_message_line == NULL)return NULL;
	if (vscroll_pos <= 0)return NULL;

	static int history_of_vscroll_pos = 0;
	static struct line_list *history_return_of_all_message_line = NULL;

	if (vscroll_pos == history_of_vscroll_pos && history_return_of_all_message_line != NULL)
		return history_return_of_all_message_line;

	int i = 1;
	while (i < vscroll_pos && all_message_line != NULL){
		all_message_line = (*all_message_line).latter_line;
		i++;
	}

	history_of_vscroll_pos = vscroll_pos;

	if (i == vscroll_pos){
		history_return_of_all_message_line = all_message_line;
		return all_message_line;
	}
	else{
		history_return_of_all_message_line = NULL;
		return NULL;
	}
}



static void show_last_error(void){
	wchar_t *error_message = NULL;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,\
			NULL,GetLastError(),\
			MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(wchar_t *)&error_message,\
			0,NULL);
	if (error_message[0]!= L'\0')MessageBoxW(NULL,(wchar_t*)error_message,L"error log",MB_OK);

	LocalFree(error_message);
}

static void write_into_line_list(wchar_t *buf,struct line_list **fll,struct line_list **prelp){

	if (fll == NULL)return;
	if (buf == NULL)return;

	if (*fll == NULL){
		*fll = (struct line_list *)malloc(sizeof(struct line_list));
		if (*fll == NULL){
			OUTPUT_MESSAGE(L"malloc error");
			return;
		}

		if (prelp == NULL){
			(**fll).previos_line= NULL;
		}else{
			(**fll).previos_line= (*prelp);
		}

		(**fll).latter_line= NULL;

		wcscpy( (**fll).line ,buf);
	}else{
		write_into_line_list(buf,&((**fll).latter_line),fll);
	}
}

static void free_line_list(struct line_list **fll) {
	if (*fll == NULL){
		return;
	}

	struct line_list *f_temp_llp = *fll;
	struct line_list *head_llp = NULL;

	while ((*f_temp_llp).latter_line != NULL){
		head_llp = f_temp_llp;
		f_temp_llp = (*f_temp_llp).latter_line;
		free(head_llp);
	}

	free(f_temp_llp);
}



//Written by Vito(DevVitoP)
