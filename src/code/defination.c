//author:Vito(DevVitoP、朮朮、小斌、小斌鹏)

#include "statement.h"

int default_main(void){

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
	}

	if(argc != 3 && argc != 2){
		wprintf(L"Usage:\tPhrases [Output_directory]\n");
		wprintf(L"\t\tPhrases：为UTF-16LE搜狗格式词库\n");
		wprintf(L"\t\tOutput_directory：为输出结果存放目录(默认在桌面)\n\n");

		wchar_t *mb_buffer = (wchar_t *)malloc(sizeof(wchar_t)*MAX_PATH);
		memset( mb_buffer,0,sizeof(wchar_t)*MAX_PATH);
		wcscat( mb_buffer,L"检测到搜狗自定义短语");

		if (_wstat(input_file,&temp_stat_file) != -1){
			wcscat( mb_buffer,L"存在:");
			wcscat( mb_buffer,input_file);
			wcscat( mb_buffer,L",是否使用");
			if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) != IDYES){
				if (choose_which_file_to_input(input_file,L"C:/Users/Administrator/Desktop") == 1)return FILE_ERROR;
			}
		}else{
			wcscat( mb_buffer,L"不存在,是否选择");
			if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) == IDYES){
				if (choose_which_file_to_input(input_file,L"C:/Users/Administrator/Desktop") == 1)return FILE_ERROR;
			}else return FILE_ERROR;
		}

		wcscpy( mb_buffer,L"当前默认输出路径为:");
		wcscat( mb_buffer,output_directory);
		wcscat( mb_buffer,L",是否更改");

		if (MessageBoxW(NULL,mb_buffer,L"Notice",MB_YESNOCANCEL) == IDYES){
			if (choose_which_path_to_output(output_directory) == 1)return DIR_ERROR;
		}

		free(mb_buffer);

	}

	//dir

	memset( &temp_stat_dir,0,sizeof (struct _stat));
	memset( &temp_stat_file,0,sizeof (struct _stat));
	if (_wstat(input_file,&temp_stat_file) == -1){
		_wperror(L"access phrses error");
		return FILE_ERROR;
	}
	if (_wstat(output_directory,&temp_stat_dir) == -1){
		_wperror(L"access directory error");
		return DIR_ERROR;
	}


	if(S_ISREG(temp_stat_file.st_mode) && S_ISDIR(temp_stat_dir.st_mode)){
		wprintf(L"Currently working in %s\n",input_file);
		wprintf(L"Default output_directory: %s\n",output_directory);
	}else{
		wprintf(L"Error type");
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
		_wperror(L"Error open");
		return FILE_ERROR;
	}else{
		wprintf(L"open:%s\n",input_file);
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

	FILE *temp= tmpfile();
	if (temp == NULL){
		_wperror(L"Error");
		return FILE_ERROR;
	}
	
	//comment
	if (f_practice != NULL && f_phrases != NULL){
		wprintf(L"\n###################################\n");
		wprintf(L"NOTICE1:\n\tpractice.txt为【一级简码第一候选和第二候选】与【二级简码的第一候选】的组合表(排序过)，\n\t目的是为了练习此表去熟悉词库。\n");
		wprintf(L"NOTICE2:\n\t搜狗格式自定义短语(极速出字词)在:\n\t(%s%s)目录下。\n",output_directory,personal_phrases);
		wprintf(L"###################################\n");
	}

	wprintf(L"\n#########\n");
	wprintf(L"请等待...\n");
	wprintf(L"wait a minute...\n");
	wprintf(L"#########\n\n");


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

		if (line[0] != L' ' && line[0] != L';' && line[0] != L'\n'){
			if (0 < line_count){
				fputws(line,temp);
				all_line_count ++;
			}
		}
	}

	wprintf(L"收入%ld行。\n",all_line_count);

	all_line_count = 0;

	//read temp to bitree
	fseek(temp,0,SEEK_SET);
	while(!feof(temp) && !ferror(temp)){
		if (fwscanf(temp,L"%[^,],%[^=]=%[^\n]\n",a,b,c) == EOF){
			wprintf(L"EOF\n");
			break;
		}

		#if NO_FUNCTION == 1
		if (c[0] != L'#' && c[0] != L'$'){
		#endif

			#if DEBUG_CODE == 1
			wprintf(L"cur:%s,%s=%s\n",a,b,c);//####dbg
			#endif

			all_line_count ++;

			read_bitree_a(&bitree,a,b,c);
			read_bitree_c(&bitree_c,a,b,c);

		#if NO_FUNCTION == 1
		}
		#endif

	}
	
	wprintf(L"处理%ld行。\n",all_line_count);
	wprintf(L"Complete creating tree.\n");

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

	wprintf(L"Complete writing.\n");

	//free
	
	free_bitree(&bitree);
	free_bitree(&bitree_c);

	fclose(f_length_sort);
	fclose(f_bbst);
	fclose(f_input);
	fclose(temp);
	fclose(f_no_child);
	fclose(f_with_child);
	fclose(f_merge_list);

	int temp_free = 0;
	while (temp_free <= CODEC_LENGTH_SETTING + 1){
		free(file_analyse_list[temp_free]);
		temp_free ++;
	}

	fclose(f_phrases);
	fclose(f_practice);
	fclose(f_practice_codec);
	fclose(f_cl_1);
	fclose(f_cl_2);
	fclose(f_cl_3);
	fclose(f_cl_4);
	fclose(f_test_theory);

	LocalFree(argv);

	wprintf(L"success.\n");
	_wsystem(L"pause");
	return 0;
}


void init_bitree(struct tree_list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (*bitree == NULL){
		*bitree = (struct tree_list *)malloc(sizeof(struct tree_list));
		if (*bitree == NULL){
			_wperror(L"malloc error");
			return;
		}
	}

	(**bitree).height = 1;
	(**bitree).balance_factor = 0;

	wcscpy( (**bitree).e.pa,a);
	wcscpy( (**bitree).e.pb,b);
	wcscpy( (**bitree).e.pc,c);

	(**bitree).next = NULL;
	(**bitree).left = NULL;
	(**bitree).right = NULL;

}

void init_next(struct tree_list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (bitree == NULL)return;
	if (*bitree == NULL)return;
	
	struct sub_list **next = &((**bitree).next);
	struct sub_list *temp_next= NULL;

	wchar_t temp_a[ENOUGH_SPACES];
	wchar_t temp_b[ENOUGH_SPACES];
	wchar_t temp_c[ENOUGH_SPACES];

	int cmp_wtoi = _wtoi(b) - _wtoi((**bitree).e.pb);
	if (cmp_wtoi < 0){
		wcscpy(temp_a,(**bitree).e.pa);
		wcscpy(temp_b,(**bitree).e.pb);
		wcscpy(temp_c,(**bitree).e.pc);

		wcscpy( (**bitree).e.pa,a);
		wcscpy( (**bitree).e.pb,b);
		wcscpy( (**bitree).e.pc,c);

		a = temp_a;
		b = temp_b;
		c = temp_c;

	}else if (cmp_wtoi == 0){

		#if DEBUG_CODE == 1
			if (wcscmp((**bitree).e.pc,c) != 0){
				wprintf(L"(%s,%s=%s)将被替为(%s,%s=%s)\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc,a,b,c);
			}
		#endif

		wcscpy( (**bitree).e.pa,a);
		wcscpy( (**bitree).e.pb,b);
		wcscpy( (**bitree).e.pc,c);

		return;
	}

	//####
	
	while (*next != NULL){//大于则向下一个链结点
		if (_wtoi(b) > _wtoi((**next).e.pb)){
			next = &((**next).next);
		}else{
			break;
		}
	}

	if (*next == NULL){//null则插入
		*next = (struct sub_list *)malloc(sizeof (struct sub_list));

		if (*next == NULL){
			_wperror(L"malloc error");
			return;
		}

		(**next).next = NULL;

		wcscpy( (**next).e.pa,a);
		wcscpy( (**next).e.pb,b);
		wcscpy( (**next).e.pc,c);
	}else{
		if (_wtoi(b) < _wtoi((**next).e.pb)){//小于 前插 继承
			
			temp_next = *next;
			*next = (struct sub_list *)malloc(sizeof (struct sub_list));

			if (*next == NULL){
				_wperror(L"malloc error");
				return;
			}

			(**next).next = temp_next;

			wcscpy( (**next).e.pa,a);
			wcscpy( (**next).e.pb,b);
			wcscpy( (**next).e.pc,c);
		}else{//等于则替换
			
			#if DEBUG_CODE == 1
				if (wcscmp((**bitree).e.pc,c) != 0){
					wprintf(L"(%s,%s=%s)将被替为(%s,%s=%s)\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc,a,b,c);
				}
			#endif
			wcscpy( (**next).e.pa,a);
			wcscpy( (**next).e.pb,b);
			wcscpy( (**next).e.pc,c);
		}
	}
	//####
}


void left_rotate(struct tree_list **bitree){

	struct tree_list *temp_left = (*((**bitree).right)).left;
	struct tree_list *temp_right = (**bitree).right;

	(*((**bitree).right)).left = *bitree;
	(**bitree).right = temp_left;
	*bitree = temp_right;


	calculate_hight_and_factor(&((**bitree).left));
	calculate_hight_and_factor(bitree);

	#if DEBUG_CODE == 1
		output_balance_bitree_to_terminal(bitree);//####dbg
	#endif

}

void right_rotate(struct tree_list **bitree){

	struct tree_list *temp_right = (*((**bitree).left)).right;
	struct tree_list *temp_left = (**bitree).left;

	(*((**bitree).left)).right = *bitree;
	(**bitree).left = temp_right;
	*bitree = temp_left;


	calculate_hight_and_factor(&((**bitree).right));
	calculate_hight_and_factor(bitree);

	#if DEBUG_CODE == 1
	output_balance_bitree_to_terminal(bitree);//####dbg
	#endif
}

void calculate_hight_and_factor(struct tree_list **bitree){

	struct tree_list **bitree_left = &((**bitree).left);
	struct tree_list **bitree_right = &((**bitree).right);

	int temp_left_height,temp_right_height;

	if ((*bitree_left) == NULL){
		temp_left_height = 0;
	}else{
		temp_left_height = (**bitree_left).height;
	}

	if ((*bitree_right) == NULL){
		temp_right_height = 0;
	}else{
		temp_right_height = (**bitree_right).height;
	}

	(**bitree).height = 1 + ((temp_left_height >= temp_right_height)?temp_left_height:temp_right_height);

	(**bitree).balance_factor = temp_left_height - temp_right_height;//lh - rh

}

void update_and_checkout_height_and_balance_factor(struct tree_list **bitree){


	if (bitree != NULL){
		if (*bitree != NULL){
		
			struct tree_list **bitree_left = &((**bitree).left);
			struct tree_list **bitree_right = &((**bitree).right);

			calculate_hight_and_factor(bitree);

			//checkout
			enum situation{NORMAL = 0,LL,RR,LR,RL};
			enum situation value;
			
			value = NORMAL;

			#if DEBUG_CODE == 1
			wprintf(L"update_balance:%s,%s=%s\tbf:%d\th:%d\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc,(**bitree).balance_factor,(**bitree).height);//####dbg
			#endif

			if((**bitree).balance_factor == 2 && *bitree_left != NULL){

				if ((**bitree_left).balance_factor == 1){//LL
					value = LL;
				}else if((**bitree_left).balance_factor == 0){//2 0 LL
					value = LL;
				}else if((**bitree_left).balance_factor == -1){//LR
					value = LR;
				}else{
					#if DEBUG_CODE == 1
					printf("#######left######\n");
					output_balance_bitree_to_terminal(bitree);//####dbg
					#endif
					perror("erorr");
					system("pause");
				}

			}

			if ((**bitree).balance_factor == -2 && *bitree_right != NULL){

				if ((**bitree_right).balance_factor == 1){//RL
					value = RL;
				}else if((**bitree_right).balance_factor == 0){//-2 0 RR
					value = RR;
				}else if((**bitree_right).balance_factor == -1){//RR
					value = RR;
				}else{
					#if DEBUG_CODE == 1
					printf("#######right######\n");
					output_balance_bitree_to_terminal(bitree);//####dbg
					#endif

					perror("erorr");
					system("pause");
				}

			}


			if (value != NORMAL){
			
				if (value == LL){
					right_rotate(bitree);
				}else if (value == RR){
					left_rotate(bitree);
				}else if (value == LR){
					left_rotate(bitree_left);
					right_rotate(bitree);
				}else if (value == RL){
					right_rotate(bitree_right);
					left_rotate(bitree);
				}

			}

		}
	}

}

void read_bitree_a(struct tree_list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (bitree == NULL)return;

	if (*bitree == NULL){
		init_bitree(bitree,a,b,c);
	}else{
		int var;

		var = wcscmp(a , (**bitree).e.pa);

		if (var < 0){//left

			if ((**bitree).left == NULL){
				init_bitree(&((**bitree).left),a,b,c);
			}else{
				read_bitree_a(&((**bitree).left),a,b,c);
			}

		}else if(var > 0){//right
			
			if ((**bitree).right== NULL){
				init_bitree(&((**bitree).right),a,b,c);
			}else{
				read_bitree_a(&((**bitree).right),a,b,c);
			}

		}else{//equal
			
			init_next(bitree,a,b,c);
		}
	}

	//balance
	update_and_checkout_height_and_balance_factor(bitree);

}

void read_bitree_b(struct tree_list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (*bitree == NULL){
		init_bitree(bitree,a,b,c);
	}else{

		int var1,var2,var3;

		var1 = _wtoi(b) - _wtoi((**bitree).e.pb);

		//use b to decide
		if (var1 < 0){//l

			if ((**bitree).left == NULL){
				init_bitree(&((**bitree).left),a,b,c);
			}else{
				read_bitree_b(&((**bitree).left),a,b,c);
			}

		}else if(var1 > 0){//r
			
			if ((**bitree).right== NULL){
				init_bitree(&((**bitree).right),a,b,c);
			}else{
				read_bitree_b(&((**bitree).right),a,b,c);
			}

		}else{//use a to decide
			
			var2 = wcscmp(a,(**bitree).e.pa);

			if (var2 < 0){//l
				if ((**bitree).left == NULL){
					init_bitree(&((**bitree).left),a,b,c);
				}else{
					read_bitree_b(&((**bitree).left),a,b,c);
				}
			}else if(var2 > 0){//r
				if ((**bitree).right== NULL){
					init_bitree(&((**bitree).right),a,b,c);
				}else{
					read_bitree_b(&((**bitree).right),a,b,c);
				}

			}else{//use c to decide

				var3 = wcscmp(c,(**bitree).e.pc);

				if (var3 < 0){//l
					if ((**bitree).left == NULL){
						init_bitree(&((**bitree).left),a,b,c);
					}else{
						read_bitree_b(&((**bitree).left),a,b,c);
					}
				}else if(var3 > 0){//r

					if ((**bitree).right== NULL){
						init_bitree(&((**bitree).right),a,b,c);
					}else{
						read_bitree_b(&((**bitree).right),a,b,c);
					}
				}else{
					wcscpy((**bitree).e.pa,a);
					wcscpy((**bitree).e.pb,b);
					wcscpy((**bitree).e.pc,c);
				}

			}

		}

		update_and_checkout_height_and_balance_factor(bitree);
	}

}

void read_bitree_c(struct tree_list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (*bitree == NULL){
		init_bitree(bitree,a,b,c);
	}else{

		int var1,var2,var3;

		var1 = wcslen(c) - wcslen((**bitree).e.pc);
		if (var1 == 0){
			var1 = wcscmp(c,(**bitree).e.pc);
		}

		//use c to decide
		if (var1 < 0){//l

			if ((**bitree).left == NULL){
				init_bitree(&((**bitree).left),a,b,c);
			}else{
				read_bitree_c(&((**bitree).left),a,b,c);
			}

		}else if(var1 > 0){//r
			
			if ((**bitree).right== NULL){
				init_bitree(&((**bitree).right),a,b,c);
			}else{
				read_bitree_c(&((**bitree).right),a,b,c);
			}
		}else{//use a to decide
			
			var2 = wcscmp(a,(**bitree).e.pa);

			if (var2 > 0){//l
				if ((**bitree).left == NULL){
					init_bitree(&((**bitree).left),a,b,c);
				}else{
					read_bitree_c(&((**bitree).left),a,b,c);
				}
			}else if(var2 < 0){//r
				if ((**bitree).right== NULL){
					init_bitree(&((**bitree).right),a,b,c);
				}else{
					read_bitree_c(&((**bitree).right),a,b,c);
				}

			}else{//use b to decide

				var3 = _wtoi(b) - _wtoi((**bitree).e.pb);

				if (var3 > 0){//l
					if ((**bitree).left == NULL){
						init_bitree(&((**bitree).left),a,b,c);
					}else{
						read_bitree_c(&((**bitree).left),a,b,c);
					}
				}else if(var3 < 0){//r

					if ((**bitree).right== NULL){
						init_bitree(&((**bitree).right),a,b,c);
					}else{
						read_bitree_c(&((**bitree).right),a,b,c);
					}
				}else{
					wcscpy((**bitree).e.pa,a);
					wcscpy((**bitree).e.pb,b);
					wcscpy((**bitree).e.pc,c);
				}

			}

		}

		update_and_checkout_height_and_balance_factor(bitree);
	}
}

void read_bitree_c_get_full_codec(struct tree_list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (*bitree == NULL){
		init_bitree(bitree,a,b,c);
	}else{

		int var1,var2;//,var3;

		var1 = wcscmp(c,(**bitree).e.pc);

		//use c to decide
		if (var1 < 0){//l

			if ((**bitree).left == NULL){
				init_bitree(&((**bitree).left),a,b,c);
			}else{
				read_bitree_c_get_full_codec(&((**bitree).left),a,b,c);
			}

		}else if(var1 > 0){//r
			
			if ((**bitree).right== NULL){
				init_bitree(&((**bitree).right),a,b,c);
			}else{
				read_bitree_c_get_full_codec(&((**bitree).right),a,b,c);
			}
		}else if(wcslen(a) > 0){//make a to maximum
			
			var2 = wcslen(a) - wcslen((**bitree).e.pa);

			if(var2 == 0)var2 = wcscmp(a,(**bitree).e.pa);

			if (var2 >= 0){
				#if DEBUG_CODE == 1
				wprintf(L"replace %s,%s=%s with %s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc,a,b,c);//####dbg
				#endif
				wcscpy((**bitree).e.pa,a);
				wcscpy((**bitree).e.pb,b);
				wcscpy((**bitree).e.pc,c);
			}

		}
	}

	update_and_checkout_height_and_balance_factor(bitree);
}

void output_bitree_node_to_files(struct tree_list **bitree,FILE *no_child,FILE *with_child,FILE *f_merge,FILE **f_list){

	int codec_length;
	int codec_num;

	fwprintf(f_merge,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);//merge

	//1 2 3 4 practice practice_codec
	codec_length = wcslen((**bitree).e.pa);
	codec_num = _wtoi((**bitree).e.pb);

	if (codec_length <= CODEC_LENGTH_SETTING && codec_length >= 1){
		fwprintf(f_list[codec_length],L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);

		if ((codec_length == 1 && codec_num <=2)||(codec_length == 2 && codec_num ==1)){
			if(wcslen((**bitree).e.pc) == 1){
				fwprintf(f_list[0],L"%s",(**bitree).e.pc);
				fwprintf(f_list[5],L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);
			}
		}
	}

	//####
	if ((**bitree).next == NULL){//no_child
		
		fwprintf(no_child,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);

	}else{//with_child

		fwprintf(with_child,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);
		
		struct sub_list *next = (**bitree).next;

		while(next != NULL){
			fwprintf(with_child,L"%s,%s=%s\n",(*next).e.pa,(*next).e.pb,(*next).e.pc);
			fwprintf(f_merge,L"%s,%s=%s\n",(*next).e.pa,(*next).e.pb,(*next).e.pc);//merge


			//1 2 3 4 practice practice_codec
			codec_num = _wtoi((*next).e.pb);

			if (codec_length <= CODEC_LENGTH_SETTING && codec_length >= 1){
				fwprintf(f_list[codec_length],L"%s,%s=%s\n",(*next).e.pa,(*next).e.pb,(*next).e.pc);

				if ((codec_length == 1 && codec_num <=2)||(codec_length == 2 && codec_num ==1)){
					if(wcslen((*next).e.pc) == 1){
						fwprintf(f_list[0],L"%s",(*next).e.pc);
					}
				}
			}

			next = (*next).next;
		}
			fwprintf(with_child,L"\n");
	}

	fwprintf(f_list[codec_length],L"\n");
	//####

}

void output_bitree_to_files(struct tree_list **bitree,FILE *no_child,FILE *with_child,FILE *f_merge,FILE **f_list){
	if (*bitree != NULL){

		output_bitree_to_files(&((**bitree).left),no_child,with_child,f_merge,f_list);
		output_bitree_node_to_files(bitree,no_child,with_child,f_merge,f_list);
		output_bitree_to_files(&((**bitree).right),no_child,with_child,f_merge,f_list);

	}
}



void free_bitree_node(struct tree_list **bitree){

	if ((**bitree).next != NULL){//with_child

		struct sub_list *pre = NULL;
		struct sub_list *cur = (**bitree).next;

		while(cur != NULL){
			pre = cur;
			cur = (*cur).next;

			free((void *)pre);
		}
	}

	free((void*) *bitree);//now no_child
}

void free_bitree(struct tree_list **bitree){
	if (*bitree != NULL){

		free_bitree(&((**bitree).left));
		free_bitree(&((**bitree).right));

		free_bitree_node(bitree);

	}
}

void specially_copy(FILE *f_input,FILE *f_output){

	fseek(f_input,2,SEEK_SET);//use 2 to pass <fffe>

	wchar_t line[ENOUGH_SPACES*3];
	int line_count;
	wchar_t d;


	while(!feof(f_input) && !ferror(f_input)){

		line_count = 0;
		while ((d = fgetwc(f_input)) != L'\n' && !feof(f_input) && !ferror(f_input)){
			line[line_count]=d;
			line_count++;
		}

		if (d == L'\n'){
			line[line_count] = d;
			line_count++;
		}

		line[line_count] = L'\0';

		if (line[0] != L' ' && line[0] != L';' && line[0] != L'\n'){
			if (0 < line_count){
				fputws(line,f_output);
			}
		}
	}


}

void phrases_generate(FILE *sougou_phrases,FILE *f1,FILE *f2,FILE *f3,FILE *f4){

	specially_copy(f1,sougou_phrases);
	specially_copy(f2,sougou_phrases);
	specially_copy(f3,sougou_phrases);
	specially_copy(f4,sougou_phrases);

}


FILE *generate_object_file(wchar_t *access_path,wchar_t *main_work_path,wchar_t *sub_work_path,wchar_t *file_name_add){

	wchar_t *buffer_path = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);
	wchar_t *main_path = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);
	wchar_t *sub_path_name = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);
	wchar_t *file_name = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);


	buffer_path[0]=L'\0';
	main_path[0]=L'\0';
	sub_path_name[0]=L'\0';
	file_name[0]=L'\0';

	if (access_path != NULL)wcscpy( buffer_path,access_path);
	if (main_work_path != NULL)wcscpy( main_path,main_work_path);
	if (sub_work_path != NULL)wcscpy( sub_path_name,sub_work_path);
	if (file_name_add != NULL)wcscpy( file_name,file_name_add);


	FILE *object_file_p = NULL;

	wcscat( buffer_path , main_path);
	wcscat( buffer_path , sub_path_name);
	wcscat( buffer_path , file_name);
	object_file_p = _wfopen(buffer_path ,L"w+,ccs=UTF-16LE");

	if (object_file_p == NULL){
		_wperror(L"error create");
		return NULL;
	}else{
		wprintf(L"create:%s\n",buffer_path);
		return object_file_p;
	}

	free(buffer_path);
	free(main_path);
	free(sub_path_name);
	free(file_name_add);
}

int generate_object_directory(wchar_t *access_path,wchar_t *main_work_path,wchar_t *sub_work_path){

	wchar_t *buffer_path = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);
	wchar_t *main_path = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);
	wchar_t *sub_path_name = (wchar_t *)malloc(sizeof (wchar_t) * MAX_PATH);

	buffer_path[0]=L'\0';
	main_path[0]=L'\0';
	sub_path_name[0]=L'\0';

	if (access_path != NULL)wcscpy( buffer_path,access_path);
	if (main_work_path != NULL)wcscpy( main_path,main_work_path);
	if (sub_work_path != NULL)wcscpy( sub_path_name,sub_work_path);

	struct _stat checkout_directory;
	memset( &checkout_directory,0,sizeof (struct _stat));

	wcscat( buffer_path,main_path);
	wcscat( buffer_path,sub_path_name);

	_wstat(buffer_path,&checkout_directory);

	if (S_ISDIR(checkout_directory.st_mode) != 1){
		if (_wmkdir(buffer_path) == 0){
			wprintf(L"create:%s\n",buffer_path);
		}else{
			_wperror(L"Error directory");
			return 1;
		}
	}else{
		wprintf(L"%s,已存在,可能将覆盖\n",buffer_path);
	}

	free(buffer_path);
	free(main_path);
	free(sub_path_name);
	return 0;
}


void output_balance_bitree_node_to_file_default(struct tree_list **bitree,FILE *fp){
	if (bitree == NULL)return;
	if (*bitree == NULL)return;

	if ((**bitree).next == NULL){//no_child

		fwprintf(fp,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);

	}else{//with_child

		fwprintf(fp,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);
		
		struct sub_list *next = (**bitree).next;

		while(next != NULL){
			fwprintf(fp,L"%s,%s=%s\n",(*next).e.pa,(*next).e.pb,(*next).e.pc);
			next = (*next).next;
		}
	}

}


void output_balance_bitree_node_to_file_number_order(struct tree_list **bitree,FILE *fp){

	if (bitree == NULL)return;
	if (*bitree == NULL)return;

	int number;
	number = 1;

	if ((**bitree).next == NULL){//no_child

		fwprintf(fp,L"%s,%d=%s\n",(**bitree).e.pa,number,(**bitree).e.pc);

	}else{//with_child

		fwprintf(fp,L"%s,%d=%s\n",(**bitree).e.pa,number,(**bitree).e.pc);
		
		struct sub_list *next = (**bitree).next;

		while(next != NULL){
			number++;
			fwprintf(fp,L"%s,%d=%s\n",(*next).e.pa,number,(*next).e.pc);
			next = (*next).next;
		}
	}

}

void output_balance_bitree_node_to_file_number_reverse_order(struct tree_list **bitree,FILE *fp){

	if (bitree == NULL)return;
	if (*bitree == NULL)return;

	int number;
	number = 1;

	if ((**bitree).next == NULL){//no_child

		fwprintf(fp,L"%s,%d=%s\n",(**bitree).e.pa,number,(**bitree).e.pc);

	}else{//with_child

		struct sub_list *next = (**bitree).next;

		while(next != NULL){
			number++;
			next = (*next).next;
		}

		fwprintf(fp,L"%s,%d=%s\n",(**bitree).e.pa,number,(**bitree).e.pc);

		next = (**bitree).next;
		while(next != NULL){
			number--;
			fwprintf(fp,L"%s,%d=%s\n",(*next).e.pa,number,(*next).e.pc);
			next = (*next).next;
		}

	}

}


void output_balance_bitree_node_to_file(struct tree_list **bitree,FILE *fp,int way){

	if (bitree == NULL)return;
	if (*bitree == NULL)return;

	if (way == NUMBER_ORDER){
		output_balance_bitree_node_to_file_number_order(bitree,fp);
	}else if (way == NUMBER_REVERSE_ORDER){
		output_balance_bitree_node_to_file_number_reverse_order(bitree,fp);
	}else{
		output_balance_bitree_node_to_file_default(bitree,fp);
	}

}


void pre_order_output_balance_bitree_LR(struct tree_list **bitree , FILE *fp){
	if (bitree != NULL){
		if (*bitree != NULL){

			#if NUMBER_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_ORDER);
			#elif NUMBER_REVERSE_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_REVERSE_ORDER);
			#else
				output_balance_bitree_node_to_file(bitree,fp,-1);
			#endif

			pre_order_output_balance_bitree_LR(&((**bitree).left),fp);
			pre_order_output_balance_bitree_LR(&((**bitree).right),fp);
		}
	}
}

void in_order_output_balance_bitree_LR(struct tree_list **bitree , FILE *fp){
	if (bitree != NULL){
	
		if (*bitree != NULL){
			in_order_output_balance_bitree_LR(&((**bitree).left),fp);

			#if NUMBER_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_ORDER);
			#elif NUMBER_REVERSE_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_REVERSE_ORDER);
			#else
				output_balance_bitree_node_to_file(bitree,fp,-1);
			#endif

			in_order_output_balance_bitree_LR(&((**bitree).right),fp);
		}
	}

}

void post_order_output_balance_bitree_LR(struct tree_list **bitree , FILE *fp){
	if (bitree != NULL){
	
		if (*bitree != NULL){
			post_order_output_balance_bitree_LR(&((**bitree).left),fp);
			post_order_output_balance_bitree_LR(&((**bitree).right),fp);

			#if NUMBER_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_ORDER);
			#elif NUMBER_REVERSE_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_REVERSE_ORDER);
			#else
				output_balance_bitree_node_to_file(bitree,fp,-1);
			#endif
		}
	}

}

void pre_order_output_balance_bitree_RL(struct tree_list **bitree , FILE *fp){
	if (bitree != NULL){
	
		if (*bitree != NULL){

			#if NUMBER_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_ORDER);
			#elif NUMBER_REVERSE_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_REVERSE_ORDER);
			#else
				output_balance_bitree_node_to_file(bitree,fp,-1);
			#endif

			pre_order_output_balance_bitree_RL(&((**bitree).right),fp);
			pre_order_output_balance_bitree_RL(&((**bitree).left),fp);
		}
	}

}

void in_order_output_balance_bitree_RL(struct tree_list **bitree , FILE *fp){
	if (bitree != NULL){
	
		if (*bitree != NULL){
			in_order_output_balance_bitree_RL(&((**bitree).right),fp);

			#if NUMBER_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_ORDER);
			#elif NUMBER_REVERSE_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_REVERSE_ORDER);
			#else
				output_balance_bitree_node_to_file(bitree,fp,-1);
			#endif

			in_order_output_balance_bitree_RL(&((**bitree).left),fp);
		}
	}

}
void post_order_output_balance_bitree_RL(struct tree_list **bitree , FILE *fp){
	if (bitree != NULL){
		if (*bitree != NULL){
			post_order_output_balance_bitree_RL(&((**bitree).right),fp);
			post_order_output_balance_bitree_RL(&((**bitree).left),fp);

			#if NUMBER_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_ORDER);
			#elif NUMBER_REVERSE_ORDER == 1
				output_balance_bitree_node_to_file(bitree,fp,NUMBER_REVERSE_ORDER);
			#else
				output_balance_bitree_node_to_file(bitree,fp,-1);
			#endif
		}
	}
	

}

#if DEBUG_CODE == 1
void output_balance_bitree_to_terminal(struct tree_list **bitree){//###dbg

	if (*bitree != NULL){
		wprintf(L"%s,%s=%s\tbf:%d\th:%d\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc,(**bitree).balance_factor,(**bitree).height);
		output_balance_bitree_to_terminal(&((**bitree).left));
		output_balance_bitree_to_terminal(&((**bitree).right));
	}

}
#endif



void output_bitree_node_to_test_theory(struct tree_list **bitree,FILE *test_theory){

	int codec_length;
	int codec_num;

	codec_length = wcslen((**bitree).e.pa);
	codec_num = _wtoi((**bitree).e.pb);

	fwprintf(test_theory,L"%s\t%s%s",(**bitree).e.pc,(**bitree).e.pa,\
			codec_num ==1 ? L"" : (**bitree).e.pb );//test_theory

	if (codec_num == 1 && codec_length < 4){
		fwprintf(test_theory,L"_\n");
	}else{
		fwprintf(test_theory,L"\n");
	}
}

void in_order_output_test_theory(struct tree_list **bitree,FILE *test_theory){
	if (bitree != NULL){
	
		if (*bitree != NULL){
			in_order_output_test_theory(&((**bitree).right),test_theory);

			output_bitree_node_to_test_theory(bitree,test_theory);

			in_order_output_test_theory(&((**bitree).left),test_theory);
		}
	}
}


int line_filter_default(wchar_t *input_line){
	if (input_line[0] == L'#'){
		return 0;//no pass
	}
	
	if (input_line[0] == L' '){
		return 0;//no pass
	}

	if (input_line[0] == L'$'){
		return 0;//no pass
	}

	if (input_line[0] == L'\n'){
		return 0;//no pass
	}

	if (input_line[0] == (wchar_t)EOF){
		return 0;//no pass
	}

	return 1;//pass
}

void table_format_convert(FILE *in,wchar_t *in_line_format,wchar_t *order,int (*line_filter)(wchar_t *input_line),FILE *out,wchar_t *out_line_format){

	wchar_t *a = (wchar_t *)malloc(sizeof(wchar_t) * ENOUGH_SPACES);
	wchar_t *b = (wchar_t *)malloc(sizeof(wchar_t) * ENOUGH_SPACES);
	wchar_t *c = (wchar_t *)malloc(sizeof(wchar_t) * ENOUGH_SPACES);

	memset( a,0,sizeof(wchar_t) * ENOUGH_SPACES);
	memset( b,0,sizeof(wchar_t) * ENOUGH_SPACES);
	memset( c,0,sizeof(wchar_t) * ENOUGH_SPACES);

	wcscpy( a,L"NULL");
	wcscpy( b,L"NULL");
	wcscpy( c,L"NULL");

	wchar_t line[ENOUGH_SPACES*3+3];
	int line_count;

	wchar_t d = !(wchar_t)EOF;

	while(d != (wchar_t)EOF){

		line_count = 0;
		while ((d = fgetwc(in)) != L'\n' && d != (wchar_t)EOF){
			line[line_count]=d;
			line_count ++;
		}

		if (d == L'\n'){
			line[line_count] = d;
			line_count++;
		}

		line[line_count] = L'\0';

		if (line_filter(line) == 1){
			if (0 < line_count){

				if (wcscmp(order, L"abc") == 0) {
					swscanf(line, in_line_format, a, b, c);
				} else if (wcscmp(order, L"acb") == 0) {
					swscanf(line, in_line_format, a, c, b);
				} else if (wcscmp(order, L"bca") == 0) {
					swscanf(line, in_line_format, b, c, a);
				} else if (wcscmp(order, L"bac") == 0) {
					swscanf(line, in_line_format, b, a, c);
				} else if (wcscmp(order, L"cab") == 0) {
					swscanf(line, in_line_format, c, a, b);
				} else if (wcscmp(order, L"cba") == 0) {
					swscanf(line, in_line_format, c, b, a);
				} else {
					swscanf(line, in_line_format, a, b, c); // 默认情况
				}

				/*
				if (_wtoi(b) == 0 && b[0] != L'0'){//b是空或其它不能认的则为1
					wcscpy(b,L"1");
				}*/

				fwprintf(out,out_line_format,a,b,c);
				/*
				if (wcscmp(order, L"abc") == 0) {
					fwprintf(out,out_line_format,a,b,c);
				} else if (wcscmp(order, L"acb") == 0) {
					fwprintf(out,out_line_format,a,c,b);
				} else if (wcscmp(order, L"bca") == 0) {
					fwprintf(out,out_line_format,b,c,a);
				} else if (wcscmp(order, L"bac") == 0) {
					fwprintf(out,out_line_format,b,a,c);
				} else if (wcscmp(order, L"cab") == 0) {
					fwprintf(out,out_line_format,c,a,b);
				} else if (wcscmp(order, L"cba") == 0) {
					fwprintf(out,out_line_format,c,b,a);
				} else {
					fwprintf(out,out_line_format,a,b,c);
				}*/
			}
		}

	}

}

void free_line_list(struct line_list **fll) {
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


void reverse_output_line_list(struct line_list **fll,FILE *f_output){

	if (*fll == NULL){
		return;
	}

	struct line_list **f_temp_line_listp = fll;

	while ((**f_temp_line_listp).latter_line != NULL){
		f_temp_line_listp = &((**f_temp_line_listp).latter_line );
	}

	while ((**f_temp_line_listp).previos_line != NULL){
		fwprintf(f_output,L"%s",(**f_temp_line_listp).line);
		f_temp_line_listp = &((**f_temp_line_listp).previos_line);
	}

}

void write_into_line_list(wchar_t *buf,struct line_list **fll,struct line_list **prelp){

	if (*fll == NULL){
		*fll = (struct line_list *)malloc(sizeof(struct line_list));
		if (*fll == NULL){
			_wperror(L"malloc error");
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


void file_reverse(FILE *fp_in,FILE *fp_out){
	
	fseek(fp_in,2,SEEK_SET);//2 to jump BOM

	wchar_t line_buffer[ENOUGH_SPACES];
	int line_count;
	wchar_t cur = !(wchar_t)EOF;
	struct line_list *file_line_list = NULL;
	struct line_list **cur_line_list_position = &file_line_list;

	while (cur != (wchar_t)EOF){

		line_count = 0;
		while ( (cur = fgetwc(fp_in)) != L'\n' && cur != (wchar_t)EOF){

			if (line_count < ENOUGH_SPACES - 2 - 1){
				line_buffer[line_count] = cur;
				line_count ++;
			}

		}

		line_buffer[line_count] = L'\n';
		line_count ++;
		line_buffer[line_count] = L'\0';

		if (*cur_line_list_position != NULL){
			write_into_line_list(line_buffer,&((**cur_line_list_position).latter_line),cur_line_list_position);
			cur_line_list_position = &((**cur_line_list_position).latter_line);
		}else{
			write_into_line_list(line_buffer,cur_line_list_position,NULL);
		}

	}

	reverse_output_line_list(&file_line_list,fp_out);
	free_line_list(&file_line_list);
}


int read_line(FILE *fp_in,wchar_t *line_buffer){
	int line_count;
	wchar_t cur = !(wchar_t)EOF;

	line_count = 0;
	while ( (cur = fgetwc(fp_in)) != L'\n' && cur != (wchar_t)EOF){

		if (line_count < ENOUGH_SPACES - 2 - 1){
			line_buffer[line_count] = cur;
			line_count ++;
		}

	}

	line_buffer[line_count] = L'\n';
	line_count ++;
	line_buffer[line_count] = L'\0';

	if (cur == (wchar_t)EOF)return EOF;
	else return 0;
}



int search_bitree_ab(struct tree_list **bi,wchar_t *a,wchar_t *b,const wchar_t *c){

	if(bi != NULL){
	
		if (*bi != NULL){

			if (wcscmp(c,(**bi).e.pc) == 0){
				if (a != NULL)wcscpy( a,(**bi).e.pa);
				if (b != NULL)wcscpy( b,(**bi).e.pb);
				return 1;
			}else if ((**bi).next != NULL){
				
				struct sub_list *next = (**bi).next;

				while(next != NULL){
					
					if (wcscmp(c,(*next).e.pc) == 0){
						if (a != NULL)wcscpy( a,(*next).e.pa);
						if (b != NULL)wcscpy( b,(*next).e.pb);
						return 1;
					}

					next = (*next).next;
				}

			}

			if (search_bitree_ab(&((**bi).left),a,b,c) == 1){
				return 1;
			}

			if (search_bitree_ab(&((**bi).right),a,b,c) == 1){
				return 1;
			}
		}
	}

	return 0;
}



int search_bitree_c(struct tree_list **bi,const wchar_t *a,const wchar_t *b,wchar_t *c){

	if (*bi != NULL){

		if (wcscmp(a,(**bi).e.pa) == 0 && _wtoi(b) == _wtoi((**bi).e.pb)){
			wcscpy( c,(**bi).e.pc);
			return 1;
		}else if ((**bi).next != NULL){
			
			struct sub_list *next = (**bi).next;

			while(next != NULL){
				
				if (wcscmp(a,(*next).e.pa) == 0 && _wtoi(b) == _wtoi((*next).e.pb)){
					wcscpy( c,(*next).e.pc);
					return 1;
				}

				next = (*next).next;
			}

		}

		if (search_bitree_c(&((**bi).left),a,b,c) == 1){
			return 1;
		}

		if (search_bitree_c(&((**bi).right),a,b,c) == 1){
			return 1;
		}
	}

	return 0;
}

//addresses of obj_node,obj_next both belong in parent node spaces.
int search_bitree_delete_node(struct tree_list **bi,wchar_t *a,wchar_t *b,wchar_t *c,struct tree_list **obj_node,struct sub_list **obj_next){

	if (*bi != NULL){

		if (wcscmp(a,(**bi).e.pa) == 0 && _wtoi(b) == _wtoi((**bi).e.pb) && wcscmp(c,(**bi).e.pc) == 0 ){
			obj_node = bi;
			obj_next = NULL;
			return 1;
		}else if ((**bi).next != NULL){
			
			struct sub_list *next = (**bi).next;

			while(next != NULL){
				if (wcscmp(a,(*next).e.pa) == 0 && _wtoi(b) == _wtoi((*next).e.pb) && wcscmp(c,(*next).e.pc) == 0 ){
				obj_node = bi;
				obj_next = &next;
				return 1;
				}

				next = (*next).next;
			}

		}

		if (search_bitree_c(&((**bi).left),a,b,c) == 1){
			return 1;
		}

		if (search_bitree_c(&((**bi).right),a,b,c) == 1){
			return 1;
		}
	}

	return 0;
}


void copy_bitree_node_for_delete(struct tree_list **node_a,const struct tree_list **node_b){

	wcscpy((**node_a).e.pa,(**node_b).e.pa);
	wcscpy((**node_a).e.pb,(**node_b).e.pb);
	wcscpy((**node_a).e.pc,(**node_b).e.pc);
	(**node_a).next = (**node_b).next;

}

void free_for_delete(struct tree_list *bi){

	if (bi != NULL){
		if ((*bi).next != NULL){
			wcscpy((*bi).e.pa,(*((*bi).next)).e.pa);
			wcscpy((*bi).e.pb,(*((*bi).next)).e.pb);
			wcscpy((*bi).e.pc,(*((*bi).next)).e.pc);

			struct sub_list *next = (*bi).next;
			(*bi).next = bi -> next -> next;
			free(next);
		}else{
			free(bi);
		}
	}

}

void delete_bitree_node_operation(struct tree_list **obj_node){

	if (obj_node != NULL){
		if(*obj_node != NULL){
			struct tree_list *temp_node = NULL;

			if ((**obj_node).right == NULL && (**obj_node).left == NULL){//leaf
				free_for_delete((*obj_node));
				*obj_node = NULL;
			}else if((**obj_node).right == NULL){//one left child
				temp_node = (*obj_node);
				*obj_node = (**obj_node).left;
				free_for_delete(temp_node);
			}else if ((**obj_node).left == NULL){//one right child
				temp_node = (*obj_node);
				*obj_node = (**obj_node).right;
				free_for_delete(temp_node);
			}else{//double child
				//find direct successor
				if ((**obj_node).next != NULL){
					free_for_delete(*obj_node);
				}else{
					struct tree_list **temp_node_parent_p = &((**obj_node).right);
					struct tree_list **temp_node_grand_p = obj_node;

					while ((**temp_node_parent_p).left != NULL){
						temp_node_grand_p = temp_node_parent_p;
						temp_node_parent_p = &((**temp_node_parent_p).left);
					}
					
					copy_bitree_node_for_delete(obj_node , (const struct tree_list **)temp_node_parent_p);
					delete_bitree_node_operation(temp_node_parent_p);
					//balance temp_node_parent_p
					update_and_checkout_height_and_balance_factor(temp_node_grand_p);
				}

			}

		}
	}
}

int bitree_delete_node(struct tree_list **bi,wchar_t *a,wchar_t *b,wchar_t *c){

	int value_of_return = 0;

	if (bi != NULL){
	
		if (*bi != NULL){

			if (bitree_delete_node(&((**bi).left),a,b,c) == 1 )value_of_return = 1;
			if (bitree_delete_node(&((**bi).right),a,b,c) == 1 )value_of_return = 1;

			if (wcscmp(a,(**bi).e.pa) == 0 && _wtoi(b) == _wtoi((**bi).e.pb) && wcscmp(c,(**bi).e.pc) == 0 ){
				delete_bitree_node_operation(bi);
				value_of_return = 1;

			}else if ((**bi).next != NULL){
				
				struct sub_list **next = &((**bi).next);
				struct sub_list *preserve_cur = NULL;

				while(*next != NULL){
					if (wcscmp(a,(**next).e.pa) == 0 && _wtoi(b) == _wtoi((**next).e.pb) && wcscmp(c,(**next).e.pc) == 0 ){
						preserve_cur = *next;
						*next = (**next).next;
						free(preserve_cur);
						value_of_return = 1;
					}

					next = &((**next).next);
				}
			}

			update_and_checkout_height_and_balance_factor(bi);

		}

	}

	return value_of_return;
}


void full_codec_disperate(wchar_t *buffer,wchar_t *a1,wchar_t *a2,wchar_t *a3,wchar_t *a4){
	int len_buffer = wcslen(buffer);

	if (len_buffer >= 4){
		a4[0]=buffer[0];
		a4[1]=buffer[1];
		a4[2]=buffer[2];
		a4[3]=buffer[3];
		a4[4]=L'\0';
	}else{
		a4[0]=L'\0';
	}

	if (len_buffer >= 3){
		a3[0]=buffer[0];
		a3[1]=buffer[1];
		a3[2]=buffer[2];
		a3[3]=L'\0';
	}else{
		a3[0]=L'\0';
	}

	if (len_buffer >= 2){
		a2[0]=buffer[0];
		a2[1]=buffer[1];
		a2[2]=L'\0';
	}else{
		a2[0]=L'\0';
	}

	if (len_buffer >= 1){
		a1[0]=buffer[0];
		a1[1]=L'\0';
	}else{
		a1[0]=L'\0';
	}

}

int use_position_to_get_word(struct tree_list *single_words,wchar_t *c,wchar_t *buffer_c,wchar_t *buffer_temp,int bufc_position){

	buffer_c[0] = c[bufc_position];
	buffer_c[1] = L'\0';
	if (search_bitree_ab(&single_words,buffer_temp,NULL,buffer_c) != 1){
		wprintf(L"单字全码树中无:%s(%0.2x %0.2x)\t来自字词:%s\n",buffer_c,((unsigned char*)buffer_c)[1],((unsigned char*)buffer_c)[0],c);
		return 1;
	}

	return 0;
}

void set_b_for_wcscat(wchar_t *a,wchar_t *b,int b_pos){
	if (wcslen(b) < b_pos){
		wprintf(L"error %s less than %d(b_pos).\n",b,b_pos);
	}else{
		b[b_pos] = L'\0';
		wcscat(a,b);
	}
}

void generate_codec(struct tree_list *single_words,wchar_t *c,wchar_t *a1,wchar_t *a2,wchar_t *a3,wchar_t *a4){
	if (single_words == NULL)return;
	if (a1 == NULL)return;
	if (a2 == NULL)return;
	if (a3 == NULL)return;
	if (a4 == NULL)return;
	if (c == NULL)return;

	wchar_t buffer[ENOUGH_SPACES]={L'\0'};
	wchar_t buffer_temp[ENOUGH_SPACES]={L'\0'};
	wchar_t buffer_c[ENOUGH_SPACES]={L'\0'};

	int error_collect = 0;
	switch (wcslen(c)){
		case 1:{
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer,0);
			break;
		}case 2:{
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,0);
			if(wcslen(buffer_temp) < 2){wprintf(L"(%s)编码(%s)长度小于2,无法编码(%s).\n",buffer_c,buffer_temp,c);break;}
			set_b_for_wcscat(buffer,buffer_temp,2);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,1);
			if(wcslen(buffer_temp) < 2){wprintf(L"(%s)编码(%s)长度小于2,无法编码(%s).\n",buffer_c,buffer_temp,c);break;}
			set_b_for_wcscat(buffer,buffer_temp,2);
			break;
		}case 3:{
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,0);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,1);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,2);
			if(wcslen(buffer_temp) < 2){wprintf(L"(%s)编码(%s)长度小于2,无法编码(%s).\n",buffer_c,buffer_temp,c);break;}
			set_b_for_wcscat(buffer,buffer_temp,2);
			break;
		}case 4:{
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,0);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,1);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,2);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,3);
			set_b_for_wcscat(buffer,buffer_temp,1);
			break;
		}default:{
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,0);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,1);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,2);
			set_b_for_wcscat(buffer,buffer_temp,1);
			error_collect += use_position_to_get_word(single_words,c,buffer_c,buffer_temp,wcslen(c)-1);
			set_b_for_wcscat(buffer,buffer_temp,1);
			break;
		}

	}

	if (error_collect > 0)buffer[0] = L'\0';
	full_codec_disperate(buffer,a1,a2,a3,a4);
}


void queue_push(struct queue_for_tree_node **queue,struct tree_list *node){
	if (queue == NULL)return;

	if (*queue == NULL){

		*queue = (struct queue_for_tree_node *)malloc(sizeof(struct queue_for_tree_node));
		if (*queue == NULL){
			_wperror(L"malloc error");
			return;
		}

		(**queue).list = (struct tree_node *)malloc(sizeof (struct tree_node));
		if ((**queue).list == NULL){
			_wperror(L"malloc error");
			return;
		}

		(**queue).head = (**queue).list;
		(**queue).tail = (**queue).list;
	}else{
		(*(**queue).tail).next = (struct tree_node *)malloc(sizeof (struct tree_node));
		(**queue).tail = (*(**queue).tail).next;
	}

	(*((**queue).tail)).next = NULL;
	(*((**queue).tail)).node = node;
}

int queue_pop(struct queue_for_tree_node **queue){

	if (queue == NULL)return 1;
	if (*queue == NULL)return 1;

	if((**queue).list != NULL){

		if ((*((**queue).list)).next != NULL){
			(**queue).list = (*((**queue).list)).next;
			free((**queue).head);
			(**queue).head = (**queue).list;
			return 0;
		}else{
			(**queue).list = NULL;
			free((**queue).head);
			(**queue).head = NULL;
			return 1;
		}

	}
	
	return 1;
}

void sequence_output_bitree_RL(struct tree_list **tree_root,FILE *fp){
	if (tree_root == NULL)return;
	if (*tree_root == NULL)return;

	struct queue_for_tree_node *queue = NULL;
	queue_push(&queue,*tree_root);

	struct tree_list *temp_name = NULL;

	while((*queue).head != NULL){
		
		temp_name = (*((*queue).head)).node;

		#if NUMBER_ORDER == 1
			output_balance_bitree_node_to_file(&temp_name,fp,NUMBER_ORDER);
		#elif NUMBER_REVERSE_ORDER == 1
			output_balance_bitree_node_to_file(&temp_name,fp,NUMBER_REVERSE_ORDER);
		#else
			output_balance_bitree_node_to_file(&temp_name,fp,-1);
		#endif
		
	
		if ((*temp_name).right != NULL){
			queue_push(&queue,(*temp_name).right);
		}

		if ((*temp_name).left != NULL){
			queue_push(&queue,(*temp_name).left);
		}

		queue_pop(&queue);

	}

}

void sequence_output_bitree_LR(struct tree_list **tree_root,FILE *fp){
	if (tree_root == NULL)return;
	if (*tree_root == NULL)return;

	struct queue_for_tree_node *queue = NULL;
	queue_push(&queue,*tree_root);

	struct tree_list *temp_name = NULL;

	while((*queue).head != NULL){
		
		temp_name = (*((*queue).head)).node;

		#if NUMBER_ORDER == 1
			output_balance_bitree_node_to_file(&temp_name,fp,NUMBER_ORDER);
		#elif NUMBER_REVERSE_ORDER == 1
			output_balance_bitree_node_to_file(&temp_name,fp,NUMBER_REVERSE_ORDER);
		#else
			output_balance_bitree_node_to_file(&temp_name,fp,-1);
		#endif
		
		if ((*temp_name).left != NULL){
			queue_push(&queue,(*temp_name).left);
		}
	
		if ((*temp_name).right != NULL){
			queue_push(&queue,(*temp_name).right);
		}

		queue_pop(&queue);

	}

}


int choose_which_path_to_output(wchar_t *buffer_path){
	if (buffer_path == NULL){
		wprintf(L"error");
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

	if (GetOpenFileNameW(&ofn) == TRUE)return 0;
	else return 1;
}



//author:Vito(DevVitoP、朮朮、小斌、小斌鹏)

