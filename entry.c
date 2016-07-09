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
//解析参数
#ifdef WIN32				//windows

	int flag = 0;
	int argc = 0;
	char *argv[16];			//最多16个参数
	char* c1 = GetCommandLineA();	//获取进程的命令行参数

	//解释命令行
	argv[0] = c1;
	argc++;
	while(*c1){
		if(*c1 == '\"')
			if(flag == 0)flag =1;
			else flag = 0;
		else if(*c1 == '' && flag==0){
			if(*(c1+1)){
				argv[argc] = c1+1;
				argc++;
			}
			*c1='\0';
		}
		c1++;
	}	
#else					//linux
	int argc;
	char** argv;

	char* ebp_reg=0;
	//ebp_reg = %ebp;
	asm("movl %%ebp,%0 \n":"=r"(ebp_reg));

	argc = *(int*)(ebp_reg + 4);
	argv = (char**)(ebp_reg+8);
#endif
//初始化堆，io
	if(!mini_crt_heap_init())
		crt_fatal_error("heap initialize failed");

	if(!mini_crt_io_init())
		crt_fatal_error("IO initialize failed");
//调用函数main
	ret = main(argc,argv);
	exit(ret);
}	

void exit(int exitcode){
	//mini_crt_call_exit_routine();
#ifdef WIN32
	ExitProcess(exitcode);
#else
	asm("movl %0,%%ebx \n\t"
			"movl $1,%%eax \n\t"
			"int $0x80   \n\t"
			"hlt \n\t"::"m"(exitcode)
			);
#endif
}
