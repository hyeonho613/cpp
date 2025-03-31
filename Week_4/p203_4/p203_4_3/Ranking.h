#include <cstdio>  // C 스타일 입출력 함수(printf, scanf 등)를 사용하기 위한 헤더 (C++에서는 std 네임스페이스 내에 있음)

struct PlayInfo {            // 사용자 정의 자료형(구조체): 여러 자료형의 데이터를 하나로 묶어 관리하기 위해 사용
    char name[200];          // 200개의 char 배열, 주로 문자열 저장에 사용
    int nMove;               // 정수형 변수 (보통 4바이트, 시스템에 따라 다를 수 있음)
    double tElapsed;         // 실수형 변수 (보통 8바이트, 시스템에 따라 다를 수 있음)
};

extern void loadRanking(char* filename);  // 파일 이름(문자열)을 매개변수로 받아 랭킹 데이터를 로드하는 함수 (다른 파일에서 정의됨)
extern void storeRanking(char* filename); // 파일 이름(문자열)을 매개변수로 받아 랭킹 데이터를 저장하는 함수 (다른 파일에서 정의됨)
extern void printRanking();               // 랭킹 데이터를 출력하는 함수 (다른 파일에서 정의됨)
extern int addRanking(int nMove, double tElap); // 이동 횟수와 경과 시간을 매개변수로 받아 랭킹에 추가하는 함수 (다른 파일에서 정의됨)
