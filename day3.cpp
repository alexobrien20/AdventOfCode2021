#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


std::vector<char> common(std::vector<std::vector<char>> input, int col)
{
    char mostCommon;
    char leastCommon;
    std::vector<int> freq;
    for(int j = 0; j < input.size(); j++)
    {
        freq.push_back(input[j][col]);
    }
    int f = std::count(freq.begin(), freq.end(), '1');
    mostCommon = (f >= static_cast<double>(freq.size()) / 2) ? '1' : '0';
    leastCommon = (f >= static_cast<double>(freq.size()) / 2) ? '0' : '1';
    return std::vector<char>{mostCommon, leastCommon};
}

void part1(std::vector<std::vector<char>> input)
{
    std::string gamma;
    std::string epsilon;
    size_t n = input[0].size();
    for(int i = 0; i < n; i++)
    {
        std::vector<char> v = common(input, i);
        gamma += v[0];
        epsilon += v[1];
    }
    std::cout << "Part 1 Answer : " << std::stoi(gamma, 0, 2) * std::stoi(epsilon, 0, 2) << "\n";
}

int part2(std::vector<std::vector<char>> input, int i)
{
    while(input.size() != 1)
    {
        for(int col = 0; col < input[0].size(); col++)
        {
            std::vector<char> v = common(input, col);
            for(auto it = input.begin(); it != input.end();)
            {
                if(input[it - input.begin()][col] != v[i])
                {
                    if(input.size() == 1)
                    {
                        break;
                    }
                    it = input.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }
    std::string a;
    for(auto line : input[0])
    {
        a += line;
    }
    return std::stoi(a, 0, 2);
}

int main()
{
    std::ifstream file("day3.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::string line;
    std::vector<std::vector<char>> input;
    while(std::getline(file, line))
    {
        std::vector<char> v(line.begin(), line.end());
        input.push_back(v);
    }
    part1(input);
    std::cout << "Part 2 Answer : " << part2(input, 0) * part2(input, 1) << "\n";
    return 0;
}