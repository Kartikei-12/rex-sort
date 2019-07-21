
#ifdef COUNT
    #undef COUNT
#endif
#define COUNT 10000

bool test_basic(int test_runs = 10)
{
    auto rng = std::default_random_engine {};

    uint64_t start_s, stop_s;
    int failure = 0, runs = test_runs;
    double rex_time = 0, std_sort_time = 0, test_runs_ = test_runs;
    std::vector<int> original, std_sort_sorted, rex_sort_sorted;

    original.reserve(COUNT);
    std_sort_sorted.reserve(COUNT);
    rex_sort_sorted.reserve(COUNT);

    for(int i=COUNT; i>0; --i)
        original.push_back(i);

    std::cout<<"basic test "<<test_runs<<" times, ";
    while(runs--)
    {
        std::shuffle(original.begin(), original.end(), rng);

        start_s = clock();
        rex_sort_sorted = rex_sort(original);
        stop_s = clock();
        rex_time += (stop_s-start_s)/double(CLOCKS_PER_SEC);

        std_sort_sorted = original;
        start_s = clock();
        std::sort(std_sort_sorted.begin(), std_sort_sorted.end());
        stop_s = clock();
        std_sort_time += (stop_s-start_s)/double(CLOCKS_PER_SEC);

        if(rex_sort_sorted.size() != std_sort_sorted.size() ||
           rex_sort_sorted.size() != original.size())
        {
            std::cout<<"Size does not match original in run "<<test_runs-runs
                     <<", breaking"<<std::endl;
            failure = 1;
            std::cout<<"Expected: "<<std_sort_sorted
                     <<" of size: "<<std_sort_sorted.size()<<std::endl
                     <<"Encountered: "<<rex_sort_sorted
                     <<" of size: "<<rex_sort_sorted.size()<<std::endl;
            break;
        }
        for(int i=0; i != original.size(); ++i)
            if(rex_sort_sorted[i] != std_sort_sorted[i])
            {
                std::cout<<std::endl;
                std::cout<<"ERROR for index "<<i<<" in run "<<test_runs-runs
                         <<", rex_sort_sorted[i],"<<rex_sort_sorted[i]
                         <<" != std_sort_sorted[i],"<<std_sort_sorted[i]
                         <<std::endl;
                std::cout<<"\n---------------------------------------------------\n";
                std::cout<<rex_sort_sorted<<"\n\n"<<original;
                std::cout<<"\n---------------------------------------------------\n";
                ++failure;
                break;
            }
    }
    std::cout<<"rex time: "<<rex_time/test_runs_
             <<" std::sort time: "<<std_sort_time/test_runs_
             <<" ... ";
    if(failure == 0)
        std::cout<<"OK";
    else
        std::cout<<"FAILURE";
    return (failure)? false : true;
}
#undef COUNT
