#include <iostream>
#include <fstream>
#include <vector>

void part1(std::vector<std::string> input)
{
    int h = 0, d = 0;
    for(auto line : input)
    {
        size_t pos = line.find(" ");
        std::string instruction = line.substr(0, pos);
        int movement = std::stoi(line.substr(pos, line.size()));
        if (instruction == "forward")
        {
            h += movement;
        }
        else if (instruction == "down")
        {
            d += movement;
        }
        else
        {
            d -= movement;
        }
    }
    std::cout << d * h << "\n";
}


void part2(std::vector<std::string> input)
{
    int h = 0, d = 0, a = 0;
    for(auto line : input)
    {
        size_t pos = line.find(" ");
        std::string instruction = line.substr(0, pos);
        int movement = std::stoi(line.substr(pos, line.size()));
        if (instruction == "forward")
        {
            h += movement;
            d += (a * movement);
        }
        else if (instruction == "down")
        {
            a += movement;
        }
        else
        {
            a -= movement;
        }
    }
    std::cout << d * h << "\n";
}

int main()
{
    std::ifstream file("day2.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::string> input;
    std::string line;
    while(std::getline(file, line))
    {
        input.push_back(line);
    }
    part1(input);
    part2(input);
}

