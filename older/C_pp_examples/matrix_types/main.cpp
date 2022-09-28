/*
    control headers through heads.h
    all librarys in libs.h
    in real life, you wouldn't have the acompanying 2D matrix with each obj...just there to show paralell
    should make template, but all objs kept to integers so focus can be on DS/A

    diagMtx   (diagonal matrix)
    lowT      (lower triangular matrix)
    UpT       (upper triangular matrix)
    symm      (symetrical matrix)
    triD      (tri-diagonal matrix)
    toep      (toeplitz matrix)
    spr       (sparse matrix)
    poly      (any polynomial ..int)

*/

#include "heads.h"

std::string DIS = "continue";
const int Blank = INT_MIN;

void pauseClear();
void diagonalDemo();
void lowTriDemo();
void upTriDemo();
void symDemo();
void triDiDemo();
void toepDemo();
void sprDemo();
void polyDemo();
//--------------------------------------------------------------------------------------------------------------------------
//==========================================================================================================================
int main() 
{
    //diagonalDemo();
    //lowTriDemo();
    //upTriDemo();
    //symDemo();
    //triDiDemo();
    //toepDemo();
    //sprDemo();
    polyDemo();

    std::cout << "\n\n ~ ~ ~ ~ PROGRAM COMPLETE ~ ~ ~ ~ \n";
    return 0; 
}

//--------------------------------------------------------------------------------------------------------------------------
void pauseClear()
{
    std::cout << "\npress any key and hit [enter] to proceed: ";    
    std::cin >> DIS;                                           
    std::cout.flush();
    system("clear");
}

//--------------------------------------------------------------------------------------------------------------------------
void diagonalDemo()
{
    std::cout << std::endl;
    diagMtx Test(6, "TEST");
    Test.printMtx();
    Test.buildRandom(7);
    Test.printMtx();
    diagMtx Dummy(Test, "DUMMY");
    Dummy.printMtx();
    pauseClear();
    Test.buildRandom(9);
    Test.printMtx();
    Test.set(4,4,99);
    Test.set(3,3,11);
    Test.printMtx();
    std::cout << "the value at row 3, col 3 is : " << Test.getVal(3,3) << std::endl;
    Test.set(3,2,1); // should fail
}

//--------------------------------------------------------------------------------------------------------------------------
void lowTriDemo()
{
    std::cout << std::endl;
    lowT Test(6, "TEST");
    Test.printMtx();
    Test.buildRandom(7);
    Test.printMtx();
    lowT Dummy(Test, "DUMMY");
    Dummy.printMtx();
    pauseClear();
    Test.buildRandom(5);
    Test.printMtx();
    Test.set(4,4,99);
    Test.set(3,3,11);
    Test.printMtx();
    std::cout << "the value at row 3, col 3 is : " << Test.getVal(3,3) << std::endl;
    Test.set(1,3,1); // should fail
}

//--------------------------------------------------------------------------------------------------------------------------
void upTriDemo()
{
    std::cout << std::endl;
    upT Test(6, "TEST");
    Test.printMtx();
    Test.buildRandom(7);
    Test.printMtx();
    upT Dummy(Test, "DUMMY");
    Dummy.printMtx();
    pauseClear();
    Test.buildRandom(5);
    Test.printMtx();
    Test.set(4,4,99);
    Test.set(3,3,11);
    Test.printMtx();
    std::cout << "the value at row 3, col 3 is : " << Test.getVal(3,3) << std::endl;
    Test.set(3,1,1); // should fail
}

//--------------------------------------------------------------------------------------------------------------------------
void symDemo()
{
    std::cout << std::endl;
    symm Test(6, "TEST");
    Test.printMtx();
    Test.buildRandom(7);
    Test.printMtx();
    symm Dummy(Test, "DUMMY");
    Dummy.printMtx();
    pauseClear();
    Test.buildRandom(5);
    Test.printMtx();
    Test.set(4,4,99);
    Test.set(3,3,11);
    Test.printMtx();
    std::cout << "the value at row 3, col 3 is : " << Test.getVal(3,3) << std::endl;
    Test.set(3,1,1); // no fail
}

//--------------------------------------------------------------------------------------------------------------------------
void triDiDemo()
{
    std::cout << std::endl;
    triD Test(6, "TEST");
    Test.printMtx();
    Test.buildRandom(7);
    Test.printMtx();
    triD Dummy(Test, "DUMMY");
    Dummy.printMtx();
    pauseClear();
    Test.buildRandom(5);
    Test.printMtx();
    Test.set(4,4,99);
    Test.set(3,3,11);
    Test.printMtx();
    std::cout << "the value at row 3, col 3 is : " << Test.getVal(3,3) << std::endl;
    Test.set(0,3,1); // should be rejected
}

//--------------------------------------------------------------------------------------------------------------------------
void toepDemo()
{
    std::cout << std::endl;
    toep Test(6, "TEST");
    Test.printMtx();
    Test.buildRandom(7);
    Test.printMtx();
    toep Dummy(Test, "DUMMY");
    Dummy.printMtx();
    pauseClear();
    Test.buildRandom(5);
    Test.printMtx();
    Test.set(4,2,99);
    Test.set(3,3,11);
    Test.printMtx();
    std::cout << "the value at row 3, col 3 is : " << Test.getVal(3,3) << std::endl;
    Test.set(0,3,1); // no fail
}

//--------------------------------------------------------------------------------------------------------------------------
void sprDemo()
{
    std::cout << std::endl;
    std::cout << "\t\t\t\t\t\t\t\t\t 1) checking default constructor, build 4 rows, 6 columns, 3 sparse elements\n";
    spr Test(4,6,3,"TEST");
    Test.print();
    pauseClear();

    std::cout << "\n\t\t\t\t\t\t\t\t\t 2) checking copy constructor: 3 rows, 4 columns, 5 sparse elements\n";
    Test.buildRandom(3, 4, 5);
    Test.print();
    spr Dummy(Test, "DUMMY");
    Dummy.print();
    pauseClear();
    
    std::cout << "\n\t\t\t\t\t\t\t\t\t 3) checking set and get\n";
    Test.buildRandom(5, 5, 1);
    Test.print();
    std::cout << "value @ row: 1 col: 1 = " << Test.getVal(1, 1) << " ...negative means blank\n";
    std::cout << "setting row: 1 col: 1 to = 99\n";
    Test.set(1, 1, 99);
    Test.print();
    std::cout << "value @ row: 1 col: 1 = " << Test.getVal(1, 1) << " ...negative means blank\n";
    pauseClear();
    
    std::cout << "\n\t\t\t\t\t\t\t\t\t 4) set all, delete to pattern\n";
    Test.buildRandom(3, 3, 3); // OPEN ME
    Test.print();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) // make > 3 to see invlaid index work (it does)
        {
            Test.set(i,j,-4); 
        }
    }
    Test.print();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Test.set(i,j,66);
        }
    }
    Test.print();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Test.set(i,j,Blank);
        }
    }
    Test.print();
    pauseClear();
    
    std::cout << "\n\t\t\t\t\t\t\t\t\t 5) check addition\n";
    spr mtxA(4,4,4,"Matrix_A");
    spr mtxB(mtxA,"Matrix_B");
    mtxA.print();
    mtxB.print();
    std::cout << "                                       matrix A + matrix B = \n\n";
    mtxA.addOther(mtxB);
    mtxA.print();
    pauseClear();
    
    std::cout << "\n\t\t\t\t\t\t\t\t\t 6)  more check addition\n";
    spr mtxC(3,6,3,"Matrix_C");
    mtxC.wipe();
    mtxC.set(0,0,5);
    mtxC.set(1,1,10);
    mtxC.set(2,2,20);
    mtxC.set(0,5,40);
    mtxC.print();
    spr mtxD(3,6,3,"Matrix_D");
    mtxD.wipe();
    mtxD.set(0,0,7);
    mtxD.set(1,4,19);
    mtxD.print();
    std::cout << "                                             matrix_C + matrix_D = \n\n";
    mtxC.addOther(mtxD);
    mtxC.print();
    pauseClear();
}

//--------------------------------------------------------------------------------------------------------------------------
void polyDemo()
{
    std::cout << std::endl;
    std::cout << "\n 1)  default constructor & default constructor w/ parameters\n";
    poly Test0;
    Test0.print(); // defaults took well
    poly Test(9,6, "TEST");
    Test.print();
    pauseClear();

    std::cout << std::endl;
    std::cout << "\n 2)  constructor from file & copy constructor\n";
    poly Dummy("poly_input.txt", "DUMMY"); // made obj from file
    Dummy.print();
    poly DummyC(Dummy,"DUMMY-C"); // copy constructor 
    DummyC.print();
    pauseClear();

    std::cout << std::endl;
    std::cout << "\n 3)  randomBuild & set\n";
    Test.buildRand(4, 5);
    Test.print();
    Test.set(9,9); // shoud be error
    Test.set(4,3);
    Test.print();
    Test.set(0,0);
    Test.print();
    Test.set(1,0);
    Test.print(); 
    Test.set(4,0);
    Test.print();
    Test.set(3,0);
    Test.print();
    Test.set(2,0);
    Test.print(); //should be blank
    pauseClear();

    std::cout << std::endl;
    std::cout << "\n 4)  get coef\n";
    Test.buildRand(5, 3);
    Test.print();
    std::cout << "the coefficent @ exp " << 9 << " is: " << Test.getCoef(9) << std::endl;
    for (int i = 5; i >= 0; i--)
    {
        std::cout << "the coefficent @ exp " << i << " is: " << Test.getCoef(i) << std::endl;
    }
    pauseClear();

    std::cout << std::endl;
    std::cout << "\n 5)  copy other & add other\n";
    Dummy.buildRand(6, 4);
    Dummy.print();
    Test.copyOther(Dummy);
    Test.print();
    std::cout << " TEST + DUMMY = \n";
    Test.addOther(Dummy);
    Test.print();
    std::cout << "--------------------------------------\n";
    Test.buildRand(3, 4);
    Dummy.buildRand(5, 2);
    Test.print();
    Dummy.print();
    std::cout << " TEST + DUMMY = \n";
    Test.addOther(Dummy);
    Test.print();
    std::cout << "--------------------------------------\n";
    Test.buildRand(7, 4);
    Dummy.buildRand(5, 2);
    Test.print();
    Dummy.print();
    std::cout << " TEST + DUMMY = \n";
    Test.addOther(Dummy);
    Test.print();
    std::cout << "--------------------------------------\n";
    pauseClear();

    std::cout << std::endl;
    std::cout << "\n 6)  test evaluation\n";
    Test.buildRand(4, 3);
    Test.print();
    for (int i = 0; i < 5; i++)
    {
        std::cout << "if x = " << i << " , this polynomial is: " << Test.calcVal(i) << std::endl;
    }
    pauseClear();

}

//==========================================================================================================================
//                                           ~ ~ ~ END ~ ~ ~                                                              //
//==========================================================================================================================