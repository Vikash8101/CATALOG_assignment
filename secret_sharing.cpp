#include <iostream>
#include <fstream>
#include <json/json.h> 
#include <vector>
#include <cmath>

using namespace std;


long long decodeValue(const string &value, int base) {
    long long result = 0;
    for (char ch : value) {
        int digit;
        if (ch >= '0' && ch <= '9') digit = ch - '0';
        else if (ch >= 'a' && ch <= 'f') digit = 10 + (ch - 'a');
        else digit = 10 + (ch - 'A');
        result = result * base + digit;
    }
    return result;
}


vector<pair<int, long long>> parseInputData(const string &filename) {
    ifstream file(filename);
    Json::Value data;
    file >> data;

    vector<pair<int, long long>> points;
    int n = data["keys"]["n"].asInt();
    
    for (const auto &key : data.getMemberNames()) {
        if (key == "keys") continue;
        int x = stoi(key);
        int base = data[key]["base"].asInt();
        string valueStr = data[key]["value"].asString();
        long long y = decodeValue(valueStr, base);
        points.emplace_back(x, y);
    }
    return points;
}


long long calculateConstantTerm(const vector<pair<int, long long>> &points, int k) {
    long long constantTerm = 0;
    for (int i = 0; i < k; ++i) {
        long long x_i = points[i].first;
        long long y_i = points[i].second;
        
        
        long long L_i = 1;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                long long x_j = points[j].first;
                L_i *= -x_j;
                L_i /= (x_i - x_j);
            }
        }
        
        
        constantTerm += y_i * L_i;
    }
    return constantTerm;
}

int main() {
    
    vector<pair<int, long long>> points1 = parseInputData("testcase1.json");
    vector<pair<int, long long>> points2 = parseInputData("testcase2.json");

    
    int k1 = 3; 
    int k2 = 7; 

    
    long long constantTerm1 = calculateConstantTerm(points1, k1);
    long long constantTerm2 = calculateConstantTerm(points2, k2);

    
    cout << "Secret for Test Case 1: " << constantTerm1 << endl;
    cout << "Secret for Test Case 2: " << constantTerm2 << endl;

    return 0;
}
