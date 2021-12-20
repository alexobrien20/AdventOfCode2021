#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <tuple>

void part1(std::string iea; std::vector<std::vector<char>> inputImage)
{
    std::vector<
    std::vector<std::tuple<int,int>> d6 {{-1,-1},{-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
    for(int i = 0; i < inputImage.size(); i++)
    {
        for(int j = 0; j < inputImage[0].size(); j++)
        {
            std::string binaryString;
            for(auto move : d6)
            {
                int x = std::get<0>(move);
                int y = std::get<1>(move);
                try
                {
                    binaryString += inputImage.at(i + x).at(j + y);
                }
                catch (std::out_of_range const &exec)
                {
                    binaryString += ".";
                }
            }
        }
    }

}


int main()
{
    std::ifstream file("day20.txt");
    if(!file){ std::cout << "Error opening file!"; return 0;}
    std::string line;
    std::string iea; 
    std::vector<std::vector<char>> inputImage;
    int counter = 0;
    while(std::getline(file, line))
    {
        if(counter == 0)
        {
            iea = line;
            counter++;
        }
        else if(!line.empty())
        {
            std::vector<char> v(line.begin(), line.end());
            inputImage.push_back(v);
        }
    }
}