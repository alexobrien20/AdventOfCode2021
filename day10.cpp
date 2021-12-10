#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>


void part1(std::vector<std::string> input)
{

    // <([]){()}[{}])
    // < = open
    // ( = open
    // [ = open
    // ] = close? 

    // e.g = [<([)]

    std::vector<char> illegalChars;
    std::vector<char> opened;
    std::vector<std::string> closed;
    for(auto line : input)
    {
        for(auto c : line)
        {
            // std::cout << "c " << c << "\n";
            if(c == '[' || c == '{' || c == '<' || c == '(')
            {
                opened.push_back(c);
            }
            else if (c == ']')
            {
                if(opened.back() != '[')
                {
                    std::cout << "Corrupted" << "\n";
                    illegalChars.push_back(c);
                    break;
                }
                else
                {
                    opened.erase(opened.end() - 1);
                }
            }
            else if (c == ')')
            {
                if(opened.back() != '(')
                {
                    std::cout << "Corrupted" << "\n";
                    illegalChars.push_back(c);
                    break;
                }
                else
                {
                    opened.erase(opened.end() - 1);
                }
            }
           else if (c == '}')
            {
                if(opened.back() != '{')
                {
                    std::cout << "Corrupted" << "\n";
                    illegalChars.push_back(c);
                    break;
                }
                else
                {
                    opened.erase(opened.end() - 1);
                }
            }
            else if (c == '>')
            {
                if(opened.back() != '<')
                {
                    std::cout << "Corrupted" <<"\n";
                    illegalChars.push_back(c);
                    break;
                }
                else
                {
                    opened.erase(opened.end() - 1);
                }
            } 
            
        }
    }
    std::map<char, int> ans {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    int answer = 0;
    for(auto c : illegalChars)
    {
        answer += ans[c];
    }
    std::cout << answer << "\n";
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
    part1(input);
    return 0;
}