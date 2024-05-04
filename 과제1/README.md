### 메뉴얼

#### 1단계
##### https://www.sqlite.org/download.html 에 들어가서 sqlite-amalgamation, sqlite-dll-win-x64, sqlite-tools-win-x64 세가지 압축파일을 다운받고 한 폴더에 모두 풀어준다.

#### 2단계
##### Visual Studio를 실행시켜 새 프로젝트를 만들고, 상단의 [도구] -> [명령중] -> [개발자 명령 프롬프트]를 실행한다.

#### 3단계
##### 명령프롬프트를 압축풀었던 폴더로 경로를 잡아주고, lib /def:sqlite3.def /machine:x64 를 입력하여 lib(라이브러리)파일을 생성한다.

#### 4단계
##### 생성된 sqlite3.lib파일 및 sqlite3.h, sqlite3.dll 포함 세가지 파일과 sj.db 파일을 생성해두었던 프로젝트 폴더로 옮긴다.

#### 5단계
##### 소스코드 입력창에 SQLite3.cpp 파일의 내용을 입력하고, lib파일을 사용하기 위해 [프로젝트 속성] -> [구성 속성] -> [링커] -> [입력] -> [추가 종속성]에 sqlite3.lib를 추가한다.

#### 6단계
##### 실행한다.
