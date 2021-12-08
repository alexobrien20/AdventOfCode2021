#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>


void part1(std::vector<std::string> input)
{
    std::vector<int> lengths = {2, 3, 4, 7};
    int sum = 0;
    for(auto l : lengths)
    {
        sum  += std::count_if(input.begin(), input.end(), [l](std::string x){return x.size() == l;});
    }
    std::cout << "Part 1 Answer : " << sum << "\n";
}

int main()
{
    std::ifstream file("day8.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::string> observed;
    std::vector<std::string> output;
    std::string line;
    while(std::getline(file, line))
    {
        auto d = line.find( " | ");
        std::string s1 = line.substr(0, d);
        std::string s2 = line.substr(d + 3, std::string::npos);
        std::string temp;
        std::stringstream ss1(s1);
        std::stringstream ss2(s2);
        while(std::getline(ss1, temp, ' '))
        {
            observed.push_back(temp);
        }
        while(std::getline(ss2, temp, ' '))
        {
            output.push_back(temp);
        }
    }
    auto t1 = std::chrono::steady_clock::now();
    part1(output);
    auto t2 = std::chrono::steady_clock::now();
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "[µs]" << std::endl;
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1).count() << "[ns]" << std::endl;
}