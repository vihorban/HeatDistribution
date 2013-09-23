#include "graphics.h"
#include "elem.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <algorithm>

int WindW, WindH;
int type;
int virtualtime=0;
int starttime;
Point startpoint;
bool started;//есть точечный источник тепла
WindowPosit OldValue;

bool showelements=false;//показывать элементы
bool showpoints=false;//Показывать узлы
bool behavior=false;//Тестинг
bool fullscreen=false;//Fullscreen=)
bool pause=false;
bool countnextvalue=false;
bool working=true;
bool heating=false;

Region Reg;
Nodes Nod;
Elements Elem,DrawElem;

void glWrite(double x, double y, int *font,const char text[256], int kls)
{
    int i;
    glRasterPos2d(x, y);
    for (i=0; i<kls; i++)
            glutBitmapCharacter(font, (int)text[i]);
}

void write_text(double R, double G, double B, double x, double y,const char str[255])
{
    glColor3d(R,G,B);
    glWrite(x, y, (int*)GLUT_BITMAP_TIMES_ROMAN_10, str, strlen(str));
}

double dist(Point a,Point b)
{
	return sqrt(double((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-BORDERW, PIXELSW+BORDERW, -BORDERH, PIXELSH+BORDERH);
	glMatrixMode(GL_MODELVIEW);
	WindW = width;
	WindH = height;
}

void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_POINT_SMOOTH);
	//DrawElem.draw(showelements);
	Elem.draw(showelements);
	Reg.draw();
	if(showpoints) Nod.draw();
	glFlush();  
	glutSwapBuffers();
}

void OnMouse(int x, int y)
{
}

void timf(int value)
{
	if(!pause&&value==int(FPS*DELAY))
	{
		cout<<virtualtime<<"\t";
		DrawElem=Elem;
		virtualtime++;
		countnextvalue=true;
	}
	glutPostRedisplay();
	if(pause)
		glutTimerFunc(1000/FPS, timf,  value);
	else if(value==int(FPS*DELAY))
		glutTimerFunc(1000/FPS, timf,  0);
	else
		glutTimerFunc(1000/FPS, timf,  value+1);
}

void OnKeyboardEvent(unsigned char keyCode, int x, int y)
{
	switch(keyCode)
	{
		case 'f': 
			{
				fullscreen = !fullscreen;
				if(fullscreen)
				{
					OldValue.WindowHeight=glutGet(GLUT_WINDOW_HEIGHT);
					OldValue.WindowWidth=glutGet(GLUT_WINDOW_WIDTH);
					OldValue.WindowX=glutGet(GLUT_WINDOW_X)-8;
					OldValue.WindowY=glutGet(GLUT_WINDOW_Y)-30;
					glutFullScreen();
				}
				else
				{
					glutPositionWindow(OldValue.WindowX,OldValue.WindowY);
					glutReshapeWindow(OldValue.WindowWidth, OldValue.WindowHeight);
				}
				break;
			}
		case 'g': 
			{
				break;
			}
		case 'w': 
			{
				break;
			}
		case 'e': 
			{
				break;
			}
		case 'm': 
			{
				break;
			}
		case 'h': 
			{
				break;
			}
		case 'd':
			{
				break;
			}
		case 'r':
			{
				break;
			}
		case 's':
			{
			}
		case 't':
			{
				break;
			}
		case Tab:
			{
				break;
			}
		case 'v':
			{
				break;
			}
		case '1': 
			{
				showelements=!showelements;
				break;
			}
		case '2': 
			{
				showpoints=!showpoints;
				break;
			}
		case '3': 
			{
				behavior=!behavior;
				break;
			}
		case '4': 
			{
				break;
			}
		case '5': 
			{
				break;
			}
		case '6': 
			{
				break;
			}
		case '7': 
			{
				break;
			}
		case '+': 
			{
				break;			
			}
		case '-': 
			{
				break;
			}
		case ' ': 
			{
				pause=!pause;
				break;
			}
		case Enter:
			{
				break;
			}
		case Del:
			{
				break;
			}
		case Backspace:
			{
				break;
			}
		case Esc:
			{
				working=false;
				exit(0);
				break;
			}
	}
}

void OnMouseButton(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		if(!started)
		{
			starttime=virtualtime;
			startpoint=Point(PixelToCoordX(x),PixelToCoordY(y));
			//cout<<"("<<PixelToCoordX(x)<<", "<<PixelToCoordY(y)<<")\t";
			started=true;
		}
	}
	if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
	{
		if(!started)
		{
			starttime=virtualtime;
			startpoint=Point(PixelToCoordX(x),PixelToCoordY(y));
			//cout<<"("<<PixelToCoordX(x)<<", "<<PixelToCoordY(y)<<")\t";
			started=true;
			heating=true;
		}
	}
}

void drawPoint(Point a,double R,double G, double B,int Size)
{
	glPointSize(GLfloat(Size));
	glBegin(GL_POINTS);
	glColor3d(R,G,B);
	glVertex2d(a.x,a.y);
	glEnd();
}

void drawLine(Point a,Point b,double R,double G, double B)
{
	glColor3d(R,G,B);
	glBegin(GL_LINE_LOOP);
		glVertex2d(a.x,a.y);
		glVertex2d(b.x,b.y);
	glEnd();
}

double PixelToCoordX(double x)
{
	return x/WindW*(PIXELSW+2*BORDERW)-BORDERW;
}

double PixelToCoordY(double y)
{
	return (1-y/WindH)*(PIXELSH+2*BORDERH)-BORDERH;
}

void help()
{
}

void init(int argc, char *argv[])
{
	WindW = 800;
	WindH = 450;
	glutInit(&argc, argv);
	glutInitWindowSize(WindW, WindH);
	glutInitWindowPosition(0,0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Visualisation");
	glutMouseFunc(OnMouseButton);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutTimerFunc(1000/FPS, timf, 0);
	glutKeyboardFunc(OnKeyboardEvent);
	glutPassiveMotionFunc(OnMouse);
	glClearColor(1, 1, 1, 0);
	glEnable(GL_POINT_SMOOTH); 
	glutMainLoop();
}

void drawLine(double a,double b,double c,double d,double R,double G,double B)
{
	Point A,C;
	A.x=a;
	A.y=b;
	C.x=c;
	C.y=d;
	drawLine(A,C,R,G,B);
}

void drawPoint(double a,double b,double R,double G, double B,int Size)
{
	Point A;
	A.x=a;
	A.y=b;
	drawPoint(A,R,G,B,Size);
}

string toint(int a)
{
	string res;
	bool min=false;
	if(a<0)
		a*=-1,min=true;
	else if(a==0)
	{
		res.push_back('0');
		return res;
	}
	while(a)
	{
		res.insert(res.begin(),a%10+48);
		a/=10;
	}
	if(min)
		res.insert(res.begin(),'-');
	return res;
}

void buildelements()
{
	type=1;
	Reg.standart(type);
	Nod=Reg.buildnodes();
	Elem=Reg.buildElements(Nod);
	DrawElem=Elem;
	if(!pause) 
	{
		Elem.recount(virtualtime);
		DrawElem=Elem;
		virtualtime++;
		countnextvalue=true;
		//Elem.recount(1);
	}
	DWORD thID;
	CreateThread(NULL, NULL, ElementsBuilder, &virtualtime, NULL, &thID);
}

unsigned long __stdcall ElementsBuilder(void* pointer)
{
	while(working)
	{
		if(countnextvalue)
		{
			int Time=((int*)pointer)[0];
			Elem.recount(Time);
			countnextvalue=false;
		}
	}
	return -1;
}

int max(vector<int> data)
{
	int res=data[0];
	for(unsigned int i=0;i<data.size();i++)
		if(data[i]>res)
			res=data[i];
	return res;
}
double q(Point X,int time)
{
	if(started)
	{
		double Radius=(time-starttime)*5;
		double d=dist(X,startpoint);
		if(d>Radius)
			return 0;
		if(heating)
			return (Radius-d)*(-2);
		return (Radius-d)*2;
	}
	return 0;
}

double bordercond(Point X, Point Y, int time)
{
	Point Med((X.x+Y.x)/2,(X.y+Y.y)/2);
	Point Null(PIXELSW/2,PIXELSH/2);
	double d=dist(Med,Null)/dist(Point(0,0),Null)*100;
	if(PIXELSW/2<X.x)
		d=-d;
	return d;
}

double bordercond(int i,int j)
{
	double med=(NUMOFROWS+NUMOFCOLS)/2;
	return ((i+j)/med-0.65)*100;
}