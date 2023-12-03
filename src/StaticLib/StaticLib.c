#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でスタック用のメモリを確保する
void initialize(STACK* s, size_t mem_size)
{
	if (s == NULL) return;

	// ToDo: mem_sizeでメモリを確保しよう
	s->stack_memory = (int*)malloc(mem_size);
	s->end = s->stack_memory + mem_size / sizeof(int);
	s->stack_pointer = s->stack_memory + mem_size / sizeof(int);
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	// ToDo: Initializeで確保したメモリを解放しよう
	if (s == NULL) return;

	free(s->stack_memory);
	s->stack_memory = NULL;
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)
{
	// ToDo: valの値をスタックに保存しよう
	if (s != NULL && s->stack_pointer > s->stack_memory)
	{
		s->stack_pointer--;
		*(s->stack_pointer) = val;
		return true;
	}
	return false;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	// ToDo: addrからはじまるnum個の整数をスタックに保存しよう
	if (s != NULL && addr != NULL && s->stack_memory <= s->stack_pointer - num && num > 0)
	{
		for (int i = 0; i < num; i++)
		{
			push(s, addr[num - 1 - i]);
		}
		return true;
	}
	return false;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	// ToDo: スタックの最上位の値を取り出して返そう
	// 不具合時は0を返す
	if (s != NULL && s->stack_pointer != s->end)
	{
		s->stack_pointer++;
		return *(s->stack_pointer - 1);
	}
	return 0;
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	// ToDo: スタックからnum個の値を取り出してaddrから始まるメモリに保存しよう
	// スタックにnum個の要素がたまっていなかったら、積まれている要素を返して、
	// 積んだ要素数を返り値として返そう
	if (s != NULL && addr != NULL && num > 0)
	{
		if (s->stack_pointer > s->end - num)
		{
			num = s->end - s->stack_pointer;
		}
		for (int i = 0; i < num; i++)
		{
			addr[i] = pop(s);
		}
		return num;
	}
	return 0;
}