//By frphn
//Made a short program as a reminder for me on how to compile link
//lacks a proper button interface and confitional for specific events


#include <iostream>
#include <string>
using namespace std;


int main()
{

    std::string response; 
    std::cout << "Need a reminder on How to Compile and Link separately with g++ ? "<< std::endl;
    cout << "Enter Y or N:" <<endl;
    getline (cin,response);
    //If N then say oh alright, take care... Create a conditional that does prev
    //If Y do the following
    cout << "Review: "<< endl;
    cout << "g++ -c A.cpp B.cpp C.cpp main.cpp" << endl;
     cout << "will generate" << endl;
      cout << "A.o B.o C.o main.o" << endl;
       cout << "Then" << endl;
        cout << "g++ -o my_program A.o B.o C.o main.o" << endl;
         cout << "Will link the objects into a single executable my_program" << endl;
}
//    std::cout << "Enter Y(Yes):" << std::cin >> >>std :: endl; << std::endl;
//    std::cout << "Enter N(No):" <<std::endl;
//
//     
//    std::cout << "How to Compile and Link separately with g++" << std::endl;




// = "y";
//89 = Y
//78 = N
//purpose of this was to demonstrate linking object files in an executable