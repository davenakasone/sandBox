/*
    ensure Eigen install is good
*/

#include <cstdio>
#include <cstdlib>
#include <../Eigen/Dense>
#include <iostream>

void test();


int main()
{
    test();

    std::printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;           
}


void test()
{
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
}


////////~~~~~~~~END>  main.cpp
