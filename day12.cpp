#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <set>

typedef std::map<std::string, std::vector<std::string>> graph;

bool checkMoreThanOne(std::vector<std::string> visited, bool part2)
{
    int moreThan1 = 0;
    for(auto v : visited)
    {
        int x = std::count(visited.begin(), visited.end(), v);
        if(x > part2)
        {
            moreThan1++;
        }
        if(moreThan1 > part2)
        {
            return false;
        }
    }
    return true;
}

int search(std::string node, graph g, std::vector<std::string> visited, int paths, bool part2)
{

    std::vector<std::string> og = visited;
    for(auto nextNode : g[node])
    {   
        visited = og;
        std::set<std::string> s(visited.begin(), visited.end());
        bool unique = (part2 == true) ? visited.size() != s.size() : true;
        if(std::find(visited.begin(), visited.end(), nextNode) != visited.end() && unique && !checkMoreThanOne(visited, part2))
        {
            continue;
        }
        else if(nextNode == "end")
        {
            paths++;
        }
        else
        {
            if(std::all_of(nextNode.begin(), nextNode.end(), [](char c){return std::islower(c);}))
            {
                visited.push_back(nextNode);
            }
            paths = search(nextNode, g, visited, paths, part2);
        }
    }
    return paths;
}

void part1(graph g)
{
    int paths = 0;
    std::vector<std::string> visited;
    int answer = search("start", g, visited, paths, false);  
    std::cout << "Part 1 Answer : " << answer << "\n";  
}

void part2(graph g)
{
    int paths = 0;
    std::vector<std::string> visited;
    int answer = search("start", g, visited, paths, true);  
    std::cout << "Part 2 Answer : " << answer << "\n";  
}

int main()
{
    std::ifstream file("day12.txt");
    if(!file){ std::cout << "Error openning file!"; return 0;}
    graph g;
    std::string line;
    while(std::getline(file, line))
    {
        std::string s = line.substr(0, line.find('-'));
        if(line.find("end") != std::string::npos)
        {
            if(s.find("end") != std::string::npos)
            {   
                std::string start = line.substr(line.find("-") + 1, std::string::npos);
                g[start].push_back(s);
            }
            else
            {
                g[s].push_back("end");
            }
        }
        else if(line.find("start") != std::string::npos)
        {
            if(s.find("start") != std::string::npos)
            {   
                std::string end = line.substr(line.find("-")+1, std::string::npos);
                g["start"].push_back(end);
            }
            else
            {
                g["start"].push_back(s);
            }
        }
        else
        {
            std::string end = line.substr(line.find('-') + 1, std::string::npos);
            g[s].push_back(end);
            g[end].push_back(s);
        }

    }
    part1(g);
    part2(g);
}