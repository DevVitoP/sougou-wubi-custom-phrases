//Written by Vito(DevVitoP、朮朮、小斌、小斌鹏)

#include "statement.h"

//Ciallo～(<·ω< )⌒☆.
//API使用请参考statement.h,实现于defination.c



//#目录文件建立示例 example1
#if 1
int main()
{
	//create ./main_work_path
	if (generate_object_directory(L".",NULL,L"/test_main_work_path") == 1)return DIR_ERROR;
	// D:/main_work_path/sub_work_path
	if (generate_object_directory(L".",L"/test_main_work_path",L"/test_sub_work_path") == 1)return DIR_ERROR;
	// D:/main_work_path/sub_work_path/file.txt
	FILE *fp = generate_object_file(L".",L"/test_main_work_path",L"/test_sub_work_path",L"/test_file.txt");
	if (fp == NULL)return FILE_ERROR;

	fwprintf(fp,L"test");

	fclose(fp);
	system("pause");
	return 0;
}
#endif

//#树读入、中序输出示例 example2
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
	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			read_bitree_a(&bi,a,b,c);
			//if (wcslen(c) > 1)read_bitree_a(&bi,a,b,c);//词
			//if (_wtoi(b) == 1)read_bitree_a(&bi,a,b,c);//首选
		}
	}

	in_order_output_balance_bitree_LR(&bi,filep_out);

	system("pause");
	return 0;
}
#endif


//#查找 删除示例 example3
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
	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			read_bitree_a(&bi,a,b,c);
		}
	}

	wchar_t buf_a[ENOUGH_SPACES]={L'\0'};
	wchar_t buf_b[ENOUGH_SPACES]={L'\0'};
	wchar_t buf_c[ENOUGH_SPACES]={L'\0'};

	//查找"测试"
	wcscpy( buf_c,L"测试");
	if (search_bitree_ab(&bi,buf_a,buf_b,buf_c) == 1){
		wprintf(L"found:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
	}else{
		wprintf(L"not found:%ls\n",buf_c);
	}

	//查找"wqvb,1"
	wcscpy(buf_a,L"wqvb");
	wcscpy(buf_b,L"1");
	if (search_bitree_c(&bi,buf_a,buf_b,buf_c) == 1){
		wprintf(L"found:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
	}else{
		wprintf(L"not found:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
	}

	//删除"测试"
	wcscpy( buf_c,L"测试");
	if (search_bitree_ab(&bi,buf_a,buf_b,buf_c) == 1){
		wprintf(L"found:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
		if (bitree_delete_node(&bi,buf_a,buf_b,buf_c) == 1){
			if (search_bitree_ab(&bi,buf_a,buf_b,buf_c) == 0){
				wprintf(L"successfully delete:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
			}else{
				wprintf(L"fail to delete:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
			}
		}else{
			wprintf(L"fail to delete:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
		}
	}else{
		wprintf(L"not found:%ls,%ls=%ls\n",buf_a,buf_b,buf_c);
	}

	
	pre_order_output_balance_bitree_LR(&bi,filep_out);
	free_bitree(&bi);

	fclose(filep_in);
	fclose(filep_out);

	system("pause");
	return 0;
}
#endif



//文本行倒置示例 example4
#if 0
int main(){

	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	file_reverse(filep_in,filep_out);

	fclose(filep_in);
	fclose(filep_out);
	system("pause");
	return 0;
}
#endif


//码表格式转换示例 example5
#if 0
int main(){

	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	//将短语格式,如"wqvb,1=你好",转为,特定格式,如"你好	wqvb1"
	table_format_convert(filep_in,L"%l[^,],%l[^=]=%l[^\n]\n",L"bca",&line_filter_default,filep_out,L"%ls\t%ls%ls\n");
	
	//将短语格式,如"wqvb,1=你好",转为,特定格式,如"wqvb	你好	1"
	//table_format_convert(filep_in,L"%l[^,],%l[^=]=%l[^\n]\n",L"acb",&line_filter_default,filep_out,L"%ls\t%ls\t%ls\n");

	//将短语格式,如"wqvb,1=你好",转为,特定格式,如"wqvb	你好"
	//table_format_convert(filep_in,L"%l[^,],%*l[^=]=%l[^\n]%l[\n]",L"abc",&line_filter_default,filep_out,L"%ls\t%ls%ls");
	
	//将短语格式,如"wqvb	你好	1",转为,短语格式,如"wqvb,1=你好"
	//table_format_convert(filep_in,L"%l[^\t]\t%l[^\t]\t%l[^\n]\n",L"acb",&line_filter_default,filep_out,L"%ls,%ls=%ls\n");

	//将短语格式,如"wqvb	你好",转为,短语格式,如"wqvb,NULL=你好"
	//table_format_convert(filep_in,L"%l[^\t]\t%l[^\n]%l[^\n]\n",L"acb",&line_filter_default,filep_out,L"%ls,%ls=%ls\n");

	fclose(filep_in);
	fclose(filep_out);
	system("pause");
	return 0;
}
#endif

//example6
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

	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	wchar_t line_buffer[ENOUGH_SPACES];
	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			read_bitree_a(&bi,a,b,c);
		}
	}
	
	sequence_output_bitree_LR(&bi,filep_out);
	free_bitree(&bi);

	fclose(filep_in);
	fclose(filep_out);
	system("pause");
	return 0;
}
#endif

//理论码长测试表生成示例 example7
#if 0
int main(){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	wchar_t line_buffer[ENOUGH_SPACES];
	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			read_bitree_c(&bi,a,b,c);
		}
	}

	in_order_output_test_theory(&bi,filep_out);
	
	free_bitree(&bi);
	
	fclose(filep_in);
	fclose(filep_out);
	system("pause");
	return 0;
}
#endif


//单字全码树提取 example8
#if 0
int main(){
//假如你是五笔的话建议用搜狗内置功能生成单字表(更标准可靠点,但可能有些不合理)

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			wcscpy(b,L"NULL");//清空b保存NULL标志
			if (wcslen(c) == 1)read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	pre_order_output_balance_bitree_LR(&bi,filep_out);

	free_bitree(&bi);

	fclose(filep_in);
	fclose(filep_out);

	system("pause");
	return 0;
}
#endif


//反编码示例 example9
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
	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	if (filep_in == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			read_bitree_c_get_full_codec(&bi,a,b,c);
		}
	}

	wchar_t a1[ENOUGH_SPACES] = {L'\0'};
	wchar_t a2[ENOUGH_SPACES] = {L'\0'};
	wchar_t a3[ENOUGH_SPACES] = {L'\0'};
	wchar_t a4[ENOUGH_SPACES] = {L'\0'};

	wchar_t *temp_words = NULL;

	temp_words = L"雌";
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"words:%ls\n",temp_words);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"雌性";
	wprintf(L"words:%ls\n",temp_words);
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"雌中雌";
	wprintf(L"words:%ls\n",temp_words);
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"雌中雄";
	wprintf(L"words:%ls\n",temp_words);
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"柚子厨真恶心";
	wprintf(L"words:%ls\n",temp_words);
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"野性守恒定律:指针和使用者的总野性保持不变,\
当指针不野时,\
野性将全部转移到使用者身上,总野性保持不变";
	wprintf(L"words:%ls\n",temp_words);

	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"指针我所欲也；\
女朋友亦我所欲也。\
二者不可得兼,\
舍女朋友而取指针者也";
	wprintf(L"words:%ls\n",temp_words);
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	temp_words = L"我好像超喜欢这玩意儿";
	wprintf(L"words:%ls\n",temp_words);
	generate_codec(bi,temp_words,a1,a2,a3,a4);
	wprintf(L"codec : a1:%ls\ta2:%ls\ta3:%ls\ta4:%ls\n\n",a1,a2,a3,a4);

	free_bitree(&bi);
	system("pause");
	return 0;
}

#endif

//反编码实操例子 example10
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
	//均UTF-16LE
	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	FILE *filep_in_conv = _wfopen(L"./input_conv.txt",L"r,ccs=UTF-16LE");

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
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

			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			generate_codec(bi,c,a1,a2,a3,a4);

			if (a4[0] != L'\0'){
				fwprintf(filep_out,L"%ls,%ls=%ls\n",a4,b,c);
			}else if(a3[0] != L'\0'){
				fwprintf(filep_out,L"%ls,%ls=%ls\n",a3,b,c);
			}else if(a2[0] != L'\0'){
				fwprintf(filep_out,L"%ls,%ls=%ls\n",a2,b,c);
			}else if(a1[0] != L'\0'){
				fwprintf(filep_out,L"%ls,%ls=%ls\n",a1,b,c);
			}
		}
	}

	fclose(filep_in);
	fclose(filep_in_conv);
	fclose(filep_out);

	free_bitree(&bi);
	system("pause");
	return 0;
}
#endif


//词库字词编码正确性检测 example11
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
	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	FILE *filep_in_conv = _wfopen(L"./input_conv.txt",L"r,ccs=UTF-16LE");

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;


	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
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

			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			generate_codec(bi,c,a1,a2,a3,a4);
			if (wcslen(a) == 4){
				if (wcscmp(a,a4) != 0){
					fwprintf(filep_out,L"%d行:(%ls)编码(%ls),与(%ls)冲突,请检查.\n",line_number,c,a,a4);
				}
			}else if(wcslen(a) == 3){
				if (wcscmp(a,a3) != 0){
					fwprintf(filep_out,L"%d行:(%ls)编码(%ls),与(%ls)冲突,请检查.\n",line_number,c,a,a3);
				}
			}else if(wcslen(a) == 2){
				if (wcscmp(a,a2) != 0){
					fwprintf(filep_out,L"%d行:(%ls)编码(%ls),与(%ls)冲突,请检查.\n",line_number,c,a,a2);
				}
			}else if(wcslen(a) == 1){
				if (wcscmp(a,a1) != 0){
					fwprintf(filep_out,L"%d行:(%ls)编码(%ls),与(%ls)冲突,请检查.\n",line_number,c,a,a1);
				}
			}
		}
	}

	free_bitree(&bi);

	fclose(filep_in);
	fclose(filep_in_conv);
	fclose(filep_out);

	system("pause");
	return 0;
}
#endif

//example12
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
	FILE *filep_in = _wfopen(L"./input.txt",L"r,ccs=UTF-16LE");
	FILE *filep_in_conv = _wfopen(L"./input_conv.txt",L"r,ccs=UTF-16LE");

	FILE *filep_out = generate_object_file(L".",L"/output.txt",NULL,NULL);
	if (filep_out == NULL)return FILE_ERROR;

	wchar_t line_buffer[ENOUGH_SPACES];
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	struct tree_list *bi = NULL;

	while (read_line(filep_in,line_buffer) != EOF){
		if (line_filter_default(line_buffer) == 1){
			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
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

			swscanf(line_buffer,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c);
			generate_codec(bi,c,a1,a2,a3,a4);
			if (wcslen(a) == 4){
				if (wcscmp(a,a4) == 0){
					fwprintf(filep_out,L"%ls,%ls=%ls\n",a,b,c);
				}
			}else if(wcslen(a) == 3){
				if (wcscmp(a,a3) == 0){
					fwprintf(filep_out,L"%ls,%ls=%ls\n",a,b,c);
				}
			}else if(wcslen(a) == 2){
				if (wcscmp(a,a2) == 0){
					fwprintf(filep_out,L"%ls,%ls=%ls\n",a,b,c);
				}
			}else if(wcslen(a) == 1){
				if (wcscmp(a,a1) == 0){
					fwprintf(filep_out,L"%ls,%ls=%ls\n",a,b,c);
				}
			}
		}
	}

	fclose(filep_in);
	fclose(filep_in_conv);
	fclose(filep_out);

	free_bitree(&bi);
	system("pause");
	return 0;
}
#endif


//Written by Vito(DevVitoP、朮朮、小斌、小斌鹏)
