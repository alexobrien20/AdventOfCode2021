#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>


bool bingoCheck(std::vector<std::vector<std::string>> board, int i, int j)
{
    int h = 0, v = 0;
    for(int right = 1; right < 5 - j; right++)
    {
        if(board[i][j + right].find("!") != std::string::npos)
        {
           h++;
        }
    }
    for(int left = 1; left <= j; left++)
    {
        if(board[i][j - left].find("!") != std::string::npos)
        {
            h++;
        }
    }
    for(int up = 1; up < 5 - i; up++)
    {
        if(board[i + up][j].find("!") != std::string::npos)
        {
            v++;
        }
    }
    for(int down = 1; down <= i; down++)
    {
        if(board[i - down][j].find("!") != std::string::npos)
        {
            v++;
        }
    }
    return (h == 4 or v == 4) ? true : false;
}

int unmarkedSum(std::vector<std::vector<std::string>> board)
{
    int sum = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        if(board[i][j].find("!") == std::string::npos)
        {
            sum += std::stoi(board[i][j]);
        }
    }
    return sum;
}

void part1(std::vector<std::vector<std::vector<std::string>>> boards, std::vector<std::string> numbers)
{
    for(auto number : numbers)
    {
        for(int board = 0; board < boards.size(); board++)
        {
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    if(boards[board][i][j] == number)
                    {
                        boards[board][i][j] += "!";
                        bool bingo = bingoCheck(boards[board], i, j);
                        if(bingo)
                        {
                            std::cout << "Part 1: " << unmarkedSum(boards[board]) * std::stoi(number) << "\n";
                            return;
                        }
                    }

                }
            }
        }
    }
}

void part2(std::vector<std::vector<std::vector<std::string>>> boards, std::vector<std::string> numbers)
{
    for(auto number : numbers)
    {
        for(auto iter = boards.begin(); iter != boards.end();)
        {
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    if(boards[iter - boards.begin()][i][j] == number)
                    {
                        boards[iter - boards.begin()][i][j] += "!";
                        bool bingo = bingoCheck(boards[iter - boards.begin()], i, j);
                        if(bingo)
                        {
                            if(boards.size() == 1)
                            {
                                std::cout << "Part 2: " << unmarkedSum(boards[iter - boards.begin()]) * std::stoi(number) << "\n";
                                return;
                            }
                            iter = boards.erase(iter);
                            goto endLoop;
                        }
                    }
                }
            }
            iter++;
            endLoop:
            {}
        }
    }
    std::cout << boards.size();
}

int main()
{
    std::ifstream file("day4.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::string line;
    int lineCounter = 0;
    std::vector<std::string> numbers;
    std::vector<std::vector<std::string>> board;
    std::vector<std::vector<std::vector<std::string>>> boards;
    while(std::getline(file, line))
    {
        if(line.find(",") != std::string::npos)
        {
            std::string substr;
            std::stringstream ss(line);
            while(std::getline(ss, substr, ','))
            {
                numbers.push_back(substr);
            }
        }
        else if(line.empty())
        {
            if(lineCounter == 5)
            {
                boards.push_back(board);
                lineCounter = 0;
                board.clear();
            }
        }
        else
        {
            std::vector<std::string> temp;
            std::string s;
            std::stringstream ss(line);
            while(std::getline(ss, s, ' '))
            {
                if (!s.empty())
                {
                    temp.push_back(s);
                }
            }
            // std::cout << temp[4] << "\n";
            board.push_back(temp);
            lineCounter++;
        }
    }
    boards.push_back(board);
    part1(boards, numbers);
    part2(boards, numbers);
    return 0;
}