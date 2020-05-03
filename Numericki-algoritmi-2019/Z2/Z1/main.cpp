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

		if (eps < 0) eps = (*this).GetEpsilon();
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
				std::cout << veka[i] << separator;
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
		if ((*this).NElems() != v.NElems()) throw std::domain_error("Incompatible formats");
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
		double eps = v.GetEpsilon();
		if (std::fabs(s)<eps) throw std::domain_error("Division by zero");
		Vector vctr(v.NElems());
		for (int i = 0; i < v.NElems(); i++)
		{
			vctr[i] = v[i] / s;
		}
		return vctr;
	}
	Vector& operator/=(double s)
	{
		double eps = (*this).GetEpsilon();
		if (std::fabs(s)<eps) throw std::domain_error("Division by zero");
		for (int i = 0; i < (*this).NElems(); i++)
		{
			veka[i] /= s;
		}
		return *this;
	}

	void Chop(double eps = -1)
	{
		if (eps < 0) eps = (*this).GetEpsilon();
		for (int i = 0; i < (*this).NElems(); i++)
		{
			if (std::abs((*this)[i]) < eps) (*this)[i] = 0;
		}
	}

	bool EqualTo(const Vector& v, double eps = -1) const
	{
		if (eps < 0) eps = (*this).GetEpsilon();
		if ((*this).NElems() != v.NElems()) return false;
		for (int i = 0; i < v.NElems(); i++)
		{
			if (std::abs((*this)[i] - v[i]) > eps) return false;
		}
		return true;
	}

};


class Matrix
{
	std::vector<std::vector<double>> mat;
	int rank = 0;
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
		mat.resize(v.NElems());
		for (int i = 0; i < v.NElems(); i++)
		{
			mat[i].resize(1);
			mat[i][0] = v[i];
		}
	}
	Matrix(std::initializer_list<std::vector<double>> l)
	{
		std::initializer_list<std::vector<double>>::iterator it = l.begin();
		int pom = (*it).size();
		for (it = l.begin(); it < l.end(); it++)
		{
			if ((*it).size() == 0) throw std::range_error("Bad dimension");
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
				mat[i][j] = (*it)[j];
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
		if (i < 0 || i >= (*this).NRows()) throw std::range_error("Invalid index");
		return &mat[i][0];
	}
	double& operator()(int i, int j)
	{
		if (i < 1 || i >= (*this).NRows() || j < 0 || j >= (*this).NCols()) throw std::range_error("Invalid index");
		return mat.at(i - 1).at(j - 1);
	}
	double operator()(int i, int j) const
	{
		if (i < 0 || i >= (*this).NRows() || j < 0 || j >= (*this).NCols()) throw std::range_error("Invalid index");
		return mat.at(i - 1).at(j - 1);
	}
	double Norm() const
	{
		double sum = 0;
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				sum = sum + std::pow(mat[i][j], 2);
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
	void Print(int width = 2, double eps = -1) const
	{
		if (eps < 0) eps = (*this).GetEpsilon();
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				if (std::abs(mat[i][j]) < eps) { std::cout << std::setw(width) << 0; continue; }
				if(mat[i][j]>0){
				std::cout << std::setw(width) << mat[i][j]; continue;
				}
				std::cout<<std::setw(width+1)<<mat[i][j];
				
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
		if (m1.NCols() != m2.NRows()) throw std::domain_error("Incompatible formats");
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
		if (m.NCols() != v.NElems()) throw std::domain_error("Incompatible formats");
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
					if (j > i)
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
			for (int j = 0; j < M.NCols(); j++)
			{
				mat[i][j] = M[i][j];
			}
		}
		return;
	}

	void Chop(double eps = -1)
	{
		if (eps < 0) eps = (*this).GetEpsilon();
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				if (std::abs((*this)[i][j]) < eps) (*this)[i][j] = 0;
			}
		}
	}

	bool EqualTo(const Matrix& m, double eps = -1)
	{
		if (eps < 0) eps = (*this).GetEpsilon();
		if ((*this).NRows() != m.NRows() || (*this).NCols() != m.NCols()) return false;
		for (int i = 0; i < (*this).NRows(); i++)
		{
			for (int j = 0; j < (*this).NCols(); j++)
			{
				if (std::abs((*this)[i][j] - m[i][j]) > eps) return false;
			}
		}
		return true;

	}
	
	
	friend Matrix LeftDiv(Matrix m1, Matrix m2)
	{
	    if(m1.NRows()!=m1.NCols()) throw std::domain_error("Divisor matrix is not square");
	    if(m1.NCols()!=m2.NRows()) throw std::domain_error("Incompatible formats");
	    
	    int n = m1.NCols(), m=m2.NRows();
	    double eps = m1.GetEpsilon();
	    Matrix x(n,m);
	    
	    for(int k=0; k<n; k++)
	    {
	    	int p=k;
	    	for(int i=k+1; i<n; i++)
	    	{
	    		if(std::fabs(m1[i][k]) > std::fabs(m1[p][k]))
	    		{
	    			p = i;
	    		}
	    	}
	    	if(std::fabs(m1[p][k])<eps) throw std::domain_error("Divisor matrix is singular");
	    	
	    	if(p!=k)
	    	{
	    		for(int j = k; j<n; j++)
	    		{
	    			double t = m1[k][j];
	    			m1[k][j]=m1[p][j];
	    			m1[p][j]=t;
	    		}
	    		for(int j=0; j<m2.NCols(); j++)
	    		{
	    			double t = m2[k][j];
	    			m2[k][j] = m2[p][j];
	    			m2[p][j]=t;
	    		}
	    	}
	    	
	    	for(int i=k+1; i<n; i++)
	    	{
	    		double u=m1[i][k]/m1[k][k];
	    		for(int j=k+1; j<n; j++)
	    		{
	    			m1[i][j] -= u*m1[k][j];
	    		}
	    		for(int j=0; j<m2.NCols(); j++)
	    		{
	    			m2[i][j] -= u*m2[k][j];
	    		}
	    	}
	   
	    }
	    
	    for(int k=0; k<m2.NCols(); k++)
	    {
	    	for(int i=n-1; i>-1; i--)
	    	{
	    		double s = m2[i][k];
	    		for(int j=i+1; j<n; j++)
	    		{
	    			s -= m1[i][j]*x[j][k];
	    		}
	    		x[i][k]=s/m1[i][i];
	    	}
	    }
	    return x;

	}
	
	friend Vector LeftDiv(Matrix m1, Vector m2)
	{
		
		if(m1.NRows()!=m1.NCols()) throw std::domain_error("Divisor matrix is not square");
		if(m1.NRows()!=m2.NElems()) throw std::domain_error("Incompatible formats");
		
		int n=m1.NRows();
		double eps = m1.GetEpsilon();
		
		for(int k=0; k<n; k++)
		{
			int p=k;
			
			for(int i=k+1; i<n; i++)
			{
				if(std::fabs(m1[i][k])>std::fabs(m1[p][k])) p = i;
			}
			
			if(std::fabs(m1[p][k])<eps) throw std::domain_error("Divisor matrix is singular");
			
			if(p!=k)
			{
				for(int j=k; j<n; j++)
				{
					double t=m1[k][j];
					m1[k][j]=m1[p][j];
					m1[p][j]=t;
				}
				double t=m2[k];
				m2[k]=m2[p];
				m2[p]=t;
			}
			
			for(int i=k+1; i<n; i++)
			{
				double u=m1[i][k]/m1[k][k];
				for(int j=k; j<n; j++)
				{
					m1[i][j] -= u*m1[k][j];
				}
				m2[i] -= u*m2[k];
			}
		}
		
		for(int i=n-1; i>-1; i--)
		{
			double s=m2[i];
			for(int j = i+1; j<n; j++)
			{
				s -= m1[i][j]*m2[j];
			}
			m2[i]=s/m1[i][i];
		}
		//radi
		return m2;

	}
	
	friend Matrix operator/(const Matrix &m, double s)
	{
		double eps = m.GetEpsilon();
		if(std::fabs(s)<eps) throw std::domain_error("Division by zero");
		Matrix temp(m.NRows(), m.NCols());
		for(int i=0; i<m.NRows(); i++)
		{
			for(int j=0; j<m.NCols(); j++)
			{
				temp[i][j]=m[i][j]/s;
			}
		}
		return temp;
	}
	
	Matrix& operator/=(double s)
	{
		double eps = (*this).GetEpsilon();
		if(std::fabs(s)<eps) throw std::domain_error("Division by zero");
		for(int i=0; i<this->NRows(); i++)
		{
			for(int j=0; j<this->NCols(); j++)
			{
				(*this)[i][j]/=s;
			}
		}
		return *this;
	}
	
	Matrix &operator /=(Matrix m)
	{
		if(m.NRows() != m.NCols()) throw std::domain_error("Divisor matrix is not square");
		if((*this).NCols() != m.NCols()) throw std::domain_error("Incompatible formats");
		
		double eps=m.GetEpsilon();
		int n=m.NCols();
		int mredovi=(*this).NRows();
		
		for(int k=0; k<n; k++)
		{
			int p=k;
			
			for(int i=k+1; i<n; i++)
			{
				if(std::fabs(m[k][i])>std::fabs(m[k][p])) p=i;
			}
			
			if(std::fabs(m[k][p])<eps) throw std::domain_error("Divisor matrix is singular");
			
			if(p!=k)
			{
				for(int j=k; j<n; j++)
				{
					double t=m[j][k];
					m[j][k]=m[j][p];
					m[j][p]=t;
				}
				for(int j=0; j<mredovi; j++)
				{
					double t=(*this)[j][k];
					(*this)[j][k]=(*this)[j][p];
					(*this)[j][p]=t;
				}
			}
			
			for(int i=k+1; i<n; i++)
			{
				double u = m[k][i]/m[k][k];
				for(int j=k+1; j<n; j++)
				{
					m[j][i] -= u*m[j][k];
				}
				for(int j=0; j<mredovi; j++)
				{
					(*this)[j][i] -= u*(*this)[j][k];
				}
			}
		
		}
		
		for(int k=0; k<mredovi; k++)
		{
			for(int i=n-1; i>-1; i--)
			{
				double s=(*this)[k][i];
				
				for(int j=i+1; j<n; j++)
				{
					s -= m[j][i]*(*this)[k][j];
				}
				
				(*this)[k][i] = s/m[i][i];
			}
		}
		
	    return *this;

	}
	
	friend Matrix operator/(Matrix m1, Matrix m2)
	{
		Matrix x=m1;
		x/=m2;
		return x;
	}
	
	double Det() const
	{
		if((*this).NRows()!=(*this).NCols()) throw std::domain_error("Matrix is not square");
	    double eps = (*this).GetEpsilon();
	    Matrix m1 = (*this);
	    int n = m1.NRows();
	    double d=1;
	    for(int k=0; k<n; k++)
	    {
	    	int p=k;
	    	
	    	for(int i = k+1; i<n; i++)
	    	{
	    		if(std::fabs(m1[i][k])>std::fabs(m1[p][k])) p=i;
	    	}
	    	
	    	if(std::fabs(m1[p][k])<eps) return 0;
	    	
	    	if(p!=k)
	    	{
	    		for(int j=k; j<n; j++)
	    		{
	    			double t = m1[k][j];
	    			m1[k][j]=m1[p][j];
	    			m1[p][j]=t;
	    		}
	    		d=(-1)*d;
	    	}
	    	
	    	d=d*m1[k][k];
	    	for(int i=k+1; i<n; i++)
	    	{
	    		double u = m1[i][k]/m1[k][k];
	    		for(int j = k; j<n; j++)
	    		{
	    			m1[i][j] -= u*m1[k][j];
	    		}
	    	}
	    }
	    return d;
	    //radi
	}
	
	friend double Det(Matrix m)
	{
		return m.Det();
	}
	
	void Invert()
	{
		if((*this).NRows()!=(*this).NCols()) throw std::domain_error("Matrix is not square");
	    double eps = (*this).GetEpsilon();
	    int n = (*this).NRows();
	    std::vector<int> w(n, -1);
		
		for(int k = 0; k<n ;k++)
		{
			int p=k;
			for(int i=k+1; i<n; i++)
			{
				if(std::fabs((*this)[i][k]) > std::fabs((*this)[p][k])) p = i;
			}
			
			if(std::fabs((*this)[p][k])<eps) throw std::domain_error("Matrix is singular");
			
			if(p!=k)
			{
				for(int j=0; j<n; j++)
				{
					double t = (*this)[k][j];
					(*this)[k][j] = (*this)[p][j];
					(*this)[p][j] = t;
				}
			}
			
			w[k]=p;
			double u=(*this)[k][k];
			(*this)[k][k] = 1;
			
			for(int j=0; j<n; j++)
			{
				(*this)[k][j]=(*this)[k][j]/u;
			}
			
			for(int i=0; i<n; i++)
			{
				if(i!=k)
				{
					u = (*this)[i][k];
					(*this)[i][k]=0;
					for(int j=0; j<n; j++)
					{
						(*this)[i][j] -= u*(*this)[k][j];
					}
				}
			}
		}
		
		for(int j=n-1; j>=0; j--)
		{
			int p = w[j];
			if(p!=j)
			{
				for(int i=0; i<n; i++)
				{
					double t = (*this)[i][p];
					(*this)[i][p] = (*this)[i][j];
					(*this)[i][j]=t;
				}
			}
		}
	}
		
	friend Matrix Inverse(Matrix m)
	{
		m.Invert();
		return m;
	}
		
		
	void ReduceToRREF()
	{
			
			int m=(*this).NRows(), n=(*this).NCols();
			int k=-1;
			int l=-1;
			double eps = (*this).GetEpsilon();
			std::vector<int> w(n, 0);
			double v=0;
			int p=0;
			
			while(k<m && l<n)
			{
				l=l+1;
				k=k+1;
				v=0;
				while(v<eps && l<n)
				{
					p=k;
					for(int i=k; i<m; i++)
					{
						if(std::fabs((*this)[i][l])>v)
						{
							v=std::fabs((*this)[i][l]);
							p=i;
						}
					}
					if(v<eps) l=l+1;
				}
				
				if(l<n)
				{
					w[l]=1;
					if(p!=k)
					{
						for(int j=0; j<(*this).NCols(); j++)
						{
							double t = (*this)[k][j];
							(*this)[k][j] = (*this)[p][j];
							(*this)[p][j]=t;
						}
					}
					
					double u=(*this)[k][l];
					for(int j=l; j<n; j++)
					{
						(*this)[k][j]/=u;
					}
					for(int i=0; i<m; i++)
					{
						if(i!=k)
						{
							u = (*this)[i][l];
							for(int j=l; j<n; j++)
							{
								(*this)[i][j] -= u*(*this)[k][j];
							}
						}
					}
				}
			}
			int r=0;
			
			for(int i=0; i<m; i++)
			{
				for(int j=0; j<n; j++)
				{
					if(i==j && (*this)[i][j]!=0) r++;
				}
			}
			
			(*this).rank=r;
			
	}
	
	friend Matrix RREF(Matrix m)
	{
		m.ReduceToRREF();
		return m;
	}
	
	int Rank() const
	{
		Matrix temp = (*this);
		temp.ReduceToRREF();
		return temp.rank;
	}
	
	friend int Rank(Matrix m)
	{
		return m.Rank();
	}
	friend class LUDecomposer;
};

class LUDecomposer
{
	Matrix a;
	Vector prevrnuti_redovi;
	
public:
	LUDecomposer(Matrix m) : a(m), prevrnuti_redovi(m.NRows())		//NE RADI DA VALJA
	{
		double eps=m.GetEpsilon();
		if(m.NRows()!=m.NCols()) throw std::domain_error("Matrix is not square");
		if(std::fabs(Det(m))<eps) throw std::domain_error("Matrix is singular");
		
		int p;
		for(int j=0; j<m.NRows(); j++)
		{
			double s;
			for(int i=0; i<=j; i++)
			{
				s=a[i][j];
				for(int k=0; k<i; k++)
				{
					s-=a[i][k]*a[k][j];
				}
				a[i][j]=s;
			}
			
			p=j;
			for(int i=j+1; i<m.NRows(); i++)
			{
				s=a[i][j];
				for(int k=0; k<j; k++)
				{
					s -= a[i][k]*a[k][j];
				}
				a[i][j]=s;
				if(std::fabs(s)>std::fabs(a[p][j])) p=i;
			}
			
			if(p!=j)
			{
				for(int l=0; l<m.NCols(); l++)
				{
					double t=a[p][l];
					a[p][l]=a[j][l];
					a[j][l]=t;
				}
			}
			prevrnuti_redovi[j]=p;
			double temp=1./a[j][j];
			for(int i=j+1; i<m.NRows(); i++)
			{
				a[i][j]*=temp;
			}
			
		}
	}
	
	void Solve(Matrix &b, Matrix &x) const
	{
			if(b.NCols()!=a.NRows() || b.NRows()!=a.NCols() || x.NRows()!=a.NCols() || x.NCols()!=a.NRows() ) throw std::domain_error("Incompatible formats");
			x=b;
			for(int k=0; k<b.NRows(); k++)
			{
				for(int i=0; i<a.NCols(); i++)
				{
					int p=prevrnuti_redovi[i];
					double s=x[p][k];
					x[p][k]=x[i][k];
					for(int j=0; j<i; j++)
					{
						s-=a[i][j]*x[j][k];
					}
					x[i][k]=s;
				
				}
			
				for(int i=a.NCols()-1; i>-1; i--)
				{
					double s=x[i][k];
					for(int j=i+1; j<a.NCols(); j++)
					{
						s-=a[i][j]*x[j][k];
					}
					x[i][k]=s/a[i][i];
				}
		}
	}
	
	Matrix Solve(Matrix b) const
	{
		Matrix temp(b.NRows(), b.NCols());
		this->Solve(b,temp);
		return temp;
	}
	
	void Solve(const Vector &b, Vector &x) const
	{
		if(b.NElems()!=a.NRows() || x.NElems()!=a.NRows()) throw std::domain_error("Incompatible formats");
		x=b;
		for(int i=0; i<b.NElems(); i++)
		{
			int p=prevrnuti_redovi[i];
			double s=x[p];
			x[p]=x[i];
			for(int j=0; j<i; j++)
			{
				s-=a[i][j]*x[j];
			}
			x[i]=s;
		}
		
		for(int i=b.NElems()-1; i>-1; i--)
		{
			double s=x[i];
			for(int j=i+1; j<b.NElems(); j++)
			{
				s-=a[i][j]*x[j];
			}
			x[i]=s/a[i][i];
		}
	}
	
	Vector Solve(Vector b) const
	{
		Vector temp(b.NElems());
		this->Solve(b,temp);
		return temp;
	}
	
	
	Matrix GetU() const
	{
		Matrix upper(a.NRows(), a.NCols());
		for(int i=0; i<a.NRows(); i++)
		{
			for(int j=0; j<a.NCols(); j++)
			{
				if(j>=i) upper[i][j]=a[i][j];
			}
		}
		return upper;
	}
	
	Matrix GetL() const
	{
		Matrix lower(a.NRows(), a.NCols());
		
		for(int i=0; i<a.NRows(); i++)
		{
			for(int j=0; j<a.NCols(); j++)
			{
				if(i==j) lower[i][j]=1;
				else if(i>j) lower[i][j]=a[i][j];
				else lower[i][j]=0;
			}
		}
		return lower;

	}
	
	Matrix GetCompactLU() const
	{
		return a;
	}
	
	Vector GetPermuation() const
	{
		return prevrnuti_redovi;
	}

};

class QRDecomposer
{
	Matrix a;
	Vector tempara;
	double perm(int i, int j) const
	{
		if(j>i) return a[i][j];
		if(i==j) return tempara[i];
		return 0;
	}
	
	Matrix MulQWithMatrica(Matrix b, bool tacno) const
	{
		if(a.NRows()!=b.NRows()) throw std::domain_error("Incompatible formats");
		for(int i=0; i<b.NCols(); i++)
		{
			Vector veka(a.NRows());
			for(int j=0; j<veka.NElems(); j++)
			{
				veka[j]=b[j][i];
			}
			veka=MulQWithVektor(veka,tacno);
			for(int j=0; j<veka.NElems(); j++)
			{
				b[j][i]=veka[j];
			}
		}
		return b;
	}
	
	Vector MulQWithVektor(Vector b, bool tacno) const
	{
		double eps=a.GetEpsilon();
		if(a.NRows()!=b.NElems()) throw std::domain_error("Incompatible formats");
		if(tacno)
		{
			for(int k=0; k<a.NCols(); k++)
			{
				double s=0; 
				for(int i=k; i<a.NRows(); i++)
					s+=a[i][k]*b[i];
				for(int i=k; i<a.NRows(); i++)
					b[i]-=s*a[i][k];
			}
			for(int i=0; i<a.NRows(); i++)
			{
				if(std::fabs(b[i])<eps) b[i]=0;
			}
		}
		else
		{
			for(int k=a.NCols()-1; k>-1; k--)
			{
				double s=0;
				for(int i=k; i<a.NRows(); i++)
					s+=a[i][k]*b[i];
				for(int i=k; i<a.NRows(); i++)
					b[i]-=s*a[i][k];
			}
			for(int i=0; i<a.NRows(); i++)
			{
				if(std::fabs(b[i])<eps) b[i]=0;
			}
		}
		return b;
	}
	
	public:
	
	QRDecomposer(Matrix m) : a(m), tempara(m.NCols())
	{
		double eps = m.GetEpsilon();
		if(m.NRows()<m.NCols()) throw std::domain_error("Invalid matrix format");
		for(int k=0; k<a.NCols(); k++)
		{
			double s=0;
			for(int i=k; i<a.NRows(); i++)
			{
				s+=a[i][k]*a[i][k];
			}
			s=std::sqrt(s);
			double q=std::sqrt(s*(s+std::fabs(a[k][k])));
			if(std::fabs(q)<eps) throw std::domain_error("Matrix is singular");
			if(a[k][k]<0) s*=(-1);
			a[k][k]=(a[k][k]+s)/q;
			for(int i=k+1; i<a.NRows(); i++)
			{
				a[i][k]/=q;
			}
			tempara[k]=(-1)*s;
			for(int j=k+1; j<a.NCols(); j++)
			{
				s=0;
				for(int i=k; i<a.NRows(); i++)
				{
					s+=a[i][k]*a[i][j];
				}
				for(int i=k; i<a.NRows(); i++)
				{
					a[i][j]-=s*a[i][k];
				}
			}
		}
	}

	void Solve(const Vector &b, Vector &x) const
	{
		if(a.NRows()!=a.NCols()) throw std::domain_error("Matrix is not square");
		if(b.NElems()!=a.NRows() || b.NElems()!=x.NElems()) throw std::domain_error("Incompatible formats");
		Vector bekica(MulQTWith(b));
		for(int i=a.NCols()-1; i>-1; i--)
		{
			double s=bekica[i];
			for(int j=i+1; j<a.NCols(); j++)
			{
				s-=perm(i,j)*x[j];
			}
			x[i]=s/perm(i,i);
		}
	}
	
	Vector Solve(Vector b) const
	{
		Vector veka(b.NElems());
		Solve(b,veka);
		return veka;
	}
	
	void Solve(Matrix &b, Matrix &x) const
	{
		if(a.NRows()!=a.NCols()) throw std::domain_error("Matrix is not square");
		if(b.NCols()!=a.NRows() || b.NRows()!=a.NCols() || x.NRows()!=a.NCols() || x.NCols()!=a.NRows()) throw std::domain_error("Incompatible formats");
		
		for(int i=0; i<b.NCols(); i++)
		{
			Vector veka1(b.NRows()), veka2(b.NRows());
			for(int j=0; j<b.NRows(); j++)
			{
				veka1[j]=b[j][i];
			}
			Solve(veka1,veka2);
			for(int j=0; j<b.NRows(); j++)
			{
				x[j][i]=veka2[j];
			}
		}
	}
	

	Matrix Solve(Matrix b) const
	{
		Matrix m(b.NRows(), b.NCols());
		Solve(b,m);
		return m;
	}
	
	
	Vector MulQWith(Vector v) const {return MulQWithVektor(v,false);}
	Matrix MulQWith(Matrix m) const {return MulQWithMatrica(m,false);}
	Vector MulQTWith(Vector v) const {return MulQWithVektor(v,true);}
	Matrix MulQTWith(Matrix m) const {return MulQWithMatrica(m,true);}
	
	
	Matrix GetR() const
	{
		Matrix erica(a.NRows(), a.NCols());
		for(int i=0; i<erica.NRows(); i++)
		{
			for(int j=0; j<erica.NCols(); j++)
			{
				erica[i][j]=perm(i,j);
			}
		}
		return erica;
	}
	
	Matrix GetQ() const
	{
		Matrix qlica(a.NRows(), a.NRows());
		for(int j=0; j<a.NRows(); j++)
		{
			for(int i=0; i<a.NRows(); i++)
			{
				qlica[i][j]=0;
			}
			qlica[j][j]=1;
			for(int k=a.NCols()-1; k>-1; k--)
			{
				double s=0; 
				for(int i=k; i<a.NRows(); i++)
					s+=a[i][k]*qlica[i][j];
				for(int i=k; i<a.NRows(); i++)
				{
					qlica[i][j]-=s*a[i][k];
				}
				
			}
		}
		return qlica;
	}


	
};

void testmatrice()
{
	try
	{
		Matrix mat{{1,2,3},{8,7,1},{6,2,3}}, mat1{{3,3,2},{7,7,2},{6,0,4}};
		(LeftDiv(mat,mat1)).Print(10);
		std::cout<<"\n";
		(mat/mat1).Print(10);
		std::cout<<"\n";
		(mat*mat1).Print(10);
		std::cout<<"\n";
		mat.ReduceToRREF();
		mat.Print(10);
		std::cout<<"\n";
		mat=RREF(mat1);
		mat.Print(10);
		std::cout<<"\n \n";
	}
	catch(std::domain_error e)
	{
		std::cout<<e.what();
	}
}

void LUtest()
{
	try{
	Matrix mat{{1,2,3},{8,7,1},{6,2,3}}, mat1{{3,3,2},{7,7,2},{6,0,4}};
	LUDecomposer LUtamtrazimobecanusrecu(mat);
	LUtamtrazimobecanusrecu.GetL().Print(10);
	std::cout<<"\n";
	LUtamtrazimobecanusrecu.GetU().Print(10);
	std::cout<<"\n";
	}catch(std::domain_error e)
	{
		std::cout<<e.what();
	}
	
}

void QRtest()
{
	try{
	Matrix mat{{1,2,3},{8,7,1},{6,2,3}}, mat1{{3,3,2},{7,7,2},{6,0,4}};
	QRDecomposer qrica(mat);
	qrica.GetQ().Print(10);
	std::cout<<"\n";
	qrica.GetR().Print(10);
	std::cout<<"\n";
	Vector veka{1,2,3};
		mat1=qrica.MulQWith(veka);
		mat1.Print(10);
	}
	catch(std::domain_error e)
	{
		std::cout<<e.what();
	}
		
}


int main() {
	
	testmatrice();
	LUtest();
	QRtest();

}

