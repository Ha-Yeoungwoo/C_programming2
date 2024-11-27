#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>


// 콜백 함수: 조회 결과를 출력합니다.
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // 데이터베이스 연결
    rc = sqlite3_open("user_info.db", &db);
    if (rc) {
        fprintf(stderr, "데이터베이스 열기 실패: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    //// 사용자 정보 테이블 생성
    //const char* sql_create = "CREATE TABLE IF NOT EXISTS Users ("
    //    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
    //    "Name TEXT NOT NULL,"
    //    "Password TEXT NOT NULL);";

    //rc = sqlite3_exec(db, sql_create, 0, 0, &errMsg);
    //if (rc != SQLITE_OK) {
    //    fprintf(stderr, "SQL 오류: %s\n", errMsg);
    //    sqlite3_free(errMsg);
    //}
    //else {
    //    printf("사용자 정보 테이블이 성공적으로 생성되었습니다.\n");
    //}

    // 사용자 정보 입력 및 저장
    char name[100], password[100];
    printf("사용자 이름을 입력하세요: ");
    scanf("%99s", name);
    printf("비밀번호를 입력하세요: ");
    scanf("%99s", password);

    char sql_insert[300];
    snprintf(sql_insert, sizeof(sql_insert),
        "INSERT INTO Users (Name, Password) VALUES ('%s', '%s');",
        name, password);

    rc = sqlite3_exec(db, sql_insert, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL 오류: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
    else {
        printf("사용자 정보가 성공적으로 저장되었습니다.\n");
    }

    // 저장된 모든 사용자 정보 조회
    const char* sql_select = "SELECT * FROM Users;";
    printf("\n저장된 모든 사용자 정보:\n");
    rc = sqlite3_exec(db, sql_select, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL 오류: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // 데이터베이스 연결 종료
    sqlite3_close(db);
    return 0;
}