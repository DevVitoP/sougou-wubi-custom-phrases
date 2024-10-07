//Written by Vito(DevVitoP、朮朮、小斌、小斌鹏)

//others dependence in build file
#include "default_main.h"

static int default_main(void);
static DWORD thread_default_main(void * args);

HANDLE init_default_main_thread(void ){
	return CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)thread_default_main,NULL,0,NULL);
}

static DWORD thread_default_main(void * args){
	return default_main();
}

static int default_main(void){

	if (setlocale(LC_ALL,"zh_CN.utf8") == NULL){
		if (setlocale(LC_ALL,"chs") == NULL){
			if (setlocale(LC_ALL,"Chinese-simplified") == NULL){
				printf("error setlocale.");
			}
		}
	}

	//args
	wchar_t *command_line = GetCommandLineW();
	int argc;
	wchar_t **argv = CommandLineToArgvW(command_line,&argc);


	wchar_t output_directory[MAX_PATH] = L"C:/Users/Administrator/Desktop";

	wchar_t input_file[MAX_PATH] = L"C:/Users/Administrator/AppData/LocalLow/SogouWB.users/00000003/Phrases.ini";

	struct _stat temp_stat_dir;
	struct _stat temp_stat_file;
	memset( &temp_stat_dir,0,sizeof (struct _stat));
	memset( &temp_stat_file,0,sizeof (struct _stat));

	if (argc == 2){
		wcscpy( input_file,argv[1]);
	}else if (argc == 3){
		wcscpy( input_file,argv[1]);
		wcscpy( output_directory,argv[2]);
	}else {

		OUTPUT_MESSAGE(L"Usage:\tPhrases [Output_directory]\n");
		OUTPUT_MESSAGE(L"\t\tPhrases：为UTF-16LE搜狗格式词库\n");
		OUTPUT_MESSAGE(L"\t\tOutput_directory：为输出结果存放目录(默认在桌面)\n\n");

		wchar_t *mb_buffer = (wchar_t *)malloc(sizeof(wchar_t)*MAX_PATH);
		memset( mb_buffer,0,sizeof(wchar_t)*MAX_PATH);

		if (_wstat(input_file,&temp_stat_file) != -1){
			wcscat( mb_buffer,L"检测到搜狗自定义短语:");
			wcscat( mb_buffer,input_file);
			wcscat( mb_buffer,L",是否使用");
			if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) != IDYES){
				OUTPUT_MESSAGE(L"选择输入文件中(UTF-16LE)...\n");
				if (choose_which_file_to_input(input_file,L"C:/Users/Administrator/Desktop") == 1){
					OUTPUT_MESSAGE(L"未选择输入文件，已退出.\n");
					return FILE_ERROR;
				}
			}
		}else if(_wstat(L"C:/Users/Administrator/AppData/LocalLow/SogouWB/Phrases.ini",&temp_stat_file) != -1){
			wcscpy( input_file,L"C:/Users/Administrator/AppData/LocalLow/SogouWB/Phrases.ini");
			wcscat( mb_buffer,L"检测到搜狗自定义短语:");
			wcscat( mb_buffer,input_file);
			wcscat( mb_buffer,L",是否使用");
			if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) != IDYES){
				OUTPUT_MESSAGE(L"选择输入文件中(UTF-16LE)...\n");
				if (choose_which_file_to_input(input_file,L"C:/Users/Administrator/Desktop") == 1){
					OUTPUT_MESSAGE(L"未选择输入文件，已退出.\n");
					return FILE_ERROR;
				}
			}
		}else{
			wcscat( mb_buffer,L"未检测到搜狗自定义短语,是否选择");
			if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) == IDYES){
				OUTPUT_MESSAGE(L"选择输入文件中(UTF-16LE)...\n");
				if (choose_which_file_to_input(input_file,L"C:/Users/Administrator/Desktop") == 1){
					OUTPUT_MESSAGE(L"未选择输入文件，已退出.\n");
					return FILE_ERROR;
				}
			}else return FILE_ERROR;
		}

		wcscpy( mb_buffer,L"当前默认输出路径为:");
		wcscat( mb_buffer,output_directory);
		wcscat( mb_buffer,L",是否更改");

		if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) == IDYES){
			OUTPUT_MESSAGE(L"选择输出目录中...\n");
			if (choose_which_path_to_output(output_directory) == 1){
				OUTPUT_MESSAGE(L"未选择输出目录，已退出.\n");
				return DIR_ERROR;
			}
		}

		free(mb_buffer);

	}


	//dir

	memset( &temp_stat_dir,0,sizeof (struct _stat));
	memset( &temp_stat_file,0,sizeof (struct _stat));
	if (_wstat(input_file,&temp_stat_file) == -1){
		OUTPUT_MESSAGE(L"access phrases error\n");
		return FILE_ERROR;
	}
	if (_wstat(output_directory,&temp_stat_dir) == -1){
		OUTPUT_MESSAGE(L"access directory error\n");
		return DIR_ERROR;
	}


	if(S_ISREG(temp_stat_file.st_mode) && S_ISDIR(temp_stat_dir.st_mode)){
		OUTPUT_MESSAGE(L"Currently working in %ls\n",input_file);
		OUTPUT_MESSAGE(L"Default output_directory: %ls\n",output_directory);
	}else{
		OUTPUT_MESSAGE(L"Error type\n");
		return DIR_ERROR;
	}

	wchar_t *codec_position_sort = L"/按编码位置排序";
	wchar_t *codec_length_sort = L"/按码长分类";
	wchar_t *about_child = L"/按有无候选分类";
	wchar_t *test_theory_dir = L"/测试理论码长用";
	wchar_t *personal_phrases = L"/搜狗五笔极速用户短语";
	wchar_t *practice_text_dir = L"/针对词库的练习文本";

	if (generate_object_directory(NULL,output_directory,L"/词库处理后") == 1)return DIR_ERROR;


	wcscat(output_directory,L"/词库处理后");
	if (generate_object_directory(NULL,output_directory,codec_position_sort) == 1)return DIR_ERROR;
	if (generate_object_directory(NULL,output_directory,codec_length_sort) == 1)return DIR_ERROR;
	if (generate_object_directory(NULL,output_directory,about_child) == 1)return DIR_ERROR;
	if (generate_object_directory(NULL,output_directory,test_theory_dir) == 1)return DIR_ERROR;
	if (generate_object_directory(NULL,output_directory,personal_phrases) == 1)return DIR_ERROR;
	if (generate_object_directory(NULL,output_directory,practice_text_dir) == 1)return DIR_ERROR;


    //FILES
	//
	FILE *f_input = _wfopen(input_file,L"r,ccs=UTF-16LE");
	if (f_input == NULL){
		OUTPUT_MESSAGE(L"Error open");
		return FILE_ERROR;
	}else{
		OUTPUT_MESSAGE(L"open:%ls\n",input_file);
	}

	//about_child
	FILE *f_no_child = generate_object_file(NULL,output_directory,about_child,L"/no_child.txt");
		if (f_no_child == NULL)return FILE_ERROR;
	FILE *f_with_child = generate_object_file(NULL,output_directory,about_child,L"/with_child.txt");
		if (f_with_child == NULL)return FILE_ERROR;

	//codec_position_sort
	FILE *f_merge_list = generate_object_file(NULL,output_directory,codec_position_sort,L"/merge_list.txt");
		if (f_merge_list == NULL)return FILE_ERROR;


	//codec_length_sort
	FILE *f_cl_1 = generate_object_file(NULL,output_directory,codec_length_sort,L"/1.codec_length.txt");
		if (f_cl_1 == NULL)return FILE_ERROR;
	FILE *f_cl_2 = generate_object_file(NULL,output_directory,codec_length_sort,L"/2.codec_length.txt");
		if (f_cl_2 == NULL)return FILE_ERROR;
	FILE *f_cl_3 = generate_object_file(NULL,output_directory,codec_length_sort,L"/3.codec_length.txt");
		if (f_cl_3 == NULL)return FILE_ERROR;
	FILE *f_cl_4 = generate_object_file(NULL,output_directory,codec_length_sort,L"/4.codec_length.txt");
		if (f_cl_4 == NULL)return FILE_ERROR;

	//practice_text_dir
	FILE *f_practice_codec = generate_object_file(NULL,output_directory,practice_text_dir,L"/practice_codec.txt");
		if (f_practice_codec == NULL)return FILE_ERROR;
	FILE *f_practice = generate_object_file(NULL,output_directory,practice_text_dir,L"/practice.txt");
		if (f_practice == NULL)return FILE_ERROR;

	//test_theory_dir
	FILE *f_test_theory = generate_object_file(NULL,output_directory,test_theory_dir,L"/test_theory.txt");
		if (f_test_theory == NULL)return FILE_ERROR;
	FILE *f_length_sort = generate_object_file(NULL,output_directory,test_theory_dir,L"/length_sort.txt");
		if (f_length_sort == NULL)return FILE_ERROR;

	//personal_phrases
	FILE *f_phrases = generate_object_file(NULL,output_directory,personal_phrases,L"/Phrases.txt");
		if (f_phrases == NULL)return FILE_ERROR;
	FILE *f_bbst = generate_object_file(NULL,output_directory,personal_phrases,L"/BBST_Phrases.txt");
		if (f_bbst == NULL)return FILE_ERROR;
	

	FILE *file_analyse_list[] = {f_practice, f_cl_1 , f_cl_2 , f_cl_3 , f_cl_4 , f_practice_codec , f_test_theory};


	//first read in temp
	FILE *temp = generate_object_file(NULL,output_directory,NULL,L"/temp");
		if (temp == NULL)return FILE_ERROR;

	wchar_t the_path_of_temp[MAX_PATH];//for rm temp
	wcscpy(the_path_of_temp,output_directory);
	wcscat(the_path_of_temp,L"/temp");


	//comment
	if (f_practice != NULL && f_phrases != NULL){
		OUTPUT_MESSAGE(L"\n###################################\n");
		OUTPUT_MESSAGE(L"NOTICE1:\n\tpractice.txt为【一级简码第一候选和第二候选】与【二级简码的第一候选】的组合表(排序过)，\n\t目的是为了练习此表去熟悉词库。\n");
		OUTPUT_MESSAGE(L"NOTICE2:\n\t搜狗格式自定义短语(极速出字词)在:\n\t(%ls%ls)目录下。\n",output_directory,personal_phrases);
		OUTPUT_MESSAGE(L"###################################\n");
	}

	OUTPUT_MESSAGE(L"\n#########\n");
	OUTPUT_MESSAGE(L"请等待...\n");
	OUTPUT_MESSAGE(L"wait a minute...\n");
	OUTPUT_MESSAGE(L"#########\n\n");


	struct tree_list *bitree = NULL;
	struct tree_list *bitree_c = NULL;

	//read f_input to temp
	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	wchar_t line[ENOUGH_SPACES*3];
	int line_count;
	wchar_t d;

	long all_line_count = 0;

	while(!feof(f_input) && !ferror(f_input)){
		line_count = 0;
		while ((d = fgetwc(f_input)) != L'\n' && !feof(f_input) && !ferror(f_input)){
			line[line_count]=d;
			line_count ++;
		}

		if (d == L'\n'){
			line[line_count] = d;
			line_count++;
		}

		line[line_count] = L'\0';

		if (line[0] != L' ' && line[0] != L';' && line[0] != L'\n' && line[0] != L'#'){
			if (0 < line_count){
				fputws(line,temp);
				all_line_count ++;
			}
		}
	}


	OUTPUT_MESSAGE(L"收入%ld行。\n",all_line_count);

	all_line_count = 0;


	//read temp to bitree
	fseek(temp,2,SEEK_SET);//2 to skip BOM

	OUTPUT_MESSAGE(L"Creating tree...\n",all_line_count);
	while(!feof(temp) && !ferror(temp)){
		if (fwscanf(temp,L"%l[^,],%l[^=]=%l[^\n]\n",a,b,c) == EOF){
			break;
		}

		#if NO_FUNCTION == 1
		if (c[0] != L'#' && c[0] != L'$'){
		#endif

			#if DEBUG_CODE == 1
			OUTPUT_MESSAGE(L"cur:%ls,%ls=%ls\n",a,b,c);//####dbg
			#endif

			all_line_count ++;

			read_bitree_a(&bitree,a,b,c);
			read_bitree_c(&bitree_c,a,b,c);

		#if NO_FUNCTION == 1
		}
		#endif

	}
	
	OUTPUT_MESSAGE(L"处理%ld行。\n",all_line_count);
	OUTPUT_MESSAGE(L"Complete creating tree.\n");

	//output tree
	output_bitree_to_files(&bitree,f_no_child,f_with_child,f_merge_list,file_analyse_list);

	sequence_output_bitree_LR(&bitree,f_bbst);

	in_order_output_test_theory(&bitree_c,f_test_theory);

	in_order_output_balance_bitree_RL(&bitree_c,f_length_sort);


	fflush(f_length_sort);
	fflush(f_bbst);
	fflush(f_no_child);
	fflush(f_with_child);
	fflush(f_merge_list);
	fflush(f_cl_1);
	fflush(f_cl_2);
	fflush(f_cl_3);
	fflush(f_cl_4);
	fflush(f_practice);
	fflush(f_practice_codec);
	fflush(f_test_theory);

	//generate phrases
	phrases_generate(f_phrases,f_cl_1,f_cl_2,f_cl_3,f_cl_4);
	fflush(f_phrases);

	OUTPUT_MESSAGE(L"Complete writing.\n");

	//free
	
	free_bitree(&bitree);
	free_bitree(&bitree_c);


	fclose(f_length_sort);
	fclose(f_bbst);
	fclose(f_input);
	fclose(f_no_child);
	fclose(f_with_child);
	fclose(f_merge_list);
	fclose(f_phrases);
	fclose(f_practice);
	fclose(f_practice_codec);
	fclose(f_cl_1);
	fclose(f_cl_2);
	fclose(f_cl_3);
	fclose(f_cl_4);
	fclose(f_test_theory);
	fclose(temp);

	_wremove(the_path_of_temp);


	LocalFree(argv);

	OUTPUT_MESSAGE(L"SUCCESS.\n");

	return 0;
}

//Written by Vito(DevVitoP、朮朮、小斌、小斌鹏)
