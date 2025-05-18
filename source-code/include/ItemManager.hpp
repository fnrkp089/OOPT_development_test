#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>
#include "Item.hpp"

using namespace std;

class ItemManager {
private:
    vector<Item> itemList;
    int selectedItemId;
    int selectedItemNum;

public:
    // 생성자
    ItemManager();

    // 메서드
    void showItemList() const;
    void saveSelectedItem(pair<int, int> saveInfo); // 매개변수 추가
    bool isEnough() const;
    void minusStock();

    // 추가 메서드
    void showBuyResult();
    int getPaymentAmount();

    // 구글테스트용 메서드
    int getselectedItemId();
    int getselectedItemNum();
    vector<Item> getItemList();
};

#endif // ITEMMANAGER_H