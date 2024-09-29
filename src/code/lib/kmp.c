#include <string.h>
#include <stdlib.h>

//具体使用
int kmp(char *string,char *obj);//string里找obj,返回出现位置

//kmp调用
int *kmp_next_val(char *s,int length);

//参考
int *kmp_next(char *s,int length);

//可视化
int kmp_visiable(char *string,char *obj);
int *kmp_next_val_visiable(char *s,int length);

int *kmp_next_val(char *s,int length){
	int *next_val = (int*)malloc(sizeof(int)*length);

	//与子串第1个位置不匹配就主串下一个与子串第1号位置比用-1表示
	next_val[0]=-1;

	int i=0;
	int j=-1;

	//同时将s视为主串、子串,用i,j描述i+1前的子串
	//i+1前的串的前后缀相等的最大长度j+1放入next[i+1]中
	while (i + 1 < length){
		if (j == -1 || s[i] == s[j]){//[初不等]与[相等]

			if (s[j + 1] == s[i + 1]){
				next_val[i + 1] = next_val[j + 1];
			}else{
				next_val[i + 1] = j + 1;
			}

			if (j == -1){
				i++;
				j = 0;
			}else{
				j++;
				i++;
			}
		}else{//[后不等]
			j = next_val[j];
		}
	}

	return next_val;
}


int *kmp_next_val_visiable(char *s,int length){
	int *next_val = (int*)malloc(sizeof(int)*length);
	next_val[0]=-1;
	int i=0;
	int j=-1;

	printf("#############\n");
	printf("char\tval\tnext\n");
	printf("%c\t%d\t%d\n",s[0],next_val[0],next_val[0]);

	while (i + 1 < length){
		if (j == -1 || s[i] == s[j]){

			if (s[j + 1] == s[i + 1]){
				next_val[i + 1] = next_val[j + 1];
			}else{
				next_val[i + 1] = j + 1;
			}

			printf("%c\t%d\t%d\n",s[i + 1],next_val[i + 1],j + 1);

			if (j == -1){
				i++;
				j=0;
			}else{
				j++;
				i++;
			}
		}else{
			j = next_val[j];
		}
	}

	return next_val;
}

int kmp_visiable(char *string,char *obj){

	if (strlen(string) < strlen(obj))return -1;
	if (strlen(obj) < 1)return -1;

	int *obj_next_val = kmp_next_val_visiable(obj,strlen(obj));
	int string_num,obj_num;
	string_num=obj_num=0;

	int position = -1;

	while(string[string_num] != '\0'){
		if (string[string_num] == obj[obj_num]){

			if(obj_num == strlen(obj) - 1){
				position =0 + string_num - obj_num;
				break;
			}else{
				string_num++;
				obj_num++;
			}

		}else{
			obj_num=obj_next_val[obj_num];
			
			if (obj_num == -1){
				obj_num = 0;
				string_num ++;
			}
		}
	}
	
	free(obj_next_val);

	return position;
}

int *kmp_next(char *s,int length){
	int *next = (int*)malloc(sizeof(int)*length);

	//与子串第1个位置不匹配就主串下一个与子串第1号位置比用-1表示
	next[0]=-1;

	int i=0;
	int j=-1;

	//同时将s视为主串、子串,用i,j描述i+1前的子串
	//i+1前的串的前后缀相等的最大长度j+1放入next[i+1]中
	while (i + 1 < length){
		if (j == -1 || s[i] == s[j]){//[初不等]与[相等]
			next[i+1] = j + 1;

			if (j == -1){
				i++;
				j = 0;
			}else{
				j++;
				i++;
			}
		}else{//[后不等]
			j = next[j];
		}
	}

	return next;
}


//在string串中找子串obj
//最大相等前后缀长n，失败时从n+1位置开始比
//初不等(-1)与后不等要讨论完全
int kmp(char *string,char *obj){

	if (strlen(string) < strlen(obj))return -1;
	if (strlen(obj) < 1)return -1;

	int *obj_next_val = kmp_next_val(obj,strlen(obj));//rember to free(next)
	int string_num,obj_num;
	string_num=obj_num=0;

	int position = -1;

	while(string[string_num] != '\0'){
		if (string[string_num] == obj[obj_num]){

			if(obj_num == strlen(obj) - 1){
				position =0 + string_num - obj_num;
				break;
			}else{
				string_num++;
				obj_num++;
			}

		}else{
			obj_num=obj_next_val[obj_num];
			
			if (obj_num == -1){
				obj_num = 0;
				string_num ++;
			}
		}
	}
	
	free(obj_next_val);

	return position;
}
