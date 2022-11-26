#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <fmt/core.h>
#include <assert.h>
#include <regex>
#include <fstream>

std::string addSnailFish(std::string a, std::string b)
{
    return fmt::format("[{},{}]",a, b);
}

std::tuple<bool, int> explodeCondition(std::string a)
{
    int level = 0;
    for(int i = 0; i < a.size(); i++)
    {
        if(level == 5)
        {
            // Only expode if it's got [d,d]
            // It's not if it's [ or ]
            if(a[i] != '[' && a[i] != ']')
                return {true, i};
        }
        else if(a[i] == '[')
            level++;
        else if(a[i] == ']')
            level--;
    }
    return {false, 0};
}

int getMagnitude(std::string a)
{
    // Find the top position to split
    if(a.find(",") == std::string::npos)
        return std::stoi(a);
    int level = 0;
    int splitPoint = 0;
    for(int i = 0; i < a.size(); i++)
    {
        if(level == 1 && i > 1)
        {
            splitPoint = i;
            break;
        }
        if(a[i] == '[')
            level++;
        if(a[i] == ']')
            level--;

    }
    std::string left = a.substr(1, splitPoint - 1);
    int size = a.size() - splitPoint - 2;
    std::string right = a.substr(splitPoint + 1, size);
    return 3 * getMagnitude(left) + 2 * getMagnitude(right);
}

bool canSplit(std::string a)
{
    std::regex reg("\\d{2,}");
    std::smatch matches;
    std::regex_search(a, matches, reg);
    return !matches.empty();
}

std::string split(std::string a)
{
    std::regex reg("\\d{2,}");
    std::smatch matches;
    std::regex_search(a, matches, reg);
    if(matches.empty())
        return a;
    int tooBigNumber = std::stoi(matches[0]);
    std::string leftFloor = std::to_string(tooBigNumber / 2);
    std::string rightCeil = std::to_string((tooBigNumber + 2 - 1) / 2);
    a = fmt::format("{}[{},{}]{}", matches.prefix().str(), leftFloor, rightCeil, matches.suffix().str());
    return a;
}

std::string newExplode(std::string a, int leftValueIndex)
{
    std::regex reg("\\d+");

    // Find the current left number.
    std::string leftString = a.substr(leftValueIndex, a.size());
    std::smatch leftMatches;
    std::regex_search(leftString, leftMatches, reg);
    std::string leftNumberString = leftMatches[0];
    int currentLeftNumber = std::stoi(leftNumberString);

    // Find the current right number.
    std::string rightString = leftString.substr(0 + leftNumberString.size() + 1);
    std::smatch rightMatches;
    std::regex_search(rightString, rightMatches, reg);
    std::string rightNumberString = rightMatches[0];
    int currentRightNumber = std::stoi(rightNumberString);

    // Find the next number behind the left numbers
    std::regex behindReg("(\\d+)(?!.*\\d)");
    std::string leftSearchString = a.substr(0, leftValueIndex - 1);
    std::smatch leftSearchMatches;
    std::regex_search(leftSearchString, leftSearchMatches, behindReg);
    std::string newLeft = leftSearchString;
    if(!leftSearchMatches.empty())
    {
        int newLeftNumber = std::stoi(leftSearchMatches[0]) + currentLeftNumber; 
        newLeft = fmt::format("{}{}{}", leftSearchMatches.prefix().str(), newLeftNumber, leftSearchMatches.suffix().str());
    }

    // Find the next number infront of the right number;
    std::string rightSearchString = rightString.substr(0 + rightNumberString.size() + 1, rightString.size());
    std::smatch rightSearchMatches;
    std::regex_search(rightSearchString, rightSearchMatches, reg);
    std::string newRight = rightSearchString;
    if(!rightSearchMatches.empty())
    {
        int newRightNumber = std::stoi(rightSearchMatches[0]) + currentRightNumber; 
        newRight = fmt::format("{}{}{}", rightSearchMatches.prefix().str(), newRightNumber, rightSearchMatches.suffix().str());
    }
    return fmt::format("{}0{}", newLeft, newRight);
}

std::string part1(std::string a)
{
    while(true)
    {
        // Keep exploding until you can't anymore
        // std::cout << "Answer " << a << "\n";
        std::tuple<bool, int> canExplodeTuple = explodeCondition(a);
        bool canExplode = std::get<0>(canExplodeTuple);
        while(canExplode)
        {
            int leftValueIndex = std::get<1>(canExplodeTuple);
            // std::cout << "Starting explode at index " << leftValueIndex << "\n";
            a = newExplode(a, leftValueIndex);
            // std::cout << "Expload result : " << a << "\n";
            canExplodeTuple = explodeCondition(a);
            canExplode = std::get<0>(canExplodeTuple);
        }
        // Then try and split once you've finished exploading
        // Check if you can explode after each split
        while(canSplit(a))
        {
            a = split(a);
            canExplodeTuple = explodeCondition(a);
            canExplode = std::get<0>(canExplodeTuple);
            if(canExplode)
                break;
        }

        // Then check if you can 
        canExplodeTuple = explodeCondition(a);
        canExplode = std::get<0>(canExplodeTuple);
        if(!canExplode)
            break;
    }
    return a;
}

int main()
{
    std::ifstream file("day18.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::string> input;
    std::string line;
    while(std::getline(file, line))
    {
        input.push_back(line);
    }

    std::string startingNumber = input[0];
    for(int i = 1; i < input.size(); i++)
    {
        startingNumber = addSnailFish(startingNumber, input[i]);
        startingNumber = part1(startingNumber);
    }
    std::cout << startingNumber << "\n";
    std::cout << "Part 1 Answer : " << getMagnitude(startingNumber) << "\n";

    int maxMagnitude = 0;
    for(int i = 0; i < input.size(); i++)
    {
        std::cout << i << "\n";
        std::string a = input[i];
        for(int j = 0; j < input.size(); j++)
        {
            if(i == j)
                continue;
            std::string b = input[j];
            std::string a_b = addSnailFish(a, b);

            a_b = part1(a_b);

            int a_b_mag = getMagnitude(a_b);

            if(a_b_mag > maxMagnitude)
                maxMagnitude = a_b_mag;
        }
    }

    std::cout << "Part 2 Answer : " << maxMagnitude << "\n";
    return 0;

}