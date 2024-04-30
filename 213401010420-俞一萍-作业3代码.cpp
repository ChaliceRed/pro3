#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>

#define Maxsize 50

typedef char ElemType;
typedef struct BiTreeNode
{
	ElemType data;
	struct BiTreeNode* LChild, * RChild;
}*BiTree;
typedef struct SqStack
{
	BiTree data[Maxsize];
	int top;
}*Stack;
//����ջ
Stack InitStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(SqStack));
	S->top = -1;
	return S;
}
//ջ��
int StackEmpty(SqStack S)
{
	if (S.top == -1)return 1;
	else return 0;
}
//��ջ
void Push(Stack S, BiTree p)
{
	S->top++;
	S->data[S->top] = p;
}
//��ջ
void Pop(Stack S, BiTree* p)
{
	*p = S->data[S->top];
	S->top--;
}
BiTree CreateBiTree()
{
	char ch;
	BiTree T;
	scanf_s("%c", &ch, 1);
	if (ch == '#')T = NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTreeNode));
		T->data = ch;
		T->LChild = CreateBiTree();
		T->RChild = CreateBiTree();
	}
	return T;
}
//�������
void PreOrder(BiTree T)
{
	SqStack* S;
	S = InitStack();
	BiTreeNode* p;
	p = T;
	while (p || !StackEmpty(*S))
	{
		if (p)
		{
			printf("%c", p->data);
			Push(S, p);
			p = p->LChild;
		}
		else
		{
			Pop(S, &p);
			p = p->RChild;
		}
	}
}
//�������
void InOrder(BiTree T)
{
	SqStack* S;
	S = InitStack();
	BiTreeNode* p;
	p = T;
	while (p || !StackEmpty(*S))
	{
		if (p)
		{
			Push(S, p);
			p = p->LChild;
		}
		else
		{
			Pop(S, &p);
			printf("%c", p->data);
			p = p->RChild;
		}
	}
}
//�������
void Postorder(BiTree T)
{
	SqStack* S;
	S = InitStack();
	BiTreeNode* p;
	p = T;
	char tag[Maxsize] = { '0' };
	while (p || !StackEmpty(*S))
	{
		if (p)
		{
			Push(S, p);
			tag[S->top] = '0';//��־����Ƿ����������
			p = p->LChild;
		}
		else
		{
			while (tag[S->top] == '1') {
				Pop(S, &p);
				printf("%c", p->data);
			}
			if (S->top == -1) break;
			Pop(S, &p);
			Push(S, p);
			p = p->RChild;
			tag[S->top] = '1';
		}


	}
}
int main()
{
	BiTree T;
	printf("��������L:\n");
	T = CreateBiTree();
	printf("\n�������: ");
	PreOrder(T);
	printf("\n�������: ");
	InOrder(T);
	printf("\n�������: ");
	Postorder(T);
	return 1;
}
