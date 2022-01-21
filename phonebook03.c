#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3 /* 배열 재할당을 테스트하기 위해서 일부러 아주 작은 값으로*/
#define BUFFER_SIZE 50

char **names; /* char* 타입의 배열의 이름이므로 char** 타입의 변수이다*/
char **numbers;

int capacity = INIT_CAPACITY; /* size of arrays*/
int n = 0;                    /* number of people in phone directory */

/* function prototypes here */
char delim[] = " ";
int main()
{
    init_directory();  /*이 함수에서 배열 names와 numbers를 생성한다.*/
    process_command(); /* 사용자의 명령을 받아 처리하는 부분을 별개의 함수로 만들었다. */

    return 0;
}

void init_directory()
{
    names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
    numbers = (char **)malloc(INIT_CAPACITY * sizeof(char *));
}

int read_line(char str[], int limit)
{
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
    {
        if (i < limit - 1) /* 배열의 용량을 초과하지 않을 때만 저장한다. */
            str[i++] = ch;
    }
    
    str[i] = '\0'; /* 마지막에 null character를 추가해준다. */

    return i; /* 실제로 읽은 문자수를 반환한다. */
}