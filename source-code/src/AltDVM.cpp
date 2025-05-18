#include "AltDVM.hpp"

AltDVM::AltDVM(const std::string& id, int x, int y)
    : DVMId(id), coordX(x), coordY(y) {}

std::string AltDVM::getId() const {
    return DVMId;
}

std::pair<int, int> AltDVM::getLocation() const {
    return {coordX, coordY};
}