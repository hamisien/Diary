/*
 * Banking System Ver 0.2
 * OOP 02
 * 작성자: hamisien
 * 내 용: Account 클래스 정의, 객체 포인터 배열 적용
 */

#include <iostream>
#define MAX_LENGHT 255

using namespace std;

void prtMenu(void);
void estAcc(void); // 1. 계좌개설
void depo(void); // 2. 입 금
void withd(void); // 3. 출 금
void prtAcc(void); // 4. 계좌정보 전체 출력

enum {ESTA = 1, DEPO, WITHD, PRTA, EXIT};

class Account{
private:
	int id = 0;
	char* name;
	int amount = 0;
public:
	Account () //int id, char* name, int amount) 
		// : id(id), name(name), amount(amount)
	{
		
	}
};

Account* Acc = new Account[MAX_LENGHT];

int ele = 1;

int main(void)
{
	int sel;
	
	while(1){
		prtMenu();
		cout << "선택: "; cin >> sel; cout << endl;

		switch(sel){
			case ESTA:
				estAcc();
				break;
			case DEPO:
				depo();
				break;
			case WITHD:
				withd();
				break;
			case PRTA:
				prtAcc();
				break;
			case EXIT:
				return 0;
			default:
				cout << "입력 오류!!" << endl;
		}
	}
	
	return 0;
}

void prtMenu(void)
{
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void estAcc(void)
{
	cout << "[계좌개설]" << endl;
	cout << "계좌ID: "; cin >> Acc[ele].id;
	cout << "이 름: "; cin >> Acc[ele].name;
	cout << "입금액: "; cin >> Acc[ele].amount;
	ele++;
}

void depo(void)
{
	int tmp_Accid = 0, tmp_amount = 0;
	
	cout << "[입   금]" << endl;
	cout << "계좌ID: "; cin >> tmp_Accid;
	cout << "입금액: "; cin >> tmp_amount;
	
	for(int i = 1; i <= ele; i++){
		if(tmp_Accid == Acc[i].id){
			Acc[i].amount += tmp_amount;
			cout << "입금완료" << endl;
			
			return;
		}
	}
	cout << "입금실패" << endl;
}

void withd(void)
{
	int tmp_Accid = 0, tmp_amount = 0;
	cout << "[출   금]" << endl;
	cout << "계좌ID: "; cin >> tmp_Accid;
	cout << "출금액: "; cin >> tmp_amount;
	
	for(int i = 1; i <= ele; i++){
		if(tmp_Accid == Acc[i].id){
			Acc[i].amount -= tmp_amount;
			cout << "출금완료" << endl;
			
			return;
		}
	}
	cout << "출금실패" << endl;
}

void prtAcc(void)
{
	for(int i = 1; i < ele; i++){
		cout << "계좌ID: " << Acc[i].id << endl;
		cout << "이 름: " << Acc[i].name << endl;
		cout << "잔 액: " << Acc[i].amount << endl << endl;	
	}
}
