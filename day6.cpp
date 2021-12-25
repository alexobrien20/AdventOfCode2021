#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

void solve(std::vector<long long> counts, int days)
{
    for(int i = 0; i < days; i++)
    {
        std::vector<long long> next{0,0,0,0,0,0,0,0,0,0};
        for(int c = 0; c < counts.size(); c++)
        {
            if(c == 0)
            {
                next[8] = counts[c];
                next[6] = counts[c];
            }
            else
            {
                next[c - 1] += counts[c];
            }
        }
        counts = next;
    }
    std::cout << std::accumulate(counts.begin(), counts.end(), 0LL) << "\n";
}


int main()
{
    std::ifstream file("day6.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<long long> input {0,0,0,0,0,0,0,0,0};
    std::string line;
    while(std::getline(file, line, ','))
    {
       input[std::stoi(line)]++;
    }
    std::cout << "Part 1 Answer : ";
    solve(input, 80);
    std::cout << "Part 2 Answer : ";
    solve(input, 256);
}