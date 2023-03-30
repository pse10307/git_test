#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#define NAME_SIZE 20

typedef struct BOOK {
char title[NAME_SIZE];
char author[NAME_SIZE];
char publisher[NAME_SIZE];
struct BOOK*link; 
}BOOK;

BOOK*createBook(void);
void start(BOOK**b1, BOOK**b2);
BOOK* initbook();
BOOK* insertbook(BOOK*b);
void print_book(BOOK * b);
void print_all_book(BOOK * b);
BOOK* deletebook(BOOK**b);
void search(BOOK ** b);

char list[NAME_SIZE];

BOOK* createBook(void)
{
    return (BOOK*)malloc(sizeof(struct BOOK));
}

void start(BOOK**b1, BOOK**b2)
{
    printf("대출, 반납, 검색, 추가, 삭제 중 무엇을 하시겠습니까?(종료하려면 0입력) "); 
    fgets(list, NAME_SIZE, stdin);

    while(1)
    {
        if(strcmp(list, "0")!=10)
        {
            if (strcmp(list, "대출")==10) 
                deletebook(b1);
            else if (strcmp(list, "반납")==10)
                insertbook(*b1);
            else if (strcmp(list, "검색")==10)
                search(b1);
            else if (strcmp(list, "추가")==10)
                insertbook(*b1);
            else if (strcmp(list, "삭제")==10)
                deletebook(b1);
            else 
                printf("잘못 입력했습니다. 다시 입력해주세요.\n");
            printf("대출, 반납, 검색, 추가, 삭제 중 무엇을 하시겠습니까?(종료하려면 0입력) "); 
            fgets(list, NAME_SIZE, stdin);
        }
        else break;
    }
}

BOOK* initbook(BOOK**b)
{
    printf("제목을 입력하세요: ");
    fgets((*b)->title, NAME_SIZE, stdin);
    (*b)->title[strlen((*b)->title) - 1] = '\0';

    printf("저자를 입력하세요: ");
    fgets((*b)->author, NAME_SIZE, stdin);
    (*b)->author[strlen((*b)->author) - 1] = '\0';

    printf("출판사를 입력하세요: ");
    fgets((*b)->publisher, NAME_SIZE, stdin);
    (*b)->publisher[strlen((*b)->publisher) - 1] = '\0';
    (*b)->link = NULL;
}


BOOK* insertbook(BOOK*b)
{
BOOK *p;
BOOK *temp=b;
p=createBook();
initbook(&p);
while(temp->link!=NULL)
{
    temp=temp->link;
    break;
}
temp->link=p;
}

void print_book(BOOK * b)
{
    printf("title=%s\nauthor=%s\npublisher=%s\n\n", b->title, b->author, b->publisher);
}

void print_all_book(BOOK * b)
{
    BOOK *temp=b;
    while (temp!=NULL) 
    {
    print_book(temp);
    temp=temp->link;
    }
}

BOOK* deletebook(BOOK**b)
{
    char name[NAME_SIZE];
    print_all_book(*b);
    printf("어떤 책을 대출(삭제) 하겠습니까?\n");
    fgets(name, NAME_SIZE, stdin);
    name[strlen(name) - 1] = '\0';

    BOOK*removed;
    BOOK*temp=*b;
    if(strncmp(name, temp->title, strlen(name))==0)
    {
        *b=temp->link; //b=&(temp->link)
        free(temp);
        return *b;
    }
    else
    {
        while(temp->link!=NULL)
        {
            if(strncmp(name, temp->link->title, strlen(name))==0)
                break;
            temp=temp->link;
        }
        if(temp->link == NULL)
            return NULL;
        removed=temp->link;
        temp->link=removed->link;
        free(removed);
    }
}

void search(BOOK**b) //저자, 출판사 검색 기능 추가
{
    char name[NAME_SIZE];
    printf("찾으려는 책의 제목을 입력하세요 : ");
    fgets(name, NAME_SIZE, stdin);
    name[strlen(name) - 1] = '\0';
    BOOK *temp=(*b);
    while (temp!=NULL)
    {
        if (strcmp(name, temp->title)==0)
            print_book(temp);
        temp=temp->link;
    }
}

int main(void) 
{
    BOOK*b1;
    b1=createBook();
    initbook(&b1);
    b1->link=NULL;

    BOOK*b2;
    b2=createBook();
    initbook(&b2);
    b2->link=NULL;
    b1->link=b2;

    start(&b1,&b2);
}