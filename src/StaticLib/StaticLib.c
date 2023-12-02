#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でスタック用のメモリを確保する
void initialize(STACK* s, size_t mem_size)
{
	if (s == NULL) return;

	if (mem_size <= 0)
	{
		s->end = s->stack_memory = s->stack_pointer = NULL;
		return;
	}
	s->stack_memory = (int*)malloc(mem_size);
	s->end = s->stack_pointer = s->stack_memory + mem_size / sizeof(int);
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	if (s == NULL) return;
	free(s->stack_memory);
	s->stack_memory = NULL;
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)
{
	if (s == NULL || s->stack_pointer == s->stack_memory) return false;
	
	s->stack_pointer--;
	*(s->stack_pointer) = val;
	return true;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	if (s == NULL || addr == NULL || s->stack_memory > s->stack_pointer - num || num <= 0) return false;

	for (int i = 0; i < num; i++)
	{
		push(s, addr[num - 1 - i]);
	}
	return true;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	if (s == NULL || s->stack_pointer == s->end) return 0;

	s->stack_pointer++;
	return *(s->stack_pointer-1);
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	if (s == NULL || addr == NULL || num <= 0) return 0;
	
	if (s->stack_pointer > s->end - num)
	{
		int cnum = s->end - s->stack_pointer;
		for (int i=0; i < cnum; i++)
		{
			addr[i] = pop(s);
		}
		return cnum;
	}

	for (int i=0; i < num; i++)
	{
		addr[i] = pop(s);
	}
	return num;
}