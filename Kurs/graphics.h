#pragma once
#include <vector>
#include <queue>
#include <string>
#include <set>
#include "GL\GLUT.H"
using namespace std;

#define Esc 27
#define Tab 9
#define Del 127
#define Enter 13
#define Backspace 8
#define PI 3.141592653897323
#define INF 1000000000
#define EPS 0.01
#define FPS 25
#define PIXELSW 1600
#define PIXELSH 904
#define BORDERW 2
#define BORDERH 2
#define DELAY 1
struct Point
{
	double x;
	double y;
	Point():x(0),y(0){}
	Point(double _x,double _y):x(_x),y(_y){}
};

struct WindowPosit
{
	int WindowWidth;
	int WindowHeight;
	int WindowX;
	int WindowY;
	WindowPosit():WindowWidth(800),WindowHeight(450),WindowX(0),WindowY(0){}
};

void glWrite(double x, double y, int *font,const char text[256], int kls);
void write_text(double R, double G, double B, double x, double y, const char str[255]);
void OnMouseButton(int button, int state, int x, int y);
void OnKeyboardEvent(unsigned char keyCode, int x, int y);
void timf(int value);
void OnMouse(int x, int y);
void Draw(void);
void Reshape(int width, int height);
void drawPoint(Point a,double R=0,double G=0, double B=0,int Size=1);
void drawPoint(double a,double b,double R=0,double G=0, double B=0,int Size=1);
void drawLine(Point a,Point b,double R=0,double G=1, double B=0);
void drawLine(double a,double b,double c,double d,double R=1,double G=0, double B=0);
double PixelToCoordX(double x);
double PixelToCoordY(double y);
void help();
double dist(Point a,Point b);
void init(int argc, char *argv[]);
string toint(int);
int max(vector<int> data);

void buildelements();
double q(Point X,int time);
double bordercond(Point X, Point Y, int time);
double bordercond(int i,int j);
unsigned long __stdcall ElementsBuilder(void* pointer);