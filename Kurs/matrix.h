#pragma once
#define MAXSIZE 1000000
#include <iostream>
#include <vector>
using namespace std;

template <class Type>
class Line;

template <class Type>
class Matrix;

template <class Type>
class Row;

template <class Type>
class System;

template <class Type>
class DiagonalSystem;

template <class Type>
class Line
{
	vector<Type> data;
	int Size;
public:
	Line();
	Line(int size);
	Line(vector<Type> Ex);
	Type& operator [](int Index);
	void resize(int size);
	void resize(int size, Type val);
	int size();
	vector<Type> ToVector();
	Matrix<Type> ToMatrix();
	Type norminf();
	Type norm1();
	Line<Type> operator +=(Line<Type>& Add);
	Line<Type> operator +(Line<Type>& Add);
	Line<Type> operator -=(Line<Type>& Sub);
	Line<Type> operator -(Line<Type>& Sub);
	Line<Type> operator *=(Type Mul);
	Line<Type> operator /=(Type Div);
	Line<Type> operator /(Type Div);
	Line<Type> operator *=(Matrix<Type> Mul);
	template<class Type>
	friend ostream& operator<<(ostream& os, Line<Type>& Out); 
	template<class Type>
	friend istream& operator>>(istream& is, Line<Type>& In);
};

int kroneker(int n, int k);
template <class Type>
Type sgn(Type a);

template <class Type>
class Row
{
	vector<Type> data;
	int Size;
public:
	Row();
	Row(int size);
	Row(vector<Type> Ex);
	Type& operator [](int Index);
	void resize(int size);
	void resize(int size, Type val);
	int size();
	Type norminf();
	Type norm1();
	vector<Type> ToVector();
	Matrix<Type> ToMatrix();
	Row<Type> operator +=(Row<Type>& Add);
	Row<Type> operator +(Row<Type>& Add);
	Row<Type> operator -=(Row<Type>& Sub);
	Row<Type> operator -(Row<Type>& Sub);
	Row<Type> operator *=(Type Mul);
	Row<Type> operator /=(Type Div);
	Row<Type> operator /(Type Div);
	template<class Type>
	friend ostream& operator<<(ostream& os, Row<Type>& Out); 
	template<class Type>
	friend istream& operator>>(istream& is, Row<Type>& In);
};

template <class Type>
class Matrix
{
	vector<Line<Type>> data;
	int Height, Width;
public:
	Matrix();
	Matrix(int size);
	Matrix(int height, int width);
	Matrix(vector<Line<Type>> d);
	Matrix(vector<Row<Type>> d);
	void resize(int size);
	void resize(int height, int width);
	pair<int,int> size();
	int height();
	int width();
	Type norminf();
	Type norm1();
	Type det();
	Type condition_number();
	Matrix<Type> converse();
	Line<Type>& operator [](int Index);
	Matrix<Type> operator +=(Matrix<Type>& Add);
	Matrix<Type> operator +(Matrix<Type>& Add);
	Matrix<Type> operator -=(Matrix<Type>& Sub);
	Matrix<Type> operator -(Matrix<Type>& Sub);
	Matrix<Type> operator *=(Matrix<Type>& Mul);
	Matrix<Type> operator *(Matrix<Type>& Mul);
	Matrix<Type> operator *=(Type Mul);
	Matrix<Type> operator /=(Type Div);
	Matrix<Type> operator /(Type Div);
	Matrix<Type> transp();
	Line<Type> line(int Index);
	Row<Type> row(int Index);
	template<class Type>
	friend ostream& operator<<(ostream& os, Matrix<Type>& Out); 
	template<class Type>
	friend istream& operator>>(istream& is, Matrix<Type>& In);
};

template <class Type>
class System
{
protected:
	int Size;
	Matrix<Type> data;
	vector<Type> solve;
	vector<Type> iteration(vector<Type> approx);
	bool checkcondition(vector<Type> approx, vector<Type> oldapprox, Type epsilon);
public:
	System();
	System(int size);
	System(Matrix<Type> d, Row<Type> cond);
	System(int size, Type alpha, Type p, Type q);
	System(int size, int m);
	Matrix<Type> matrix();
	Row<Type> freevector();
	Row<Type> solutuion();
	void resize(int size);
	bool issolved();
	void Gauss();
	void Sqkor();
	void Seidel(Type epsilon);
	void solve_uptriangle();
	void solve_downtriangle();
	void Show_solve();
	void Show_solve(ostream& os);
	void Show_matrix();
	Line<Type>& operator [](int Index);
	template<class Type>
	friend ostream& show_solve(ostream& os, System<Type>& Out); 
	template<class Type>
	friend ostream& show_matrix(ostream& os, System<Type>& Out); 
	template<class Type>
	friend ostream& operator<<(ostream& os, System<Type>& Out); 
	template<class Type>
	friend istream& operator>>(istream& is, System<Type>& In);
};

template <class Type>
class DiagonalSystem:public System<Type>
{
	int diagonal;
	int myindex;
public:
	DiagonalSystem();
	DiagonalSystem(Matrix<Type> d, Row<Type> cond,int _diagonal);
	int newcoord(int i,int j);
	int oldcoord(int i,int j);
	void Gauss();
	void solve_uptriangle();
};

template<class Type>
Type norm_inf(vector<Type> data);
template<class Type>
Type norm_1(vector<Type> data);

template<class Type>
Matrix<Type> operator*(Matrix<Type>& Mul1, Type Mul2);
template<class Type>
Matrix<Type> operator*(Type Mul2, Matrix<Type>& Mul1);

template<class Type>
Line<Type> operator*(Line<Type>& Mul1, Type Mul2);
template<class Type>
Line<Type> operator*(Type Mul2, Line<Type>& Mul1);

template<class Type>
Type operator*(Line<Type> Mul1, Row<Type> Mul2);
template<class Type>
Type operator*(Row<Type> Mul1, Line<Type> Mul2);

template<class Type>
Line<Type> operator*(Line<Type> Mul1,Matrix<Type> Mul2);
template<class Type>
Row<Type> operator*(Matrix<Type> Mul1,Row<Type> Mul2);

typedef Line<int> ILine;
typedef Line<double> DLine;
typedef Row<int> IRow;
typedef Row<double> DRow;
typedef Matrix<int> IMatrix;
typedef Matrix<double> DMatrix;
typedef System<int> ISystem;
typedef System<double> DSystem;

template<class Type>
ostream& operator<<(ostream& os, Matrix<Type>& Out)
{
	for(int i=0;i<Out.Height;i++)
	{
		for(int j=0;j<Out.Width;j++)
			os<<Out.data[i][j]<<"\t";
		os<<endl;
	}
	return os;
}

template<class Type>
istream& operator>>(istream& is, Matrix<Type>& In)
{
	int height(0),width(0);
	cout<<"Enter height and widht of matrix:"<<endl;
	is>>height>>width;
	In.resize(height,width);
	cout<<"Enter items of matrix:"<<endl;
	for(int i=0;i<In.Height;i++)
	{
		for(int j=0;j<In.Width;j++)
			is>>In.data[i][j];
	}
	return is;
}

template<class Type>
Matrix<Type>::Matrix():Height(0),Width(0){}

template<class Type>
Matrix<Type>::Matrix(int height, int width):Height(height), Width(width)
{
	if(Height<0||Height>MAXSIZE)
		cout<<"Height out of range"<<endl, Height=0;
	if(Width<0||Width>MAXSIZE)
		cout<<"Width out of range"<<endl, Width=0;
	data.resize(Height);
	for(int i=0;i<Height;i++)
	{
		data[i].resize(Width);
		for(int j=0; j<Width;j++)
			data[i][j]=(i==j);
	}
}

template<class Type>
void Matrix<Type>::resize(int height, int width)
{
	Height=height, Width=width;
	if(Height<0||Height>MAXSIZE)
		cout<<"Height out of range"<<endl, Height=0;
	if(Width<0||Width>MAXSIZE)
		cout<<"Width out of range"<<endl, Width=0;
	data.resize(Height);
	for(int i=0;i<Height;i++)
	{
		data[i].resize(Width);
		for(int j=0; j<Width;j++)
			data[i][j]=(i==j);
	}
}

template<class Type>
void Matrix<Type>::resize(int size)
{
	this->resize(size,size);
}

template<class Type>
Matrix<Type>::Matrix(int Size):Height(Size), Width(Size)
{
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Height=0, Width=0;
	data.resize(Height);
	for(int i=0;i<Height;i++)
	{
		data[i].resize(Width);
		for(int j=0; j<Width;j++)
			data[i][j]=(i==j);
	}
}

template<class Type>
Line<Type>& Matrix<Type>::operator [](int Index)
{
	if(Index<0||Index>=Height)
		cout<<"Row ["<<Index<<"] : subscription out of range"<<endl;
	else
		return data[Index];
	return data[0];
}

template<class Type>
Line<Type>& System<Type>::operator[](int Index)
{
	return data[Index];
}

template<class Type>
Matrix<Type> Matrix<Type>::operator+=(Matrix<Type>& Add)
{
	if(Add.Height!=Height||Add.Width!=Width)
	{
		cout<<"Can`t add martixes"<<endl;
	}
	else
	{
		for(int i=0;i<Height;i++)
			for(int j=0;j<Width;j++)
				data[i][j]+=Add.data[i][j];
	}
	return (*this);
}

template<class Type>
Matrix<Type> Matrix<Type>::operator-=(Matrix<Type>& Sub)
{
	if(Sub.Height!=Height||Sub.Width!=Width)
	{
		cout<<"Can`t subtract martixes"<<endl;
	}
	else
	{
		for(int i=0;i<Height;i++)
			for(int j=0;j<Width;j++)
				data[i][j]-=Sub.data[i][j];
	}
	return (*this);
}

template<class Type>
Matrix<Type> Matrix<Type>::operator+(Matrix<Type>& Add)
{
	Matrix<Type> Result(*this);
	Result+=Add;
	return Result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator-(Matrix<Type>& Sub)
{
	Matrix<Type> Result(*this);
	Result-=Sub;
	return Result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator*=(Matrix<Type>& Mul)
{
	vector<Line<Type>> NewData;
	if(Width!=Mul.Height)
	{
		cout<<"Can`t multiply matrixes"<<endl;
	}
	else
	{
		Width=Mul.Width;
		NewData.resize(Height);
		for(int i=0;i<Height;i++)
		{
			NewData[i].resize(Width,Type(0));
			for(int j=0;j<Width;j++)
				for(int k=0;k<Mul.Height;k++)
					NewData[i][j]+=data[i][k]*Mul.data[k][j];
		}
		data=NewData;
	}
	return (*this);
}

template<class Type>
Matrix<Type> Matrix<Type>::operator*(Matrix<Type>& Mul)
{
	Matrix<Type> Result(*this);
	Result*=Mul;
	return Result;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator*=(Type Mul2)
{
	for(int i=0;i<Height;i++)
		for(int j=0;j<Width;j++)
			data[i][j]*=Mul2;
	return (*this);
}

template<class Type>
Matrix<Type> operator*(Matrix<Type>& Mul1, Type Mul2)
{
	Matrix<Type> Result(Mul1);
	Result*=Mul2;
	return Result;
}

template<class Type>
Matrix<Type> operator*(Type Mul2, Matrix<Type>& Mul1)
{
	return Mul1*Mul2;
}

template<class Type>
Line<Type>::Line():Size(0){}

template<class Type>
Line<Type>::Line(int size):Size(size)
{
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size);
	for(int i=0;i<Size;i++)
		data[i]=Type(0);
}

template<class Type>
Line<Type>::Line(vector<Type> Ex)
{
	Size=Ex.size();
	data=Ex;
}

template<class Type>
void Line<Type>::resize(int size)
{
	Size=size;
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size);
}

template <class Type>
void Line<Type>::resize(int size, Type val)
{
	Size=size;
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size,val);
}

template<class Type>
Type& Line<Type>::operator [](int Index)
{
	if(Index<0||Index>=Size)
		cout<<"Line ["<<Index<<"] : subscription out of range"<<endl;
	else
		return  data[Index];
	return data[0];
}

template <class Type>
vector<Type> Line<Type>::ToVector()
{
	return data;
}

template <class Type>
Matrix<Type> Line<Type>::ToMatrix()
{
	Matrix<Type> Result(1,Size);
	for(int i=0;i<Size;i++)
		Result[0][i]=data[i];
	return Result;
}

template <class Type>
Line<Type> Line<Type>::operator+=(Line<Type>& Add)
{
	if(Size!=Add.Size)
	{
		cout<<"Can`t add lines"<<endl;
	}
	else
	{
		for(int i=0;i<Size;i++)
			data[i]+=Add.data[i];
	}
	return (*this);
}

template <class Type>
Line<Type> Line<Type>::operator+(Line<Type>& Add)
{
	Line<Type> Result(*this);
	Result+=Add;
	return Result;
}

template <class Type>
Line<Type> Line<Type>::operator-=(Line<Type>& Sub)
{
	if(Size!=Sub.Size)
	{
		cout<<"Can`t subtract lines"<<endl;
	}
	else
	{
		for(int i=0;i<Size;i++)
			data[i]-=Sub.data[i];
	}
	return (*this);
}

template <class Type>
Line<Type> Line<Type>::operator-(Line<Type>& Sub)
{
	Line<Type> Result(*this);
	Result-=Sub;
	return Result;
}

template<class Type>
ostream& operator<<(ostream& os, Line<Type>& Out)
{
	for(int i=0;i<Out.Size;i++)
		os<<Out.data[i]<<"\t";
	os<<endl;
	return os;
}

template<class Type>
istream& operator>>(istream& is, Line<Type>& In)
{
	int size(0);
	cout<<"Enter size of line:"<<endl;
	os>>size;
	In.resize(size);
	cout<<"Enter items of line:"<<endl;
	for(int i=0;i<In.Size;i++)
		os>>In.data[i];
	return os;
}

template<class Type>
Line<Type> Line<Type>::operator*=(Type Mul)
{
	for(int i=0;i<Size;i++)
		data[i]*=Mul;
	return (*this);
}

template<class Type>
Line<Type> operator*(Line<Type>& Mul1, Type Mul2)
{
	Line<Type> Result(Mul1);
	Result*=Mul2;
	return Result;
}

template<class Type>
Line<Type> operator*(Type Mul2, Line<Type>& Mul1)
{
	return Mul1*Mul2;
}

template<class Type>
Row<Type>::Row():Size(0){}

template<class Type>
Row<Type>::Row(int size):Size(size)
{
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size);
	for(int i=0;i<Size;i++)
		data[i]=Type(0);
}

template<class Type>
Row<Type>::Row(vector<Type> Ex)
{
	Size=Ex.size();
	data=Ex;
}

template<class Type>
void Row<Type>::resize(int size)
{
	Size=size;
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size);
}

template <class Type>
void Row<Type>::resize(int size, Type val)
{
	Size=size;
	if(Size<0||Size>MAXSIZE)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size,val);
}

template<class Type>
Type& Row<Type>::operator [](int Index)
{
	if(Index<0||Index>=Size)
		cout<<"Row ["<<Index<<"] : subscription out of range"<<endl;
	else
		return  data[Index];
	return data[0];
}

template <class Type>
vector<Type> Row<Type>::ToVector()
{
	return data;
}

template <class Type>
Matrix<Type> Row<Type>::ToMatrix()
{
	Matrix<Type> Result(Size,1);
	for(int i=0;i<Size;i++)
		Result[i][0]=data[i];
	return Result;
}

template <class Type>
Row<Type> Row<Type>::operator+=(Row<Type>& Add)
{
	if(Size!=Add.Size)
	{
		cout<<"Can`t add rows"<<endl;
	}
	else
	{
		for(int i=0;i<Size;i++)
			data[i]+=Add.data[i];
	}
	return (*this);
}

template <class Type>
Row<Type> Row<Type>::operator+(Row<Type>& Add)
{
	Row<Type> Result(*this);
	Result+=Add;
	return Result;
}

template <class Type>
Row<Type> Row<Type>::operator-=(Row<Type>& Sub)
{
	if(Size!=Sub.Size)
	{
		cout<<"Can`t subtract rows"<<endl;
	}
	else
	{
		for(int i=0;i<Size;i++)
			data[i]-=Sub.data[i];
	}
	return (*this);
}

template <class Type>
Row<Type> Row<Type>::operator-(Row<Type>& Sub)
{
	Row<Type> Result(*this);
	Result-=Sub;
	return Result;
}

template<class Type>
ostream& operator<<(ostream& os, Row<Type>& Out)
{
	for(int i=0;i<Out.Size;i++)
		os<<Out.data[i]<<"\t";
	os<<endl;
	return os;
}

template<class Type>
istream& operator>>(istream& is, Row<Type>& In)
{
	int size(0);
	cout<<"Enter size of row:"<<endl;
	os>>size;
	In.resize(size);
	cout<<"Enter items of row:"<<endl;
	for(int i=0;i<In.Size;i++)
		os>>In.data[i];
	return os;
}

template<class Type>
Row<Type> Row<Type>::operator*=(Type Mul)
{
	for(int i=0;i<Size;i++)
		data[i]*=Mul;
	return (*this);
}

template<class Type>
Row<Type> operator*(Row<Type>& Mul1, Type Mul2)
{
	Row<Type> Result(Mul1);
	Result*=Mul2;
	return Result;
}

template<class Type>
Row<Type> operator*(Type Mul2, Row<Type>& Mul1)
{
	return Mul1*Mul2;
}

template<class Type>
Line<Type> Matrix<Type>::line(int Index)
{
	if(Index<0||Index>=Height)
		cout<<"Matrix_line ["<<Index<<"] : subscription out of range"<<endl, Index=0;
	return data[Index];
}

template<class Type>
Row<Type> Matrix<Type>::row(int Index)
{
	if(Index<0||Index>=Width)
		cout<<"Matrix_row ["<<Index<<"] : subscription out of range"<<endl, Index=0;
	Row<Type> Result(Height);
	for(int i=0;i<Height;i++)
		Result[i]=data[i][Index];
	return Result;
}

template<class Type>
Type operator*(Line<Type> Mul1, Row<Type> Mul2)
{
	Type Result(0);
	if(Mul1.size()!=Mul2.size())
	{
		cout<<"Can`t multiply line and row"<<endl;
	}
	else
	{
		for(int i=0;i<Mul1.size();i++)
			Result+=Mul1[i]*Mul2[i];
	}
	return Result;
}

template<class Type>
Type operator*(Row<Type> Mul1, Line<Type> Mul2)
{
	return Mul2*Mul1;
}

template<class Type>
Line<Type> Line<Type>::operator*=(Matrix<Type> Mul)
{
	if(Size!=Mul.height())
	{
		cout<<"Can`t multiply line and matrix"<<endl;
	}
	else
	{
		vector<Type> res(Mul.width());
		for(int i=0;i<Mul.width();i++)
			res[i]=(*this)*Mul.row(i);
		Size=Mul.width();
		data=res;
	}
	return (*this);
}

template<class Type>
Line<Type> operator*(Line<Type> Mul1, Matrix<Type> Mul2)
{
	Line<Type> Result(Mul1);
	Result*=Mul2;
	return Result;
}

template<class Type>
Row<Type> operator*(Matrix<Type> Mul1, Row<Type> Mul2)
{
	Row<Type> Result(Mul2);
	if(Mul1.width()!=Mul2.size())
	{
		cout<<"Can`t multiply row and matrix"<<endl;
	}
	else
	{
		Result.resize(Mul1.height());
		for(int i=0;i<Mul1.height();i++)
			Result[i]=Mul1.line(i)*Mul2;
	}
	return Result;
}

template<class Type>
int Line<Type>::size()
{
	return Size;
}

template<class Type>
int Row<Type>::size()
{
	return Size;
}

template<class Type>
pair<int,int> Matrix<Type>::size()
{
	return pair<int,int>(Height,Width);
}

template<class Type>
int Matrix<Type>::width()
{
	return Width;
}

template<class Type>
int Matrix<Type>::height()
{
	return Height;
}

template<class Type>
System<Type>::System():Size(0),data(0)
{}

template<class Type>
DiagonalSystem<Type>::DiagonalSystem():Size(0),data(0),diagonal(0),myindex(0)
{}

template<class Type>
System<Type>::System(int size):Size(size)
{
	if(size<0||size>MAXSIZE-1)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size, Size+1);
}

template<class Type>
void System<Type>::resize(int size)
{
	solve.clear();
	Size=size;
	if(size<0||size>MAXSIZE-1)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size, Size+1);
}

template<class Type>
ostream& operator<<(ostream& os, System<Type>& Out)
{
	for(int i=0;i<Out.Size;i++)
	{
		for(int j=0;j<Out.Size+1;j++)
		{
			char sym='+';
			if(j==Out.Size-1) sym='=';
			else if(j==Out.Size) sym=' ';
			os<<Out.data[i][j];
			if(j<Out.Size)
				os<<"*x", os<<j+1;
			os<<sym,
			os<<"\t";
		}
		os<<endl;
	}
	Out.Show_solve(os);
	return os;
}

template<class Type>
istream& operator>>(istream& is, System<Type>& In)
{
	int size(0);
	cout<<"Enter size if system:"<<endl;
	is>>size;
	In.resize(size);
	cout<<"Enter parameters of euations:"<<endl;
	for(int i=0;i<In.Size;i++)
	{
		cout<<"Equation #"<<i+1<<":"<<endl;
		for(int j=0;j<In.Size+1;j++)
			is>>In.data[i][j];
	}
	return is;
}

template<class Type>
ostream& show_matrix(ostream& os, System<Type>& Out)
{
	os<<Out.data;
	return os;
}

template<class Type>
void System<Type>::Show_matrix()
{
	show_matrix(cout,*this);
}

template<class Type>
ostream& show_solve(ostream& os, System<Type>& Out)
{
	for(unsigned int i=0;i<Out.solve.size();i++)
	{
		os<<Out.solve[i]<<"\t";
		if(i%4==3)
			os<<"\n";
	}
	os<<endl;
	return os;
}

template<class Type>
void System<Type>::Show_solve(ostream& os)
{
	if(issolved())
	{
		cout<<"The solution is:"<<endl;
		show_solve(os,*this);
	}
	else
		cout<<"System hasn`t been solved yet"<<endl;
}

template<class Type>
void System<Type>::Show_solve()
{
	if(issolved())
	{
		cout<<"The solution is:"<<endl;
		show_solve(cout,*this);
	}
	else
		cout<<"System hasn`t been solved yet"<<endl;
}

template<class Type>
bool System<Type>::issolved()
{
	return !solve.empty();
}

template<class Type>
Matrix<Type> System<Type>::matrix()
{
	Matrix<Type> Result(Size);
	for(int i=0;i<Size;i++)
		for(int j=0;j<Size;j++)
			Result[i][j]=data[i][j];
	return Result;
}

template<class Type>
Row<Type> System<Type>::freevector()
{
	Row<Type> Result(Size);
	for(int i=0;i<Size;i++)
		Result[i]=data[i][Size];
	return Result;
}

template<class Type>
void System<Type>::solve_uptriangle()
{
	solve.resize(Size);
	for(int i=Size-1;i>=0;i--)
	{
		Type sum(0);
		for(int j=i+1;j<Size;j++)
			sum+=data[i][j]*solve[j];
		solve[i]=(data[i][Size]-sum)/data[i][i];
	}
}

template<class Type>
void DiagonalSystem<Type>::solve_uptriangle()
{
	solve.resize(Size);
	for(int i=Size-1;i>=0;i--)
	{
		Type sum(0);
		for(int j=i+1;newcoord(i,j)<diagonal;j++)
			sum+=data[i][newcoord(i,j)]*solve[j];
		solve[i]=(data[i][diagonal]-sum)/data[i][newcoord(i,i)];
	}
}

template<class Type>
void System<Type>::Gauss()
{
	Matrix<Type> reservematrix=data;
	//Show_matrix();
	for(int i=0;i<Size;i++)
	{
		data[i]/=data[i][i];
		for(int j=i+1;j<Size;j++)
			data[j]-=data[j][i]*data[i];
		//Show_matrix();
	}
	solve_uptriangle();
	data=reservematrix;
}

template<class Type>
void System<Type>::Sqkor()
{
	Matrix<Type> S(Size);
	Matrix<Type> D(Size);
	for(int i=0;i<Size;i++)
	{
		Type pi=data[i][i];
		for(int l=0;l<i;l++)
			pi-=S[l][i]*S[l][i]*D[l][l];
		D[i][i]=sgn(pi);
		S[i][i]=sqrt(Type(abs(pi)));
		for(int j=i+1;j<Size;j++)
		{
			S[i][j]=data[i][j];
			for(int l=0;l<i;l++)
				S[i][j]-=S[l][i]*S[l][j]*D[l][l];
			S[i][j]/=S[i][i]*D[i][i];
		}
	}
	System<Type> Sys1(S.transp()*D,freevector());
	Sys1.solve_downtriangle();
	System<Type> Sys2(S,Sys1.solutuion());
	Sys2.solve_uptriangle();
	solve=Sys2.solutuion().ToVector();
}

template<class Type>
Line<Type> Line<Type>::operator/=(Type Div)
{
	for(int i=0;i<Size;i++)
		if(Div) data[i]/=Div;
	return (*this);
}

template<class Type>
Line<Type> Line<Type>::operator/(Type Div)
{
	Line<Type> Result(*this);
		Result/=Div;
	return Result;
}

template<class Type>
System<Type>::System(int size, Type alpha, Type p, Type q):Size(size)
{
	if(size<0||size>MAXSIZE-1)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size, Size+1);
	vector<Type> ppow(Size),qpow(Size);
	Type c(1);
	ppow[0]=1;
	qpow[0]=1;
	for(int i=1;i<Size;i++)
	{
		ppow[i]=ppow[i-1]*p;
		qpow[i]=qpow[i-1]*q;
		c+=ppow[i]*qpow[i];
	}
	Type z=(alpha-1)/c;
	for(int i=0;i<Size;i++)
		for(int j=0;j<Size;j++)
			data[i][j]=kroneker(i,j)+z*ppow[i]*qpow[j];
	for(int i=0;i<Size;i++)
	{
		data[i][Size]=0;
		for(int j=1;j<Size;j++)
			data[i][Size]+=j*data[i][j];
	}
}

template<class Type>
System<Type>::System(int size, int m):Size(size)
{
	if(size<0||size>MAXSIZE-1)
		cout<<"Size out of range"<<endl, Size=0;
	data.resize(Size, Size+1);
	vector<Type> qpow(2*Size,1);
	Type t(0),q,k(Size+m);
	if(m%2)
		q=Type(1.05)-Type(m)/100;
	else
		q=Type(1.05)+Type(m)/100;
	if(Size) qpow[0]=q;
	for(int i=1;i<2*Size;i++)
		qpow[i]=qpow[i-1]*q;
	for(int i=0;i<Size;i++)
		t+=qpow[2*i+1];
	for(int i=0;i<Size;i++)
	{
		data[i].resize(Size+1);
		for(int j=0;j<Size;j++)
			if(j!=i)
				data[i][j]=2*t+(qpow[i]+qpow[j])*k;
			else
				data[i][j]=2*qpow[i]*k*k;
		data[i][Size]=t+3*qpow[i];
	}
}

template<class Type>
Type Matrix<Type>::det()
{
	Type Result(0);
	if(Height!=Width)
		cout<<"Can`t count determinate"<<endl;
	else
	{
		Matrix<Type> Ex(*this);
		for(int i=0;i<Height;i++)
			for(int j=i+1;j<Height;j++)
				Ex.data[j]-=Ex.data[j][i]*Ex.data[i]/Ex.data[i][i];
		Result=1;
		for(int i=0;i<Height;i++)
			Result*=Ex.data[i][i];
	}
	return Result;
}

template<class Type>
vector<Type> System<Type>::iteration(vector<Type> approx)
{
	vector<Type> Result(Size,0);
	for(int i=0;i<Size;i++)
		if(data[i][i])
		{
			for(int j=0;j<i;j++)
				Result[i]-=data[i][j]/data[i][i]*Result[j];
			for(int j=i+1;j<Size;j++)
				Result[i]-=data[i][j]/data[i][i]*approx[j];
			Result[i]+=data[i][Size]/data[i][i];
		}
	return Result;
}

template<class Type>
Matrix<Type>::Matrix(vector<Line<Type>> d)
{
	bool ok=true;
	for(unsigned int i=0; (i<d.size()-1)&&ok;i++)
		if(d[i].size()!=d[i+1].size()) ok=false;
	if(ok)
	{
		Height=d.size();
		if(d.size())
			Width=d[0].size();
		else
			Width=0;
		data=d;
	}
	else
	{
		cout<<"Can`t create matrix from lines"<<endl;
	}
}

template<class Type>
Matrix<Type>::Matrix(vector<Row<Type>> d)
{
	bool ok=true;
	for(unsigned int i=0; (i<d.size()-1)&&ok;i++)
		if(d[i].size()!=d[i+1].size()) ok=false;
	if(ok)
	{
		if(d.size())
			Height=d[0].size();
		else
			Height=0;
		Width=d.size();
		data.resize(Height);
		for(int i=0;i<Height;i++)
		{
			data[i].resize(Width);
			for(int j=0;j<Width;j++)
				data[i][j]=d[j][i];
		}
	}
	else
	{
		cout<<"Can`t create matrix from rows"<<endl;
	}
}

template<class Type>
void System<Type>::solve_downtriangle()
{
	solve.resize(Size);
	for(int i=0;i<Size;i++)
	{
		Type sum(0);
		for(int j=0;j<i;j++)
			sum+=data[i][j]*solve[j];
		solve[i]=(data[i][Size]-sum)/data[i][i];
	}
}

template<class Type>
Row<Type> System<Type>::solutuion()
{
	if(!issolved())
	{
		cout<<"System hasn`t benn solved yet"<<endl;
	}
	return Row<Type>(solve);
}

template<class Type>
System<Type>::System(Matrix<Type> d,Row<Type> cond)
{
	if(d.width()!=d.height()||d.width()!=cond.size())
	{
		cout<<"Can`t create system from matrix and row"<<endl;
		Size=0;
	}
	else
	{
		Size=cond.size();
		data.resize(Size);
		for(int i=0;i<Size;i++)
		{
			data[i].resize(Size+1);
			for(int j=0;j<Size;j++)
				data[i][j]=d[i][j];
			data[i][Size]=cond[i];
		}
	}
}

template<class Type>
DiagonalSystem<Type>::DiagonalSystem(Matrix<Type> d,Row<Type> cond,int _diagonal):diagonal(_diagonal)
{
	myindex=(diagonal-1)/2;
	if(d.width()!=d.height()||d.width()!=cond.size())
	{
		cout<<"Can`t create system from matrix and row"<<endl;
		Size=0;
	}
	else
	{
		Size=cond.size();
		data.resize(Size);
		for(int i=0;i<Size;i++)
		{
			data[i].resize(diagonal+1);
			for(int j=0;j<diagonal;j++)
				data[i][j]=d[i][oldcoord(i,j)];
			data[i][diagonal]=cond[i];
		}
	}
}

template<class Type>
int DiagonalSystem<Type>::newcoord(int i,int j)
{
	if(j==Size)
		return diagonal;
	if(i<=myindex)
		return j;
	if(i>=Size-myindex)
		return j-Size+diagonal;
	return j-i+myindex;
}

template<class Type>
int DiagonalSystem<Type>::oldcoord(int i,int j)
{
	if(j==diagonal) return Size;
	if(i<=myindex)
		return j;
	if(i>=Size-myindex)
		return j+Size-diagonal;
	return j+i-myindex;
}

template<class Type>
void DiagonalSystem<Type>::Gauss()
{
	Matrix<Type> reservematrix=data;
	for(int i=0;i<Size;i++)
	{
		for(int j=1;j<=myindex&&i+j<Size;j++)
		{
			Type k=data[i+j][newcoord(i+j,i)]/data[i][newcoord(i,i)];
			for(int p=0;p<=myindex&&newcoord(i,i+p)<diagonal;p++)
				data[i+j][newcoord(i+j,i+p)]-=k*data[i][newcoord(i,i+p)];
			data[i+j][diagonal]-=k*data[i][diagonal];
		}
	}
	solve_uptriangle();
	data=reservematrix;
}

template<class Type>
Matrix<Type> Matrix<Type>::converse()
{
	vector<Row<Type>> res(Width);
	if(Width!=Height)
	{
		cout<<"Can`t count converse matrix"<<endl;
	}
	else
	{
		for(int i=0;i<Width;i++)
		{
			Row<Type> cond(Height);
			cond[i]=1;
			System<Type> ToSolve(*this,cond);
			ToSolve.Gauss();
			res[i]=ToSolve.solutuion();
		}
	}
	return Matrix(res);
}

template<class Type>
Type norm_inf(vector<Type> data)
{
	Type Result(0);
	for(unsigned int i=0;i<data.size();i++)
		if(abs(data[i])>Result)
			Result=abs(data[i]);
	return Result;
}

template<class Type>
Type norm_1(vector<Type> data)
{
	Type Result(0);
	for(unsigned int i=0;i<data.size();i++)
		Result+=abs(data[i]);
	return Result;
}

template<class Type>
Type Line<Type>::norm1()
{
	return norm_1(data);
}

template<class Type>
Type Line<Type>::norminf()
{
	return norm_inf(data);
}

template<class Type>
Type Row<Type>::norm1()
{
	return norm_1(data);
}

template<class Type>
Type Row<Type>::norminf()
{
	return norm_inf(data);
}


template<class Type>
Type Matrix<Type>::norm1()
{
	Type Result(0);
	for(int i=0;i<Width;i++)
	{
		Type sum(0);
		for(int j=0;j<Height;j++)
			sum+=abs(data[j][i]);
		if(sum>Result) Result=sum;
	}
	return Result;
}

template<class Type>
Type Matrix<Type>::norminf()
{
	Type Result(0);
	for(int i=0;i<Height;i++)
	{
		Type sum(0);
		for(int j=0;j<Width;j++)
			sum+=abs(data[i][j]);
		if(sum>Result) Result=sum;
	}
	return Result;
}

template<class Type>
Type Matrix<Type>::condition_number()
{
	return norm1()*converse().norm1();
	//return norminf()*converse().norminf(); //two different types of norm
}

template<class Type>
bool System<Type>::checkcondition(vector<Type> approx, vector<Type> oldapprox, Type epsilon)
{
	for(unsigned int i=0;i<approx.size();i++)
		if(abs(approx[i]-oldapprox[i])>=epsilon)
			return false;
	return true;
}

template<class Type>
void System<Type>::Seidel(Type epsilon)
{
	vector<Type> newappr(Size,1),oldappr;
	do
	{
		oldappr=newappr;
		newappr=iteration(oldappr);
	}
	while(!checkcondition(newappr,oldappr,epsilon));
	solve=newappr;
}

int kroneker(int n, int k)
{
	return(n==k);
}

template<class Type>
Matrix<Type> Matrix<Type>::transp()
{
	Matrix<Type> res(Width,Height);
	for(int i=0;i<Height;i++)
		for(int j=0;j<Width;j++)
			res[j][i]=data[i][j];
	return res;
}

template <class Type>
Type sgn(Type a)
{
	if(a<0) return Type(-1);
	return Type(1);
}

double myround(double x)
{
	if (modf(x,0)>=0.5)
		return x>=0?ceil(x):floor(x);
	else
		return x<0?ceil(x):floor(x);
}

double myround(double r,unsigned places)
{
	double off=pow(double(10),double(places));
	return myround(r*off)/off;
}