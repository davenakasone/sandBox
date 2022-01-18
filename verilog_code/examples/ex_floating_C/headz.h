/*
    user defined
*/

#ifndef H_headz
#define H_headz

#include "ieee745_num.h"  // struct to hold floating number

void proof(); // proving for a class

// add 2 iee745 numbers, combines many functions
int add_nums(ieee745* numA, ieee745* numB, ieee745* result);

// get absolute value of a double, magnitude needs
double dub_abs(ieee745* given);

// load number to struct
int loadNum(ieee745* inst, int sign, int* exp, int* flt, bool initGRS);    

// initialization of struct for padding and assurance
int init_nums(ieee745* newNum);

// deep copy a number struct
int copy_num(ieee745* in_data, ieee745* copy_to);

// compare binary arrays
bool compare_bins(int* bin_A, int* bin_B, int length);

// call to print number in detail
int printNumDetail(ieee745* stcNum);   

// print bins w/ or w/o header  + custom message
int print_SHEFgrs(ieee745* stcNum, bool head, char* message);  

// proper right shift, usually for alignment and adjust with carry out
int shift_right_EHFgrs(ieee745* numIn);

// basic right shift  MSB @ idx = 0
int shift_right(int left_fill, int* bin, int length);

// proper left shift, usually for adjust with borrow out
int shift_left_EHFgrs(ieee745* numIn);

// basic left shift  MSB @ idx = 0
int shift_left(int right_fill, int* bin, int length);

// the full adder
int full_adder(int* bin_A, int* bin_B, int* bin_c, int c_in, int start, int stop);
int fa_sum(int a_bit, int b_bit, int in_c);
int fa_cout(int a_bit, int b_bit, int in_c);

// the full subtractor
int full_sub(int* inX, int* inY, int* outA, int b_in, int start, int stop);
int fs_diff(int x_bit, int y_bit, int in_bor);
int fs_bout(int x_bit, int y_bit, int in_bor);

ieee745 g_numA;
ieee745 g_numAog;
ieee745 g_numB;
ieee745 g_numBog;
ieee745 g_result;

int g_status;

FILE fpWite;
FILE fpRead;


#endif


////////~~~~~~~~END>  headz.h
