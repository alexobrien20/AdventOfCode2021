#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

void part1(std::vector<std::vector<std::string>> paper, int fold)
{
    // Everything below 7 is fine and doesn't change
    // Don't change line y = 7
    // Every above y = 7 is going to be affected
    for(int row = 8; row < paper.size(); row++)
    {
        for(int col = 0; col < paper[0].size(); col++)
        {
            
        }
    }
}


int main()
{
    std::ifstream file("day13.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::vector<std::string>> input(1000, std::vector<std::string> (100, "."));
    std::vector<int> folds;
    std::string line;
    while(std::getline(file, line))
    {
        if(line.find(",") != std::string::npos)
        {
            int x = std::stoi(line.substr(0, line.find(",")));
            int y = std::stoi(line.substr(line.find(",")+1, std::string::npos));
            std::cout << "x " << x << " y " << y << "\n";
            input[y][x] = "#";
        }
        else if(line.find("=") != std::string::npos)
        {
            int fold = std::stoi(line.substr(line.find("=")+1,std::string::npos));
            folds.push_back(fold);
        }
    }
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j< 11; j++)
        {
            std::cout << input[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}