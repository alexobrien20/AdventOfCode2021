#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>


std::vector<std::tuple<int,int>> flashed;

void search(std::vector<std::vector<int>> &input, int row, int col)
{
    input[row][col] = 0;
    flashed.push_back(std::make_tuple(row,col));
    std::vector<std::tuple<int,int>> ds {{-1,-1},{-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
    for(auto xy : ds)
    {
        int x = std::get<0>(xy), y = std::get<1>(xy);
        if(std::find(flashed.begin(), flashed.end(), std::make_tuple(row + x, col + y)) != flashed.end())
        {
            continue;
        }
        try{
            if(input.at(row + x).at(col + y) == 10)
            {
                search(input, row + x, col + y);
            }
            else
            {
                input.at(row + x).at(col + y) += 1;
                if(input.at(row + x).at(col + y) == 10)
                {
                    search(input, row + x, col + y);
                }
            }
        }
        catch (std::out_of_range const &exec)
        {}
    }
}


void solve(std::vector<std::vector<int>> input, int max_days, bool part2 = false)
{
    int answer = 0;
    for(int day = 1; day <= max_days; day++)
    {
        for(int row = 0; row < input.size(); row++)
        {
            for(int col = 0; col < input[0].size(); col++)
            {
                input[row][col] += 1;
            }
        }
        for(int row = 0; row < input.size(); row++)
        {
            for(int col = 0; col < input[0].size(); col++)
            {
                if(input[row][col] == 10)
                {
                    search(input, row , col);
                }
            }
        }
        if(part2 && flashed.size() == input.size() * input[0].size())
        {
            std::cout << "Part 2 Answer : " << day << "\n";
            return;
        }
        answer += flashed.size();
        flashed.clear();  
    }
    std::cout << "Part 1 Answer : " << answer << "\n";
}


int main()
{
    std::ifstream file("day11.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::vector<int>> input;
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<char> v(line.begin(), line.end());
        std::vector<int> temp;
        for(auto x : v)
        {
            temp.push_back(std::stoi(std::string(1, x)));
        }
        input.push_back(temp);
    }
    solve(input, 100);
    solve(input, 100000, true);
}
