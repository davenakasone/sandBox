/*
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

    sleep_for(10ns);
    sleep_until(system_clock::now() + 1s);
    */



    /*
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    */
    


     /*
    #include <iostream>
    #include <ctime>

    using namespace std;

    void sleep(float seconds){
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    // do nothing until the elapsed time has passed.
    while(clock() < startClock+secondsAhead);
    return;
    }
    int main(){

    cout << "Next string coming up in one second!" << endl;
    sleep(1.0);
    cout << "Hey, what did I miss?" << endl;

    return 0;
    }
    */
    


     /*
    #include<chrono>
#include<thread>

int main(){
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
}
    */


    /*
        The correct syntax will be: cout << "Flushing the output stream." << flush; 
        If you are using a clear screen command (system ("CLS");) in the middle of a program and it does not 
        appear to be working ... flush the cout statements which precede the clear screen command

        also OS dependent
    */
//

#include <iostream>
#include <chrono>
#include <thread>


int main() {
    std::cout << "\nThis is the easiest way to delay (3 seconds)...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "just make sure you have <chrono> and <thread>\n";

    std::cout << "dealying then clearing is useful...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout.flush();
    system("clear");
    std::cout << "it doesn't need any header files.\n";

    // windows system("pause"); ....will wait for a key stroke
    // unix based:
    //system("read"); // there are lots of them...most are really big security risks
    
return 0;
}