#include <iostream>
#include <fstream>
#include <vector>


void part1(std::vector<int> numbers)
{
    int answer = 0;
    for(unsigned int i = 0; i < numbers.size() - 1; i++)
    {
        answer += 1 ? numbers[i + 1] > numbers[i] : 0;
    }
    std::cout << "Part 1 Answer " << answer << "\n";
}

void part2(std::vector<int> numbers)
{
    int answer = 0;
    for(unsigned int i = 0; i < numbers.size() - 2; i++)
    {
        answer += 1 ? numbers[i + 3] > numbers[i] : 0;
    }
    std::cout << "Part 2 Answer " << answer << "\n";
}

int main()
{
    std::ifstream file("day1.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<int> numbers;
    int number;
    while(file >> number)
    {
        numbers.push_back(number);
    }
    part1(numbers);
    part2(numbers);
}