
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

/********������������********/
#define PR_Box printf("��")
#define PR_Gold printf("��")
#define PR_Ag printf("��")
#define PR_FBird printf("��")
#define PR_DBird printf("��")
#define PR_Land printf("�שש�")
#define PR_Bg_TL printf("�X")
#define PR_Bg_TR printf("�[")
#define PR_Bg_DL printf("�^")
#define PR_Bg_DR printf("�a")
#define PR_Bg_X printf("�T")
#define PR_Bg_Y printf("�U")
#define PR_Blank printf(" ");
int Grade = 1, C_Gold = 0, C_Ag = 0, Score = 0, Delay_time = 1000,Max_blank=10,Distance=18;
//Grade ��Ϸ�ȼ� 
//Score ���� 
//Max_blank ���������̴�֮��������� 
//Distance ���������̴�֮��ľ���
struct Birds//С��Ľṹ��
{
int x, y;//С���λ��
int condition;//�˱���δ��
};

Birds *Bird = (Birds*)malloc(sizeof(Birds));//��С��ָ�����ռ�

struct Bg//�̴ѵĽṹ��--ѭ��˫������
{
int x, y;//���̴ѵ����½�ש�������
int l_blank;//���������̴�֮��ľ���
int reward[9];
Bg *pri;//ǰָ��-ָ��ǰһ�����
Bg *next;//��ָ��-ָ���һ�����
};

Bg *Bg1 = new Bg[sizeof(Bg)];//��һ���̴ѽ�����ó�ȫ�ֱ���

void Position(int x, int y)//������ƶ���X,Y���괦
{
COORD pos = {x,y};
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);                                                             
SetConsoleCursorPosition(Out, pos);
}

void CreatBird()//����С��
{
Bird->x=41;//С�������
Bird->y=10;
Bird->condition =0;
}

void CreatBg()//�������ݽṹΪѭ��˫��������̴�
{
Bg *Bg2 = (Bg*)malloc(sizeof(Bg));


Bg1->x=90;Bg1->y =8;
Bg2->x=Bg1->x+Distance;Bg2->y =9;


Bg1->l_blank =Max_blank-Grade;
Bg2->l_blank =Max_blank-Grade;


Bg1->next=Bg2;                        //Bg1Ϊѭ������ı�ͷ��㣬��Bg2Ϊ���һ������ڵ� 
Bg1->pri=Bg2;
Bg2->next=Bg1;
Bg2->pri=Bg1;
}

void InsertBg(Bg *p)//����һ�������뵽������֮��ѭ��˫������Ĳ���
{int temp;
Bg *Bgs = (Bg*)malloc(sizeof(Bg));
Bgs->x=p->pri->x+Distance;
Bgs->l_blank =Max_blank-Grade;

srand((int)time(0));//��ϵͳʱ����Ϊ���������������
temp=rand();//���������

if(temp%2==0)//�������%2==0ʱ���̴ѿ������ƶ� ���ȿ��ܵ�ѡ�������϶��������ƶ� 
{ if((temp%4+p->pri->y+Max_blank-Grade)<21)//����Ƿ���������ƶ��Ŀ�����
Bgs->y=p->pri->y+temp%4;//�����������ƶ�temp%4����λ
else
Bgs->y=p->pri->y;//���ޣ��򲻶�
}
else//��֮��Ȼ
{
if((p->pri->y-temp%4)>2)
Bgs->y=p->pri->y-temp%4;
else
Bgs->y=p->pri->y;
}


Bgs->pri=p->pri;//ѭ������ָ��
Bgs->next =p;
p->pri->next=Bgs;
p->pri =Bgs;
}

void Check_Bg(Bg *q)//����Ƿ����̴ѳ�����Ļ�����г��������ƶ�����Ļ�Ҳࡣ
{ Bg *p=q;int i=0,temp;
while(++i<=5)//ע���̴�ֻ��5����������ѭ���ƶ���
{ if(p->x>-4)//�����̴�δ����            
p=p->next;
else       //�������ӳ��� 
{ srand((int)time(0));
temp=rand();
if(temp%2==0)//++
{ if((temp%4+p->y+Max_blank-Grade)<21)
p->y=p->y+temp%4;
else
p->y=p->y;

p->x=p->pri->x+Distance;//���̴��ƶ���ǰһ�����Ҳ�+Distance�ĵ�λ������ѭ������������Ӿ͵�������棩 
p->l_blank=Max_blank-Grade;//�������������̴ѵľ���
}
else//��֮��Ȼ
{
if((p->y-temp%4)>2)
p->y=p->y-temp%4;
else
p->y=p->y;

p->x=p->pri->x+Distance;
p->l_blank=Max_blank-Grade;
}
}

}

}
void Loop_Bg(Bg *q)//�̴ѵ���ѭ���ƶ�
{
Bg *p=q;int i=0;
while(++i<=5)
{p->x=p->x-1;        //���ƶ���һ������ 
 
if(Bird->x==p->x)//ÿ����һ���̴ѣ���һ��
{Score+=1;
if(Score%4==0&&Grade<4)//�̴�
Grade++;
}

p=p->next ;          //���ƶ����ĸ����ӣ���ѭ������ 

}
}

void Prt_Bg(Bg *q)//���̴�----������Ĵ���
{ Bg *p=q;int i=0,k,j;
while(++i<=5)
{ 
if(p->x>0&&p->x<=78)
{ 
for(k=2;k<p->y;k++)//�������̴��ϰ벿��
{ Position(p->x+1,k);
PR_Box;PR_Box;PR_Blank;//����������ӣ�����ո����ԭ����Ӱ
}
Position(p->x,p->y);//�������̴��°벿��
PR_Box;PR_Box;PR_Box;PR_Blank;//����������ӣ�����ո����ԭ����Ӱ

Position(p->x,p->y+p->l_blank+1);//�������̴��ϰ벿�֣�+1��Ϊ��ʹ������֮��ľ���Ϊl_blank 
PR_Box;PR_Box;PR_Box;PR_Blank;//����������ӣ�����ո����ԭ����Ӱ
k=k+p->l_blank+2;   //+2ʹ������֮�����Ϊl_blank 
for(k;k<=22;k++)//�������̴��°벿��
{Position(p->x+1,k);
PR_Box;PR_Box;PR_Blank;//����������ӣ�����ո����ԭ����Ӱ
}
Position(p->x,23);//������µ��� 
for(k=1;k<Distance/3-2;k++)
PR_Land;
}
p=p->next;


if(p->x==0)             //�������ߵ��������ʱ���ÿո��������,�����������⡣��Ϊһ��PR_Boxռ���񣬶�һ��PR_Blankֻռһ������Ҫ��˫���Ŀո������ 
{ 
for(j=2;j<p->y;j++)
{
Position(p->x+1,j);
PR_Blank;PR_Blank;
}
Position(p->x,p->y);   // x+1
PR_Blank;PR_Blank;PR_Blank;
Position(p->x,p->y+Max_blank-Grade+1);
PR_Blank;PR_Blank;PR_Blank;
j=j+Max_blank-Grade+2;
for(j;j<=22;j++)
{Position(p->x+1,j);
PR_Blank;PR_Blank;
}
}
}


}






void PrtBg()//������������
{ int i;
Position(1,1);PR_Bg_TL;
Position(79,1);PR_Bg_TR;
Position(1,24);PR_Bg_DL;
Position(79,24);PR_Bg_DR;
for(i=3;i<=78;i+=2)
{ Position(i,1);PR_Bg_X;
Position(i,24);PR_Bg_X;
}
/*for(i=2;i<=23;i++)
{ Position(1,i);PR_Bg_Y;printf("%d",i-1);
Position(79,i);PR_Bg_Y;
}*/ 
//����ע���е����ѭ���ṹ��ʵ�����ô�����Ϊ��������������ѭ���˶�������������֡�Bg_Y�ᱻ�ڵ�ס 
}

void PrtBird()//����
{ Position(Bird->x,Bird->y-1);//���ԭ����Ļ������� ��ԭ����ΪС��������䣬�����Ҫ�Ƚ�y-1���λ����� 
PR_Blank;
Position(Bird->x,Bird->y);//������
PR_FBird;
Position(35,25);  //��ȥ��Position(38,2); 
printf("Score:%d",Score);//����÷�
}

int CheckYN(Bg *q)//����Ƿ�ײ��
{ Bg *p=q;int i=0;
while(++i<=5)
{ if(Bird->y>23)//���Ƿ����
return 0;
if(Bird->x==p->x&&Bird->y<=p->y)//�Ƿ�ײ�����̴����
return 0;
if(Bird->x>=p->x&&Bird->x<=p->x+6&&Bird->y==p->y)//�Ƿ�ײ�����̴��²ࡣ��ȥ�õ���if((Bird->x==p->x||Bird->x==p->x+1||Bird->x==p->x+2)&&Bird->y==p->y)
return 0;
if(Bird->x==p->x&&Bird->y>p->y+p->l_blank+1)//�Ƿ�ײ�����̴����
return 0;
if(Bird->x>=p->x&&Bird->x<=p->x+6&&Bird->y==p->y+p->l_blank+1)//�Ƿ�ײ�����̴��ϲ�
return 0;
p=p->next;
}
return 1;
}

void Prtfirst()
{
int i;

for(i=0;i<5;i++)
printf("\n");
printf("\n��ʼ��Ϸ��Ŷ������\n");
for(i=0;i<5;i++)
printf("\n");

system("pause");
system("cls");
Position(0,0);
}
//�ú���ԭ�������һ��  i=0;while(i++<40*25) PR_Blank; 


int main()
{int i=0;char ch;
Prtfirst();//��ʼ��Ļ

PrtBg();//���������ߵĿ��
CreatBg();//����ѭ��˫�������̴�
InsertBg(Bg1);//��ѭ��˫�������в���һ���̴ѽ��
InsertBg(Bg1);//��ѭ��˫�������в���һ���̴ѽ��
InsertBg(Bg1);//��ѭ��˫�������в���һ���̴ѽ��
CreatBird();//����С��
while(1)
{
if(!CheckYN(Bg1))//������Ƿ�����
break;//�����ڣ����˳�
Check_Bg(Bg1);//����Ƿ����̴�X����<0
Prt_Bg(Bg1);//�������̴�
PrtBird();//��С��
Loop_Bg(Bg1);//�����̴ѵ���ѭ��
Bird->y=Bird->y+1;
if(GetAsyncKeyState(VK_UP))//����Ƿ��а���
{ Position(Bird->x,Bird->y-1);
PR_Blank;//����Ļ�����ԭС��
Bird->y=Bird->y-4;//���λ������4������
}
 Sleep(100);

}
Position(38,10);
printf("You Lost!");
Position(1,25);
system("pause");



}
// 1 2 3 4 5 6 7 8 10 15 20 25 30 35 38
//�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T
//1 ���� ����
//2 ���� ����
//3 ���� ����
//4 ���� ����
//5 ���� ����
//6 ���� ����
//7 ������ ����
//8 ����
//9 ����
//10 �� ������
//11
//12 ������
//13 ����
//14 ����
//15 ���� ������
//16 ���� ����
//17 ���� �� ����
//18 ���� ����
//19 ���� ����
//20 ���� ����
//21 ���� ����
//22�ששөששөששөששөששөששөששөששөששөששөששөששө�
//�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T
