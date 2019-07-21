
#ifdef COUNT
    #undef COUNT
#endif
#define COUNT 100000

void timed_example()
{
    uint64_t start_s, stop_s;
    std::vector<int> unsorted, sorted;

    sorted.reserve(COUNT);
    unsorted.reserve(COUNT);

    for(int i=COUNT; i>0; --i)
        unsorted.push_back(i);

    start_s = clock();           // Start clock
    sorted = rex_sort(unsorted); // Sorting using rex-sort
    stop_s = clock();            // End clock
    std::cout<<"rex-sort Time: "<<(stop_s-start_s)/double(CLOCKS_PER_SEC)<<std::endl;

    start_s = clock();                           // Start clock
    std::sort(unsorted.begin(), unsorted.end()); // Sorting usint In built sorting algorithm
    stop_s = clock();                            // End clock
    std::cout<<"Inbuilt-sort Time: "<<(stop_s-start_s)/double(CLOCKS_PER_SEC)<<std::endl;
}
#undef COUNT
