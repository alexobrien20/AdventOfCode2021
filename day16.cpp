#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <bitset>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>

int Answer1 = 0;

std::string convertToBinary(char hexStr)
{
    std::stringstream ss;
    ss << std::hex << hexStr;
    unsigned n;
    ss >> n;
    std::bitset<4> b(n);
    return b.to_string().c_str();
}

std::tuple<std::string, long> parse1(std::string stringOfBinary)
{
    // First workout the packet type ID (4 == literal value and operator otherwise)
    int typeId = std::stoi(stringOfBinary.substr(3, 3), nullptr, 2);
    int packetVersion = std::stoi(stringOfBinary.substr(0, 3), nullptr, 2);
    Answer1 += packetVersion;
    // std::cout << "Packet version " << packetVersion << " Packet Type " << typeId << "\n";
    stringOfBinary = stringOfBinary.substr(6, stringOfBinary.size());
    if(typeId == 4)
    {
        // Keep going until you have a group begging in 0?
        // Not interesting in first six numbers;
        std::string literalValue;
        while(true)
        {
            literalValue.append(stringOfBinary.substr(1, 4));
            std::string firstNumber = stringOfBinary.substr(0,1);
            stringOfBinary = stringOfBinary.substr(5, stringOfBinary.size());
            if(firstNumber == "0" || stringOfBinary.size() < 5)
                break;
        }
        // std::cout << std::stol(literalValue, nullptr, 2) << "\n";
        return std::make_tuple(stringOfBinary, std::stol(literalValue, nullptr, 2));
    }
    else
    {
        // Operator value
        std::vector<long> packetValues;
        int lengthTypeId = std::stoi(stringOfBinary.substr(0,1), nullptr, 2);
        stringOfBinary = stringOfBinary.substr(1,stringOfBinary.size());
        // std::cout << "length type " << lengthTypeId << "\n";
        if(lengthTypeId == 1)
        {
            int numOfBits = std::stoi(stringOfBinary.substr(0,11), nullptr, 2);
            stringOfBinary = stringOfBinary.substr(11, stringOfBinary.size());
            // std::cout << "There are " << numOfBits << " bits!\n";
            for(int i = 0; i < numOfBits; i++)
            {
                auto r = parse1(stringOfBinary);
                stringOfBinary = std::get<0>(r);
                packetValues.push_back(std::get<1>(r));
                // stringOfBinary = parse1(stringOfBinary);
            }     
        }
        else
        {
            // 0000000000110111101000101001010010001001000000000
            int L = std::stoi(stringOfBinary.substr(0, 15), nullptr, 2);
            stringOfBinary = stringOfBinary.substr(15, stringOfBinary.size());
            std::string packetsToParse = stringOfBinary.substr(0, L);
            while(packetsToParse.size() > 0)
            {
                // packetsToParse = parse1(packetsToParse);
                auto r = parse1(packetsToParse);
                packetsToParse = std::get<0>(r);
                packetValues.push_back(std::get<1>(r));
            }
            stringOfBinary = stringOfBinary.substr(L, stringOfBinary.size());
        }
        if(typeId == 0)
        {
            return std::make_tuple(stringOfBinary, std::accumulate(packetValues.begin(), packetValues.end(), 0L));
        }
        else if(typeId == 1)
        {
            long mult = 1;
            for(auto x : packetValues)
                mult *= x;
            return std::make_tuple(stringOfBinary, mult);
        }
        else if(typeId == 2)
        {
            return std::make_tuple(stringOfBinary, *(std::min_element(packetValues.begin(), packetValues.end())));
        }
        else if(typeId == 3)
        {
            return std::make_tuple(stringOfBinary, *(std::max_element(packetValues.begin(), packetValues.end())));
        }
        else if(typeId == 5)
        {
           int x = (packetValues[0] > packetValues[1]) ? 1 : 0;
           return std::make_tuple(stringOfBinary, x);
        }
        else if(typeId == 6)
        {
            int x = (packetValues[0] < packetValues[1]) ? 1 : 0;
            return std::make_tuple(stringOfBinary, x);
        }
        else
        {
            int x = (packetValues[0] == packetValues[1]) ? 1 : 0;
            return std::make_tuple(stringOfBinary, x);
        }
    }
}

int main()
{
    std::ifstream file("day16.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::vector<int>> input;
    std::string line;
    std::getline(file, line);
    std::string bLine;
    for(auto c : line)
    {
        bLine.append(convertToBinary(c));
    }
    parse1(bLine);
    std::cout << "Answer 1 " << Answer1 << "\n";
    std::cout << std::get<1>(parse1(bLine)) << "\n";
    return 0;
}
