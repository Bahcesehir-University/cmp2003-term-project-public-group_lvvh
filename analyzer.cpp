#include "analyzer.h"

// Students may use ANY data structure internally

void TripAnalyzer::ingestFile(const std::string& csvPath) {
    std::ifstream file(csvPath);
    
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    
    std::getline(file, line)
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;
        
        try {
            if (line.empty()) {
                continue;
            }
            
            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }
            
            if (fields.size() == 6) {
                if (fields[3].length() < 16) {
                    continue;
                }
                
                zone_counts[fields[1]]++;  
                slot_counts[{fields[1], std::stoi(fields[3].substr(11, 2))}]++;
            }
        }
        catch(const std::exception& e) {
            // Skip malformed rows
        }
    }
    
    file.close();
}
void TripAnalyzer::ingestStdin() {
	std::string line;

    while (std::getline(std::cin, line)) {

        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;

        try
        {
            if (line.empty()) {
            continue;
            }

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }
		
            if (fields.size() == 6) {
                if (fields[3].length() < 16) {
                    continue;
                }

                zone_counts[fields[1]]++;  
                slot_counts[{fields[1], std::stoi(fields[3].substr(11, 2))}]++;
            }
        }
        catch(const std::exception& e)
        {
        }
    }
}


vector<ZoneCount> TripAnalyzer::topZones(int k) const {
    std::vector<ZoneCount> zones;
    zones.reserve(zone_counts.size());
    
    for (const auto& pair : zone_counts) {
        zones.push_back({pair.first, pair.second});
    }

    std::sort(zones.begin(), zones.end(), 
          [](const ZoneCount& a, const ZoneCount& b) {
              if (a.count != b.count)
                  return a.count > b.count;
              return a.zone < b.zone;
          });
    
    if (zones.size() > static_cast<size_t>(k)) {
        zones.resize(k);
    }
    
    return zones;
}

vector<SlotCount> TripAnalyzer::topBusySlots(int k) const {
    std::vector<SlotCount> slots;
    slots.reserve(slot_counts.size());
    
    for (const auto& pair : slot_counts) {
        slots.push_back({pair.first.first, pair.first.second, pair.second});
    }
    
    std::sort(slots.begin(), slots.end(), 
          [](const SlotCount& a, const SlotCount& b) {
              if (a.count != b.count)
                  return a.count > b.count;
              if (a.zone != b.zone)
                  return a.zone < b.zone;
              return a.hour < b.hour;
          });
    
    if (slots.size() > static_cast<size_t>(k)) {
        slots.resize(k);
    }
    
    return slots;
}
