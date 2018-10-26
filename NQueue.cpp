#include<windows.h>
#include"resource.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define TURE  1
#define FALSE 0
#define INFINITE  65700

int QUEEN;//表示解决的是几个皇后的问题

typedef  struct
{
	int *base;
	int *top;
	int stacksize;//目前存放的皇后个数
}Stack;

//栈的基本操作
int InitStack(Stack *s)
{
	s->base = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
	if (!s->base)return FALSE;
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;//当前栈的长度
	return TURE;
}

int Push(Stack *s, int e)
{
	if (s->top - s->base >= s->stacksize)//表明此时栈满了，要增加栈的长度
	{
		s->base = (int*)realloc(s->base, (s->stacksize + STACKINCREMENT)*sizeof(int));
		if (!s->base)return FALSE;
		s->top = s->base + s->stacksize;
		s->stacksize = s->stacksize + STACKINCREMENT;
	}
	*(s->top++) = e;
	return TURE;
}

int Pop(Stack *s)
{
	if (s->top == s->base)
		return FALSE;//此时栈空
	s->top--;
}

int Gettop(Stack *s)
{
	int e;
	if (s->top == s->base)
		return FALSE;
	*(s->top - 1) = e;
	return e;
}

int Clearstack(Stack *s)
{
	if (s->base != NULL)
		free(s->base);
	s->top = 0;
	s->stacksize = 0;
	return TURE;
}

int Empty(Stack *s)
{
	if (s->top == s->base)
		return TURE;
	return FALSE;
}

Stack S;//建立一个棋盘，栈中存放的是皇后的列，而栈的每一层表示皇后的行，这样就避免了行的冲突


void init()//初始化棋盘
{
	int i;
	for (i = 0;i<QUEEN;i++)
		Push(&S, INFINITE);
}

int valid(int row, int col)//判断该行列处能否放置皇后
{
	int i;
	for (i = 0;i<QUEEN;i++)
	{
		if (S.base[i] == col || abs(i - row) == abs(S.base[i] - col))//判断行是否相等即行之间有冲突或者斜线上的冲突
		{
			return FALSE;
		}
	}
	return TURE;
}

void print()  //打印输出N皇后的一组解
{
	int i, j;
	for (i = 0; i < QUEEN; i++)
	{
		for (j = 0; j < QUEEN; j++)
		{
			if (S.base[i] != j)      //S.base[i]为初始值
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 6);
				printf("%c  ", '#');
			}
			else                //S.base[i]表示在第i行的第S.base[i]列可以放置皇后
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xC);//把皇后的位置颜色改成红色便于区分
				printf("%c  ", '@');
			}
		}
		printf("\n");
	}
	printf("各皇后的位置是：\n");
	for (i = 0; i < QUEEN; i++)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 5);
		printf("%d  ", S.base[i]);
	}
	printf("\n");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0xF);
	printf("--------------------------------\n");
}

void nqueen()//核心算法
{
	int s = 0;//记录下解的个数
	int i = 0, j = 0;
	while (i<QUEEN)//对i行的每一列进行查看，看看是否可以放置皇后
	{
		while (j<QUEEN)
		{
			if (valid(i, j))//如果该放置位置有效
			{
				S.base[i] = j;//那么此处记录下放置的列的信息
				j = 0;//重新把列的信息置零，则探测下一行时，又重新开始查看
				break;
			}
			else
			{
				j++;//如果此列不能放置，那么列加一，继续查看
			}
		}
		if (S.base[i] == INFINITE)//如果在第i行没有找到能够放置的位置
		{
			if (i == 0)//回溯到第一行还是找不到，程序终止
				break;
			else
			{
				i--;//在该行找不到放置的位置，那么应该回溯到上一行，说明上一行皇后的位置不合理
				j = S.base[i] + 1;//上一行皇后的位置不合理，把它往后移动一位，不往前移，因为再之前的都放置好了
				S.base[i] = INFINITE;//皇后的位置移动了，那么这一行皇后的位置不确定，还得查看
				continue;
			}
		}
		if (i == QUEEN - 1)//已经到了最后一行了，最后一行找到了一个皇后的位置，那么有一个结果，打印出来
		{
			AllocConsole();//调用控制台输出结果
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//改颜色
			SetConsoleTextAttribute(hConsole, 0x3);//改颜色
			system("title N皇后问题的解");  //设置cmd窗口标题
			system("date /T");//显示日期
			system("TIME /T");//显示时间
			freopen("conout$", "w", stdout);
			printf("answer %d :  \n", ++s);
			print();
			j = S.base[i] + 1;//从最后一行放置皇后位置的下一列继续进行查看
			S.base[i] = INFINITE;//最后一列清零
			continue;
		}
		i++;//继续查看下一行皇后的位置
	}
}
INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//消息回调函数
	switch (uMsg)
	{
	   case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			MessageBox(hwndDlg, "您点击了确定，要开始计算吗？", "温馨提示",MB_ICONQUESTION| 0);
			QUEEN= GetDlgItemInt(hwndDlg, IDC_EDIT1, NULL, TRUE);
			if (QUEEN == 2 || QUEEN == 3)
			{
				MessageBox(hwndDlg, "您输入的数据不合理，请重新开始", "温馨提示",MB_ICONSTOP| 0);
			}
			EndDialog(hwndDlg, IDOK);
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(hwndDlg, "您点击了取消，要退出程序吗？", "温馨提示",MB_ICONQUESTION| 0);
			EndDialog(hwndDlg, IDCANCEL);
		}
		if (LOWORD(wParam) == IDC_BACK)
		{
			MessageBox(hwndDlg, "八皇后问题是一个以国际象棋为背景的问题：如何能够在8×8的国际象棋棋盘上放置八个皇后，使得任何一个皇后都无法直接吃掉其他的皇后？为了达到此目的，任两个皇后都不能处于同一条横行、纵行或斜线上。八皇后问题可以推广为更一般的n皇后摆放", "背景知识", 0);
		}
		if (LOWORD(wParam) == IDC_THINK)
		{
			MessageBox(hwndDlg, "最容易想到的方法就是有序地从第 1 列的第 1 行开始，尝试放上一个皇后，然后再尝试第 2 列的第几行能够放上一个皇后，如果第 2 列也放置成功，那么就继续放置第 3 列，如果此时第 3 列没有一行可以放置一个皇后，说明目前为止的尝试是无效的（即不可能得到最终解），那么此时就应该回溯到上一步（即第 2 步），将上一步（第 2 步）所放置的皇后的位置再重新取走放在另一个符合要求的地方…如此尝试性地遍历加上回溯，就可以慢慢地逼近最终解了。", "思路", 0);
		}
		if (LOWORD(wParam) == IDC_MATH)
		{
			MessageBox(hwndDlg, "N皇后的解题思路中用到了回溯法", "算法", 0);
		}
		if (LOWORD(wParam) == IDC_MORE)
		{
			MessageBox(hwndDlg, "关于N皇后问题还有其他不同的解法，感兴趣的同学可以多去了解呀，谢谢使用此系统！", "更多", MB_ICONINFORMATION | 0);
		}
		break;
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, "欢迎您来到N皇后问题", "解题方案",MB_ICONINFORMATION |0);
	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, NULL, theProc);
	InitStack(&S);
	init();
	nqueen();
	system("pause");
}

