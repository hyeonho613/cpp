#include <iostream>
#include <string>

// 문제 1: 예외 클래스를 정의하여 예외의 종류와 금액 정보를 저장
// - 기본 예외 클래스와 입금/출금 예외를 위한 파생 클래스
class AccountException {
protected:
    std::string message; // 예외 메시지 저장
    int amount;         // 금액 정보 저장
public:
    AccountException(const std::string& msg, int amt) : message(msg), amount(amt) {}
    virtual std::string getMessage() const { return message; } // 메시지 반환
    int getAmount() const { return amount; } // 금액 반환
    virtual ~AccountException() {} // 가상 소멸자
};

class InvalidDepositException : public AccountException {
public:
    InvalidDepositException(int amt) // 입금 금액이 0 이하일 때
        : AccountException("Invalid deposit", amt) {}
};

class InsufficientFundsException : public AccountException {
public:
    InsufficientFundsException(int amt, int bal) // 출금 금액이 잔액 초과일 때
        : AccountException("Insufficient funds", amt) {}
};

// 문제 2: CustomerAccount 클래스의 deposit(), withdraw()에서 예외 상황 발생 시 예외를 던지기만 함
class CustomerAccount {
private:
    int balance; // 계좌 잔액
public:
    CustomerAccount(int b = 0) : balance(b) {} // 생성자
    int getBalance() const { return balance; } // 잔액 조회
    int deposit(int amount) { // 입금 함수
        if (amount <= 0) throw InvalidDepositException(amount); // 음수 입금 시 예외
        balance += amount;
        return balance;
    }
    int withdraw(int amount) { // 출금 함수
        if (amount > balance) throw InsufficientFundsException(amount, balance); // 잔액 부족 시 예외
        balance -= amount;
        return balance;
    }
};

// 문제 3: main()에서 예외 처리를 포함한 테스트 코드 작성, 예외 처리 동작 확인
int main() {
    CustomerAccount account(1000); // 초기 잔액 1000

    try { // 입금 테스트
        std::cout << "Balance: " << account.getBalance() << std::endl; // 초기 잔액 출력
        account.deposit(500); // 정상 입금
        std::cout << "After deposit 500: " << account.getBalance() << std::endl; // 입금 후 잔액
        account.deposit(-100); // 잘못된 입금 시도
    } catch (const InvalidDepositException& e) { // 입금 예외 처리
        std::cout << e.getMessage() << ": " << e.getAmount() << std::endl;
    }

    try { // 출금 테스트
        account.withdraw(300); // 정상 출금
        std::cout << "After withdraw 300: " << account.getBalance() << std::endl; // 출금 후 잔액
        account.withdraw(2000); // 잔액 초과 출금 시도
    } catch (const InsufficientFundsException& e) { // 출금 예외 처리
        std::cout << e.getMessage() << std::endl;
    } catch (...) { // 기타 예외 처리
        std::cout << "Unknown error" << std::endl;
    }

    return 0;
}