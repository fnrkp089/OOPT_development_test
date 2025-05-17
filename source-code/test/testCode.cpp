#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Item.hpp"
#include "ItemManager.hpp"
#include "DVM.hpp"

using namespace std;
/**
 * 각 클래스에서 메서드별로 테스트 코드 하나씩
 * 연관되는 테스트 코드는 나중에
 */

ItemManager itemManager;

// ----- Item.hpp 관련 테스트 코드 -----
// 음료수 이름 출력
TEST(ItemTest, GetItemName) {
    EXPECT_EQ(itemManager.getItemList()[0].getName(), "콜라");
}

// 음료수 가격 출력
TEST(ItemTest, GetItemCost) {
    EXPECT_EQ(itemManager.getItemList()[0].getCost(1), 1500);
}

// 음료수 수량 출력
TEST(ItemTest, GetItemStock) {
    EXPECT_EQ(itemManager.getItemList()[0].getStock(), 10);
}
// 재고 감소
TEST(ItemTest, DecreaseItemStock) {
    Item item(1, "콜라", 1500, 5);
    item.decreaseStock(1);
    EXPECT_EQ(item.getStock(), 4);
}
// ----- Item.hpp 관련 테스트 코드 -----

// ----- ItemManager.hpp 관련 테스트 코드 -----

// selectedItemId 반환
TEST(ItemManagerTest, SaveSelectedItemId){
    itemManager.saveSelectedItem(make_pair(1,1));
    EXPECT_EQ(itemManager.getselectedItemId(), 1);
}

// selectedItemNum 반환
TEST(ItemManagerTest, SaveSelectedItemNum){
    itemManager.saveSelectedItem(make_pair(1,1));
    EXPECT_EQ(itemManager.getselectedItemNum(), 1);
}

// 재고 확인 TRUE
TEST(ItemManagerTest, IsEnoughTrue){
    itemManager.saveSelectedItem(make_pair(1,1));
    EXPECT_TRUE(itemManager.isEnough());
}

// 재고 확인 FALSE
TEST(ItemManagerTest, IsEnoughFalse){
    itemManager.saveSelectedItem(make_pair(1,50));
    EXPECT_FALSE(itemManager.isEnough());
}

// 재고 확인 FALSE
TEST(ItemManagerTest, MinusStock){
    itemManager.saveSelectedItem(make_pair(1,1));
    itemManager.minusStock();
    EXPECT_EQ(itemManager.getItemList()[0].getStock(), 9);
}

// 재고 확인 FALSE
TEST(ItemManagerTest, GetPaymentAmount){
    itemManager.saveSelectedItem(make_pair(1,1));
    EXPECT_EQ(itemManager.getPaymentAmount(), 1500);
}

// ----- DVM.hpp 관련 테스트 코드 -----
TEST(DVMTest, AskBuyOrCodeInput) {
    DVM dvm("12",1,1);
    std::istringstream fakeInput("1\n");
    std::streambuf* originalCin = std::cin.rdbuf();  // 원래 cin 백업
    std::cin.rdbuf(fakeInput.rdbuf());               // cin을 가짜로 교체

    bool result = dvm.askBuyOrCodeInput();

    EXPECT_TRUE(result);

    std::cin.rdbuf(originalCin);  // 원래 cin 복원
}
// ----- DVM.hpp 관련 테스트 코드 -----