#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>


std::vector<int> part1(std::vector<std::string> input)
{
    int answer = 0;
    std::vector<char> opened;
    std::vector<int> dropLines;
    std::map<char, int> ans {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    std::map<char, char> s{{']', '['}, {')','('}, {'}', '{'}, {'>', '<'}};
    for(int i = 0; i < input.size(); i++)
    {
        for(auto c : input[i])
        {
            if(c == '[' || c == '{' || c == '<' || c == '(')
            {
                opened.push_back(c);
            }
            else
            {
                if(opened.back() != s[c])
                {
                    dropLines.push_back(i);
                    answer += ans[c];
                    break;
                }
                else
                {
                    opened.erase(opened.end() - 1);
                }
            }   
        }
    }
    std::cout << "Part 1 Answer : " << answer << "\n";
    return dropLines;
}

void part2(std::vector<int> dropLines, std::vector<std::string> input)
{
    std::sort(dropLines.begin(), dropLines.end(), std::greater<>());
    for(auto drop : dropLines)
    {
        auto it = input.begin() + drop;
        input.erase(input.begin() + drop);
    }
    std::vector<long> answers;
    std::map<char, char> s{{'[', ']'}, {'(',')'}, {'{', '}'}, {'<', '>'}};
    std::map<char, int> score{{'}', 3}, {'>', 4}, {']', 2}, {')', 1}};
    for(auto line : input)
    {
        std::vector<char> opened;
        for(auto c : line)
        {
            if(c == '[' || c == '{' || c == '<' || c == '(')
            {
                opened.push_back(c);
            }
            else
            {
                opened.erase(opened.end() - 1);
            }
        }
        long answer2 = 0;
        for(int i = opened.size() - 1; i >= 0; i--)
        {
            answer2 *= 5;
            answer2 += score[s[opened[i]]];
        } 
        answers.push_back(answer2);
    }
    std::sort(answers.begin(), answers.end());
    std::cout << "Part 2 Answer : " << answers[(answers.size() / 2)] << "\n";
}

int main()
{
    std::ifstream file("day10.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::string> input;
    std::string line;
    while(std::getline(file, line))
    {
        input.push_back(line);
    }
    std::vector<int> dropLines = part1(input);
    part2(dropLines, input);
}