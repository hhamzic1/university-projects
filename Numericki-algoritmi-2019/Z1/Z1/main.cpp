// NA zadaca 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <iomanip>
class Vector
{
	std::vector<double>veka;
public:
	explicit Vector(int n)
	{
		if (n < 1) throw std::range_error("Bad dimension");
		veka.resize(n, 0);
	}
	Vector(std::initializer_list<double> l)
	{
		if (l.size() == 0) throw std::range_error("Bad dimension");
		veka.resize(l.size());
		int i = 0;
		for (std::initializer_list<double>::iterator it = l.begin(); it < l.end(); it++)
		{
		    veka[i] = *it;
			i++;
		}
	}
	int NElems() const
	{
		return veka.size();
	}
	double& operator[](int i)
	{
		return veka[i];
	}
	double operator[](int i) const
	{
		return veka[i];
	}
	double& operator()(int i)
	{
		if (i - 1 >= (int)veka.size() || i - 1 < 0) throw std::range_error("Invalid index");
		return veka.at(i - 1);
	}
	double operator()(int i) const
	{
		if (i - 1 >= (int)veka.size() || i - 1 < 0) throw std::range_error("Invalid index");
		return veka.at(i - 1);
	}
	double Norm() const
	{
		double sum = 0;
		for (int i = 0; i < (int)veka.size(); i++)
		{
			sum += std::pow(veka[i], 2);
		}
		return std::sqrt(sum);
	}
	friend double VectorNorm(const Vector& v)
	{
		double sum = 0;
		for (int i = 0; i < v.NElems(); i++)
		{
			sum += std::pow(v[i], 2);
		}
		return std::sqrt(sum);
	}
	double GetEpsilon() const
	{
		return 10 * std::numeric_limits<double>::epsilon() * (*this).Norm();
	}
	void Print(char separator = '\n', double eps = -1) const
	{
		
		if (eps < 0) eps= (*this).GetEpsilon();
		for (int i = 0; i < (*this).NElems(); i++)
		{
			if (i < (*this).NElems() - 1) 
			{ 
				if (std::abs(veka[i]) < eps) { std::cout << 0 << separator; continue; }
				std::cout << veka[i] << separator; continue; 
			}
			if (separator == '\n')
			{
				if (std::abs(veka[i]) < eps)
				{
					std::cout << 0 << separator; 
					break;
				}
				std::cout << veka[i]<< separator;
				break;
			}
			std::cout << veka[i];
		}
	}
	friend void PrintVector(const Vector& v, char separator = '\n', double eps = -1)
	{
	
		if (eps < 0) eps = v.GetEpsilon();
		for (int i = 0; i < v.NElems(); i++)
		{
			if (i < v.NElems() - 1)
			{
				if (std::abs(v[i]) < eps) { std::cout << 0 << separator; continue; }
				std::cout << v[i] << separator; continue;
			}
			if (separator == '\n')
			{
				if (std::abs(v[i]) < eps)
				{
					std::cout << 0 << separator;
					break;
				}
				std::cout << v[i] << separator;
				break;
			}
			std::cout << v[i];
		}

	}
	friend Vector operator+(const Vector& v1, const Vector& v2)
	{
		if (v1.NElems() != v2.NElems()) throw std::domain_error("Incompatible formats");
		Vector vctr(v1.NElems());
		for (int i = 0; i < vctr.NElems(); i++)
		{
			vctr[i] = v1[i] + v2[i];
		}
		return vctr;

	}
	Vector& operator+=(const Vector& v)
	{
		if((*this).NElems()!= v.NElems()) throw std::domain_error("Incompatible formats");
		for (int i = 0; i < v.NElems(); i++)
		{
			veka[i] += v[i];
		}
		return *this;

	}
	friend Vector operator-(const Vector& v1, const Vector& v2)
	{
		if (v1.NElems() != v2.NElems()) throw std::domain_error("Incompatible formats");
		Vector vctr(v1.NElems());
		for (int i = 0; i < vctr.NElems(); i++)
		{
			vctr[i] = v1[i] - v2[i];
		}
		return vctr;


	}
	Vector& operator-=(const Vector& v)
	{
		if ((*this).NElems() != v.NElems()) throw std::domain_error("Incompatible formats");
		for (int i = 0; i < v.NElems(); i++)
		{
			veka[i] -= v[i];
		}
		return *this;


	}
	friend Vector operator*(double s, const Vector& v)
	{
		Vector vctr(v.NElems());
		for (int i = 0; i < v.NElems(); i++)
		{
			vctr[i] = v[i] * s;
		}
		return vctr;
	}
	friend Vector operator*(const Vector& v, double s)
	{
		Vector vctr(v.NElems());
		for (int i = 0; i < v.NElems(); i++)
		{
			vctr[i] = v[i] * s;
		}
		return vctr;

	}
	Vector& operator*=(double s)
	{
		for (int i = 0; i < (*this).NElems(); i++)
		{
			veka[i] *= s;
		}
		return *this;
	}
	friend double operator*(const Vector& v1, const Vector& v2)
	{
		if (v1.NElems() != v2.NElems()) throw std::domain_error("Incompatible formats");
		double sum = 0;
		for (int i = 0; i < v1.NElems(); i++)
		{
			sum += v1[i] * v2[i];
		}
		return sum;
	}
	friend Vector operator/(const Vector& v, double s)
	{
		if (s == 0) throw std::domain_error("Division by zero");
		Vector vctr(v.NElems());
		for (int i = 0; i < v.NElems(); i++)
		{
			vctr[i] = v[i] / s;
		}
		return vctr;
	}
	Vector& operator/=(double s)
	{
		if (s == 0) throw std::domain_error("Division by zero");
		for (int i = 0; i < (*this).NElems(); i++)
		{
			veka[i] /= s;
		}
		return *this;
	}

};


class Matrix
{
	std::vector<std::vector<double>> mat;
public:

	Matrix(int m, int n)
	{
		if (m < 1 || n < 1) throw std::range_error("Bad dimension");
		mat.resize(m);
		for (int i = 0; i < m; i++)
		{
			mat[i].resize(n);
		}
	}
	Matrix(const Vector& v)
	{
		mat.resize(1);
		for (int i = 0; i < v.NElems(); i++)
		{
			mat[0][i] = v[i];
		}
	}
	Matrix(std::initializer_list<std::vector<double>> l)
	{
		std::initializer_list<std::vector<double>>::iterator it = l.begin();
			int pom = (*it).size();
		for (it = l.begin(); it < l.end(); it++)
		{
			if((*it).size()==0) throw std::range_error("Bad dimension");
			if ((*it).size() != pom) throw std::logic_error("Bad matrix");
		}
		it = l.begin();
		mat.resize(l.size());
		for (int i = 0; i < (int)l.size(); i++)
		{
			mat[i].resize(pom);
		}

		for (int i = 0; i < (int)l.size(); i++)
		{
			for (int j = 0; j < pom; j++)
			{
				mat[i][j]=(*it)[j];
			}
			it++;
		}
	}
	int NRows() const
	{
		return (int)mat.size();
	}
	int NCols() const
	{
		return (int)mat[0].size();
	}
	double* operator[](int i)
	{
		if (i<0 || i>(*this).NRows()) throw std::range_error("Invalid index");
		return &mat[i][0];
	}
	const double* operator[](int i) const
	{
		if (i<0 || i>=(*this).NRows()) throw std::range_error("Invalid index");
		return &mat[i][0];
	}
	double& operator()(int i, int j)
	{
		if (i<1 || i>=(*this).NRows() || j<0 || j>=(*this).NCols()) throw std::range_error("Invalid index");
		return mat.at(i-1).at(j-1);
	}
	double operator()(int i, int j) const
	{
		if (i < 0 || i >= (*this).NRows() || j < 0 || j >= (*this).NCols()) throw std::range_error("Invalid index");
		return mat.at(i-1).at(j-1);
	}
	double Norm() const
	{
		double sum = 0;
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				sum =sum + std::pow(mat[i][j],2);
			}
		}
		return std::sqrt(sum);
	}
	friend double MatrixNorm(const Matrix& m)
	{
		double sum = 0;
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				sum += std::pow(m[i][j], 2);
			}
		}
		return std::sqrt(sum);

	}
	double GetEpsilon() const
	{
		return 10 * std::numeric_limits<double>::epsilon() * (*this).Norm();
	}
	void Print(int width = 10, double eps = -1) const
	{
		if (eps < 0) eps = (*this).GetEpsilon();
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				if (std::abs(mat[i][j]) < eps) { std::cout << std::setw(width) << 0; continue; }
				std::cout << std::setw(width) << mat[i][j];
			}
			std::cout << "\n";
		}
	}
	friend void PrintMatrix(const Matrix& m, int width = 10, double eps = -1)
	{
		if (eps < 0) eps = m.GetEpsilon();
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				if (std::abs(m[i][j]) < eps) { std::cout << std::setw(width) << 0; continue; }
				std::cout << std::setw(width) << m[i][j];
			}
			std::cout << "\n";
		}

	}
	friend Matrix operator +(const Matrix& m1, const Matrix& m2)
	{
		if (m1.NCols() != m2.NCols() || m1.NRows() != m2.NRows()) throw std::domain_error("Incompatible formats");
		Matrix mat(m1.NRows(), m1.NCols());
		for (int i = 0; i < m1.NRows(); i++)
		{
			for (int j = 0; j < m1.NCols(); j++)
			{
				mat[i][j] = m1[i][j] + m2[i][j];
			}
		}
		return mat;
	}
	Matrix& operator +=(const Matrix& m)
	{
		if (m.NCols() != (*this).NCols() || m.NRows() != (*this).NRows()) throw std::domain_error("Incompatible formats");
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				(*this)[i][j] += m[i][j];
			}
		}
		return *this;
	}
	friend Matrix operator -(const Matrix& m1, const Matrix& m2)
	{
		if (m1.NCols() != m2.NCols() || m1.NRows() != m2.NRows()) throw std::domain_error("Incompatible formats");
		Matrix mat(m1.NRows(), m1.NCols());
		for (int i = 0; i < m1.NRows(); i++)
		{
			for (int j = 0; j < m1.NCols(); j++)
			{
				mat[i][j] = m1[i][j] - m2[i][j];
			}
		}
		return mat;

	}
	Matrix& operator -=(const Matrix& m)
	{
		if (m.NCols() != (*this).NCols() || m.NRows() != (*this).NRows()) throw std::domain_error("Incompatible formats");
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				(*this)[i][j] -= m[i][j];
			}
		}
		return *this;

	}
	friend Matrix operator *(double s, const Matrix& m)
	{
		Matrix mat(m.NRows(), m.NCols());
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				mat[i][j] = m[i][j] * s;
			}
		}
		return mat;


	}
	friend Matrix operator *(const Matrix& m, double s)
	{
		Matrix mat(m.NRows(), m.NCols());
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				mat[i][j] = m[i][j] * s;
			}
		}
		return mat;


	}
	Matrix& operator *=(double s)
	{
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				(*this)[i][j] *= s;
			}
		}
		return *this;
	}
	friend Matrix operator *(const Matrix& m1, const Matrix& m2)
	{
		if (m1.NCols()!= m2.NRows()) throw std::domain_error("Incompatible formats");
		Matrix mat(m1.NRows(), m2.NCols());
		for (int i = 0; i < m1.NRows(); i++)
		{
			for (int j = 0; j < m2.NCols(); j++)
			{
				mat[i][j] = 0;
				for (int k = 0; k < m2.NRows(); k++) mat[i][j] = mat[i][j] + m1[i][k] * m2[k][j];
			}
		}
		return mat;
	}
	Matrix& operator *=(const Matrix& m)
	{
		if ((*this).NCols() != m.NRows()) throw std::domain_error("Incompatible formats");
		Matrix M((*this).NRows(), m.NCols());
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				M[i][j] = 0;
				for (int k = 0; k < m.NRows(); k++) M[i][j] = M[i][j] + mat[i][k] * m[k][j];
			}
		}
		mat.resize(M.NRows());
		for (int i = 0; i < M.NRows(); i++) mat[i].resize(M.NCols());
		for (int i = 0; i < M.NRows(); i++)
		{
			for (int j = 0; j < M.NCols(); j++) mat[i][j] = M[i][j];
		}

		return *this;

	}
	friend Vector operator *(const Matrix& m, const Vector& v)
	{
		if(m.NCols()!=v.NElems()) throw std::domain_error("Incompatible formats");
		Vector veka(m.NRows());
		for (int i = 0; i < m.NRows(); i++)
		{
			for (int j = 0; j < m.NCols(); j++)
			{
				veka[i] = 0;
				for (int k = 0; k < v.NElems(); k++)
				{
					veka[i] = veka[i] + m[i][k] * v[k];
				}
			}
		}
		return veka;
	}
	friend Matrix Transpose(const Matrix& m)
	{
		Matrix M(m.NCols(), m.NRows());
		for (int i = 0; i < m.NRows(); ++i)
			for (int j = 0; j < m.NCols(); ++j)
			{
				M[j][i] = m[i][j];
			}
		return M;

	}
	void Transpose()
	{
		double temp;
		if ((*this).NCols() == (*this).NRows())
		{
			for (int i = 0; i < (*this).NRows(); ++i)
			{
				for (int j = 0; j < (*this).NCols(); ++j)
				{
					if (j == i) continue;
					if (j>i)
					{
						temp = mat[i][j];
						mat[i][j] = mat[j][i];
						mat[j][i] = temp;
					}
				}
			}
			return;
		}
		Matrix M((*this).NCols(), (*this).NRows());
		for (int i = 0; i < (*this).NRows(); ++i)
		{
			for (int j = 0; j < (*this).NCols(); ++j)
			{
				M[j][i] = mat[i][j];
			}
		}
		(*this).mat.resize(M.NRows());
		for (int i = 0; i < M.NRows(); i++) (*this).mat[i].resize(M.NCols());


			for (int i = 0; i < M.NRows(); i++)
			{
				for (int j = 0 ; j < M.NCols(); j++)
				{
					mat[i][j] = M[i][j];
				}
			}
		return;
	}

};



int main() {

//test većine bitnih metoda koje u sebi interno koriste manje bitne metode!
	try{
	Matrix mat{{1,2,3},{3,4,5},{5,6,7}};
	Vector vek{1,2,3};
	vek=mat*vek;
	mat=mat*mat;
	mat.Transpose();
	mat.Print();
	mat=Transpose(mat);
	std::cout<<"______________________________________________________\n";
	mat.Print();
	}catch(...){
		std::cout<<"error";
	}
	

}