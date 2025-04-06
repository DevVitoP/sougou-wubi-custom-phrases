//Written by Vito
#define NO_FUNCTION 0

HANDLE init_default_main_thread(void );

#ifndef OUTPUT_MESSAGE
	#define OUTPUT_MESSAGE(str,...) wprintf((str) __VA_OPT__(,) __VA_ARGS__)
#endif
