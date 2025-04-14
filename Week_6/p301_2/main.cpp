#include "dictionary.h"
#include <iostream>

int main() {
    MyDic dic;
    string command;

    while (true) {
        cout << "\n명령어 (add/load/store/print/get/exit): ";
        cin >> command;
        cin.ignore(); // 버퍼 비우기

        if (command == "exit") {
            break;
        }
        else if (command == "add") {
            string eng, kor;
            cout << "영어 단어: ";
            getline(cin, eng);
            cout << "한글 뜻: ";
            getline(cin, kor);
            dic.add(eng, kor);
        }
        else if (command == "load") {
            string filename;
            cout << "파일 이름: ";
            getline(cin, filename);
            dic.load(filename);
        }
        else if (command == "store") {
            string filename;
            cout << "파일 이름: ";
            getline(cin, filename);
            dic.store(filename);
        }
        else if (command == "print") {
            cout << "=== 현재 단어장 ===" << endl;
            dic.print();
        }
        else if (command == "get") {
            int id;
            cout << "조회할 단어 번호 (0부터 시작): ";
            cin >> id;
            cin.ignore();
            string eng = dic.getEng(id);
            string kor = dic.getKor(id);
            if (!eng.empty()) {
                cout << "영어: " << eng << ", 한글: " << kor << endl;
            } else {
                cout << "유효하지 않은 번호입니다." << endl;
            }
        }
        else {
            cout << "알 수 없는 명령어입니다." << endl;
        }
    }

    return 0;
}