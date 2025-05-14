#include "Item.hpp"
#include <iostream>

// 생성자 정의 (done)
Item::Item(int itemId, const std::string& name, int cost, int stock)
    : itemId(itemId), name(name), cost(cost), stock(stock) {}

// 재고 반환 (done)
int Item::getStock() const {
    return stock;
}

// 수량에 따른 총 비용 계산 (done)
int Item::getCost(int itemNum) const {
    return cost * itemNum;
}

// 추가 메서드
void Item::decreaseStock(int amount) {
    if (stock >= amount) {
        stock -= amount;
    }
}

void Item::printMenu() const{
    std::cout << "ID: " << itemId
            << ", Name: " << name
            << ", Price: " << cost
            << ", Stock: " << stock << std::endl;
}

void Item::printResult(int selectedItemNum) const{
    std::cout << name << " " << selectedItemNum << "개 구매되었습니다." << std::endl;
}