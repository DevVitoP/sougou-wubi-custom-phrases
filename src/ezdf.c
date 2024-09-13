
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define ENOUGH_SPACES 32

struct element{
	wchar_t pa[ENOUGH_SPACES];
	wchar_t pb[ENOUGH_SPACES];
	wchar_t pc[ENOUGH_SPACES];
};

struct sub_list{
	struct element e;

	struct sub_list *next;
};

struct list{
	struct element e;

	struct sub_list *next;

	struct list *left;
	struct list *right;
};

void init_bitree(struct list **bitree,wchar_t *a,wchar_t *b,wchar_t *c);
void init_next(struct list **bitree,wchar_t *a,wchar_t *b,wchar_t *c);

void read_bitree(struct list **bitree,wchar_t *a,wchar_t *b,wchar_t *c);

void output_bitree_node_to_file(struct list **bitree,FILE *no_child,FILE *with_child);
void output_bitree_to_file(struct list **bitree,FILE *no_child,FILE *with_child);

void free_bitree_node(struct list **bitree);
void free_bitree(struct list **bitree);

int main(int argc, char *argv[])
{
	char *def_path = "C:/Program Files (x86)/SogouWBInput/5.5.0.2584/phrases.ini";
	char output_path[MAX_PATH];

	char *output_path_def = "C:/Users/Administrator/Desktop/";

	if (argc == 1){

		printf("format:\n\
				ezdf.exe phrases.ini output_path\n\
				\n\
				default.\n\
				");
		printf("work in %s\n",def_path);
		printf("output under %s\n",output_path_def);

	}else if (argc == 3){
		def_path = argv[1];
		output_path_def = argv[2];

		printf("work in %s\n",def_path);
		printf("output under %s\n",output_path_def);
	}else{
		printf("too few or too many argument.\nwork with default.\n");
		printf("work in %s\n",def_path);
		printf("output under %s\n",output_path_def);
	}

	FILE *f_input = fopen(def_path,"r,ccs=UNICODE");

	strcpy( output_path,output_path_def);
	strcat( output_path,"ez_one.txt");
	FILE *f_no_child= fopen(output_path,"w,ccs=UNICODE");
	if (f_no_child == NULL){
		perror("error create");
		return 1;
	}else{
		printf("create:%s\n",output_path);
	}

	strcpy( output_path,output_path_def);
	strcat( output_path,"df_multi.txt");
	FILE *f_with_child= fopen(output_path,"w,ccs=UNICODE");
	if (f_with_child == NULL){
		perror("error create");
		return 1;
	}else{
		printf("create:%s\n",output_path);
	}

	printf("wait...\n");


	FILE *temp= tmpfile();


	if (f_input == NULL || f_no_child == NULL || f_with_child == NULL){
		perror("Error");
		return 1;
	}


	struct list *bitree = NULL;
	init_bitree(&bitree,L"mmmm",L"1",L"");

	wchar_t a[ENOUGH_SPACES];
	wchar_t b[ENOUGH_SPACES];
	wchar_t c[ENOUGH_SPACES];

	wchar_t line[ENOUGH_SPACES*3];
	int line_count,write_count;
	wchar_t d;

	while(!feof(f_input) && !ferror(f_input)){
		line_count = 0;
		write_count = 0;
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
			if (write_count <= line_count - 1){
				fputws(line,temp);
			}
		}
	}

	fclose(f_input);

	fseek(temp,0,SEEK_SET);

	while(!feof(temp) && !ferror(temp)){
		if (fwscanf(temp,L"%[^,],%[^=]=%[^\n]\n",a,b,c) == EOF){
			printf("EOF\n");
			break;
		}

		//if (_wtoi(b) == 1)b[0]=L'\0';
	
		if (c[0] != L'#' && c[0] != L'$'){
			//read tree

			read_bitree(&bitree,a,b,c);

		}
	}

	//output tree
	output_bitree_to_file(&bitree,f_no_child,f_with_child);

	free_bitree(&bitree);

	fclose(temp);
	fclose(f_no_child);
	fclose(f_with_child);

	printf("success.\n");
	return 0;
}




void init_bitree(struct list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (*bitree == NULL){
		*bitree = (struct list *)malloc(sizeof(struct list));
		if (*bitree == NULL){
			perror("malloc error");
			return;
		}
	}

	wcscpy( (**bitree).e.pa,a);
	wcscpy( (**bitree).e.pb,b);
	wcscpy( (**bitree).e.pc,c);

	(**bitree).next = NULL;
	(**bitree).left = NULL;
	(**bitree).right = NULL;

}

void init_next(struct list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	struct sub_list **next = &((**bitree).next);

	while(*next != NULL){
		if (_wtoi(b) != _wtoi((**next).e.pb)){
			next = &((**next).next);
		}else{
			wcscpy( (**next).e.pa,a);
			wcscpy( (**next).e.pb,b);
			wcscpy( (**next).e.pc,c);
			return;
		}
	}

	*next = (struct sub_list *)malloc(sizeof (struct sub_list));

	if (*next == NULL){
		perror("malloc error");
		return;
	}

	(**next).next = NULL;

	wcscpy( (**next).e.pa,a);
	wcscpy( (**next).e.pb,b);
	wcscpy( (**next).e.pc,c);

}

void read_bitree(struct list **bitree,wchar_t *a,wchar_t *b,wchar_t *c){

	if (*bitree == NULL){
		init_bitree(bitree,a,b,c);
	}else{

		int var;

		var = wcscmp(a , (**bitree).e.pa);

		if (_wtoi(b) == 1){//node

			if (var < 0){//left

				if ((**bitree).left == NULL){
					init_bitree(&((**bitree).left),a,b,c);
				}else{
					read_bitree(&((**bitree).left),a,b,c);
				}

			}else if(var > 0){//right
				
				if ((**bitree).right== NULL){
					init_bitree(&((**bitree).right),a,b,c);
				}else{
					read_bitree(&((**bitree).right),a,b,c);
				}

			}else{//equal
				wcscpy( (**bitree).e.pa,a);
				wcscpy( (**bitree).e.pb,b);
				wcscpy( (**bitree).e.pc,c);
			}

		}else{//next
			
			if (var < 0){//left

				if ((**bitree).left == NULL){
					init_bitree(&((**bitree).left),a,b,c);
					init_next(&((**bitree).left),a,b,c);
				}else{
					read_bitree(&((**bitree).left),a,b,c);
				}

			}else if(var > 0){//right
				
				if ((**bitree).right== NULL){
					init_bitree(&((**bitree).right),a,b,c);
					init_next(&((**bitree).right),a,b,c);
				}else{
					read_bitree(&((**bitree).right),a,b,c);
				}

			}else{//equal
				init_next(bitree,a,b,c);
			}

		}

	}
}

void output_bitree_node_to_file(struct list **bitree,FILE *no_child,FILE *with_child){

	if ((**bitree).next == NULL){//no_child

		fwprintf(no_child,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);

	}else{//with_child
		  
		fwprintf(with_child,L"%s,%s=%s\n",(**bitree).e.pa,(**bitree).e.pb,(**bitree).e.pc);

		struct sub_list *next = (**bitree).next;

		while(next != NULL){
			fwprintf(with_child,L"%s,%s=%s\n",(*next).e.pa,(*next).e.pb,(*next).e.pc);
			next = (*next).next;
		}

		fwprintf(with_child,L"\n");
	}

}

void output_bitree_to_file(struct list **bitree,FILE *no_child,FILE *with_child){
	if (*bitree != NULL){

		output_bitree_to_file(&((**bitree).left),no_child,with_child);
		output_bitree_node_to_file(bitree,no_child,with_child);
		output_bitree_to_file(&((**bitree).right),no_child,with_child);

	}
}



void free_bitree_node(struct list **bitree){
	if ((**bitree).next == NULL){//no_child
		free((void*) *bitree);
	}else{//with_child

		struct sub_list *pre = NULL;
		struct sub_list *cur = (**bitree).next;

		while(cur != NULL){
			pre = cur;
			cur = (*cur).next;

			free((void *)pre);
		}

		free((void*) *bitree);
	}
}

void free_bitree(struct list **bitree){
	if (*bitree != NULL){

		free_bitree(&((**bitree).left));
		free_bitree(&((**bitree).right));

		free_bitree_node(bitree);

	}
}


