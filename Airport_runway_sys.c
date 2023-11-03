// ACTIVITY SELECTION MULTILAYER
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define size 20

struct node
{
    char name[size];
    int start;
    int finish;
    int srno;
    struct node *link;
} *head = NULL, *head1=NULL;


void copyList()
{
    struct node *temp = head, *newnode,*temp1;
    newnode = (struct node *)malloc(sizeof(struct node));

    head1=newnode;
    temp1=head1;
    strncpy(newnode->name, temp->name, strlen(temp->name));
    newnode->finish=temp->finish;
    newnode->srno=temp->srno;
    newnode->start=temp->start;

    while (temp->link != NULL)
    {
        newnode = (struct node *)malloc(sizeof(struct node));
        temp1->link=newnode;
        temp1 = temp1->link;
        temp=temp->link;
        
        strncpy(newnode->name, temp->name, strlen(temp->name));
        newnode->finish=temp->finish;
        newnode->srno=temp->srno;
        newnode->start=temp->start;

        newnode->link = NULL;
    }

}

void idx(struct node *hd)
{
    struct node *temp = hd;
    int i=1;
    while (temp != NULL)
    {
        temp->srno=i;
        i++;
        temp = temp->link;
    }
}

void insert(char naam[size], int s, int f)
{
    struct node *temp = head, *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));

    strncpy(newnode->name, naam, strlen(naam) - 1);
    newnode->start = s;
    newnode->finish = f;
    newnode->link = NULL;

    int key = f;
    if (head == NULL || key < head->finish)
    {
        newnode->link = head;
        head = newnode;
    }
    else
    {
        temp = head;
        while (temp->link != NULL && temp->link->finish < key)
        {
            temp = temp->link;
        }
        newnode->link = temp->link;
        temp->link = newnode;
    }
    idx(head);
    copyList();
}

void delete (int key,struct node *hd)
{
    struct node *temp = hd, *prev;
    if (temp != NULL && key==temp->srno)
    {
        hd = temp->link; 
        free(temp);        
        return;
    }

    while (temp != NULL && key!=temp->srno)
    {
        prev = temp;
        temp = temp->link;
    }


    if (temp == NULL)
    {
        return;
    }

    prev->link = temp->link;

    free(temp); 
    if (hd == head)
    {
        idx(hd);
        copyList();
    }
}

void display(struct node *hd)
{
    struct node *temp = hd;
    while (temp != NULL)
    {
        printf("\n%d\t%s\t%d\t%d\n", temp->srno, temp->name, temp->start, temp->finish);
        temp = temp->link;
    }
}


void deletep (int pos)
{
    struct node* temp = head1;

    int i;
    if (pos == 0) {
        head1 = head1->link; 

        temp->link = NULL;
        free(temp);
    }
    else {
        for (i = 0; i < pos - 1; i++) {
            temp = temp->link;
        }
        struct node* del = temp->link;

        temp->link = temp->link->link;
        del->link = NULL;
        free(del);
    }
}


int actselection(int i)
{
    struct node *temp = head1;
    if (temp == NULL)
    {
        return 0;
    }
    struct node *tmp=head1->link;
    int t=1,arr[size],k;

    
    printf("Selected Activities for Process '%d' are as follows :-\n",i);
    printf("\n%d\t%s\t%d\t%d\n", temp->srno, temp->name, temp->start, temp->finish);
    arr[0]=temp->srno;
    

    while (tmp != NULL)
    {
        if (temp->finish <= tmp->start)
        {
            printf("\n%d\t%s\t%d\t%d\n", tmp->srno, tmp->name, tmp->start, tmp->finish);
            arr[t]=tmp->srno;
            t++;
            temp=tmp;
            tmp=tmp->link;
        }
        else{
            tmp=tmp->link;
        }
    }
    for(k=0;k<t;k++) 
    {
        deletep(arr[k]-(k+1));
    }

    idx(head1);
    actselection(i+1);
    return 0;
}

int main()
{
    int c, s, f, key;
    char name[size], naam[size];

    printf("Welcome to Activity selection System\n\n");
    while (1)
    {
        printf("Choose from the following :-\n1. Insert the activity.\n2. Delete an Activity.\n3. Display all Activity.\n4. Display Best Activities to be selected.\n5. List Copied.\n6. Exit the system.");

        printf("\n\nEnter your choice :- ");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            printf("Enter the name of the Activity :- ");
            fflush(stdin);
            fgets(name, size, stdin);
            fflush(stdin);
            printf("Enter the Start time :- ");
            scanf("%d", &s);
            printf("Enter the Finish time :- ");
            scanf("%d", &f);

            insert(name, s, f);
            break;

        case 2:
            printf("Enter the index of the Activity to be Deleted :- ");
            scanf("%d",&key);

            delete (key,head);
            break;

        case 3:
            display(head);
            break;

        case 4:
            actselection(1);
            break;
        case 5:
            display(head1);
            break;
        case 6:
            printf("\n^_^ Thanks For using Our service ^_^ ");
            return 0;
        default:
            printf("Invalid Entry");
            break;
        }
    }
    return 0;
}