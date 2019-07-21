// Author: Kartikei Mittal @kartikeimittal@gmail.com
// Project: https://github.com/Kartikei-12/rex-sort
// main.cpp file for project rex-sort,
// which is sorting algorithm which
// leverage feature of Linked List
// that allows insertion in O(1) time.

#include<iostream>
#include<algorithm>
#include<exception>
#include<vector>
#include<random>
#include<time.h>

#include "user_exception.h"
#include "rex-sort.h"
#include "tests.h"
#include "example.h"

#define cout std::cout
#define endl std::endl
#define string std::string



int main(int argc, char *argv[]) try
{
    string parameter = (argv[1])? argv[1] : "";

    if(parameter == "timed-example")
        timed_example();
    else if(parameter == "test-basic")
        test_basic();
    else
    {
        cout<<"-------------------------------------------------------"<<endl
            <<"Help:"<<endl;
        cout<<"Running Timed Example:"<<endl;
        timed_example(); cout<<endl;
        cout<<"Running Basic test: "<<endl;
        test_basic();
    }

    // std::vector<int> temp = {7,6,5,4,3,2,1};
    // std::vector<int> temp2 = rex_sort(temp);
    // cout<<"Array: "<<temp2;
    // // Checking result
    // for(int i=0; i<temp.size(); ++i)
    //     if(i+1 != temp2[i])
    //     {
    //         cout<<"Something went wrong: "<<i<<" "<<temp2;
    //         break;
    //     }

    return 0;
}
catch(UserException &e) { std::cerr<<e.what(); }
catch(std::exception &e) { std::cerr<<"Inbuilt exception: "<<e.what(); }
catch(...) { std::cerr<<"Unknown error"; }
