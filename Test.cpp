#include <iostream>
#include "doctest.h"
#include "Matrix.hpp"

using namespace zich;

TEST_CASE("Bad inputs")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> arr2x2 = {1, 2, 3, 4};
    std::vector<double> arr3 = {1, 2, 3, 4, 5, 6};
    std::vector<double> arr_prime; 
    arr_prime.assign(arr1.begin(), arr1.end());
    arr_prime.push_back(10);
    arr_prime.push_back(11);

    SUBCASE("constructor")
    {
        SUBCASE("(zero / negative) (row / col)")
        {
            CHECK_THROWS(Matrix(identity, 0, 0));
            CHECK_THROWS(Matrix(identity, -1, 1));
            CHECK_THROWS(Matrix(identity, 1, -1));
            CHECK_THROWS(Matrix(identity, -1, -1));   
        }
        SUBCASE("wrong (row / col)")
        {
            CHECK_NOTHROW(Matrix(arr1, 3, 3));
            CHECK_THROWS(Matrix(arr1, 3, 4));
            CHECK_THROWS(Matrix(arr1, 4, 3));
        }
        SUBCASE("prime num of elements, can just one (row / col) matrix")
        {
            CHECK_THROWS(Matrix(arr_prime, 3, 4));
            CHECK_THROWS(Matrix(arr_prime, 4, 3));
            CHECK_THROWS(Matrix(arr_prime, 5, 2));
            CHECK_THROWS(Matrix(arr_prime, 2, 6));
            
            CHECK_NOTHROW(Matrix(arr_prime, 1, 11));
            CHECK_NOTHROW(Matrix(arr_prime, 11, 1));
        }
    }


    Matrix m_ident3x3(identity, 3, 3);
    Matrix m_prime1x11(arr_prime, 1, 11);
    Matrix m_2x3(arr3, 2, 3);
    Matrix m_3x2(arr3, 3, 2);
    Matrix m_1x6(arr3, 1, 6);

    SUBCASE("arithmetic operators")
    {
        SUBCASE("diffrent total size of matrix")
        {
            CHECK_THROWS(m_3x2 += m_ident3x3);
            CHECK_THROWS(m_3x2 *= m_ident3x3);
            CHECK_THROWS(m_3x2 -= m_ident3x3);
            CHECK_THROWS(m_3x2 + m_ident3x3);
            CHECK_THROWS(m_3x2 - m_ident3x3);
            CHECK_THROWS(m_3x2 * m_ident3x3);

        }
        SUBCASE("same total size but diff split of row/col")
        {
            CHECK_THROWS(m_2x3 += m_3x2);
            CHECK_THROWS(m_2x3 -= m_3x2);
            CHECK_THROWS(m_2x3 + m_3x2);
            CHECK_THROWS(m_2x3 - m_3x2);
            CHECK_THROWS(m_1x6 *= m_2x3);
            CHECK_THROWS(m_1x6 * m_2x3);

            SUBCASE("wont edit matrixes when using mul"){CHECK_NOTHROW(m_2x3 *= m_3x2);}
            CHECK_NOTHROW(m_ident3x3 * m_3x2);
        }
    }

    SUBCASE("verify boolean operators wont throw about diffrency in proportion")
    {
        CHECK_NOTHROW(bool a = m_2x3 == m_prime1x11);
        CHECK_NOTHROW(bool b = m_2x3 != m_prime1x11);
        CHECK_NOTHROW(bool c = m_2x3 < m_prime1x11);
        CHECK_NOTHROW(bool d = m_2x3 <= m_prime1x11);
        CHECK_NOTHROW(bool e = m_2x3 > m_prime1x11);
        CHECK_NOTHROW(bool f = m_2x3 >= m_prime1x11);
    }
}    


TEST_CASE("Good inputs")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> arr2x2 = {1, 2, 3, 4};
    std::vector<double> arr2x2_plus_one = {2, 3, 4, 5};
    std::vector<double> arr2x2_mul2 = {2, 4, 6, 8};
    std::vector<double> arr2x2n = {-1, -2, -3, -4};
    std::vector<double> arr3 = {1, 2, 3, 4, 5, 6};
    std::vector<double> arr_mul_2x3_3x2 = {22, 28, 49, 64};
    /*
        [1 2 3]   [1 2]
        [4 5 6]   [3 4]
                  [5 6]    

        [22 28]
        [49 64]

    */
    std::vector<double> arr1_zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<double> arr3_zero = {0, 0, 0, 0, 0, 0};
    std::vector<double> arr_zero2x2 = {0, 0, 0, 0};

    Matrix m_ident3x3(identity, 3, 3);
    Matrix m_3x3(arr1, 3, 3);
    Matrix m_2x3(arr3, 2, 3);
    Matrix m_3x2(arr3, 3, 2);
    Matrix m_1x6(arr3, 1, 6);
    Matrix m_zero3x3(arr1_zero, 3, 3);
    Matrix m_zero2x3(arr3_zero, 2, 3);
    Matrix m_2x2(arr2x2, 2, 2);
    Matrix m_2x2negative(arr2x2n, 2, 2);
    Matrix m_zero2x2(arr_zero2x2, 2, 2);
    Matrix m_2x2_plus_one(arr2x2_plus_one, 2, 2);
    Matrix m_2x2_mul2(arr2x2_mul2, 2, 2);
    Matrix m_2x3_mul_3x2(arr_mul_2x3_3x2, 2, 2);
    
    Matrix temp;

    SUBCASE("boolean operators")
    {
        SUBCASE("eq, n_eq")
        {
            CHECK_EQ(m_ident3x3, m_ident3x3);
            CHECK_EQ(true, m_1x6 == m_1x6);
            CHECK_EQ(false, m_2x3 == m_3x2);
            CHECK_EQ(false, m_3x3 == m_ident3x3);
            CHECK_EQ(false, m_3x3 == m_3x2);            

            CHECK_EQ(false, m_ident3x3 != m_ident3x3);
            CHECK_EQ(false, m_1x6 != m_1x6);
            CHECK_NE(m_2x3, m_3x2);
            CHECK_EQ(true, m_3x3 != m_ident3x3);
            CHECK_EQ(true, m_3x3 != m_3x2);            
        
        }
        SUBCASE("gt, lt, ge, le")
        {
            CHECK_EQ(false, m_ident3x3 > m_ident3x3);
            CHECK_EQ(false, m_ident3x3 < m_ident3x3);
            CHECK_EQ(true, m_ident3x3 >= m_ident3x3);
            CHECK_EQ(true, m_ident3x3 <= m_ident3x3);

            CHECK_EQ(true, m_2x2 > m_zero3x3);
            CHECK_EQ(false, m_2x2 < m_zero3x3);
            CHECK_EQ(true, m_2x2 >= m_zero3x3);
            CHECK_EQ(false, m_2x2 <= m_zero3x3);

            CHECK_EQ(false, m_2x2negative > m_zero3x3);
            CHECK_EQ(true, m_2x2negative < m_zero3x3);
            CHECK_EQ(false, m_2x2negative >= m_zero3x3);
            CHECK_EQ(true, m_2x2negative <= m_zero3x3);            
        }
    }
    SUBCASE("arithmetic operators")
    {
        SUBCASE("+ ,- operators ")
        {   

            CHECK_EQ(m_zero3x3, m_ident3x3 - m_ident3x3);

            CHECK_EQ(m_zero3x3, m_3x3 - m_3x3);
            CHECK_NE(m_zero3x3, m_3x3 + m_3x3);
            
            CHECK_EQ(true, m_zero2x2 == (m_2x2 + m_2x2negative));
            CHECK_EQ(false, m_zero2x2 == (m_2x2 - m_2x2negative));
            
            SUBCASE("use += -=")
            {
                m_ident3x3 -= m_ident3x3;
                CHECK_EQ(true, m_zero3x3 == m_ident3x3);

                m_3x3 += m_3x3;
                CHECK_NE(m_zero3x3, m_3x3);
            }
        }
        SUBCASE("* operator ")
        {
            SUBCASE("mul by zero")
            {
                SUBCASE("by the zero mat")
                {
                    CHECK_EQ(m_zero2x2, m_2x2*m_zero2x2);
                    CHECK_NE(m_zero2x2, m_2x2*m_zero2x3);
                    CHECK_EQ(m_zero2x3, m_2x2*m_zero2x3);
                }      
                SUBCASE("use *=")
                {
                    m_2x2_plus_one *= m_zero2x3;
                    m_2x2negative *= m_zero2x3;
                    CHECK_NE(m_zero2x2, m_2x2_plus_one);
                    CHECK_EQ(m_zero2x3, m_2x2negative);
                }
            }
            SUBCASE("mul with ident")
            {
                CHECK_EQ(true, m_3x3 == (m_3x3*m_ident3x3));
                CHECK_EQ(true, m_2x3 == (m_2x3*m_ident3x3));
            
                m_3x3 *= m_ident3x3;
                CHECK_EQ(m_3x3, m_3x3);
                m_2x3 *= m_ident3x3;
                CHECK_EQ(m_2x3, m_2x3);
            }
            SUBCASE("mul by num")
            {
                CHECK_EQ(m_2x2_mul2, m_2x2 * 2);
                CHECK_EQ(m_2x2_mul2, 2 * m_2x2);

                m_2x2 *= 2;
                CHECK_EQ(m_2x2_mul2, m_2x2);
            }
            SUBCASE("mul with no ident mat")
            {
                CHECK_EQ(m_2x3_mul_3x2, m_2x3 * m_3x2);
                CHECK_NE(m_2x3_mul_3x2, m_3x2 * m_2x3);

                Matrix m_mul = m_2x3*m_3x2;
                m_2x3 *= m_3x2;
                CHECK_EQ(m_mul, m_2x3);
            }
        }

        SUBCASE("++, --, increase then decrease same matrix")
        {
            CHECK_EQ(false, m_2x2_plus_one == m_2x2);
            m_2x2++;
            ++m_2x2;
            m_2x2--;
            CHECK_EQ(true, m_2x2_plus_one == m_2x2);
            --m_2x2;
            CHECK_EQ(false, m_2x2_plus_one == m_2x2);
        }
    }
}