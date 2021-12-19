#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <set>
#include <queue>

typedef std::vector<std::vector<int>> graph;

void solve(graph input, int rs = 0, int cs = 0)
{
    // Create a distance vector, init to inf
    graph dist(input.size(), std::vector<int>(input[0].size(), 1e9));
    // Source distance = 0
    dist[rs][cs] = 0;

    // Unvisited nodes
    graph visited(input.size(), std::vector<int>(input[0].size(), false));


    auto cmp = [](std::tuple<int,int,int>& left, std::tuple<int,int,int>& right) { return std::get<0>(left) > std::get<0>(right);};
    std::priority_queue<std::tuple<int,int,int>, std::vector<std::tuple<int,int,int>>, decltype(cmp)> pq(cmp);

    int counter = -1;
    pq.push(std::make_tuple(0,0,0));

    while(!pq.empty())
    {

        std::tuple<int,int,int> currentNode = pq.top();
        int currentDistance = std::get<0>(currentNode);
        int current_x = std::get<1>(currentNode);
        int current_y = std::get<2>(currentNode);
        pq.pop();

        std::vector<std::tuple<int,int>> moves {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for(auto move: moves)
        {
            int x = std::get<0>(move);
            int y = std::get<1>(move);
            try{
                if(visited.at(current_x + x).at(current_y + y) == false)
                {
                    int nextDistance = currentDistance + input.at(current_x + x).at(current_y + y);
                    if(nextDistance < dist.at(current_x + x).at(current_y + y))
                    {
                        dist.at(current_x + x).at(current_y + y) = nextDistance;
                        pq.push(std::make_tuple(nextDistance, current_x + x, current_y + y));
                    }
                }  
            }
            catch (std::out_of_range const &exec)
            {}
        }
        visited[current_x][current_y] = true;
    }
    std::cout << dist[input.size() - 1][input[0].size() - 1] << "\n";
}

int main()
{
    std::ifstream file("day15.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    std::vector<std::vector<int>> input;
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<int> temp;
        for(char l : line)
        {
            int a = l - '0';
            temp.push_back(a);
        }
        input.push_back(temp);
    }
    // std::vector<std::vector<int>> input2;
    // for(int row = 0; row < input.size(); row++)
    // {
    //     for(int i = 0; i < 4; i++)
    //     {
    //         std::vector<int>temp = std::for_each(input[row].begin(), input[row].end(), [](int n){return (n == 9) ? 1 : n++;});
    //     }
    // }
    solve(input);
}