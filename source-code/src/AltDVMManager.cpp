#include "AltDVMManager.hpp"
#include <cmath>
#include <limits>

using namespace std;

AltDVMManager::AltDVMManager(ItemManager im) : itemManager(im) {
    DVMList.emplace_back("2", 1, 3);
    DVMList.emplace_back("3", 2, 4);
    DVMList.emplace_back("4", 5, 8);
}

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
            selectedDVMId = dvm.getId();
        }
    }
}

string AltDVMManager::getSelectedDVM() const {
    return selectedDVMId;
}

void AltDVMManager::reset() {
    DVMList.clear();
    selectedDVMId.clear();
}

std::pair<int,int> AltDVMManager::getAltDVMLocation() const{
    for(int iter = 0; iter<DVMList.size(); iter++){
        if(DVMList[iter].getId().compare(selectedDVMId)==0){
            return DVMList[iter].getLocation();
        }
    }
    return {-1,-1};
}

std::vector<AltDVM> AltDVMManager::getAltDVMList()
{
    return DVMList;
}