#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
	
	char *path_def1 = "C:/Program Files (x86)/SogouWBInput/5.5.0.2584/phrases.ini";
	char *path_def2 = "C:/Users/Administrator/Desktop/test_theory.txt";

	if (argc == 1){
		printf("format:\n\
				test_theory phrases.ini output.txt\n\
				make sure all in unicode\n");
	}else if (argc == 3){
		path_def1 = argv[1];
		path_def2 = argv[2];
	}else{
		printf("too many or too few argument.\ndefault.\n");
	}

	FILE *f_input = fopen(path_def1,"r,ccs=UNICODE");
	FILE *f_checkout_output= fopen(path_def2,"w,ccs=UNICODE");

	if (f_input == NULL){
		perror("can not open phrases.ini");
		return 1;
	}

	if (f_checkout_output == NULL){
		perror("can not create file:");
		return 1;
	}

	FILE *temp= tmpfile();

	if (f_input == NULL){
		printf("Can\'t open Phrases.ini\n");
		return 1;
	}

	if (f_checkout_output == NULL){
		printf("Can\'t create Phrases.txt\n");
		return 1;
	}

	wchar_t a[1024];
	wchar_t b[1024];
	wchar_t c[1024];

	wchar_t line[4096];
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

		if (_wtoi(b) == 1)b[0]=L'\0';
	
		if (c[0] != L'#' && c[0] != L'$'){
			fwprintf(f_checkout_output,L"%s\t%s%s\n",c,a,b);
		}
	}

	fclose(temp);
	fclose(f_checkout_output);

	return 0;
}

