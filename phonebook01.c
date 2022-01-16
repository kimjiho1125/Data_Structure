#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];   /* names */
char *numbers[CAPACITY]; /* phone numbers */
int n = 0;               /* number of people in phone directory*/

void add();
void find();
void status();
void remove1();

int main()
{
    char command[BUFFER_SIZE];
    while (1)
    {
        printf("$ ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0)
        {
            add();
        }
        else if (strcmp(command, "find") == 0)
        {
            find();
        }
        else if (strcmp(command, "status") == 0)
        {
            status();
        }
        else if (strcmp(command, "delete") == 0)
        {
            remove1();
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        return 0;
    }
}

void add()
{
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    scanf("%s", buf1);
    scanf("%s", buf2);

    names[n] = strdup(buf1); 
    numbers[n] = strdup(buf2);

    printf("$s was added successfully.\n", buf1);
}
void find(){
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int i;
    for(i=0;i<n;i++){
        if (strcmp(buf, names[i]) == 0)
        {
            printf("%s\n", numbers[i]);
            return;
        }
    }
    printf("No person named '%s' exist.\n",buf);
}

void status(){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s\n", names[i],numbers[i]);
    }
    printf("Total %d persons.\n",n);
}

void remove1(){
    char buf[BUFFER_SIZE];
    scanf("%s", buf);

    int i;
    for(i=0;i<n;i++){
        if(strcmp(buf,names[i])==0){
            names[i] = names[n-1];
            numbers[i] = numbers[n-1];
            n--;
            printf("'%s' was deleted successfully. \n", buf);
            return;
        }
    }
    printf("No person named '%s' exist. \n",buf);
}