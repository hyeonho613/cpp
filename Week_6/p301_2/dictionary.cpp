#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <sstream>

void MyDic::add(string eng, string kor) {
    // 중복 체크
    for (int i = 0; i < nWords; i++) {
        if (words[i].eng == eng) {
            cout << "중복된 단어입니다: " << eng << endl;
            return;
        }
    }

    // 단어 추가
    if (nWords < MAXWORDS) {
        words[nWords].eng = eng;
        words[nWords].kor = kor;
        nWords++;
        cout << "단어 추가 완료!" << endl;
    } else {
        cout << "단어장 용량이 가득 찼습니다!" << endl;
    }
}

void MyDic::load(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    nWords = 0;
    string line;
    while (getline(file, line) && nWords < MAXWORDS) {
        if (line.empty()) continue; // 빈 줄 무시
        stringstream ss(line);
        string eng, kor;
        if (ss >> eng) {
            getline(ss >> ws, kor); // 공백 이후 나머지 문자열을 kor로
            if (!eng.empty() && !kor.empty()) {
                // 중복 체크
                bool isDuplicate = false;
                for (int i = 0; i < nWords; i++) {
                    if (words[i].eng == eng) {
                        isDuplicate = true;
                        break;
                    }
                }
                if (!isDuplicate) {
                    words[nWords].eng = eng;
                    words[nWords].kor = kor;
                    nWords++;
                }
            }
        }
    }
    file.close();
    cout << "=== 로드된 단어장 ===" << endl;
    print();
}

void MyDic::store(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "파일을 저장할 수 없습니다: " << filename << endl;
        return;
    }

    for (int i = 0; i < nWords; i++) {
        file << words[i].eng << " " << words[i].kor << endl;
    }
    file.close();
    cout << "파일 저장 완료: " << filename << endl;
}

void MyDic::print() {
    if (nWords == 0) {
        cout << "단어장이 비어있습니다." << endl;
        return;
    }
    for (int i = 0; i < nWords; i++) {
        cout << (i + 1) << ". " << words[i].eng << " : " << words[i].kor << endl;
    }
}

string MyDic::getEng(int id) {
    if (id >= 0 && id < nWords) {
        return words[id].eng;
    }
    return "";
}

string MyDic::getKor(int id) {
    if (id >= 0 && id < nWords) {
        return words[id].kor;
    }
    return "";
}