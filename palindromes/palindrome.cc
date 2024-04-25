#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>
#include <unordered_map>
#include <windows.h>


using namespace std;

int main() {

    ifstream file("words.txt");
    ofstream res("result.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return -1;
    }

    unordered_map<string, set<string>> map;

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for (string s; file >> s; ) {
        transform(s.begin(), s.end(), s.begin(), [](const char& c){
            return ::tolower(c);
        });
        string tmp = s;
        sort(s.begin(), s.end());

        if(map.find(s) == map.end()){
            map.insert( {s, set<string>{tmp}} ); 
        }
        else{
            map[s].insert(tmp);
        }
    }

    file.close();
    vector<pair<string, set<string>>> vec(map.begin(), map.end());

    sort(vec.begin(), vec.end(), [](const auto& a, const auto& b){
        return a.second.size() > b.second.size();
    });


    for(const auto& [key, value]: vec){
        if (value.size() > 0){
        res << key <<"[" << value.size() << "] == ";
        for(const auto& element : value){
            res << "[" << element << "] ";
        }
        res << endl;
        }
    }

    res.close();

    QueryPerformanceCounter(&end);
    double elapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    std::cout << "Elapsed time: " << elapsedTime << " seconds" << std::endl;

    return 0;
}