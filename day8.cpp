#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>
#include <algorithm>


bool check(std::string f, std::string x, int similar = 0)
{
    int c = f.size(), s = 0;
    for(auto letter : x)
    {
        if(f.find(letter) != std::string::npos)
        {
            s++;
        }
    }
    return s == c - similar;
}

void solve(std::vector<std::string>input)
{
    int answer1 = 0;
    int answer2 = 0;
    for(auto line : input)
    {
        std::vector<std::string> o;
        std::vector<std::string> i;
        auto d = line.find( " | ");
        std::string s1 = line.substr(0, d);
        std::string s2 = line.substr(d + 3, std::string::npos);
        std::string temp;
        std::stringstream ss1(s1);
        std::stringstream ss2(s2);
        while(std::getline(ss1, temp, ' '))
        {
            o.push_back(temp);
        }
        while(std::getline(ss2, temp, ' '))
        {
            i.push_back(temp);
        }
        std::vector<int> lengths = {2, 3, 4, 7};
        for(auto l : lengths)
        {
            answer1  += std::count_if(i.begin(), i.end(), [l](std::string x){return x.size() == l;});
        }
        auto one = std::find_if(o.begin(), o.end(), [](std::string x){return x.size() == 2;});
        auto four = std::find_if(o.begin(), o.end(), [](std::string x){return x.size() == 4;});
        auto seven = std::find_if(o.begin(), o.end(), [](std::string x){return x.size() == 3;});
        auto eight = std::find_if(o.begin(), o.end(), [](std::string x){return x.size() == 7;});
        auto three = std::find_if(o.begin(), o.end(), [=](std::string x){return check(*seven, x) && x.size() == 5;});
        auto nine = std::find_if(o.begin(), o.end(), [=](std::string x){return check(*seven, x) && x.size() == 6 && check(*three, x);});
        auto zero = std::find_if(o.begin(), o.end(), [=](std::string x){return !check(*nine, x) && x.size() == 6 && check(*seven, x);});
        auto six = std::find_if(o.begin(), o.end(), [=](std::string x){return !check(*nine, x) && x.size() == 6 && !check(*zero, x);});
        auto five = std::find_if(o.begin(), o.end(), [=](std::string x){return check(*six, x, 1) && x.size() == 5;});
        auto two = std::find_if(o.begin(), o.end(), [=](std::string x){return !check(*five, x) && x.size() == 5 && !check(*three, x);});

        std::map<std::string, std::string> maps {{*zero, "0"},{*one, "1"},{*two, "2"},{*three, "3"},{*four, "4"},{*five, "5"},{*six, "6"},{*seven, "7"},{*eight, "8"},{*nine, "9"},};
        std::string ans;
        for(auto y : i)
        {
            auto v = std::find_if(o.begin(), o.end(), [=](std::string x){return check(y, x) && x.size() == y.size();});
            ans += maps[*v];
        }
        answer2 += std::stoi(ans);
        }
    std::cout << "Part 1 Answer : " << answer1 << "\n";
    std::cout << "Part 2 Answer : " << answer2 << "\n";
}
int main()
{
    std::ifstream file("day8.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::string> input;
    std::string line;
    while(std::getline(file, line))
    {
        input.push_back(line);
    }
    solve(input);
}