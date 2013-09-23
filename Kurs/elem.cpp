#include <ctime>
#include <fstream>
#include "elem.h"
#include "matrix.h"
Region::Region():typ(0),numofcols(NUMOFCOLS),numofrows(NUMOFROWS){}
void Region::init(int type, vector<double> params_)
{
	typ=type;
	params=params_;
	Point LeftDown(params[0],params[1]);
	Point LeftUp(params[2],params[3]);
	Point RightUp(params[4],params[5]);
	Point RightDown(params[6],params[7]);
	modparams.push_back(LeftDown);
	modparams.push_back(LeftUp);
	modparams.push_back(RightUp);
	modparams.push_back(RightDown);
}
void Region::init(int type, vector<Point> modparams_)
{
	typ=type;
	modparams=modparams_;
	params.push_back(modparams[0].x);
	params.push_back(modparams[0].y);
	params.push_back(modparams[1].x);
	params.push_back(modparams[1].y);
	params.push_back(modparams[2].x);
	params.push_back(modparams[2].y);
	params.push_back(modparams[3].x);
	params.push_back(modparams[3].y);
}
string Region::Type()
{
	if(typ==1) return string("Rectangle");
	return string("Not defined");
}
void Region::draw()
{
	if(typ==1)
	{
		Point LeftDown(params[0],params[1]);
		Point LeftUp(params[2],params[3]);
		Point RightUp(params[4],params[5]);
		Point RigthDown(params[6],params[7]);
		drawLine(LeftDown,LeftUp,0,1,1);
		drawLine(LeftUp,RightUp,0,1,1);
		drawLine(RightUp,RigthDown,0,1,1);
		drawLine(RigthDown,LeftDown,0,1,1);
	}
}
void Region::standart(int type)
{
	if(type==1)
	{
		vector<double> par;
		par.push_back(0);
		par.push_back(0);
		par.push_back(0);
		par.push_back(PIXELSH);
		par.push_back(PIXELSW);
		par.push_back(PIXELSH);
		par.push_back(PIXELSW);
		par.push_back(0);
		init(type,par);
	}
}
Nodes::Nodes(){}
Nodes::Nodes(vector<Point> _Node,vector<double> _temp):Node(_Node),temp(_temp){}
void Nodes::push_back(Point _Node, double _temp=0)
{
	Node.push_back(_Node);
	temp.push_back(_temp);
}
double Nodes::temperature(int index)
{
	return temp[index];
}
Point Nodes::node(int index)
{
	return Node[index];
}
void Nodes::draw()
{
	for(unsigned int i=0;i<Node.size();i++)
		drawPoint(Node[i],100/255.0,67/255.0,33/255.0,2);
}
Triangle::Triangle(){}
Triangle::Triangle(Point _X, Point _Y, Point _Z, double tX, double tY, double tZ):X(_X),Xt(tX),Y(_Y),Yt(tY),Z(_Z),Zt(tZ)
{
	countcoef();
}
Triangle::Triangle(Nodes& Base, int _X, int _Y, int _Z):X(Base.node(_X)),Xt(Base.temperature(_X)),Y(Base.node(_Y)),Yt(Base.temperature(_Y)),Z(Base.node(_Z)),Zt(Base.temperature(_Z))
{
	countcoef();
}
void Triangle::drawtriangle()
{
	drawLine(X,Y);
	drawLine(Z,Y);
	drawLine(X,Z);
}
vector<Point> Triangle::TriPoints()
{
	vector<Point> Result;
	Result.push_back(X);
	Result.push_back(Y);
	Result.push_back(Z);
	return Result;
}
void Triangle::countcoef()
{
	xmax=X.x;
	xmin=X.x;
	if(Y.x>X.x)
		xmax=Y.x;
	else
		xmin=Y.x;
	if(Z.x>xmax)
		xmax=Z.x;
	if(Z.x<xmin)
		xmin=Z.x;
	ymax=X.y;
	ymin=X.y;
	if(Y.y>X.y)
		ymax=Y.y;
	else
		ymin=Y.y;
	if(Z.y>ymax)
		ymax=Z.y;
	if(Z.y<ymin)
		ymin=Z.y;
	Det=square()*2;
	a=((Y.x*Z.y-Z.x*Y.y)*Xt+(Z.x*X.y-Z.y*X.x)*Yt+(X.x*Y.y-X.y*Y.x)*Zt)/Det;
	b=((Y.y-Z.y)*Xt+(Z.y-X.y)*Yt+(X.y-Y.y)*Zt)/Det;
	c=((Z.x-Y.x)*Xt+(X.x-Z.x)*Yt+(Y.x-X.x)*Zt)/Det;
}
void Triangle::recounttemp()
{
	a=((Y.x*Z.y-Z.x*Y.y)*Xt+(Z.x*X.y-Z.y*X.x)*Yt+(X.x*Y.y-X.y*Y.x)*Zt)/Det;
	b=((Y.y-Z.y)*Xt+(Z.y-X.y)*Yt+(X.y-Y.y)*Zt)/Det;
	c=((Z.x-Y.x)*Xt+(X.x-Z.x)*Yt+(Y.x-X.x)*Zt)/Det;
}
double Triangle::square()
{
	return ((Y.x*Z.y-Z.x*Y.y)+(Z.x*X.y-Z.y*X.x)+(X.x*Y.y-X.y*Y.x))/2;
}
double Triangle::temperature(double Ax, double Ay)
{
	return a+b*Ax+c*Ay;
}
double Triangle::temperature(Point A)
{
	return temperature(A.x,A.y);
}
bool Triangle::isintriag(double Ax, double Ay)
{
	double m,n,p;
	m=(X.x-Ax)*(Y.y-X.y)-(Y.x-X.x)*(X.y-Ay);
	n=(Y.x-Ax)*(Z.y-Y.y)-(Z.x-Y.x)*(Y.y-Ay);
	p=(Z.x-Ax)*(X.y-Z.y)-(X.x-Z.x)*(Z.y-Ay);
	return ((m >= 0 && n >= 0 && p >= 0) || (m <= 0 && n <= 0 && p <= 0));
}
bool Triangle::isintriag(Point A)
{
	return isintriag(A.x,A.y);
}
void Triangle::drawtemp()
{
	int xbegin,xend,ybegin,yend;
	xbegin=(int)floor(xmin/DETALISATION);
	xbegin*=DETALISATION;
	xbegin+=DETALISATION/2;
	xend=(int)ceil(xmax/DETALISATION);
	xend*=DETALISATION;
	xend-=DETALISATION/2;
	ybegin=(int)floor(ymin/DETALISATION);
	ybegin*=DETALISATION;
	ybegin+=DETALISATION/2;
	yend=(int)ceil(ymax/DETALISATION);
	yend*=DETALISATION;
	yend-=DETALISATION/2;
	for(int i=xbegin;i<=xend;i+=DETALISATION)
		for(int j=ybegin;j<=yend;j+=DETALISATION)
			if(isintriag(i,j))
			{
				double t=temperature(i,j)/100,b,r,g;
				if(t>1) t=1;
				if(t<-1) t=-1;
				if(t>=0)
					r=1,b=1-t,g=1-t;
				else
					r=1+t,b=1,g=1+t;
				glColor3d(r,g,b);
				glBegin(GL_QUADS);
				glVertex2i(i-DETALISATION/2,j-DETALISATION/2);
				glVertex2i(i-DETALISATION/2,j+DETALISATION/2);
				glVertex2i(i+DETALISATION/2,j+DETALISATION/2);
				glVertex2i(i+DETALISATION/2,j-DETALISATION/2);
				glEnd();
			}
}
Elements::Elements():numofnods(0){}
Elements::Elements(int _numofnods):numofnods(_numofnods){}
void Elements::push_back(Triangle data,Element helpdata)
{
	Set.push_back(data);
	Data.push_back(helpdata);
	if(helpdata.maxint()>numofnods)
		numofnods=helpdata.maxint();
}
void Elements::draw(bool flag=false)
{
	for(unsigned int i=0;i<Set.size();i++)
	{
		Set[i].drawtemp();
		if(flag) Set[i].drawtriangle();
	}
}
Nodes Region::buildnodes()
{
	Nodes Result;
	srand(unsigned(time(0)));
	if(typ==1)
	{
		double steph=double(PIXELSH)/numofrows,stepw=double(PIXELSW)/numofcols;
		if(numofrows<=numofcols)
		{
			for(int i=0;i<=numofcols;i++)
				for(int j=0;j<=numofrows;j++)
					//Result.push_back(Point(stepw*i,steph*j),sqrt(stepw*i*stepw*i+steph*j*steph*j)/PIXELSH*50-50);
					//Result.push_back(Point(stepw*i,steph*j),double(rand())/RAND_MAX*200-100);
					Result.push_back(Point(stepw*i,steph*j),0);
		}
		else
		{
			for(int j=0;j<=numofrows;j++)
				for(int i=0;i<=numofcols;i++)
					//Result.push_back(Point(stepw*i,steph*j),sqrt(stepw*i*stepw*i+steph*j*steph*j)/PIXELSH*50-50);
					//Result.push_back(Point(stepw*i,steph*j),double(rand())/RAND_MAX*200-100);
					Result.push_back(Point(stepw*i,steph*j),0);
		}
	}
	return Result;
}
Elements Region::buildElements(Nodes& Base)
{
	Elements Result;
	if(typ==1)
	{
		if(numofrows<=numofcols)
		{
			for(int i=0;i<numofcols;i++)
				for(int j=0;j<numofrows;j++)
				{
					Result.push_back(Triangle(Base,i*(numofrows+1)+j,i*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j),Element(i*(numofrows+1)+j,i*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j));
					Result.push_back(Triangle(Base,i*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j),Element(i*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j));
					if(i==0&&CONDLEFT) Result.addcondition(Border(true,j,j+1,Base.node(j),Base.node(j+1),ENV_TEMPLEFT));
					if(i==numofcols-1&&CONDRIGHT) Result.addcondition(Border(true,(numofcols)*(numofrows+1)+j,(numofcols)*(numofrows+1)+j+1,Base.node((numofcols)*(numofrows+1)+j),Base.node((numofcols)*(numofrows+1)+j+1),ENV_TEMPRIGHT));
					if(j==0&&CONDDOWN) Result.addcondition(Border(true,(i)*(numofrows+1)+j,(i+1)*(numofrows+1)+j,Base.node((i)*(numofrows+1)+j),Base.node((i+1)*(numofrows+1)+j),ENV_TEMPDOWN));
					if(j==numofrows-1&&CONDUP) Result.addcondition(Border(true,(i)*(numofrows+1)+j+1,(i+1)*(numofrows+1)+j+1,Base.node((i)*(numofrows+1)+j+1),Base.node((i+1)*(numofrows+1)+j+1),ENV_TEMPUP));
				}
		}
		else
		{
			for(int j=0;j<numofrows;j++)
				for(int i=0;i<numofcols;i++)
				{
					Result.push_back(Triangle(Base,j*(numofcols+1)+i,j*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i),Element(j*(numofcols+1)+i,j*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i));
					Result.push_back(Triangle(Base,j*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i),Element(j*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i));
					if(j==0&&CONDDOWN) Result.addcondition(Border(true,i,i+1,Base.node(i),Base.node(i+1),ENV_TEMPDOWN));
					if(j==numofrows-1&&CONDUP) Result.addcondition(Border(true,(numofrows)*(numofcols+1)+i,(numofrows)*(numofcols+1)+i+1,Base.node((numofrows)*(numofcols+1)+i),Base.node((numofrows)*(numofcols+1)+i+1),ENV_TEMPUP));
					if(i==0&&CONDLEFT) Result.addcondition(Border(true,(j)*(numofcols+1)+i,(j+1)*(numofcols+1)+i,Base.node((j)*(numofcols+1)+i),Base.node((j+1)*(numofcols+1)+i),ENV_TEMPLEFT));
					if(i==numofcols-1&&CONDRIGHT) Result.addcondition(Border(true,(j)*(numofcols+1)+i+1,(j+1)*(numofcols+1)+i+1,Base.node((j)*(numofcols+1)+i+1),Base.node((j+1)*(numofcols+1)+i+1),ENV_TEMPRIGHT));
				}
		}
	}
	return Result;
}
void Nodes::appeace()
{
	for(unsigned int i=0;i<temp.size();i++)
		temp[i]*=0.8;
}
void Nodes::disturb1()
{
	srand(unsigned(time(0)));
	for(unsigned int i=0;i<temp.size();i++)
		temp[i]+=double(rand())/RAND_MAX*10-5;
}
void Nodes::disturb()
{
	for(unsigned int i=0;i<temp.size();i+=6)
	{
		temp[i]+=1;
		/*if(temp[i]>=100)
			temp[i]=100;*/
	}
	for(unsigned int i=4;i<temp.size();i+=6)
	{
		temp[i]-=1;
		/*if(temp[i]<=-100)
			temp[i]=-100;*/
	}
}
Point Triangle::Posi()
{
	return X;
}
Point Triangle::Posj()
{
	return Z;
}
Point Triangle::Posk()
{
	return Y;
}
void Elements::recount(int time)
{
	vector<double> Temp(numofnods);
	double kxx=MATERIAL_COND;
	double kyy=MATERIAL_COND;
	double h=MATERIAL_EXCH;
	Matrix<double> K(numofnods);
	for(int i=0;i<numofnods;i++)
		K[i][i]=0;
	Row<double> F(numofnods);
	Row<double> Fi(3);
	Matrix<double> Ki(3);
	for(unsigned int i=0;i<Set.size();i++)
	{
		double A=Set[i].square();
		Ki=kxx/4/A*Set[i].B()+kyy/4/A*Set[i].C();
		Fi=Set[i].Q(time);
		for(int s=0;s<3;s++)
		{
			F[Data[i].index(s)]+=Fi[s];
			for(int p=0;p<3;p++)
				K[Data[i].index(s)][Data[i].index(p)]+=Ki[s][p];
		}
	}
	for(unsigned int i=0;i<Conditions.size();i++)
	{
		Ki=Conditions[i].L()*h;
		Fi=Conditions[i].R();
		if(Conditions[i].type()) Fi*=h;
		for(int s=0;s<2;s++)
		{
			F[Conditions[i].index(s)]+=Fi[s];
			for(int p=0;p<2;p++)
				K[Conditions[i].index(s)][Conditions[i].index(p)]+=Ki[s][p];
		}
	}
	int diag=(min(NUMOFCOLS,NUMOFROWS)+1)*2+1;
	DiagonalSystem<double> Solution(K,F,diag);
	Solution.Gauss();
	Temp=Solution.solutuion().ToVector();
	if(time==0)
	{
		ofstream file;
		file.open("matrixoutput.txt");
		file<<K<<"Free vector:\n"<<F;
		file<<"Solution:\n";
		file<<Solution.solutuion();
		file.close();
		/*DWORD thID;
		DSystem TempSystem(K,F);
		CreateThread(NULL, NULL, FileWriter, &TempSystem, NULL, &thID);*/
	}
	for(unsigned int i=0;i<Set.size();i++)
	{
		Set[i].settemp(Temp[Data[i].i()],Temp[Data[i].k()],Temp[Data[i].j()]);
		Set[i].recounttemp();
	}
}
int Elements::countnods()
{
	return numofnods;
}
int Elements::counttriangles()
{
	return Set.size();
}
Element::Element():I(0),J(0),K(0){}
Element::Element(int i,int k, int j):I(i),J(j),K(k){}
int Element::maxint()
{
	return max(max(J,K),I)+1;
}
int Element::i()
{
	return I;
}
int Element::j()
{
	return J;
}
int Element::k()
{
	return K;
}
void Triangle::settemp(double tX, double tY, double tZ)
{
	Xt=tX,Yt=tY,Zt=tZ;
}
double Triangle::_b(int i)
{
	if(i==0) return Z.y-Y.y;
	else if(i==1) return Y.y-X.y;
	else return X.y-Z.y;
}
double Triangle::_c(int i)
{
	if(i==0) return Y.x-Z.x;
	else if(i==1) return X.x-Y.x;
	else return Z.x-X.x;
}
Matrix<double> Triangle::B()
{
	Matrix<double> Result(3);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			Result[i][j]=_b(i)*_b(j);
	return Result;
}
Matrix<double> Triangle::C()
{
	Matrix<double> Result(3);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			Result[i][j]=_c(i)*_c(j);
	return Result;
}
Row<double> Triangle::Q(int time)
{
	Row<double> Result(3);
	Result[0]=q(X,time)/3;
	Result[1]=q(Z,time)/3;
	Result[2]=q(Y,time)/3;
	return Result;
}
int Element::index(int i)
{
	if(i==0)
		return I;
	if(i==1)
		return J;
	return K;
}
Border::Border():type_(0),i(0),j(0),param(0){}
Border::Border(bool _type,int _i,int _j, Point _X, Point _Y, double _param):type_(_type),i(_i),j(_j), X(_X), Y(_Y), param(_param){}
double Border::l()
{
	return dist(X,Y);
}
Matrix<double> Border::L()
{
	Matrix<double> Result(2);
	if(type_==1)
	{
		Result[0][0]=2;
		Result[0][1]=1;
		Result[1][0]=1;
		Result[1][1]=2;
	}
	else
	{
		Result[0][0]=0;
		Result[1][1]=0;
	}
	return Result*(l()/6);
}
Row<double> Border::R()
{
	Row<double> Result(2);
	Result[1]=1;
	Result[0]=1;
	Result*=param*(l()/2);
	return Result;
}
int Border::index(int _i)
{
	if(_i==0)
		return i;
	return j;
}
bool Border::type()
{
	return type_;
}
void Elements::addcondition(Border data)
{
	Conditions.push_back(data);
}

unsigned long __stdcall FileWriter(void* pointer)
{
	DSystem Temp=((DSystem*)pointer)[0];
	ofstream file;
	file.open("matrixoutput.txt");
	file<<Temp.matrix()<<"Free vector:\n"<<Temp.freevector();
	file<<"Solution:\n";
	DiagonalSystem<double> New(Temp.matrix(),Temp.freevector(),(min(NUMOFCOLS,NUMOFROWS)+1)*2+1);
	New.Gauss();
	file<<New.solutuion();
	/*Temp.Gauss();
	file<<"Checking solution:\n";
	file<<Temp.solutuion()-New.solutuion();*/
	file.close();
	return 0;
}