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
void init_directory();
void process_command();
void load(char *fileName);
void add(char *name,char *number);
void status();
void find(char *name);
int search(char *name);
void remove(char* name);
void save(char *fileName);
void reallocate();


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

void process_command(){
    char command_line[BUFFER_SIZE]; /* 한 라인을 통채로 읽어오기 위한 버퍼*/
    char *command, *argument1, *argument2;

    while(1){
        printf("$ ");

        if(read_line(command_line,BUFFER_SIZE)<=0) /* 명령줄을 통채로 읽는다 */
            continue;                              /* 아무것도 입력안하면 continue(while문의 시작으로 돌아감) */
        
        command = strtok(command_line,delim);  /* 첫 번째 토큰은 명령어이다 */
        if(command == NULL) continue;
        
        if(strcmp(command, "read") == 0){
            argument1 = strtok(NULL,delim); /* read명령에서 두번째 토큰은 파일명이다 */
            if(argument1 == NULL){
                printf("File name required.\n");
                continue;
            }
            load(argument1); /* 파일명을 인자로 주면서 load를 호출한다 */
        }
        else if(strcmp(command, "add") == 0){
            argument1 = strtok(NULL,delim);
            argument2 = strtok(NULL,delim);

            if(argument1 == NULL || argument2 == NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            add(argument1,argument2);
            printf("%s was added successfully.\n", argument1);
        }
        else if(strcmp(command,"find") == 0){
            argument1 = strtok(NULL, delim);
            if(argument1 == NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            find(argument1);
        }
        else if(strcmp(command, "status") == 0) 
            status();
        else if(strcmp(command,"delete")==0){
            argument1 = strtok(NULL,delim);
            if(argument1 == NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            remove(argument1);
        }
        else if(strcmp(command,"save")==0){
            argument1 = strtok(NULL,delim);
            argument2 = strtok(NULL,delim);

            if(argument1 == NULL || strcmp("as",argument1) != 0 || argument2 == NULL){
                printf("Invalid command format.\n");
                continue;
            }
            save(argument2);
        }
        else if(strcmp(command,"exit") == 0)
            break;
    }
}

void load(char *fileName){
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    FILE *fp = fopen(fileName,"r");
    if(fp==NULL){
        printf("Open failed.\n");
        return;
    }
    while((fscanf(fp,"s",buf1)!=EOF)){
        fscanf(fp,"%s",buf2);
        add(buf1,buf2);
    }
    fclose(fp);
}

void add(char *name,char *number){
    if(n>=capacity)
        reallocate();
    int i=n-1;
    while(i>=0 && strcmp(names[i],name)>0){
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }
    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);

    n++;
}

void status(){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s\n", names[i],numbers[i]);
    }
    printf("Total %d persons.\n", n);
}

void find(char *name){
    int index = search(name);
    if(index == -1)
        printf("No person named '%s' exist.\n", name);
    else 
        printf("%s\n", numbers[index]);
}

int search(char *name){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(name,names[i])==0){
            return i;
        }
    }
    return -1;
}

void remove(char *name){
    
    int i = search(name);
    if( i == -1){
        printf("No person named '%s' exist", name);
        return;
    }

    int j = i;
    for(; j<n-1; j++){
        names[j] = names[j+1];
        numbers[j] = numbers[j+1]; 
    }

    n--;
    printf("'%s' was deleted successfully.\n", name);
}

void save(char *fileName){
    int i;
    FILE *fp = fopen(fileName,"w");
    if(fp==NULL){
        printf("Open failed.\n");
        return;
    }

    for(i=0;i<n;i++){
        fprintf(fp, "%s %s\n",names[i],numbers[i]);
    }
    fclose(fp);
}

void reallocate(){
    
    int i;

    capacity *= 2;
    char **tmp1 = (char **)malloc(capacity*sizeof(char *));
    char **tmp2 = (char **)malloc(capacity*sizeof(char *));

    for (i=0;i<n;i++){
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }

    free(names);
    free(numbers);

    names = tmp1;
    numbers = tmp2;
}