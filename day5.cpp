#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int sumAbove(std::vector<std::vector<int>> numbers)
{
    int threshold = 1;
    int sum = 0;
    for(int row = 0; row < numbers.size(); row++)
    {
        sum += count_if(numbers[row].begin(), numbers[row].end(), [threshold](int value){return value > threshold;}); 
    }
    return sum;
};

void part1(std::vector<std::vector<int>> input, std::vector<std::vector<int>> numbers)
{
    for(auto line : input)
    {

        int x1 = line[0], y1 = line[1], x2 = line[2], y2 = line[3];
        if(x1 == x2 || y1 == y2)
        {
            for(int col = std::min(x1, x2); col <= std::max(x1, x2); col++)
            {
                for(int row = std::min(y1 ,y2); row <= std::max(y1, y2); row++)
                {
                    numbers[row][col] += 1;
                }
            }
        }
    }
    std::cout << "Part 1 Answer : " << sumAbove(numbers) << "\n";
}

void part2(std::vector<std::vector<int>> input, std::vector<std::vector<int>> numbers)
{
    for(auto line : input)  
    {
        int x1 = line[0], y1 = line[1], x2 = line[2], y2 = line[3];
        // Horizonal and Vertical
        if(x1 == x2 || y1 == y2)
        {
            for(int col = std::min(x1, x2); col <= std::max(x1, x2); col++)
            {
                for(int row = std::min(y1 ,y2); row <= std::max(y1, y2); row++)
                {
                    numbers[row][col] += 1;
                }
            }
        }
        // Diagonal 
        if(std::abs(x1 - x2) == std::abs(y1 - y2))
        {
            int row = std::min(y1, y2);
            if(x1 - x2 != y1 - y2)
            {
                int col = std::max(x1, x2);
                for(row; row <= std::max(y1, y2); row++, col--)
                {
                    numbers[row][col] += 1;
                }
            }
            else
            {
                for(int col = std::min(x1, x2); col <= std::max(x1, x2); row++, col++)
                {
                    numbers[row][col] += 1;
                }
            }
        }
    }
    std::cout << "Part 2 Answer : " << sumAbove(numbers) << "\n";
}


int main()
{
    std::ifstream file("day5.txt");
    if(!file){ std::cout << "Error opening file!"; return 0;}
    std::string line;
    std::vector<std::vector<int>> numbers(1000, std::vector<int>(1000,0));
    std::vector<std::vector<int>> input;
    while(std::getline(file, line))
    {
        std::vector<int> temp;
        std::string s1 = line.substr(0, line.find(" -> "));
        std::string s2 = line.substr(line.find(" -> ") + 4, std::string::npos);
        std::stringstream ss(s1 + "," + s2);
        std::string substr;
        while(std::getline(ss, substr, ','))
        {
            temp.push_back(std::stoi(substr));
        }
        input.push_back(temp);
    }
    part1(input, numbers);
    part2(input, numbers);
}