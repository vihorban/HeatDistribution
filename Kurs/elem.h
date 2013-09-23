#pragma once
#include "matrixheader.h"
#include "graphics.h"
using namespace std;
#define NUMOFCOLS 20
#define NUMOFROWS 20
#define DETALISATION 4//must be odd
#define MATERIAL_COND 30.0
#define MATERIAL_EXCH 5.0
#define ENV_TEMPDOWN bordercond(i,j)
#define ENV_TEMPUP -50
#define ENV_TEMPLEFT bordercond(i,j)
#define ENV_TEMPRIGHT -25
#define CONDLEFT 1
#define CONDRIGHT 0
#define CONDDOWN 1
#define CONDUP 0
class Nodes;
class Triangle;
class Elements;
class Element;
class Border;
class Region
{
	int typ;//type
	vector<double> params;
	vector<Point> modparams;
	int numofcols;
	int numofrows;
public:
	Region();
	void init(int type, vector<double> params_);
	void init(int type, vector<Point> modparams_);
	void standart(int type);
	string Type();
	void draw();
	Nodes buildnodes();
	Elements buildElements(Nodes& Base);
};
class Nodes
{
	vector<Point> Node;
	vector<double> temp;
public:
	Nodes();
	Nodes(vector<Point> _Node,vector<double> _temp);
	void draw();
	void push_back(Point Node, double _temp);
	double temperature(int index);
	Point node(int index);
	void appeace();
	void disturb();
	void disturb1();
};
class Triangle
{
	Point X,Y,Z;
	double Xt,Yt,Zt;
	double a,b,c;
	double xmax,xmin,ymax,ymin;
	double Det;
public:
	Triangle();
	Triangle(Nodes& Base, int _X, int _Y, int _Z);
	Triangle(Point _X, Point _Y, Point _Z, double tX, double tY, double tZ);
	vector<Point> TriPoints();
	void countcoef();
	void settemp(double tX, double tY, double tZ);
	double temperature(Point A);
	double temperature(double Ax, double Ay);
	double square();
	bool isintriag(Point A);
	bool isintriag(double Ax, double Ay);
	void drawtriangle();
	void drawtemp();
	void recounttemp();
	Point Posi();
	Point Posj();
	Point Posk();
	double _b(int i);
	double _c(int i);
	Matrix<double> B();
	Matrix<double> C();
	Row<double> Q(int time);
};
class Elements
{
	int numofnods;
	vector<Triangle> Set;
	vector<Element> Data;
	vector<Border> Conditions;
public:
	int countnods();
	int counttriangles();
	Elements();
	Elements(int _numofnods);
	void push_back(Triangle data, Element helpdata);
	void addcondition(Border data);
	void draw(bool flag);
	void recount(int time);
};
class Element
{
	int I;
	int J;
	int K;
public:
	Element();
	Element(int i,int k, int j);
	int maxint();
	int i();
	int j();
	int k();
	int index(int i);
};
class Border
{
	bool type_;//1: h(T-TENV)	0: q
	int i;
	int j;
	Point X;
	Point Y;
	double param;
public:
	Border();
	Border(bool type,int i,int j, Point X, Point Y, double param);
	double l();
	Matrix<double> L();
	Row<double> R();
	int index(int _i);
	bool type();
};
unsigned long __stdcall FileWriter(void* pointer);