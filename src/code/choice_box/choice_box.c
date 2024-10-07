//Written by Vito(DevVitoP、朮朮、小斌、小斌鹏)

#include "choice_box.h"

int choose_which_path_to_output(wchar_t *buffer_path){
	if (buffer_path == NULL){
		OUTPUT_MESSAGE(L"error");
		return 1;
	}

	BROWSEINFOW bsinfo;
	bsinfo.hwndOwner = NULL;
	bsinfo.pidlRoot = NULL;
	bsinfo.pszDisplayName = buffer_path;
	bsinfo.lpszTitle = L"选择输出保存的目录";
	bsinfo.ulFlags = 0;
	bsinfo.lpfn = NULL;
	bsinfo.lParam = 0;
	bsinfo.iImage = 0;


	LPCITEMIDLIST id_list = NULL;
	id_list = SHBrowseForFolderW(&bsinfo);
	if (id_list == NULL)return 1;

	if (SHGetPathFromIDListW(id_list,buffer_path) == FALSE)return 1;
	if (id_list != NULL)CoTaskMemFree((PVOID)id_list);

	return 0;
}


int choose_which_file_to_input(wchar_t *szFile,wchar_t *init_dir){

	if (szFile == NULL)return 1;

	OPENFILENAMEW ofn;       
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = L'\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"所有文件 (*.*)\0*.*\0文本文件 (*.TXT)\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = init_dir;
	ofn.lpstrTitle = L"选择码表文件，确保是短语格式且UTF-16LE";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameW(&ofn) != 0)return 0;
	else return 1;
}
