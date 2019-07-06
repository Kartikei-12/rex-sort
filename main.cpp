
#include<iostream>
#include<exception>
#include<vector>
#include<time.h>

#include "user_exception.h"
#include "rex_sort.h"

#define COUNT 25000

int main(int argc, char *argv[]) try
{
    // std::vector<int> temp = {7,6,5,4,3,2,1};
    std::vector<int> temp;
    for(int i=COUNT; i>0; i -= 2)
    {
        temp.push_back(i-1);
        temp.push_back(i);
    }

    std::cout<<"\nStarting\n";
    uint64_t start_s, stop_s;
    start_s = clock();
    std::vector<int> temp2 = rex_sort(temp);
    stop_s = clock();
    // std::cout<<"Array: "<<temp2;
    std::cout<<"rex-sort Time: "<<(stop_s-start_s)/double(CLOCKS_PER_SEC);

    for(int i=1; i<=COUNT; ++i)
        if(i != temp2[i-1])
        {
            std::cout<<"Something went wrong: "<<i;
            for(int j=i; j<i+10; ++j)
                std::cout<<" "<<temp2[j];
            break;
        }

    return 0;
}
catch(UserException &e) { std::cerr<<e.what(); }
catch(std::exception &e) { std::cerr<<"Inbuilt exception: "<<e.what(); }
catch(...) { std::cerr<<"Unknown error"; }
