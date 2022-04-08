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
        
        size_t row, col;
        double sum;
        std::vector<std::vector<double>> my_mat;

    public:

        /* constructor */
        Matrix() = default;
        Matrix(int row, int col);
        Matrix (const std::vector<double>& mat, int row, int col);
        ~Matrix();

        // getters
        size_t get_row() const{ return this->row; }
        size_t get_col() const{ return this->col; }
        std::vector<std::vector<double>> get_mat() const { return this->my_mat; }
        double get_sum() const { return this->sum; } // sum all fields
        
        // setter
        void set_sum(double val){ this->sum = val; } // change the total sum

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