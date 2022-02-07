#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITIY 100
#define BUFFER_LENGTH 100

// 구조체 struct person을 정의하면서
// 동시에 그것을 Person으로 renaming했다
// 이런 식으로 사용할 경우 struct tag인 person을 생략해도 좋다
typedef struct person {
    char *name;
    char *number;
    char *email;
    char *group;
} Person;

// Person 타입의 배열directory를 선언한다
Person directory[CAPACITIY];

int n = 0; /* number of people in phone directory */

int read_line(FILE * fp, char str[], int n) {
    
    int ch , i = 0;

    while((ch = fgetc(fp)) != '\n' && ch != EOF){
        if (i<n){
            str[i++] = ch;
        }
    }

    str[i] = '\0';
    return i;
}

void load(char *fileName) {
    char buffer[BUFFER_LENGTH];
    char *name, *number, *email, *group;

    FILE *fp = fopen(fileName,"r");
    if(fp == NULL) {
        printf("Open failed.\n");
        return;
    }

    while(1) {
        if (read_line(fp,buffer,BUFFER_LENGTH)<=0){
            break;
        }
        name = strtok(buffer,"#");
        number = strtok(NULL,"#");
        email = strtok(NULL,"#");
        group = strtok(NULL,"#");
        add(name,number,email,group);
    }
    fclose(fp);
}

void add(char *name,char *number,char *email, char *group) {
    
    int i = n-1;
    while (i>=0 && strcmp(directory[i].name,name) > 0) {
        directory[i+1] = directory[i];
        i--;
    }
    directory[i].name = strdup(name);
    directory[i].number = strdup(number);
    directory[i].email = strdup(email);
    directory[i].group = strdup(group);

    n++;
}

int compose_name(char str[], int limit) {
    char * ptr;
    int length = 0;

    ptr = strtok(NULL, " ");
    if (ptr == NULL)
        return 0;
    strcpy(str,ptr);
    length += strlen(ptr);

    while((ptr = strtok(NULL, " ")) != NULL) {
        if (length + strlen(ptr) + 1 < limit) {
            str[length++] = ' ';
            str[length] = '\0';
            strcat(str,ptr);
            length += strlen(ptr);
        }
    }
    return length;
}

int main() {
    char command_line[BUFFER_LENGTH];
    char *command, *argument;
    char name_str[BUFFER_LENGTH];

    while(1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0){
            continue;
        }
        command = strtok(command_line, " ");

        if(strcmp(command, "read") == 0) {
            argument = strtok(NULL, " ");
            if(argument == NULL) {
                printf("Invalid arguments. \n");
                continue;
            }
            load(argument);
        }
        else if (strcmp(command,"add") == 0) {
            if (compose_name(name_str,BUFFER_LENGTH) <= 0) {
                printf("Name required.\n");
                continue;
            }
            handle_add(name_str);
        }
        else if (strcmp(command,"find") == 0) {
            if (compose_name(name_str,BUFFER_LENGTH) <= 0) {
                printf("Name required.\n");
                continue;
            }
            find(name_str);
        }
        else if (strcmp(command,"status") == 0) {
            status();
        }
        else if (strcmp(command,"delete") == 0) {
            if (compose_name(name_str,BUFFER_LENGTH) <= 0){
                printf("Invalid arguments.\n");
                continue;
            }
            remove(name_str);
        }
        
    }
}