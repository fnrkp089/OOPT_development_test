#include "ItemManager.hpp"
#include <iostream>

// 생성자
ItemManager::ItemManager()
    : selectedItemId(0), selectedItemNum(0) {
    // 초기 아이템 등록
    itemList.emplace_back(1, "콜라", 1500, 10);
    itemList.emplace_back(2, "사이다", 1400, 8);
    itemList.emplace_back(3, "녹차", 1300, 5);
    itemList.emplace_back(4, "홍차", 1350, 6);
    itemList.emplace_back(5, "밀크티", 1800, 7);
    itemList.emplace_back(6, "탄산수", 1200, 10);
    itemList.emplace_back(7, "보리차", 1100, 9);
    itemList.emplace_back(8, "캔커피", 1600, 8);
    itemList.emplace_back(9, "물", 1000, 20);
    itemList.emplace_back(10, "에너지드링크", 2000, 6);
    itemList.emplace_back(11, "유자차", 1500, 4);
    itemList.emplace_back(12, "식혜", 1400, 5);
    itemList.emplace_back(13, "아이스티", 1350, 6);
    itemList.emplace_back(14, "딸기주스", 1700, 7);
    itemList.emplace_back(15, "오렌지주스", 1700, 8);
    itemList.emplace_back(16, "포도주스", 1700, 7);
    itemList.emplace_back(17, "이온음료", 1300, 10);
    itemList.emplace_back(18, "아메리카노", 1900, 5);
    itemList.emplace_back(19, "핫초코", 1800, 6);
    itemList.emplace_back(20, "카페라떼", 2000, 4);
}

// 아이템 목록 보여주기
void ItemManager::showItemList() const {
    for(int id=0; id<itemList.size(); id++){
        std::cout << "ID: " << id+1
                << ", Name: " << itemList[id].getName()
                << ", Price: " << itemList[id].getCost(1)
                << ", Stock: " << itemList[id].getStock() << std::endl;
    }
}

// 선택된 아이템 저장
void ItemManager::saveSelectedItem(pair<int, int> saveInfo) {
    selectedItemId = saveInfo.first;
    selectedItemNum = saveInfo.second;
}

// 선택된 아이템의 재고가 충분한지 확인
bool ItemManager::isEnough() const {
    if(itemList[selectedItemId-1].getStock() >= selectedItemNum)
        return true;
    else
        return false;
}

// 선택된 아이템 재고 감소
void ItemManager::minusStock() {
    itemList[selectedItemId-1].decreaseStock(selectedItemNum);
}

// 구매 결과 출력
void ItemManager::showBuyResult() {
    cout << itemList[selectedItemId-1].getName() << " " << selectedItemNum << "개 구매되었습니다." << std::endl;
}

int ItemManager::getPaymentAmount(){
    return itemList[selectedItemId-1].getCost(selectedItemNum);
}

// 구글테스트용 메서드
int ItemManager::getselectedItemId(){
    return selectedItemId;
}
int ItemManager::getselectedItemNum(){
    return selectedItemNum;
}

vector<Item> ItemManager::getItemList(){
    return itemList;
}