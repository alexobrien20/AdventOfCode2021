#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

void checkOrInsert(std::map<std::string, long long> &pairCounts, std::string newPair, long long val = 1)
{
    auto lb = pairCounts.lower_bound(newPair);
    if(lb != pairCounts.end() && !(pairCounts.key_comp()(newPair, lb->first)))
    {
        pairCounts[newPair] += val;
    }
    else
    {
        pairCounts.insert({newPair, val});
    }    
}

std::map<std::string, long long> step(std::map<std::string, std::string> rules, std::map<std::string, long long> pairCounts, std::map<std::string, long long> &runningCounts)
{
    std::map<std::string, long long> newCounts = pairCounts;
    for(auto pairCount : pairCounts)
    {
        long long val = std::get<1>(pairCount);
        if(val == 0){continue;}
        std::string pair = std::get<0>(pairCount);
        std::string a = rules[pair], newPair1 = pair[0] + a, newPair2 = a + pair[1];
        newCounts[pair] -= val;
        checkOrInsert(newCounts, newPair1, val);
        checkOrInsert(newCounts, newPair2, val);
        checkOrInsert(runningCounts, a, val);
    }
    return newCounts;
}

void solve(std::map<std::string, std::string> rules, std::string start, int steps)
{
    std::map<std::string, long long> runningCounts; 
    std::map<std::string, long long> pairCounts;
    for(int i = 0; i < start.size(); i++)
    {
        std::string pair = start.substr(i, 2);
        checkOrInsert(pairCounts, pair);
        checkOrInsert(runningCounts, std::string(1, start[i]));
    }
    for(int i = 0; i < steps; i++)
    {
        pairCounts = step(rules, pairCounts, runningCounts);
    }
    auto x = std::max_element(runningCounts.begin(), runningCounts.end(), [](const std::pair<std::string, long long>&p1, const std::pair<std::string, long long> &p2){return p1.second < p2.second;});
    auto y = std::min_element(runningCounts.begin(), runningCounts.end(), [](const std::pair<std::string, long long>&p1, const std::pair<std::string, long long> &p2){return p1.second < p2.second;});
    std::cout << (*x).second - (*y).second;
}

int main()
{
    std::ifstream file("day14.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::map<std::string, std::string> input;
    std::string line;
    std::string start;
    while(std::getline(file, line))
    {
        if(line.find(" -> ") != std::string::npos)
        {
            std::string pair = line.substr(0, line.find(" -> "));
            std::string insert = line.substr(line.find(" -> ") + 4, std::string::npos);
            input.insert({{pair, insert}});
        }
        else if(!line.empty())
        {
            start = line;
        }
    }
    std::cout << "Part 1 Answer ";
    solve(input, start, 10);
    std::cout << "\nPart 2 Answer ";
    solve(input, start, 40);
    std::cout << "\n";
}