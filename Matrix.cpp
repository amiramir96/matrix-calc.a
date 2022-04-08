#include "Matrix.hpp"

using std::istream;
using std::ostream;

namespace zich
{

    bool compare_proportion(const Matrix& mat1, const Matrix& mat2)
    /* this function check if col, row of two matrixes is completely the same! */
    { return (mat1.get_row() == mat2.get_row() && mat1.get_col() == mat2.get_col()); }

    bool possible_to_mul(const Matrix& mat1, const Matrix& mat2)
    /* this function verify that we can do the multiplication operation of 'mat1*mat2' via mat1_col == mat2_row */
    { return mat1.get_col() == mat2.get_row(); }

    Matrix::Matrix (const std::vector<double>& mat, int row, int col) 
    {        /* constructor, will make a 2dim vector filled by the mat input values */

        if (row <= 0 || col <= 0)
        {
            throw std::invalid_argument("cannot get negative or zero as sizes input\n");
        }
        if (row*col != mat.size())
        {
            throw std::invalid_argument("size of vector not equal to 2dim matrix\n");
        }

        double fields_value = 0;
        size_t temp = 0;
        for (int i=0; i < row; i++)
        {
            this->my_mat.push_back(std::vector<double>((size_t)col));
            for (int j=0; j < col; j++)
            {
                temp = (size_t)(i*col +j);
                this->my_mat[(size_t)i][(size_t)j] = (mat[temp]); // the row idx i -> i rows, ea row 'col' fields, + j fields to curr field
                fields_value += mat[temp];
            }            
        }
        this->col = (size_t)col;
        this->row = (size_t)row;
        this->sum = fields_value;
    
    }

    Matrix::Matrix (int row, int col)
    { /* returns zero mat with row*col sizes */
        if (row <= 0 || col <= 0)
        {
            throw std::invalid_argument("cannot get negative or zero as sizes input\n");
        }

        for (int i=0; i < row; i++)
        { // create the 2nd dim
            this->my_mat.push_back(std::vector<double>((size_t)col));      
        }
        this->col = (size_t)col;
        this->row = (size_t)row;
        this->sum = 0;
    }
    Matrix::~Matrix()
    {
        this->my_mat.clear();
    }

    /* arithmetic operators */
    Matrix operator-(const Matrix& mat) { /* just use mul func to return negative mat */ return mat * -1; }
    Matrix operator-(const Matrix& mat1, const Matrix& mat2)
    { /* sub between two matrixes, set ans at new matrix same sizes (named res) */
        if (!compare_proportion(mat1, mat2))
        {
            throw std::invalid_argument("matrixes sizes is not the same, cant support this operation\n");
        }

        Matrix res(mat1.get_row(), mat1.get_col()); // result mat same sizes
        for (size_t i=0; i < res.get_row(); i++) // minus cal
        {
            for (size_t j=0; j < res.get_col(); j++)
            {
                res.my_mat[i][j] = mat1.my_mat[i][j] - mat2.my_mat[i][j]; // set ans at res matrix
            }
        }
        res.set_sum(mat1.get_sum() - mat2.get_sum()); // update totalsum field
        return res;
    }
    void operator-=(Matrix& origin, const Matrix& mat_sub)
    { /* sub between two matrixes, origin matrix is the one being subbed */
        if (!compare_proportion(origin, mat_sub))
        {
            throw std::invalid_argument("matrixes sizes is not the same, cant support this operation\n");
        }

        for (size_t i=0; i < origin.get_row(); i++) // minus cal
        {
            for (size_t j=0; j < origin.get_col(); j++)
            {
                origin.my_mat[i][j] -= mat_sub.my_mat[i][j]; // set ans at origin matrix
            }
        }
        origin.set_sum(origin.get_sum() - mat_sub.get_sum()); // update totalsum field
    }

    Matrix operator-(const Matrix& mat, double num){ return Matrix({1}, 1, 1); }
    void operator-=(Matrix& origin, double num){};

    Matrix operator+(const Matrix& mat){ /* just use mul func to return positive same mat */ return mat * 1; }
    Matrix operator+(const Matrix& mat1, const Matrix& mat2)
    { /* add between two matrixes, set ans at new matrix same sizes (named res) */
        if (!compare_proportion(mat1, mat2))
        {
            throw std::invalid_argument("matrixes sizes is not the same, cant support this operation\n");
        }

        Matrix res(mat1.get_row(), mat1.get_col()); // result mat same sizes
        for (size_t i=0; i < res.get_row(); i++) // additive cal
        {
            for (size_t j=0; j < res.get_col(); j++)
            {
                res.my_mat[i][j] = mat1.my_mat[i][j] + mat2.my_mat[i][j]; // set ans at res matrix
            }
        }
        res.sum = mat1.sum + mat2.sum; // update totalsum field
        return res;
    }
    void operator+=(Matrix& origin, const Matrix& mat_add)
    { /* add between two matrixes, origin matrix is the one being added */
        if (!compare_proportion(origin, mat_add))
        {
            throw std::invalid_argument("matrixes sizes is not the same, cant support this operation\n");
        }

        for (size_t i=0; i < origin.get_row(); i++) // additive cal
        {
            for (size_t j=0; j < origin.get_col(); j++)
            {
                origin.my_mat[i][j] += mat_add.my_mat[i][j]; // set ans at origin matrix
            }
        }
        origin.sum += mat_add.sum; // update totalsum field
    }
    
    Matrix operator+(const Matrix& mat, double num){ return Matrix({1}, 1, 1); }
    void operator+=(Matrix& origin, double num){}

    Matrix operator*(const Matrix& mat){ return Matrix({1}, 1, 1); }
    
    Matrix operator*(const Matrix& mat1, const Matrix& mat2)
    { /* read here for definition of matrix mul: https://en.wikipedia.org/wiki/Matrix_multiplication
        the funct first verify that we can operate the mul 
        then, exec multiplication and save the values of ea field at result Matrix */
        if (!possible_to_mul(mat1, mat2))
        {
            throw std::invalid_argument("mat1.col != mat2.row => cannot mul them! \n");
        }

        Matrix res(mat1.get_row(), mat2.get_col());
        for (size_t i=0; i < mat1.get_row(); i++)
        { // row of mat1
            for (size_t j=0; j < mat2.get_col(); j++)
            { // col of mat2  
                for (size_t k=0; k < mat1.get_col(); k++)
                { // shared size (col mat1 // row mat 2)
                // current field of rest mat == [row of mat1][col of mat2]
                    res.my_mat[i][j] += mat1.my_mat[i][k] * mat2.my_mat[k][j]; 
                }
                res.sum += res.my_mat[i][j];
            }
        }
        return res;
    }
    void operator*=(Matrix& origin, const Matrix& mat_mul)
    { /* will use mul bet 2 matrixes and then switch origin to be res matrix */
        Matrix res = origin * mat_mul;
        origin = res;
    }
    Matrix operator*(const Matrix& mat, double num)
    { /* mul by scalar-'num' all fields of mat and set it at new matrix and returns it */
        Matrix res(mat.get_row(), mat.get_col()); // result matrix
        for (size_t i=0; i < res.get_row(); i++)
        {
            for (size_t j=0; j < res.get_col(); j++)
            {
                res.my_mat[i][j] = mat.my_mat[i][j] * num; // mul by scalar-'num'
            }
        }
        res.set_sum(mat.get_sum()*num); // update total sum field
        return res;
    }
    Matrix operator*(double num, const Matrix& mat)
    /* same as the above function, multiplie scalar and matrix is commutative operating ! */
    { return mat * num; }
    void operator*=(Matrix& origin, double num)
    { /* mul by scalar-'num' all fields of mat */
        for (size_t i=0; i < origin.get_row(); i++)
        {
            for (size_t j=0; j < origin.get_col(); j++)
            {
                origin.my_mat[i][j] *= num; // mul by scalar-'num'
            }
        }
        origin.set_sum(origin.get_sum()*num); // update total sum field
    }

    void operator++(Matrix& mat)
    { /* increament all fields of matrix by 1 */
        for (size_t i=0; i < mat.get_row(); i++)
        {
            for (size_t j=0; j < mat.get_col(); j++)
            {
                mat.my_mat[i][j] += 1;
            }
        }
    }
    void operator++(Matrix& mat, int dummy_flag_for_postfix_increament){ /*just use increament*/ ++mat; }

    void operator--(Matrix& mat)
    { /* decrease all fields of matrix by 1 */
        for (size_t i=0; i < mat.get_row(); i++)
        {
            for (size_t j=0; j < mat.get_col(); j++)
            {
                mat.my_mat[i][j] -= 1;
            }
        }
    }
    void operator--(Matrix& mat, int dummy_flag_for_postfix_increament){ /*just use decrease*/ --mat; }

    /* boolean operators */
    bool operator==(const Matrix& mat1, const Matrix& mat2)
    { /* compare all fields of mat1, mat2, if and only if completly the same -> returns true*/
        bool not_same = false;
        if (!compare_proportion(mat1, mat2))
        { // sizes not same
            return not_same;
        }
        for (size_t i=0; i < mat1.get_row(); i++)
        {
            for (size_t j=0; j < mat1.get_col(); j++)
            {
                if (mat1.my_mat[i][j] != mat2.my_mat[i][j])
                {
                    return not_same; // one field not same is enough to return false 
                }
            }
        }
        return !not_same; // no false = true
    }
    bool operator!=(const Matrix& mat1, const Matrix& mat2)
    /* not == is same as !=, at least one field of matrixes is not the same will return true */
    { return !(mat1 == mat2); }
    bool operator<(const Matrix& mat1, const Matrix& mat2)
    /* mat1 < mat2 means mat1.sum < mat2.sum */
    { return mat1.sum < mat2.sum; }
    bool operator<=(const Matrix& mat1, const Matrix& mat2)
    /* mat1 <= mat2 means: mat1.sum <= mat2.sum equivalent to  not(mat1.sum > mat2.sum) */
    { return !(mat1 > mat2); }
    bool operator>(const Matrix& mat1, const Matrix& mat2)
    /* mat1 < mat2 means mat1.sum > mat2.sum */
    { return mat1.sum > mat2.sum; }
    bool operator>=(const Matrix& mat1, const Matrix& mat2)
    /* mat1 >= mat2 means: mat1.sum >= mat2.sum equivalent to  not(mat1.sum < mat2.sum) */
    { return !(mat1 < mat2); }

    // Global Operators
    istream &operator>>(istream &in, const Matrix &mat) { return in; }
    ostream &operator<<(ostream &out, const Matrix &mat){ return out; }

}