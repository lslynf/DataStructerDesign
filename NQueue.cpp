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

int QUEEN;//��ʾ������Ǽ����ʺ������

typedef  struct
{
	int *base;
	int *top;
	int stacksize;//Ŀǰ��ŵĻʺ����
}Stack;

//ջ�Ļ�������
int InitStack(Stack *s)
{
	s->base = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
	if (!s->base)return FALSE;
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;//��ǰջ�ĳ���
	return TURE;
}

int Push(Stack *s, int e)
{
	if (s->top - s->base >= s->stacksize)//������ʱջ���ˣ�Ҫ����ջ�ĳ���
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
		return FALSE;//��ʱջ��
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

Stack S;//����һ�����̣�ջ�д�ŵ��ǻʺ���У���ջ��ÿһ���ʾ�ʺ���У������ͱ������еĳ�ͻ


void init()//��ʼ������
{
	int i;
	for (i = 0;i<QUEEN;i++)
		Push(&S, INFINITE);
}

int valid(int row, int col)//�жϸ����д��ܷ���ûʺ�
{
	int i;
	for (i = 0;i<QUEEN;i++)
	{
		if (S.base[i] == col || abs(i - row) == abs(S.base[i] - col))//�ж����Ƿ���ȼ���֮���г�ͻ����б���ϵĳ�ͻ
		{
			return FALSE;
		}
	}
	return TURE;
}

void print()  //��ӡ���N�ʺ��һ���
{
	int i, j;
	for (i = 0; i < QUEEN; i++)
	{
		for (j = 0; j < QUEEN; j++)
		{
			if (S.base[i] != j)      //S.base[i]Ϊ��ʼֵ
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 6);
				printf("%c  ", '#');
			}
			else                //S.base[i]��ʾ�ڵ�i�еĵ�S.base[i]�п��Է��ûʺ�
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xC);//�ѻʺ��λ����ɫ�ĳɺ�ɫ��������
				printf("%c  ", '@');
			}
		}
		printf("\n");
	}
	printf("���ʺ��λ���ǣ�\n");
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

void nqueen()//�����㷨
{
	int s = 0;//��¼�½�ĸ���
	int i = 0, j = 0;
	while (i<QUEEN)//��i�е�ÿһ�н��в鿴�������Ƿ���Է��ûʺ�
	{
		while (j<QUEEN)
		{
			if (valid(i, j))//����÷���λ����Ч
			{
				S.base[i] = j;//��ô�˴���¼�·��õ��е���Ϣ
				j = 0;//���°��е���Ϣ���㣬��̽����һ��ʱ�������¿�ʼ�鿴
				break;
			}
			else
			{
				j++;//������в��ܷ��ã���ô�м�һ�������鿴
			}
		}
		if (S.base[i] == INFINITE)//����ڵ�i��û���ҵ��ܹ����õ�λ��
		{
			if (i == 0)//���ݵ���һ�л����Ҳ�����������ֹ
				break;
			else
			{
				i--;//�ڸ����Ҳ������õ�λ�ã���ôӦ�û��ݵ���һ�У�˵����һ�лʺ��λ�ò�����
				j = S.base[i] + 1;//��һ�лʺ��λ�ò��������������ƶ�һλ������ǰ�ƣ���Ϊ��֮ǰ�Ķ����ú���
				S.base[i] = INFINITE;//�ʺ��λ���ƶ��ˣ���ô��һ�лʺ��λ�ò�ȷ�������ò鿴
				continue;
			}
		}
		if (i == QUEEN - 1)//�Ѿ��������һ���ˣ����һ���ҵ���һ���ʺ��λ�ã���ô��һ���������ӡ����
		{
			AllocConsole();//���ÿ���̨������
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//����ɫ
			SetConsoleTextAttribute(hConsole, 0x3);//����ɫ
			system("title N�ʺ�����Ľ�");  //����cmd���ڱ���
			system("date /T");//��ʾ����
			system("TIME /T");//��ʾʱ��
			freopen("conout$", "w", stdout);
			printf("answer %d :  \n", ++s);
			print();
			j = S.base[i] + 1;//�����һ�з��ûʺ�λ�õ���һ�м������в鿴
			S.base[i] = INFINITE;//���һ������
			continue;
		}
		i++;//�����鿴��һ�лʺ��λ��
	}
}
INT_PTR CALLBACK theProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//��Ϣ�ص�����
	switch (uMsg)
	{
	   case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			MessageBox(hwndDlg, "�������ȷ����Ҫ��ʼ������", "��ܰ��ʾ",MB_ICONQUESTION| 0);
			QUEEN= GetDlgItemInt(hwndDlg, IDC_EDIT1, NULL, TRUE);
			if (QUEEN == 2 || QUEEN == 3)
			{
				MessageBox(hwndDlg, "����������ݲ����������¿�ʼ", "��ܰ��ʾ",MB_ICONSTOP| 0);
			}
			EndDialog(hwndDlg, IDOK);
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			MessageBox(hwndDlg, "�������ȡ����Ҫ�˳�������", "��ܰ��ʾ",MB_ICONQUESTION| 0);
			EndDialog(hwndDlg, IDCANCEL);
		}
		if (LOWORD(wParam) == IDC_BACK)
		{
			MessageBox(hwndDlg, "�˻ʺ�������һ���Թ�������Ϊ���������⣺����ܹ���8��8�Ĺ������������Ϸ��ð˸��ʺ�ʹ���κ�һ���ʺ��޷�ֱ�ӳԵ������Ļʺ�Ϊ�˴ﵽ��Ŀ�ģ��������ʺ󶼲��ܴ���ͬһ�����С����л�б���ϡ��˻ʺ���������ƹ�Ϊ��һ���n�ʺ�ڷ�", "����֪ʶ", 0);
		}
		if (LOWORD(wParam) == IDC_THINK)
		{
			MessageBox(hwndDlg, "�������뵽�ķ�����������شӵ� 1 �еĵ� 1 �п�ʼ�����Է���һ���ʺ�Ȼ���ٳ��Ե� 2 �еĵڼ����ܹ�����һ���ʺ������ 2 ��Ҳ���óɹ�����ô�ͼ������õ� 3 �У������ʱ�� 3 ��û��һ�п��Է���һ���ʺ�˵��ĿǰΪֹ�ĳ�������Ч�ģ��������ܵõ����ս⣩����ô��ʱ��Ӧ�û��ݵ���һ�������� 2 ����������һ������ 2 ���������õĻʺ��λ��������ȡ�߷�����һ������Ҫ��ĵط�����˳����Եر������ϻ��ݣ��Ϳ��������رƽ����ս��ˡ�", "˼·", 0);
		}
		if (LOWORD(wParam) == IDC_MATH)
		{
			MessageBox(hwndDlg, "N�ʺ�Ľ���˼·���õ��˻��ݷ�", "�㷨", 0);
		}
		if (LOWORD(wParam) == IDC_MORE)
		{
			MessageBox(hwndDlg, "����N�ʺ����⻹��������ͬ�Ľⷨ������Ȥ��ͬѧ���Զ�ȥ�˽�ѽ��ллʹ�ô�ϵͳ��", "����", MB_ICONINFORMATION | 0);
		}
		break;
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, "��ӭ������N�ʺ�����", "���ⷽ��",MB_ICONINFORMATION |0);
	DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, NULL, theProc);
	InitStack(&S);
	init();
	nqueen();
	system("pause");
}

