#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

std::vector<std::tuple<int,int>> part1(std::vector<std::vector<int>> input)
{
    std::vector<std::tuple<int,int>> indexs;
    for(int i = 0; i < input.size(); i++)
    {
        for(int j = 0; j < input[0].size(); j++)
        {
            // Look right
            if(j != input[0].size() - 1)
            {
                if(input[i][j + 1] <= input[i][j])
                {
                    continue;
                }
            }
            // Look left
            if( j != 0)
            {
                if(input[i][j - 1] <= input[i][j])
                {
                    continue;
                }
            }
            // Look up
            if(i != 0)
            {
                if(input[i-1][j] <= input[i][j])
                {
                    continue;
                }
            }
            // Look down
            if (i != input.size() - 1)
            {
                if(input[i+1][j] <= input[i][j])
                {
                    continue;
                }
            }
            std::tuple<int,int> index {i,j};
            indexs.push_back(index);
        }
    }
    return indexs;
}

std::vector<std::tuple<int,int>> search(int i, int j, std::vector<std::vector<int>> input, std::vector<std::tuple<int,int>> points)
{
    std::tuple<int,int> index {i,j};
    if (std::find(points.begin(), points.end(), index) != points.end())
    {
        return points;
    }
    points.push_back(index);
    // Look right
    if(j != input[0].size() - 1)
    {
        if(input[i][j + 1] > input[i][j] && input[i][j + 1] != 9)
        {
            points = search(i, j + 1, input, points);
        }
    }
    // Look left
    if( j != 0)
    {
        if(input[i][j - 1] > input[i][j] && input[i][j - 1] != 9)
        {
            points = search(i, j - 1, input, points);
        }
    }
    // Look up
    if(i != 0)
    {
        if(input[i-1][j] > input[i][j] && input[i - 1][j] != 9)
        {
            points = search(i-1, j, input, points);
        }
    }
    // Look down
    if (i != input.size() - 1)
    {
        if(input[i+1][j] > input[i][j] && input[i + 1][j] != 9)
        {
            points = search(i+1, j, input, points);
        }
    }
    return points;
}

void part2(std::vector<std::vector<int>> input, std::vector<std::tuple<int,int>> indexs)
{
    std::vector<int> counts;
    std::vector<std::tuple<int,int>> points;
    for(auto index : indexs)
    {
        int i = std::get<0>(index);
        int j = std::get<1>(index);
        auto p = search(i, j, input, points);
        counts.push_back(p.size());
    }
    std::sort(counts.begin(), counts.end(), std::greater<int>());
    int answer = 1;
    for(int i = 0; i < 3; i++)
    {
        answer *= counts[i];
    }
    std::cout << "Part 2 Answer : " << answer << "\n";
}


int main()
{
    std::ifstream file("day9.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::vector<int>> input;
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<int> temp;
        for(auto i : line)
        {
            int v = i - '0';
            temp.push_back(v);
        }
        input.push_back(temp);
    }
    std::vector<std::tuple<int,int>> indexs = part1(input);
    int answer = 0;
    for(auto index : indexs)
    {
        int row = std::get<0>(index), col = std::get<1>(index);
        answer += input[row][col] + 1;
    }
    std::cout << "Part 1 Answer : " << answer << "\n";
    part2(input, indexs);
    return 0;
}