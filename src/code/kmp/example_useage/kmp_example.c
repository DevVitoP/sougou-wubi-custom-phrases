//Written by Vito(DevVitoP)
#include "kmp.h"

#include <locale.h>

int main(){
	
	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				wprintf(L"error setlocale.");
			}
		}
	}
	

	wchar_t *e1 = L"Miku殿下赛高!";
	wchar_t *e2 = L"赛高";

	char *a1 = "ciao hello ciallo!";
	char *a2 = "ciallo";
	char *a3 = "柚子";

	int pos_e = kmp_wchar(e1,e2);
	int pos_a = kmp_char(a1,a2);

	if (pos_e >= 0){
		wprintf(L"在(%ls)中(%d)个字符开始找到(%ls)\n",e1,pos_e + 1,e2);
	}else{
		wprintf(L"未在(%ls)中找到(%ls)\n",e1,e2);
	}

	if (pos_a >= 0){
		wprintf(L"在(%s)中(%d)个字符开始找到(%s),啧,柚子厨真恶心\n",a1,pos_a + 1,a2);
	}else{
		wprintf(L"似乎没有柚子厨\n",a1,a2);
	}

	pos_a = kmp_char(a1,a3);
	if (pos_a >= 0){
		wprintf(L"在(%s)中(%d)个字符开始找到(%s),啧,柚子厨真恶心\n",a1,pos_a + 1,a3);
	}else{
		wprintf(L"似乎没有柚子厨\n",a1,a3);
	}

	wprintf(L"\n\n");
	kmp_next_val_wchar_visiable(e1,wcslen(e2));
	wprintf(L"\n\n");
	kmp_next_val_char_visiable(a1,strlen(a2));

	system("pause");
	return 0;
}


