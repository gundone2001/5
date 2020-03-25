#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Item
{
    char c;
    struct Item *next;
}Item;

int getList(Item **);//reads a line
void putList(Item *);// put a line
Item *deleteList(Item *);// delete a line
Item skipSpace(Item **);// skip spaces
int strspnitem(Item *, char *);// counts the number of consecutive characters
Item copyWord(Item **, Item **, int );// copy N chars 
Item reorg(Item *, Item **,Item **);// create two lines 
Item plusprobel(Item **p)//add ' ' to end of line  

Item *deleteList(Item *ptr)// delete a line
{
    Item *tmp = NULL;
    while (ptr != NULL)
    {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}

int getList(Item **pptr)//reads a line
{
    char buf[81], *str;
    Item head = {'*', NULL};
    Item *last = &head;
    int n, rc = 1;
    do
    {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            deleteList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if (n > 0)
        {
            for (str = buf; *str != '\0'; ++str)
            {
                last->next = (Item *)malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        }
        else
            scanf("%*c");
    } while (n > 0);
    *pptr = head.next;
    return rc;
}

Item skipSpace(Item **p)// skip spaces
{
    if(*p!=NULL)
    {
    while ((*p)->c == ' ' || (*p)->c == '\t')
    {  
       if((*p)->next!=NULL)
       {
       (*p) = (*p)->next;
       }
       else 
       {
           break;
       }
    }
    }
}
Item plusprobel(Item **p)//add ' ' to end of line 
{

    (*p)->next = (Item *)malloc(sizeof(Item));
    (*p) = (*p)->next;
    (*p)->c = ' ';
}
int strspnitem(Item *p, char *a)// counts the number of consecutive characters
{
    int i = 0;
    // puts(a);
    while (p != NULL)
    {
        if ((*p).c == *a)
            i++;
        else
            break;
        p = p->next;
        //puts("!@!");
    }
    //printf(" Chislo: %d\n", i);
    return i;
}

Item copyWord(Item **from, Item **to, int k)// copy N chars 
{
    char a[1];
    while (k > 0)
    {
        (*to)->next = (Item *)malloc(sizeof(Item));
        (*to) = (*to)->next;
        (*to)->c = (*from)->c;
        (*from) = (*from)->next;
        k--;
    }
}

void putList(Item *ptr)// put a line
{
    printf("\"");
    for (; ptr != NULL; ptr = ptr->next)
        printf("%c", ptr->c);
    printf("\"");
    printf("\n");
}

Item reorg(Item *s, Item **one,Item **two)// create two lines 
{
    int flag = 0, flag1 = 0, nacalo = 1;
    Item headone = {'*', NULL};
    Item *lastone = &headone;
    Item headtwo = {'*', NULL};
    Item *lasttwo = &headtwo;
    char a[1];
    while (s != NULL)
    {
        skipSpace(&s);
        a[0] = s->c;
        if(a[0]==' ' || a[0]=='\t')
        {
            s=s->next;
            continue;
        }
        if (strspnitem(s, a) != 1)
        {
            if (flag != 0)
            {
                plusprobel(&lastone);
            }
            flag = 1;
            flag1 = 1;
            copyWord(&s, &lastone, strspnitem(s, a));
        }
        else
        {
            if (nacalo == 0)
            {
                if (flag1 == 1)
                {
                    plusprobel(&lasttwo);
                }
            }
            nacalo = 0;
            flag1 = 0;
            copyWord(&s, &lasttwo, 1);
            //puts("!");
            if(s!=NULL)
            {
            if (s->c == ' ' ||  s->c == '\t')
            {
                flag1 = 1;
            }
            }
        }  
    }
    lastone->next = NULL;
    lasttwo->next = NULL;
    *one = headone.next;
    *two = headtwo.next;
}

int main()
{
    Item *s;
    Item *one, *two;
    while (puts("ENTER string:"), getList(&s))
    {
        reorg(s,&one,&two);
        puts("Result string:");
        putList(one);
        puts("Result string:");
        putList(two);
        s = deleteList(s);
        one = deleteList(one);
        two = deleteList(two);
    }

    return 0;
}