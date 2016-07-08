//entry.c
#include "minicrt.h"

#ifdef WIN32
#include<Windows.h>
#endif

extern int main(int argc,char *argv[]);
void exit(int);

static void crt_fatal_error(const char* msg){
	exit(1);
}

void mini_crt_entry(void){
	int ret;
}
