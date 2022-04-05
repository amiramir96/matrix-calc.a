#include "Matrix.hpp"

using std::istream;
using std::ostream;

namespace zich
{

    bool compare_proportion(const Matrix& mat1, const Matrix& mat2){ return (mat1.get_row() == mat2.get_row() && mat1.get_col() == mat2.get_col()); }

    Matrix::Matrix (const std::vector<double>& mat, int row, int col) 
    {
        if (row <= 0 || col <= 0)
        {
            throw std::invalid_argument("cannot get negative or zero as sizes input");
        }
        std::copy(mat.begin(), mat.end(), std::back_inserter(this->my_mat));
        this->col = col;
        this->row = row;
    }
    Matrix::~Matrix()
    {
        this->my_mat.clear();
    }

    /* arithmetic operators */
    Matrix operator-(const Matrix& mat){ return Matrix({1}, 1, 1); }
    Matrix operator-(const Matrix& mat1, const Matrix& mat2){ return Matrix({1}, 1, 1); }
    Matrix operator-(const Matrix& mat, double num){ return Matrix({1}, 1, 1); }
    void operator-=(Matrix& origin, const Matrix& mat_sub){};
    void operator-=(Matrix& origin, double num){};

    Matrix operator+(const Matrix& mat){ return Matrix({1}, 1, 1); }
    Matrix operator+(const Matrix& mat1, const Matrix& mat2){ return Matrix({1}, 1, 1); }
    Matrix operator+(const Matrix& mat, double num){ return Matrix({1}, 1, 1); }
    void operator+=(Matrix& origin, const Matrix& mat_add){}
    void operator+=(Matrix& origin, double num){}

    Matrix operator*(const Matrix& mat){ return Matrix({1}, 1, 1); }
    Matrix operator*(const Matrix& mat1, const Matrix& mat2){ return Matrix({1}, 1, 1); }
    Matrix operator*(const Matrix& mat, double num){ return Matrix({1}, 1, 1); }
    Matrix operator*(double num, const Matrix& mat){ return Matrix({1}, 1, 1); }
    void operator*=(Matrix& origin, const Matrix& mat_mul){}
    void operator*=(Matrix& origin, double num){}

    void operator++(Matrix& mat){}
    void operator++(Matrix& mat, int dummy_flag_for_postfix_increament){}

    void operator--(Matrix& mat){}
    void operator--(Matrix& mat, int dummy_flag_for_postfix_increament){}

    /* boolean operators */
    bool operator==(const Matrix& mat1, const Matrix& mat2){ return compare_proportion(mat1, mat2); }
    bool operator!=(const Matrix& mat1, const Matrix& mat2){ return compare_proportion(mat1, mat2); }
    bool operator<(const Matrix& mat1, const Matrix& mat2){ return compare_proportion(mat1, mat2); }
    bool operator<=(const Matrix& mat1, const Matrix& mat2){ return compare_proportion(mat1, mat2); }
    bool operator>(const Matrix& mat1, const Matrix& mat2){ return compare_proportion(mat1, mat2); }
    bool operator>=(const Matrix& mat1, const Matrix& mat2){ return compare_proportion(mat1, mat2); }

    // Global Operators
    istream &operator>>(istream &in, const Matrix &mat) { return in; }
    ostream &operator<<(ostream &out, const Matrix &mat){ return out; }

}