#include <stdio.h>

void f_int(int* p){
	printf("f_int: %d\n",*p);
}

void f_void_int(void* p){
	printf("f_void_int: %d\n",*(int *)p);
}

void f_void_void(void* p){
	printf("f_void_void_1: %p\n",p);
	// Not possible!
	//printf("f_void_void_2: %x\n",*p);
}

int main_cfunc(void) {
	// your code goes here
	int *p;
	int i = 30;
	p = &i;

	f_int(p);
	f_void_int(p);
	f_void_void(p);

	return 0;
}
