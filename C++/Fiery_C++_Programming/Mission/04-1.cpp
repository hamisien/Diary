/*
    * Date: 2021.08.14.
    * Author: hamisien
    * Title: Mission 04-1
*/

#include <iostream>
using namespace std;

class FruitSeller
{
private:
    int APPLE_PRICE;
    int numOfApples;
    int myMoney;

public:
    void InitMembers(int price, int num, int money)
    {
        APPLE_PRICE=price;
        numOfApples=num;
        myMoney=money;
    }
    int SaleApples(const int &money) // 매개변수 형식을 const 참조자 형식으로 변경하여 변수 변경의 가능성을 줄임.
    {
        if (money/APPLE_PRICE < 0){
            cout << "사과의 구매를 목적으로 0보다 작은 수를 전달할 수 없습니다." << endl;
            return 0;
        }
        int num=money/APPLE_PRICE;
        numOfApples-=num;
        myMoney+=money;
        return num;
    }
    void ShowSalesResult() const // 함수 끝에 const 함수를 추가하여 해당 함수에서 멤버변수의 값을 변경하지 않음을 선언함.
    {
        cout << "남은 사과: " << numOfApples << endl;
        cout << "판매 수익: " << myMoney << endl << endl;
    }
};

class FruitBuyer
{
    int myMoney; // private
    int numOfApples; // private

public:
    void InitMembers(const int &money) // 매개변수 형식을 const 참조자 형식으로 변경하여 변수 변경의 가능성을 줄임.
    {
        myMoney=money;
        numOfApples=0;
    }
    void BuyApples(FruitSeller &seller, int money)
    {
        numOfApples+=seller.SaleApples(money);
        myMoney-=money;
    }
    void ShowBuyResult() const // 함수 끝에 const 함수를 추가하여 해당 함수에서 멤버변수의 값을 변경하지 않음을 선언함.
    {
        cout << "현재 잔액: " << myMoney << endl;
        cout << "사과 개수: " << numOfApples << endl << endl;
    }
};

int main(void)
{
    FruitSeller seller;
    seller.InitMembers(1000, 20, 0);
    FruitBuyer buyer;
    buyer.InitMembers(5000);
    buyer.BuyApples(seller, 2000);

    cout << "과일 판매자의 현황" << endl;
    seller.ShowSalesResult();
    cout << "과일 구매자의 현황" << endl;
    buyer.ShowBuyResult();

    return 0;
}