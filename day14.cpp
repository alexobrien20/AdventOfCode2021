#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

std::string step(std::vector<std::tuple<std::string, std::string>> input, std::string start)
{
    std::string last;
    std::string answer;
    for(int i = 0; i < start.size() - 1; i++)
    {
        std::string pair = start.substr(i, 2);
        for(auto rule : input)
        {
            std::string p = std::get<0>(rule);
            if(pair == p)
            {
                std::string a = std::get<1>(rule);
                // std::cout << "Pair " << pair << "\n";
                // std::cout << "With " << p << " Insert " << a << "\n";
                answer+= pair[0] + a;
                last = pair[1];
            }
        }
    }
    answer += last;
    return answer;
}

void part1(std::vector<std::tuple<std::string, std::string>> input, std::string start, int steps)
{
    for(int i = 0; i < steps; i++)
    {
        start = step(input, start);
    }
    std::map<char, int> counts;
    for(int i = 0; i < start.size(); i++)
    {
        counts[start[i]]++;
    }
    auto x = std::max_element(counts.begin(), counts.end(), [](const std::pair<char, int>&p1, const std::pair<char, int> &p2){return p1.second < p2.second;});
    auto y = std::min_element(counts.begin(), counts.end(), [](const std::pair<char, int>&p1, const std::pair<char, int> &p2){return p1.second < p2.second;});
    std::cout << (*x).second - (*y).second << "\n";
}

int main()
{
    std::ifstream file("day14.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::tuple<std::string, std::string>> input;
    std::string line;
    std::string start;
    while(std::getline(file, line))
    {
        if(line.find(" -> ") != std::string::npos)
        {
            std::string pair = line.substr(0, line.find(" -> "));
            std::string insert = line.substr(line.find(" -> ") + 4, std::string::npos);
            input.push_back(std::make_tuple(pair, insert));
        }
        else if(!line.empty())
        {
            start = line;
        }
    }
    part1(input, start, 40);
    return 0;
}