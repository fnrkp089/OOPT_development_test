#pragma once
#include <string>
#include <utility>

class AltDVM {
private:
    std::string DVMId;
    int coordX;
    int coordY;

public:
    AltDVM(const std::string& id, int x, int y);
    std::string getId() const;
    std::pair<int, int> getLocation() const;
};