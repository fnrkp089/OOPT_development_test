#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Item.hpp"
#include "ItemManager.hpp"
#include "Bank.hpp"
#include "PaymentManager.hpp"
#include "AuthCode.hpp"
#include "AuthCodeManager.hpp"
#include "AltDVM.hpp"
#include "AltDVMManager.hpp"
#include "MsgManager.hpp"
#include "DVM.hpp"

using namespace std;
/**
 * 각 클래스에서 메서드별로 테스트 코드 하나씩
 * 연관되는 테스트 코드는 나중에
 * Item -> 4개
 * ItemManager -> 6개
 * Bank -> 5개
 * PaymentManager -> 1개
 * AuthCode -> 3개
 * AuthCodeManager -> 5개
 * AltDVM -> 3개
 * AltDVMManager -> 5개
 * MsgManager -> 0개 (아직 구현 덜됨)
 * DVM -> 1개
 * 총 33개
 */

ItemManager itemManager;
PaymentManager paymentManager;
AuthCodeManager authCodeManager;
AltDVMManager altDVMManager(itemManager);
Bank bank;

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
    EXPECT_EQ(itemManager.getSelectedItemId(), 1);
}

// selectedItemNum 반환
TEST(ItemManagerTest, SaveSelectedItemNum){
    itemManager.saveSelectedItem(make_pair(1,1));
    EXPECT_EQ(itemManager.getSelectedItemNum(), 1);
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

// ----- Bank.hpp 관련 테스트 코드 -----
// 결제 성공
TEST(BankTest, PaySuccess) {
    EXPECT_EQ(bank.pay("12345", 5000), 1);
}

// 카드 정보 안맞음
TEST(BankTest, CardNumNotValid) {
    EXPECT_EQ(bank.pay("12343", 5000), 2);
}

// 계좌에 돈이 부족함
TEST(BankTest, MoneyLack) {
    EXPECT_EQ(bank.pay("12345", 50000), 3);
}

// Bank에 계좌정보 저장해둔 map에 잘 저장되는지
TEST(BankTest, GetAccount) {
    auto drinks = bank.getAccount();
    for (const auto& [cardNum, money] : drinks) {
        EXPECT_EQ(cardNum, "12345");
    }
}

TEST(BankTest, GetMoney) {
    auto drinks = bank.getAccount();
    for (const auto& [cardNum, money] : drinks) {
        EXPECT_EQ(money, 10000);
    }
}
// ----- Bank.hpp 관련 테스트 코드 -----

// ----- PaymentManager.hpp 관련 테스트 코드 -----
TEST(PaymentManagerTest, GetCardNum) {
    std::istringstream fakeInput("12345\n");
    std::streambuf* originalCin = std::cin.rdbuf();  // 원래 cin 백업
    std::cin.rdbuf(fakeInput.rdbuf());               // cin을 가짜로 교체

    string result = paymentManager.getCardNum();

    EXPECT_EQ(result, "12345");

    std::cin.rdbuf(originalCin);  // 원래 cin 복원
}

// ----- PaymentManager.hpp 관련 테스트 코드 -----

// ----- AuthCode.hpp 관련 테스트 코드 -----
TEST(AuthCodeTest, getCode){
    AuthCode authCode("12345",1,3);
    EXPECT_EQ(authCode.getCode(), "12345");
}

TEST(AuthCodeTest, getItemId){
    AuthCode authCode("12345",1,3);
    EXPECT_EQ(authCode.getItemId(), 1);
}

TEST(AuthCodeTest, getItemNum){
    AuthCode authCode("12345",1,3);
    EXPECT_EQ(authCode.getItemNum(), 3);
}
// ----- AuthCode.hpp 관련 테스트 코드 -----

// ----- AuthCodeManager.hpp 관련 테스트 코드 -----
TEST(AuthCodeManagerTest, GenerateCode){
    string authCode = authCodeManager.generateCode();
    EXPECT_TRUE(authCode.size()==5);
}

TEST(AuthCodeManagerTest, IsvalidAuthCodeTrue){
    authCodeManager.saveAuthCode("10101", 1, 3);
    EXPECT_TRUE(authCodeManager.isValidAuthCode("10101"));
}

TEST(AuthCodeManagerTest, IsvalidAuthCodeFalse){
    authCodeManager.saveAuthCode("10101", 1, 3);
    EXPECT_FALSE(authCodeManager.isValidAuthCode("11111"));
}

TEST(AuthCodeManagerTest, PopAuthCodeId){
    authCodeManager.saveAuthCode("10101", 1, 3);
    pair<int,int> itemIditemNum = authCodeManager.popAuthCode("10101");
    EXPECT_EQ(itemIditemNum.first, 1);
}

TEST(AuthCodeManagerTest, PopAuthCodeNum){
    authCodeManager.saveAuthCode("10101", 1, 3);
    pair<int,int> itemIditemNum = authCodeManager.popAuthCode("10101");
    EXPECT_EQ(itemIditemNum.second, 3);
}
// ----- AuthCodeManager.hpp 관련 테스트 코드 -----

// ----- AltDVM.hpp 관련 테스트 코드 -----
TEST(AltDVMTest, GetID){
    AltDVM altDVM("2", 3, 4);
    EXPECT_EQ(altDVM.getId(), "2");
}
TEST(AltDVMTest, GetLocationX){
    AltDVM altDVM("2", 3, 4);
    EXPECT_EQ(altDVM.getLocation().first, 3);
}

TEST(AltDVMTest, GetLocationY){
    AltDVM altDVM("2", 3, 4);
    EXPECT_EQ(altDVM.getLocation().second, 4);
}
// ----- AltDVM.hpp 관련 테스트 코드 -----

// ----- AltDVMManager.hpp 관련 테스트 코드 -----
TEST(AltDVMManagerTest, AddDVM1){
    altDVMManager.addDVM("5", 5, 6, "T");
    EXPECT_EQ(altDVMManager.getAltDVMList()[3].getId(), "5");
}

TEST(AltDVMManagerTest, AddDVM2){
    altDVMManager.addDVM("5", 5, 6, "T");
    EXPECT_EQ(altDVMManager.getAltDVMList()[3].getLocation(), make_pair(5,6));
}

TEST(AltDVMManagerTest, SelectAltDVM){
    altDVMManager.selectAltDVM(1,1);
    EXPECT_EQ(altDVMManager.getSelectedDVM(), "2");
}

TEST(AltDVMManagerTest, GetAltDVMLocation){
    altDVMManager.selectAltDVM(1,1);
    EXPECT_EQ(altDVMManager.getAltDVMLocation(), make_pair(1,3));
}

TEST(AltDVMManagerTest, Reset){
    altDVMManager.reset();
    EXPECT_EQ(altDVMManager.getAltDVMList().size(), 0);
}
// ----- AltDVMManager.hpp 관련 테스트 코드 -----

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