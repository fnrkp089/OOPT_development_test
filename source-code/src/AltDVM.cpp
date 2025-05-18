#include "AltDVM.hpp"

using namespace std;

AltDVM::AltDVM(const string& id, int x, int y)
    : DVMId(id), coorX(x), coorY(y) {}

string AltDVM::getId() const {
    return DVMId;
}

pair<int, int> AltDVM::getLocation() const {
    return {coorX, coorY};
}