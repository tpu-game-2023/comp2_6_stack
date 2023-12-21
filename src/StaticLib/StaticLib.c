#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include<malloc.h>
#include <stdlib.h>
#include<stdio.h>
#include "../include/lib_func.h"


// mem_size の容量でスタック用のメモリを確保する

void initialize(STACK* s, size_t mem_size) {
	if (s == NULL) return;

	s->stack_memory = (int*)malloc(mem_size);
	s->stack_pointer = s->stack_memory;
	s->end = s->stack_memory + mem_size / sizeof(int);  // end ポインタを設定
}





void finalize(STACK* s)
{
	if (s == NULL) return;

	free(s->stack_memory);
	s->stack_memory = NULL;
	s->stack_pointer = NULL;
	s->end = NULL;
}




// valの値をスタックに積む。実行の成否を返す
// 修正: pushが成功する条件を満たすように修正
// 修正: pushが成功する条件を満たすように修正
bool push(STACK* s, int val) {
	if (s == NULL || s->stack_pointer == NULL || s->end == NULL) {
		return false; // NULLポインタチェック
	}

	if (s->stack_pointer == s->end) {
		return false; // スタックオーバーフロー
	}

	*(s->stack_pointer) = val;
	s->stack_pointer++;

	return true;
}



// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
// 修正: push_arrayが成功する条件を満たすように修正
// 修正: push_arrayが成功する条件を満たすように修正
bool push_array(STACK* s, int* addr, int n)
{
	if (s == NULL || addr == NULL || n <= 0)
		return false;

	// 修正: スタックに余裕がない場合
	if ((size_t)n > (size_t)(s->end - s->stack_pointer)) {
		return false;
	}

	for (int i = 0; i < n; ++i) {
		if (!push(s, addr[i])) {
			// push が失敗した場合はエラーを返す
			return false;
		}
	}

	return true;  // 正常終了を示す true を返す
}


// スタックから一つの要素を取り出す

// 修正: メモリ操作が逆順になっていたため修正
int pop(STACK* s) {
	if (s == NULL || s->stack_pointer == NULL || s->stack_pointer == s->stack_memory) {
		return 0; // スタックアンダーフローまたはNULLポインタエラー
	}

	s->stack_pointer--;  // デクリメントしてから値を取得
	int result = *(s->stack_pointer);

	return result;
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す

int pop_array(STACK* s, int* addr, int num) {
	if (s == NULL || addr == NULL || num <= 0) {
		return 0; // NULLポインタチェックまたは不正な引数
	}

	int count = 0;
	while (num > 0 && s->stack_pointer > s->stack_memory) {
		*(addr++) = *(--(s->stack_pointer));
		num--;
		count++;
	}

	return count;
}








