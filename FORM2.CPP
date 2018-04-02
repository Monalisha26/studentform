#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<dir.h>
#include<stdlib.h>
#include<bios.h>
union REGS in,out;
typedef struct Student
{
int roll;
char name[20];
int marks;
}St;
void form();
void display();
void graph();
 int callmouse()
 {
 in.x.ax=1;
 int86(51,&in,&out);
 return 1;
 }
 void mouseposi(int &xpos,int &ypos,int &click)
 {
 in.x.ax=3;
 int86(51,&in,&out);
 click=out.x.bx;
 xpos=out.x.cx;
 ypos=out.x.dx;
  }
 int mousehide()
 {
 in.x.ax=2;
 int86(51,&in,&out);
 return 1;
 }
 void setposi(int &xpos,int &ypos)
 {
 in.x.ax=4;
 in.x.cx=xpos;
 in.x.dx=ypos;
 int86(51,&in,&out);
 }
 int main()
 {
 int x,y,cl,a,b,midx,midy,i,flag=0;
 clrscr();
 int g=DETECT,m,n,key;
 initgraph(&g,&m,"C:\\YOGSOFT\\TC\\BIN");
 midx=getmaxx()/2;
 midy=getmaxy()/2;
 while(flag!=1)
 {
 cl=0;
 cleardevice();
 setcolor(RED);
 rectangle(midx-85,midy-60,midx+130,midy+113);
 rectangle(midx-85,midy-103,midx+130,midy-60);
 setcolor(YELLOW);
 rectangle(midx-75,midy-50,midx+120,midy-17);
 rectangle(midx-75,midy-10,midx+120,midy+23);
 rectangle(midx-75,midy+30,midx+120,midy+63);
 rectangle(midx-75,midy+70,midx+120,midy+103);
 outtextxy(midx-70,midy-42,"1.STUDENT DATA ENTRY");
 outtextxy(midx-70,midy-3,"2.STUDENT DATA DISPLAY");
 outtextxy(midx-70,midy+37,"3.STUDENT GRAPH DISPLAY");
 outtextxy(midx-70,midy+77,"4.EXIT");
 setcolor(BLUE);
 settextstyle(SMALL_FONT,HORIZ_DIR,10);
settextjustify(CENTER_TEXT,CENTER_TEXT);
 outtextxy(midx,midy-90,"MENU");
 a=100;
 b=400;
 setposi(a,b);
 callmouse();
 do
 {cl=0;
 do
 {
 mouseposi(x,y,cl);
 }while(cl!=1);
 }while((!(((x>=midx-75)&&(x<=midx+120))&&((y>=midy-50)&&(y<=midy+103)))));
 if(((x>=midx-75)&&(x<=midx+95))&&((y>=midy-50)&&(y<=midy-17)))
 form();
 if(((x>=midx-75)&&(x<=midx+120))&&((y>=midy-10)&&(y<=midy+23)))
 display();
 if(((x>=midx-75)&&(x<=midx+120))&&((y>=midy+30)&&(y<=midy+63)))
 graph();
if(((x>=midx-75)&&(x<=midx+120))&&((y>=midy+70)&&(y<=midy+103)))
 flag=1;
 }
 closegraph();
  }
void form()
   {
  FILE *fp;
  int gd,gm,midx,midy,a,b,cl,x,y,key;
  a=100;
  b=400;
  gd=DETECT;
  char li[100];
  St s;
  initgraph(&gd,&gm,"C:\\YOGISOFT\\TC\\BIN");
  midx=getmaxx()/2;
  midy=getmaxy()/2;
  fp=fopen("st.dat","ab");
  setcolor(GREEN);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  settextstyle(TRIPLEX_FONT,0,3);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  outtextxy((getmaxx()/2)-30,30,"Student Data Form");
  line(10,50,getmaxx()-10,50);
  gotoxy(10,7);
  printf("STUDENT NAME:");
  gotoxy(10,14);
  printf("STUDENT ROLL:");
  gotoxy(10,21);
  printf("STUDENT MARKS:");
  setcolor(BLUE);
  rectangle(midx - 60, midy + (midy/2) , midx + 50, midy + (midy/2) + 35);
  setcolor(YELLOW);
  rectangle(midx-140,(midy/2)-30,midx-10,(midy/2)-5);
  rectangle(midx-140,(midy)-40,midx-10,(midy)-15);
  rectangle(midx-135,(midy)+(midy/2)-45,midx-10,midy+(midy/2)-20);
  settextstyle(TRIPLEX_FONT,0,1);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  outtextxy(midx - 20, midy + (midy/2)+15 ,"Submit");
  gotoxy(25,7);
  scanf("%s",&s.name);
  gotoxy(25,14);
  scanf("%d",&s.roll);
  gotoxy(25,21);
  scanf("%d",&s.marks);
  fwrite(&s,sizeof(s),1,fp);
  fclose(fp);
  setposi(a,b);
  callmouse();
  do
  {
  cl=0;
  do
  {
  mouseposi(x,y,cl);
  }while(cl!=1);
  }while((!(((x>=midx-60)&&(x<=midx+50)) && ((y>=midy+(midy/2)-20)&&(y<=midy + (midy/2)+20))))&&((key=bioskey(0))==2181));
  closegraph();
  }
void display()
  {  FILE *fp;
  char li[100];
  int gd,gm,nextline,midx;
  gd=DETECT;
  St s;
   fp=fopen("st.dat","rb");
initgraph(&gd,&gm,"C:\\YOGISOFT\\TC\\BIN");
midx=getmaxx()/2;
setcolor(YELLOW);
rectangle(10,10,getmaxx()-10,getmaxy()-10);
line(10,50,getmaxx()-10,50);
line(10,80,getmaxx()-10,80);
setcolor(LIGHTGRAY);
nextline=0;
while(fread(&s,sizeof(s),1,fp)==1)
{
sprintf(li,"%-10s            %5d                    %5d",s.name,s.roll,s.marks);
outtextxy(30,120+nextline,li);
nextline+=30;
}
fclose(fp);
settextstyle(DEFAULT_FONT,0,3);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtextxy((getmaxx()/2)-30,30,"STUDENT RECORD");
setcolor(BLUE);
settextstyle(SMALL_FONT,HORIZ_DIR,5);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtextxy(50,70,"NAME");
outtextxy(midx-70,70,"ROLL");
outtextxy(midx+50,70,"MARKS");
setcolor(RED);
line(150,50,150,getmaxy()-10);
line(300,50,300,getmaxy()-10);
getch();
closegraph();
}

void graph()
{FILE *fp;
int gd,gm,i=150,j=200;
St s;
gd=DETECT;
fp=fopen("st.dat","rb");
initgraph(&gd,&gm,"C:\\YOGISOFT\\TC\\BIN");
setcolor(GREEN);
settextstyle(TRIPLEX_FONT,0,3);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtextxy((getmaxx()/2)-30,30,"BAR GRAPH");
setcolor(RED);
line(90,410,90,50);
line(90,410,590,410);
outtextxy(65,60,"Y");
outtextxy(570,420,"X");
outtextxy(70,415,"0");
setfillstyle(HATCH_FILL,YELLOW);
while(fread(&s,sizeof(s),1,fp)==1)
{
bar(i,s.marks,j,410);
settextstyle(TRIPLEX_FONT,0,1);
outtextxy(i,420,s.name);
i+=80;
j+=80;
}
fclose(fp);
getch();
closegraph();
}
