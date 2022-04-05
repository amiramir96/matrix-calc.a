#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::istream;
using std::ostream;
using std::vector;

namespace zich
{

class Matrix 
{
    private:
        
        int row, col;
        std::vector<double> my_mat;

    public:

        /* constructor */
        Matrix() = default;
        Matrix (const std::vector<double>& mat, int row, int col);
        ~Matrix();

        // getters
        int get_row() const{ return this->row; }
        int get_col() const{ return this->col; }
        std::vector<double> get_mat(); 
        double get_sum(); // sum all fields
        
        /* arithmetic operators */
        friend Matrix operator-(const Matrix& mat);
        friend Matrix operator-(const Matrix& mat1, const Matrix& mat2);
        friend Matrix operator-(const Matrix& mat, double num);
        friend void operator-=(Matrix& origin, const Matrix& mat_sub);
        friend void operator-=(Matrix& origin, double num);

        friend Matrix operator+(const Matrix& mat);
        friend Matrix operator+(const Matrix& mat1, const Matrix& mat2);
        friend Matrix operator+(const Matrix& mat, double num);
        friend void operator+=(Matrix& origin, const Matrix& mat_add);
        friend void operator+=(Matrix& origin, double num);

        friend Matrix operator*(const Matrix& mat);
        friend Matrix operator*(const Matrix& mat1, const Matrix& mat2);
        friend Matrix operator*(const Matrix& mat, double num);
        friend Matrix operator*(double num, const Matrix& mat);
        friend void operator*=(Matrix& origin, const Matrix& mat_mul);
        friend void operator*=(Matrix& origin, double num);

        friend void operator++(Matrix& mat);
        friend void operator++(Matrix& mat, int dummy_flag_for_postfix_increament);

        friend void operator--(Matrix& mat);
        friend void operator--(Matrix& mat, int dummy_flag_for_postfix_increament);

        /* boolean operators */
        friend bool operator==(const Matrix& mat1, const Matrix& mat2);
        friend bool operator!=(const Matrix& mat1, const Matrix& mat2);

        friend bool operator<(const Matrix& mat1, const Matrix& mat2);
        friend bool operator<=(const Matrix& mat1, const Matrix& mat2);

        friend bool operator>(const Matrix& mat1, const Matrix& mat2);
        friend bool operator>=(const Matrix& mat1, const Matrix& mat2);

        // global
        friend istream &operator>>(istream &in, const Matrix &mat);
        friend ostream &operator<<(ostream &out, const Matrix &mat);

};        


        
}   