#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>


std::vector<std::vector<std::string>> yFold(std::vector<std::vector<std::string>> paper, int fold)
{
    int c = 2;
    for(int row = fold - 1; row >= 0; row--, c+=2)
    {
        for(int col = 0; col < paper[0].size(); col++)
        {
            std::string p = paper[row + c][col];
            if(p == ".")
            {
                continue;
            }
            else
            {
                paper[row][col] = p;
            }
        }
    }
    std::vector<std::vector<std::string>> newPaper;
    for(int i = 0; i < fold; i++)
    {
        newPaper.push_back(paper[i]);
    }
    return newPaper;
}

std::vector<std::vector<std::string>> xFold(std::vector<std::vector<std::string>> paper, int fold)
{
    int c = 2;
    for(int col = fold - 1; col >= 0; col--, c+=2)
    {
        for(int row = 0; row < paper.size(); row++)
        {
            std::string p = paper[row][col + c];
            if(p == ".")
            {
                continue;
            }
            else
            {
                paper[row][col] = p;
            }
        }
    }
    std::vector<std::vector<std::string>> newPaper;
    for(int i = 0; i < paper.size(); i++)
    {
        std::vector<std::string> f(paper[i].begin(), paper[i].begin() + fold);
        newPaper.push_back(f);
    }
    return newPaper;
}


void part1(std::vector<std::vector<std::string>> paper, std::tuple<std::string, int> fold)
{
    std::string foldType = std::get<0>(fold);
    int foldNum = std::get<1>(fold);
    if(foldType == "x")
    {
        paper = xFold(paper, foldNum);
    }
    else
    {
        paper = yFold(paper, foldNum);
    }
    int answer1 = 0;
    for(int i = 0; i < paper.size(); i++)
    {
        answer1 += std::count_if(paper[i].begin(), paper[i].end(), [](std::string x){return x == "#";});
    }
    std::cout << "Part 1 Answer : " << answer1 << "\n";
}

void part2(std::vector<std::vector<std::string>> paper, std::vector<std::tuple<std::string, int>> folds)
{
    for(auto fold : folds)
    {
        std::string foldType = std::get<0>(fold);
        int foldNum = std::get<1>(fold);
        if(foldType == "x")
        {
            paper = xFold(paper, foldNum);
        }
        else
        {
            paper = yFold(paper, foldNum);
        }
    }
    for(int i = 0; i < paper.size(); i++)
    {
        for(int j = 0; j < paper[0].size(); j++)
        {
            std::cout << paper[i][j];
        }
        std::cout << "\n";
    }
}


int main()
{
    std::ifstream file("day13.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::vector<std::string>> input(2000, std::vector<std::string> (2000, "."));
    std::vector<std::tuple<std::string, int>> folds;
    std::string line;
    while(std::getline(file, line))
    {
        if(line.find(",") != std::string::npos)
        {
            int x = std::stoi(line.substr(0, line.find(",")));
            int y = std::stoi(line.substr(line.find(",")+1, std::string::npos));
            input[y][x] = "#";
        }
        else if(line.find("=") != std::string::npos)
        {
            std::string fold = line.substr(line.find("=") - 1,std::string::npos);
            std::string foldType = fold.substr(0, fold.find("="));
            int foldNum = std::stoi(fold.substr(fold.find("=") + 1, std::string::npos));
            folds.push_back(std::make_tuple(foldType, foldNum));
        }
    }
    part1(input, folds[0]);
    part2(input, folds);
    return 0;
}