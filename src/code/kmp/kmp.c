//Written by Vito(DevVitoP)

//#########EXPOSE####################
#include "kmp.h"
//#########EXPOSE END####################

static int *kmp_next_val_wchar(wchar_t *s,int length);

int kmp_wchar(wchar_t *string,wchar_t *find){
	if (find == NULL)return -1;
	if (string == NULL)return -1;

	int len_string = wcslen(string);
	int len_find = wcslen(find);

	if (len_string <= 0)return -1; 
	if (len_find <= 0)return -1; 

	int *next_val = kmp_next_val_wchar(find,wcslen(find));

	int position = -1;

	int string_pos = 0;
	int find_pos = 0;

	while (string_pos <= len_string - 1){

		if (string[string_pos] == find[find_pos]){
			
			if (find_pos == len_find - 1){
				//zero means array index
				position = 0 + string_pos - find_pos;
				break;
			}

			string_pos ++;
			find_pos ++;

		}else{
			find_pos = next_val[find_pos];

			if (find_pos == -1){
				find_pos = 0;
				string_pos ++;
			}

		}

	}

	free(next_val);
	return position;
}

static int *kmp_next_val_wchar(wchar_t *s,int length){

	if (length <= 0)return NULL;
	if (s == NULL)return NULL;

	int *next_val = (int *)malloc(sizeof (int) *length);
	if (next_val == NULL)return NULL;

	int pos = 0;
	int max_pre = -1;
	next_val[pos] = max_pre;

	pos = 1;
	while (pos <= length - 1){

		if (max_pre == -1){
			max_pre = 0;

			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			pos ++;
		}else if (s[pos - 1] == s[max_pre]){
			max_pre ++;

			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			next_val[pos] = max_pre;
			pos ++;
		}else{
			max_pre = next_val[max_pre];
		}
	
	}

	return next_val;
}

void kmp_next_val_wchar_visiable(wchar_t *s,int length){
	//target: cur next_val(当前字符前,与后缀匹配的最大前缀)
	
	//[前字符(next_val)][字符(cur next_val)]
	//(前字符)与(前字符next_val) -> (cur next_val)
	//字符 -> 优化next_val

	if (length <= 0)return;
	if (s == NULL)return;

	int *next_val = (int *)malloc(sizeof (int) *length);
	if (next_val == NULL)return;

	int pos = 0;//cur
	int max_pre = -1;//前字符next_val
	next_val[pos] = max_pre;

	OUTPUT_MESSAGE(L"wchar\tnext\tnext_val\n",s[pos],max_pre,next_val[pos]);
	OUTPUT_MESSAGE(L"%lc\t%d\t%d\n",s[pos],max_pre,next_val[pos]);

	pos = 1;
	while (pos <= length - 1){

		if (max_pre == -1){
			max_pre = 0;

			//优化
			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			OUTPUT_MESSAGE(L"%lc\t%d\t%d\n",s[pos],max_pre,next_val[pos]);
			pos ++;
		}else if (s[pos - 1] == s[max_pre]){
			max_pre ++;

			//优化
			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			OUTPUT_MESSAGE(L"%lc\t%d\t%d\n",s[pos],max_pre,next_val[pos]);

			next_val[pos] = max_pre;
			pos ++;
		}else{
			max_pre = next_val[max_pre];
		}
	
	}

	free(next_val);
}

//#####################



static int *kmp_next_val_char(char *s,int length);

int kmp_char(char *string,char *find){
	if (find == NULL)return -1;
	if (string == NULL)return -1;

	int len_string = strlen(string);
	int len_find = strlen(find);

	if (len_string <= 0)return -1; 
	if (len_find <= 0)return -1; 

	int *next_val = kmp_next_val_char(find,strlen(find));

	int position = -1;

	int string_pos = 0;
	int find_pos = 0;

	while (string_pos <= len_string - 1){

		if (string[string_pos] == find[find_pos]){
			
			if (find_pos == len_find - 1){
				//zero means array index
				position = 0 + string_pos - find_pos;
				break;
			}

			string_pos ++;
			find_pos ++;

		}else{
			find_pos = next_val[find_pos];

			if (find_pos == -1){
				find_pos = 0;
				string_pos ++;
			}

		}

	}

	free(next_val);
	return position;
}

static int *kmp_next_val_char(char *s,int length){

	if (length <= 0)return NULL;
	if (s == NULL)return NULL;

	int *next_val = (int *)malloc(sizeof (int) *length);
	if (next_val == NULL)return NULL;

	int pos = 0;
	int max_pre = -1;
	next_val[pos] = max_pre;

	pos = 1;
	while (pos <= length - 1){

		if (max_pre == -1){
			max_pre = 0;

			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			pos ++;
		}else if (s[pos - 1] == s[max_pre]){
			max_pre ++;

			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			next_val[pos] = max_pre;
			pos ++;
		}else{
			max_pre = next_val[max_pre];
		}
	
	}

	return next_val;
}

void kmp_next_val_char_visiable(char *s,int length){
	//target: cur next_val(当前字符前,与后缀匹配的最大前缀)
	
	//[前字符(next_val)][字符(cur next_val)]
	//(前字符)与(前字符next_val) -> (cur next_val)
	//字符 -> 优化next_val

	if (length <= 0)return;
	if (s == NULL)return;

	int *next_val = (int *)malloc(sizeof (int) *length);
	if (next_val == NULL)return;

	int pos = 0;//cur
	int max_pre = -1;//前字符next_val
	next_val[pos] = max_pre;

	OUTPUT_MESSAGE(L"char\tnext\tnext_val\n",s[pos],max_pre,next_val[pos]);
	OUTPUT_MESSAGE(L"%c\t%d\t%d\n",s[pos],max_pre,next_val[pos]);

	pos = 1;
	while (pos <= length - 1){

		if (max_pre == -1){
			max_pre = 0;

			//优化
			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			OUTPUT_MESSAGE(L"%c\t%d\t%d\n",s[pos],max_pre,next_val[pos]);
			pos ++;
		}else if (s[pos - 1] == s[max_pre]){
			max_pre ++;

			//优化
			if (s[max_pre] == s[pos]){
				next_val[pos] = next_val[max_pre];
			}else{
				next_val[pos] = max_pre;
			}

			OUTPUT_MESSAGE(L"%c\t%d\t%d\n",s[pos],max_pre,next_val[pos]);

			next_val[pos] = max_pre;
			pos ++;
		}else{
			max_pre = next_val[max_pre];
		}
	
	}

	free(next_val);
}


//Written by Vito(DevVitoP)
