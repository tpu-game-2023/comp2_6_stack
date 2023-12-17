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
	if (s->stack_memory==NULL) return;

	s->stack_top = -1;
	s->stack_max = mem_size/sizeof(int)-1;
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	// ToDo: Initializeで確保したメモリを解放しよう
	if (s == NULL) return;

	if (s->stack_memory == NULL) return;

	free(s->stack_memory);
	s->stack_memory = NULL;
	s->stack_top = NULL;
	s->stack_max = NULL;
}


// valの値をスタックに積む。実行の成否を返す
	bool push(STACK * s, int val)
{
	// ToDo: valの値をスタックに保存しよう
		if (s == NULL|| s->stack_top >= s->stack_max) return false;

		else
		{
			s->stack_top++;
			s->stack_memory[s->stack_top] = val;
			return true;
		}
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	// ToDo: addrからはじまるnum個の整数をスタックに保存しよう
	if (s == NULL|| num <= 0|| s->stack_top + num - 1 >= s->stack_max) return false;

	else
	{
		for (int i=num-1;i>=0;i--)
		{
			s->stack_top++;
			s->stack_memory[s->stack_top] = addr[i];
		}
		return true;
	}
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	// ToDo: スタックの最上位の値を取り出して返そう
	// 不具合時は0を返す
	if (s == NULL) return false;

	else if (s->stack_top <= -1)
	{
		return 0;
	}

	else
	{
		int val;
		val = s->stack_memory[s->stack_top];
		s->stack_memory[s->stack_top] = 0;
		s->stack_top--;
		return val;
	}
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	// ToDo: スタックからnum個の値を取り出してaddrから始まるメモリに保存しよう
	// スタックにnum個の要素がたまっていなかったら、積まれている要素を返して、
	// 積んだ要素数を返り値として返そう
	if (s == NULL|| addr == NULL) return false;

	else if (num < 0|| s->stack_top <= -1) return 0;

	else if (s->stack_top > -1+num-1)
	{
		for (int i = 0; i < num; i++)
		{
			addr[i] = s->stack_memory[s->stack_top];
			s->stack_memory[s->stack_top] = 0;
			s->stack_top--;
		}
	}
	
	else
	{
		int renum=0;
		do
		{
			addr[renum] = s->stack_memory[s->stack_top];
			s->stack_memory[s->stack_top] = 0;
			s->stack_top--;
			renum++;
		} while (s->stack_top > -1);
		return renum;
	}
}