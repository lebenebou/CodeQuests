
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

int getNumberOfRuns(std::vector<bool>& seen, std::mt19937& generator)
{
    std::fill(seen.begin(), seen.end(), false);
    int totalRuns = 0;
    int timesCovered = 0;

    std::uniform_int_distribution<int> distribution(0, seen.size() - 1);


    while(timesCovered < seen.size())
    {
        int time = distribution(generator);
        if(!seen[time])
        {
            seen[time] = true;
            ++timesCovered;
        }
        ++totalRuns;
    }
    return totalRuns;
}

int main(int argc, char const *argv[])
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::vector<bool> seen(60);
    
    const int trials = 100000;
    double average = 0.0;

    for(int i = 0; i < trials; ++i)
    {
        average += (getNumberOfRuns(seen, generator) - average) / (i + 1);
    }
    std::cout << average << std::endl;
    
    return 0;
}