#include "Item.hpp"
#include <iostream>

// 생성자 정의
Item::Item(int itemId, const std::string& name, int cost, int stock)
    : itemId(itemId), name(name), cost(cost), stock(stock) {}

// 재고 반환
int Item::getStock() const {
    return stock;
}

// 수량에 따른 총 비용 계산
int Item::getCost(int itemNum) const {
    return cost * itemNum;
}

string Item::getName() const {
    return name;
}

// 추가 메서드
void Item::decreaseStock(int amount) {
    if (stock >= amount) {
        stock -= amount;
    }
}