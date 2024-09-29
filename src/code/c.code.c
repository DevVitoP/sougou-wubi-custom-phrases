//author:Vito(DevVitoP、朮朮、小斌、小斌鹏)

#include "statement.h"

#if 1
int main(){
	return default_main();
}
#endif

//Ciallo～(<·ω< )⌒☆.
//API使用请参考statement.h,实现于defination.c

//#目录文件建立示例
#if 0
int main()
{
	// D:/main_work_path
	if (generate_object_directory(L"D:",NULL,L"/main_work_path") == 1)return DIR_ERROR;
	// D:/main_work_path/sub_work_path
	if (generate_object_directory(L"D:",L"/main_work_path",L"/sub_work_path") == 1)return DIR_ERROR;
	// D:/main_work_path/sub_work_path/file.txt
	FILE *fp = generate_object_file(L"D:",L"/main_work_path",L"/sub_work_path",L"/file.txt");
	if (fp == NULL)return FILE_ERROR;

	fclose(fp);
	return 0;
}
#endif

//#树读入、输出示例
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	//注：input.txt应为短语格式
	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_a(&bi,a,b,c);
			//if (wcslen(c) > 1)read_bitree_a(&bi,a,b,c);//词
			//if (_wtoi(b) == 1)read_bitree_a(&bi,a,b,c);//首选
		}
	}

	in_order_output_balance_bitree_LR(&bi,filep_out);

	return 0;
}
#endif


//#查找 删除示例
#if 0
int main()
{

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	//注：input.txt应为短语格式
	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_a(&bi,a,b,c);
		}
	}

	wchar_t buf_a[ENOUGH_SPACES]={L'\0'};
	wchar_t buf_b[ENOUGH_SPACES]={L'\0'};
	wchar_t buf_c[ENOUGH_SPACES]={L'\0'};

	//查找"测试"
	wcscpy( buf_c,L"测试");
	if (search_bitree_ab(&bi,buf_a,buf_b,buf_c) == 1){
		wprintf(L"found:%s,%s=%s\n",buf_a,buf_b,buf_c);
	}else{
		wprintf(L"not found:%s\n",buf_c);
	}

	//查找"wqvb,1"
	wcscpy(buf_a,L"wqvb");
	wcscpy(buf_b,L"1");
	if (search_bitree_c(&bi,buf_a,buf_b,buf_c) == 1){
		wprintf(L"found:%s,%s=%s\n",buf_a,buf_b,buf_c);
	}else{
		wprintf(L"not found:%s,%s=%s\n",buf_a,buf_b,buf_c);
	}

	//删除"测试"
	wcscpy( buf_c,L"测试");
	if (search_bitree_ab(&bi,buf_a,buf_b,buf_c) == 1){
		wprintf(L"found:%s,%s=%s\n",buf_a,buf_b,buf_c);
		if (bitree_delete_node(&bi,buf_a,buf_b,buf_c) == 1){
			if (search_bitree_ab(&bi,buf_a,buf_b,buf_c) == 0){
				wprintf(L"successfully delete:%s,%s=%s\n",buf_a,buf_b,buf_c);
			}else{
				wprintf(L"fail to delete:%s,%s=%s\n",buf_a,buf_b,buf_c);
			}
		}else{
			wprintf(L"fail to delete:%s,%s=%s\n",buf_a,buf_b,buf_c);
		}
	}else{
		wprintf(L"not found:%s,%s=%s\n",buf_a,buf_b,buf_c);
	}

	
	pre_order_output_balance_bitree_LR(&bi,filep_out);
	free_bitree(&bi);

	return 0;
}
#endif



//文本行倒置示例
#if 0
int main(){

	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	file_reverse(filep_in,filep_out);

	return 0;
}
#endif


//码表格式转换示例
#if 0
int main(){

	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	//将短语格式,如"wqvb,1=你好",转为,特定格式,如"你好	wqvb1"
	//table_format_convert(filep_in,L"%[^,],%[^=]=%[^\n]\n",L"acb",&line_filter_default,filep_out,L"%s\t%s%s\n");
	

	//将短语格式,如"wqvb	你好	1",转为,特定格式,如"wqvb,1=你好"
	//table_format_convert(filep_in,L"%[^\t]\t%[^\t]\t%[^\n]\n",L"acb",&line_filter_default,filep_out,L"%s,%s=%s\n");

	//将短语格式,如"wqvb	你好",转为,特定格式,如"wqvb,NULL=你好"
	table_format_convert(filep_in,L"%[^ ] %[^\n]%[^\n]\n",L"acb",&line_filter_default,filep_out,L"%s,%s=%s\n");

	return 0;
}
#endif


//极速短语可由:层序LR输出AVL,如：
//经过实验在短语最值30w条下也能符合预期
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	wchar_t line_buffer[ENOUGH_SPACES];
	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_a(&bi,a,b,c);
		}
	}
	
	sequence_output_bitree_LR(&bi,filep_out);
	free_bitree(&bi);

	return 0;
}
#endif

//理论码长测试表生成示例
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	wchar_t line_buffer[ENOUGH_SPACES];
	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_c(&bi,a,b,c);
		}
	}
	in_order_output_test_theory(&bi,filep_out);
	free_bitree(&bi);
	return 0;
}
#endif


//单字全码树提取
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			wcscpy(b,L"NULL");//清空b保存NULL标志
			read_bitree_c_get_full_codec(&bi,a,b,c);
			read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	pre_order_output_balance_bitree_LR(&bi,filep_out);

	free_bitree(&bi);
	return 0;
}
#endif


//反编码示例
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}
	//input.txt为全码单字表
	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	wchar_t a1[ENOUGH_SPACES] = {L'\0'};
	wchar_t a2[ENOUGH_SPACES] = {L'\0'};
	wchar_t a3[ENOUGH_SPACES] = {L'\0'};
	wchar_t a4[ENOUGH_SPACES] = {L'\0'};

	generate_codec(bi,L"我",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"我的",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"我的指",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"我的指针",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"我的指针啊",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"你怎么又越界了",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"没朋友，没女朋友，就和你这指针过日子",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);
	generate_codec(bi,L"超我好像真喜欢这玩意儿",a1,a2,a3,a4);
	wprintf(L"a1:%s\ta2:%s\ta3:%s\ta4:%s\n",a1,a2,a3,a4);

	free_bitree(&bi);
	return 0;
}

#endif

//反编码实操例子
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}
	//input.txt为全码单字表,input_conv.txt为要生成编码的短语格式的表
	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	FILE *filep_in_conv = _wfopen(L"C:/Users/Administrator/Desktop/input_conv.txt",L"r,ccs=UTF-16LE");

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	wchar_t a1[ENOUGH_SPACES] = {L'\0'};
	wchar_t a2[ENOUGH_SPACES] = {L'\0'};
	wchar_t a3[ENOUGH_SPACES] = {L'\0'};
	wchar_t a4[ENOUGH_SPACES] = {L'\0'};

	while (read_line(filep_in_conv,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
		
			a1[0] = L'\0';
			a2[0] = L'\0';
			a3[0] = L'\0';
			a4[0] = L'\0';

			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			generate_codec(bi,c,a1,a2,a3,a4);

			if (a4[0] != L'\0'){
				fwprintf(filep_out,L"%s,%s=%s\n",a4,b,c);
			}else if(a3[0] != L'\0'){
				fwprintf(filep_out,L"%s,%s=%s\n",a3,b,c);
			}else if(a2[0] != L'\0'){
				fwprintf(filep_out,L"%s,%s=%s\n",a2,b,c);
			}else if(a1[0] != L'\0'){
				fwprintf(filep_out,L"%s,%s=%s\n",a1,b,c);
			}
		}
	}

	free_bitree(&bi);
	return 0;
}
#endif


//词库字词编码正确性检测
#if 0
int main(){
	
	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	//input.txt为全码单字表,input_conv.txt为要生成编码的短语格式的表
	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	FILE *filep_in_conv = _wfopen(L"C:/Users/Administrator/Desktop/input_conv.txt",L"r,ccs=UTF-16LE");

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	wchar_t a1[ENOUGH_SPACES] = {L'\0'};
	wchar_t a2[ENOUGH_SPACES] = {L'\0'};
	wchar_t a3[ENOUGH_SPACES] = {L'\0'};
	wchar_t a4[ENOUGH_SPACES] = {L'\0'};

	int line_number = 0;
	while (read_line(filep_in_conv,line_buffer) != EOF){

		line_number ++;

		if (line_filter_default(line_buffer) == 1){
		
			a1[0] = L'\0';
			a2[0] = L'\0';
			a3[0] = L'\0';
			a4[0] = L'\0';

			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			generate_codec(bi,c,a1,a2,a3,a4);
			if (wcslen(a) == 4){
				if (wcscmp(a,a4) != 0){
					fwprintf(filep_out,L"%d行:(%s)编码(%s),与(%s)冲突,请检查.\n",line_number,c,a,a4);
				}
			}else if(wcslen(a) == 3){
				if (wcscmp(a,a3) != 0){
					fwprintf(filep_out,L"%d行:(%s)编码(%s),与(%s)冲突,请检查.\n",line_number,c,a,a3);
				}
			}else if(wcslen(a) == 2){
				if (wcscmp(a,a2) != 0){
					fwprintf(filep_out,L"%d行:(%s)编码(%s),与(%s)冲突,请检查.\n",line_number,c,a,a2);
				}
			}else if(wcslen(a) == 1){
				if (wcscmp(a,a1) != 0){
					fwprintf(filep_out,L"%d行:(%s)编码(%s),与(%s)冲突,请检查.\n",line_number,c,a,a1);
				}
			}
		}
	}

	free_bitree(&bi);
	return 0;
}
#endif


//只提取词库中的编码正确的字词(或说叫不与单字树冲突的),注：单字如86中的“的、我”之类的特殊单字算不正确的不包含，后面可自行导入
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}
	//input.txt为全码单字表,input_conv.txt为要生成编码的短语格式的表
	FILE *filep_in = _wfopen(L"C:/Users/Administrator/Desktop/input.txt",L"r,ccs=UTF-16LE");
	FILE *filep_in_conv = _wfopen(L"C:/Users/Administrator/Desktop/input_conv.txt",L"r,ccs=UTF-16LE");

	FILE *filep_out = generate_object_file(L"C:/Users/Administrator/Desktop",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	wchar_t a1[ENOUGH_SPACES] = {L'\0'};
	wchar_t a2[ENOUGH_SPACES] = {L'\0'};
	wchar_t a3[ENOUGH_SPACES] = {L'\0'};
	wchar_t a4[ENOUGH_SPACES] = {L'\0'};

	while (read_line(filep_in_conv,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
		
			a1[0] = L'\0';
			a2[0] = L'\0';
			a3[0] = L'\0';
			a4[0] = L'\0';

			swscanf(line_buffer,L"%[^,],%[^=]=%[^\n]\n",a,b,c);
			generate_codec(bi,c,a1,a2,a3,a4);
			if (wcslen(a) == 4){
				if (wcscmp(a,a4) == 0){
					fwprintf(filep_out,L"%s,%s=%s\n",a,b,c);
				}
			}else if(wcslen(a) == 3){
				if (wcscmp(a,a3) == 0){
					fwprintf(filep_out,L"%s,%s=%s\n",a,b,c);
				}
			}else if(wcslen(a) == 2){
				if (wcscmp(a,a2) == 0){
					fwprintf(filep_out,L"%s,%s=%s\n",a,b,c);
				}
			}else if(wcslen(a) == 1){
				if (wcscmp(a,a1) == 0){
					fwprintf(filep_out,L"%s,%s=%s\n",a,b,c);
				}
			}
		}
	}

	free_bitree(&bi);
	return 0;
}
#endif


//author:Vito(DevVitoP、朮朮、小斌、小斌鹏)
