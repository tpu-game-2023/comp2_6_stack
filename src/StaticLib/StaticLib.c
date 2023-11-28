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
	if (s->stack_memory == NULL) return;

	s->capacity = mem_size / sizeof(int);
	s->num = 0;
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	// ToDo: Initializeで確保したメモリを解放しよう
	if (s != NULL && s->stack_memory != NULL) {
		free(s->stack_memory);
		s->stack_memory = NULL;
		s->num = s->capacity = 0;
	}
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)
{
	// ToDo: valの値をスタックに保存しよう
	if (s == NULL || s->num >= s->capacity)
		return false;

	s->stack_memory[s->num] = val;
	s->num++;
	return true;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	// ToDo: addrからはじまるnum個の整数をスタックに保存しよう
	if (s == NULL || addr == NULL || num <= 0 || s->num + num > s->capacity)
		return false;

	for (int i = num - 1; i >= 0; i--) {
		push(s, addr[i]);
	}
	return true;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	// ToDo: スタックの最上位の値を取り出して返そう
	// 不具合時は0を返す
	if (s == NULL || s->num <= 0)
		return 0;

	s->num--;
	int val = s->stack_memory[s->num];
	return val;
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	// ToDo: スタックからnum個の値を取り出してaddrから始まるメモリに保存しよう
	// スタックにnum個の要素がたまっていなかったら、積まれている要素を返して、
	// 積んだ要素数を返り値として返そう
	if (s == NULL || addr == NULL || num <= 0)
		return 0;

	int i = 0;
	while (i < num) {
		if (s->num > 0) {
			addr[i] = pop(s);
			i++;
		}
		else break;
	}
	return i;
}