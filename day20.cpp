#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <tuple>

std::vector<std::vector<char>> padImage(std::vector<std::vector<char>> inputImage, char padding)
{
    std::vector<char> paddedRow(inputImage[0].size() + 4, padding);
    inputImage.push_back(paddedRow);
    inputImage.push_back(paddedRow);
    inputImage.insert(inputImage.begin(), paddedRow);
    inputImage.insert(inputImage.begin(), paddedRow);
    for(int i = 1; i < inputImage.size() - 1; i++)
    {
        inputImage[i].push_back(padding);
        inputImage[i].push_back(padding);
        inputImage[i].insert(inputImage[i].begin(), padding);
        inputImage[i].insert(inputImage[i].begin(), padding);
    }
    return inputImage;
}

std::vector<std::vector<char>> enhanceImage(std::string iea, std::vector<std::vector<char>> inputImage, char padding)
{
    inputImage = padImage(inputImage, padding);
    std::vector<std::vector<char>> outputImage{inputImage.size(), std::vector<char>(inputImage[0].size())};
    std::vector<std::tuple<int,int>> d6 {{-1,-1},{-1,0}, {-1,1}, {0,-1},{0,0}, {0,1}, {1,-1}, {1,0}, {1,1}};
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
                    char value = inputImage.at(i + x).at(j + y);
                    if(value == '.')
                        binaryString += "0";
                    else
                        binaryString += "1";
                }
                catch (std::out_of_range const &exec)
                {
                    // Else if not exists it must be a '.'?
                    binaryString += (padding == '.') ? "0" : "1";
                }
            }
            int binaryNumber = std::stoi(binaryString, nullptr, 2);
            char newValue = iea[binaryNumber];
            outputImage[i][j] = newValue;
        }
    }

    return outputImage;
}

int countPixels(std::vector<std::vector<char>> inputImage)
{
    int pixels = 0;
    // Don't count the padding
    for(int i = 1; i < inputImage.size() - 1; i++)
    {
        for(int j = 1; j < inputImage[0].size() - 1; j++)
        {
            if(inputImage[i][j] == '#')
                pixels++;
        }
    }
    return pixels;
}

void part2(std::string iea, std::vector<std::vector<char>> inputImage, int n)
{
    char padding = '.';
    for(int i = 0; i < n; i++)
    {
        inputImage = enhanceImage(iea, inputImage, padding);
        std::string binaryString = std::string(9, padding);
        for(char& c : binaryString)
        {
            c = (c == '.') ? '0' : '1';
        }
        padding = iea[std::stoi(binaryString, nullptr, 2)];
    }

    std::cout << "N : " << n << " Answer is : " << countPixels(inputImage) << "\n";
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
    part2(iea, inputImage, 50);
    part2(iea, inputImage, 2);
}