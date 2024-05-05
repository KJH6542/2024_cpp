#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <string>

using namespace std;

// 총점과 평균을 저장하는 구조체
struct StudentStats {
    string name;
    int koreanScore = 0;
    int englishScore = 0;
    int totalScore = 0;
    double averageScore = 0;
};

// SQLite3 쿼리 콜백 함수
int callback(void* data, int argc, char** argv, char** azColName) {
    vector<StudentStats>* stats = static_cast<vector<StudentStats>*>(data);

    // 각 학생의 이름과 성적 정보를 구조체에 저장
    StudentStats studentStats;
    studentStats.name = argv[1];
    int koreanScore = stoi(argv[2]);
    int englishScore = stoi(argv[3]);
    studentStats.koreanScore = koreanScore;
    studentStats.englishScore = englishScore;
    studentStats.totalScore = koreanScore + englishScore;
    studentStats.averageScore = static_cast<double>(studentStats.totalScore) / 2.0;

    stats->push_back(studentStats);

    return 0;
}

int main() {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // 데이터베이스 연결
    rc = sqlite3_open("sj.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string sql = "SELECT * FROM student;";

    vector<StudentStats> studentStatsList;

    // 쿼리 실행
    rc = sqlite3_exec(db, sql.c_str(), callback, &studentStatsList, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }
    else {
        cout << "학생별 총점 및 평균" << endl;
        cout << "-------------------------" << endl;
        for (size_t i = 0; i < studentStatsList.size(); i++) {
            cout << "학생 이름: " << studentStatsList[i].name << endl;
            cout << "총점: " << studentStatsList[i].totalScore << endl;
            cout << "평균: " << studentStatsList[i].averageScore << endl;
            cout << "-------------------------" << endl;
        }

        int koreantotalScore = 0;
        int englishtotalScore = 0;
        for (size_t i = 0; i < studentStatsList.size(); i++) {
            koreantotalScore += studentStatsList[i].koreanScore;
            englishtotalScore += studentStatsList[i].englishScore;
        }

        double koreanaverageScore = static_cast<double>(koreantotalScore) / studentStatsList.size();
        double englishaverageScore = static_cast<double>(englishtotalScore) / studentStatsList.size();
        cout << endl;
        cout << "과목별 총점 및 평균" << endl;
        cout << "-------------------------" << endl;
        cout << "국어 총점: " << koreantotalScore << endl;
        cout << "국어 평균: " << koreanaverageScore << endl;
        cout << "-------------------------" << endl;
        cout << "영어 총점: " << englishtotalScore << endl;
        cout << "영어 평균: " << englishaverageScore << endl;
        cout << "-------------------------" << endl;
    }

    // 데이터베이스 연결 해제
    sqlite3_close(db);

    return 0;
}
