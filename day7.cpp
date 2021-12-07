#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>

void part1(std::vector<int> input)
{
    auto min = std::min_element(input.begin(), input.end());
    auto max = std::max_element(input.begin(), input.end());
    std::vector<int> sums;
    for(int i = *min; i <= *max; i++)
    {
        int sum = 0;
        for(auto number : input)
        {
            sum += std::abs(number - i);
        }
        sums.push_back(sum);
    }
    auto m = std::min_element(sums.begin(), sums.end());
    std::cout << "Part 1 Answer " << *m << "\n";
}

void part2(std::vector<int> input)
{
    auto min = std::min_element(input.begin(), input.end());
    auto max = std::max_element(input.begin(), input.end());
    std::vector<int> sums;
    for(int i = *min; i <= *max; i++)
    {
        int sum = 0;
        for(auto number : input)
        {
            int temp = (std::abs(number - i) * (std::abs(number - i) + 1))/2;
            sum += temp;
        }

        sums.push_back(sum);
    }
    auto m = std::min_element(sums.begin(), sums.end());
    std::cout << "Part 2 Answer " << *m << "\n";   
}

int main()
{
    std::ifstream file("day7.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::string line;
    int lineCounter = 0;
    std::vector<int> numbers;
    while(std::getline(file, line, ','))
    {
        numbers.push_back(std::stoi(line));
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    part1(numbers);
    part2(numbers);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<< " milliseconds\n";
}