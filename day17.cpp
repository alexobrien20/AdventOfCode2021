#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void solve(int x1, int x2, int y1, int y2)
{
    std::vector<int> ys;
    int a2= 0;
    for(int x = 0; x < 1000; x++)
    {
        for(int y = -1000; y < 1000; y++) 
        {
            int x_pos = 0;
            int y_pos = 0;
            int step = 0;
            while(true)
            {
                if(x_pos > std::max(x1, x2) || y_pos < std::min(y1,y2))
                {
                    break;
                }
                else if (x_pos >= std::min(x1, x2) && x_pos <= std::max(x1, x2) && y_pos >= std::min(y1,y2) && y_pos <= std::max(y1,y2))
                {
                    a2++;
                    ys.push_back((y * (y + 1)) / 2);
                    break;
                }
                if(step < x)
                {
                    x_pos += (x - step);
                }
                y_pos += (y - step);
                step++;
            }
        }
    }
    int max = *std::max_element(ys.begin(), ys.end());
    std::cout << "Part 1 Answer : " << max << "\n";
    std::cout << "Part 2 Answer : " << a2 << "\n";
}

int main()
{
    std::ifstream file("day17.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    int x1, x2, y1, y2;
    std::string line;
    while(std::getline(file, line))
    { 
        std::string s = line.substr(0, line.find(","));
        std::string xs = s.substr(s.find("x") + 2, std::string::npos);
        std::string ys = line.substr(line.find("y") + 2, std::string::npos);
        y1 = std::stoi(ys.substr(0, ys.find("..")));
        y2 = std::stoi(ys.substr(ys.find("..") + 2, std::string::npos));
        x1 = std::stoi(xs.substr(0, xs.find("..")));
        x2 = std::stoi(xs.substr(xs.find("..") + 2, std::string::npos));
    }
    solve(x1, x2, y1, y2);
}