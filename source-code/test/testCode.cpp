#include <gtest/gtest.h>
#include "Item.hpp"
#include "ItemManager.hpp"

/**
 * 각 클래스에서 메서드별로 테스트 코드 하나씩
 * 연관되는 테스트 코드는 나중에
 */

// ----- Item.hpp 관련 테스트 코드 -----
// 음료수 이름 출력
TEST(ItemTest, GetItemName) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_EQ(item.getName(), "콜라");
}

// 음료수 가격 출력
TEST(ItemTest, GetItemCost) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_EQ(item.getCost(1), 1500);
}

// 음료수 수량 출력
TEST(ItemTest, GetItemStock) {
    Item item(1, "콜라", 1500, 10);
    EXPECT_EQ(item.getStock(), 10);
}
// 재고 감소
TEST(ItemTest, DecreaseItemStock) {
    Item item(1, "콜라", 1500, 5);
    item.decreaseStock(1);
    EXPECT_EQ(item.getStock(), 4);
}
// ----- Item.hpp 관련 테스트 코드 -----

// ----- ItemManager.hpp 관련 테스트 코드 -----

TEST(ItemManagerTest, SaveSelectedItem){
    ItemManager itemManager;
    itemManager.saveSelectedItem(make_pair(1,1));
}