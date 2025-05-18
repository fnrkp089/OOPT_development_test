#include "AltDVMManager.hpp"
#include <cmath>
#include <limits>

AltDVMManager::AltDVMManager(ItemManager* im) : itemManager(im) {}

void AltDVMManager::addDVM(const std::string& dvmId, int coordX, int coordY, const std::string& availability) {
    if (availability == "T") {
        DVMList.emplace_back(dvmId, coordX, coordY);
    }
}

void AltDVMManager::selectAltDVM(int currX, int currY) {
    if (DVMList.empty()) return;

    int minDist = std::numeric_limits<int>::max();
    for (auto& dvm : DVMList) {
        auto [x, y] = dvm.getLocation();
        int dist = (currX - x) * (currX - x) + (currY - y) * (currY - y);
        if (dist < minDist) {
            minDist = dist;
            selectedDVM = dvm.getId();
        }
    }
}

std::string AltDVMManager::getSelectedDVM() const {
    return selectedDVM;
}

void AltDVMManager::reset() {
    DVMList.clear();
    selectedDVM.clear();
}