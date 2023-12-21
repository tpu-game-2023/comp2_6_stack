#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include<malloc.h>
#include <stdlib.h>
#include<stdio.h>
#include "../include/lib_func.h"




void initialize(STACK* s, size_t mem_size) {
	if (s == NULL) return;

	s->stack_memory = (int*)malloc(mem_size);
	s->stack_pointer = s->stack_memory;
	s->end = s->stack_memory + mem_size / sizeof(int);  
}





void finalize(STACK* s)
{
	if (s == NULL) return;

	free(s->stack_memory);
	s->stack_memory = NULL;
	s->stack_pointer = NULL;
	s->end = NULL;
}




bool push(STACK* s, int val) {
	if (s == NULL ) {
		return false; 
	}
	if (s->stack_pointer-1 < s->stack_memory) {
		return false; 
	}

	*--s->stack_pointer = val;


	return true;
}




bool push_array(STACK* s, int* addr, int num)
{
	if (s == NULL )
		return false;

	if(num<=0)
		return false;
	
	if (s->stack_pointer-num<s->stack_memory) {
		return false;
	}

	s->stack_pointer -= num;
	memcpy(s->stack_pointer, addr, num * sizeof(int));//numの数だけメモリを確保

	return true;  
}



int pop(STACK* s) {
	if (s == NULL ) {
		return false; 
	}
	if (s->end < s->stack_pointer + 1) return 0;

	return *s->stack_pointer++;
}



int pop_array(STACK* s, int* addr, int num) {
	if (s == NULL ) {
		return　false 
	}
	if(addr==NULL){
		
	return false;
}
	if (s->end < s->stack_pointer + num) {
		num = s->end - s->stack_pointer;
	}
	if (num < 0) return 0;

	memcpy(addr, s->stack_pointer, sizeof(int) * num);
	s->stack_pointer += num;

	return num;
}








