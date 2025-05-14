// done
#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
private:
    int itemId;
    std::string name;
    int cost;
    int stock;

public:
    // 생성자
    Item(int itemId, const std::string& name, int price, int stock);

    // Getter
    int getStock() const;
    int getCost(int itemNum) const;
    string getName() const;

    // 추가 메서드
    void decreaseStock(int amount);
};

#endif // ITEM_H