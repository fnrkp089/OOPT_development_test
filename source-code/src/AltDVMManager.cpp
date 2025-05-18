#include "AltDVMManager.hpp"
#include <cmath>
#include <limits>

using namespace std;

AltDVMManager::AltDVMManager(ItemManager* im) : itemManager(im) {}

void AltDVMManager::addDVM(const string& dvmId, int coorX, int coorY, const string& availability) {
    if (availability == "T") {
        DVMList.emplace_back(dvmId, coorX, coorY);
    }
}

void AltDVMManager::selectAltDVM(int currX, int currY) {
    if (DVMList.empty()) return;

    int minDist = numeric_limits<int>::max();
    for (auto& dvm : DVMList) {
        auto [x, y] = dvm.getLocation();
        int dist = (currX - x) * (currX - x) + (currY - y) * (currY - y);
        if (dist < minDist) {
            minDist = dist;
            selectedDVM = dvm.getId();
        }
    }
}

string AltDVMManager::getSelectedDVM() const {
    return selectedDVM;
}

void AltDVMManager::reset() {
    DVMList.clear();
    selectedDVM.clear();
}