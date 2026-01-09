#pragma once
// ===================== YOUR LIBRARY IMPORTS =====================
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
// ===================== analyzer.h (inlined) =====================
using namespace std;

struct ZoneCount {
    std::string zone;
    long long count;
};

struct SlotCount {
    std::string zone;
    int hour;
    long long count;
};


class TripAnalyzer {
public:
    void ingestStdin();
    void ingestFile(const std::string& csvPath);

    std::unordered_map<std::string, long long> zone_counts;
    std::map<std::pair<std::string, int>, long long> slot_counts;

    std::vector<ZoneCount> topZones(int k = 10) const;

    std::vector<SlotCount> topBusySlots(int k = 10) const;
};
