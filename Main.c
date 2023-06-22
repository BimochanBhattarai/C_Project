#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

void show_record();
void enter_record();
void space(int);
void head();
void vote();
void Candidates_Entry();
void list_candidates();
void give_vote(int);
void varification();
void result();

int *VoteCount;

struct Student
{
    int roll;
    char name[25];
    char mobile[10];
    struct dob
    {
        int year;
        int month;
        int day;
    } d;

} S, C;

int main()
{
    int choose_opt;
    head();
    do
    {
        printf("\n1. Show the list of the students.");
        printf("\n2. Enter new students.");
        printf("\n3. Start voting for Class Representative (CR).");
        printf("\n4. Exit");
        printf("\nEnter your choice by choosing number: ");
        scanf("%d", &choose_opt);
        switch (choose_opt)
        {
        case 1:
            show_record();
            break;
        case 2:
            enter_record();
            break;
        case 3:
            vote();
            break;
        case 4:
            printf("\nTerminating Program...\n");
            break;
        default:
            system("cls");
            printf("\nYou entered wrong value!!\n");
            printf("Please enter the valid value (1, 2, 3 or 4)\n");
            break;
        }
    } while (choose_opt != 4);

    return 0;
}

void enter_record()
{
    system("cls");
    char check = 'N';
    do
    {
        here:
        head();
        printf("\tData Entry Form.\n");
        printf("The roll number should be unique.\n");
        printf("\nRoll no: ");
        scanf("%d", &S.roll);
        printf("Name: ");
        scanf(" %[^\n]s", S.name);
        printf("Mobile: ");
        scanf(" %s", S.mobile);
        printf("Birth year: ");
        scanf("%d", &S.d.year);
        printf("Birth month: ");
        scanf("%d", &S.d.month);
        printf("Birth date: ");
        scanf("%d", &S.d.day);
        FILE *Stu;
        Stu = fopen("Record.txt","r");
        while ((fread(&C,sizeof(C),1,Stu))==1);
        {
            if(S.roll==C.roll)
            {
                system("cls");
                printf("\nYou cannot have two students of same Roll number.");
                printf("\nEnter the data again.\n");
                goto here;

            }
        }
        fclose(Stu);
        if (strlen(S.mobile) != 10)
        {
            system("cls");
            printf("The mobile number should be of 10 digits.\n");
            goto here;
        }
        FILE *Enter;
        Enter = fopen("Record.txt", "a");
        fwrite(&S, sizeof(S), 1, Enter);
        fclose(Enter);
        printf("\nYour data sucessfully entered...");
        printf("\nDo you want to enter more data?");
        printf("\nEnter 'Y' if yes and 'N' if no.\n");
        scanf(" %c", &check);
    } while (check == 'Y' || check == 'y');
}

void show_record()
{
    system("cls");
    head();
    printf("\t\t  RECORD LIST\n");
    printf("Roll No.\tName\t\t\tMobile");
    FILE *Stu;
    Stu = fopen("Record.txt", "r");
    while (fread(&C, sizeof(C), 1, Stu) == 1)
    {
        printf("\n%02d", C.roll);
        printf("\t\t%s", C.name);
        space(strlen(C.name));
        printf("%s", C.mobile);
    }
    printf("\n\n\n\n\n");
    fclose(Stu);
}

void space(int length)
{
    for (int i = 1; i < 25 - length; i++)
    {
        printf(" ");
    }
}

void head()
{
    printf("\tKATHFORD INTERNATIONAL COLLEGE");
    printf("\n\t\tFirst Semester\n");
}

void Candidates_Entry()
{
    system("cls");
    int num_candidates, count;
    char option;
    int ID, roll;
    FILE *Cand, *Record;
    show_record();
    here:
    printf("\n\nAre the candidates on the list above?\n");
    printf("\nIf yes, enter 'Y' to select them.");
    printf("\nIf no, enter 'N' to enter their name.\n");
    scanf(" %c",&option);
    if(option=='Y'||option=='y')
    {
        printf("\nEnter the number of candidates: ");
        scanf("%d",&num_candidates);
        
        for (int i = 0; i < num_candidates; i++)
        {
            there:
            printf("\nEnter the roll number of %d candidate: ",i+1);
            scanf("%d",&ID);
            count = 0;
            Cand = fopen("Candidates.txt","a+");
            while ((fread(&roll,sizeof(roll),1,Cand))==1)
            {
                if (roll == ID)
                {
                    printf("\nYou cannot enter same id again.");
                    goto there;
                }
            }
            Record = fopen("Record.txt","r");
            rewind(Record);
            while ((fread(&C,sizeof(C),1,Record))==1)
            {
            
                if (C.roll == ID)
                {
                    count++;
                }
            
            }
            if(count==0)
            {
                printf("\nThe student is not in the list!");
                printf("\nPlease enter again.");
                goto there;
            }
            fclose(Record);
            fwrite(&ID,sizeof(ID),1,Cand);
            fclose(Cand);
        
        }
    printf("The candidates are selected.");
    getch();
    }
    else if(option=='N'||option=='n')
    {
        enter_record();
    }
    else
    {
        printf("\nYou entered invalid value.");
        printf("\nEnter the value again.");
        goto here;
    }
    
}

void vote()
{
    system("cls");
    head();
    int select;
    this:
    printf("\n1. List of the candidates.");
    printf("\n2. Enter the candidates.");
    printf("\n3. Give vote.");
    // printf("%n4. Result.");
    printf("\nSelect the option using their number.(1 or 2)\n");
    scanf("%d",&select);
    if (select==1)
    {
        list_candidates();
    }
    else if(select == 2)
    {
        Candidates_Entry();
    }
    else if (select == 3)
    {
        varification();
    }
    // else if (select == 4)
    // {
    //     result();
    // }
    else
    {
        printf("You choose wrong option, please choose again.");
        goto this;
    }

}

void list_candidates()
{
    system("cls");
    head();
    char a;
    int ch;
    FILE *Cand, *Record;
    Cand = fopen("Candidates.txt","r");
    Record = fopen("Record.txt","r");
    if (fgetc(Cand)!=EOF)
    {
        rewind(Cand);
        printf("The list of candidates for Class Representative are: \n\n");
        printf("Roll No.\tName\t\t\tMobile");
        while ((fread(&ch,sizeof(ch),1,Cand))==1)
        {
            rewind(Record);
            while ((fread(&C,sizeof(C),1,Record))==1)
            {
                if (ch==C.roll)
                {
                    printf("\n%02d", C.roll);
                    printf("\t\t%s", C.name);
                    space(strlen(C.name));
                    printf("%s", C.mobile);
                    
                }
                
            }
            
        }
        
    }
    else
    {
        printf("The list is empty.\n\n\n\n");
        fclose(Cand);
        fclose(Record);
        return;
    }
    fclose(Cand);
    fclose(Record);
    FILE *ptr;
    printf("\nIf you want to clear the list, enter 'Y' if yes, and any other to continue.");
    scanf(" %c",&a);
    if(a == 'Y' || a == 'y')
    {
        remove("Candidates.txt");
        ptr = fopen("Apple.txt","w");
        fclose(ptr);
        rename("Apple.txt","Candidates.txt");
    }
    printf("\n\n\n");
}

void give_vote(int ID)
{
    system("cls");
    head();
    // for (int i = 1; i <= 5; i++)
    // {
    //     *(VoteCount+i) = 0;
    // }
    
    int vote;
    FILE *ptr = fopen("Record.txt","r");
    while ((fread(&C,sizeof(C),1,ptr))==1)
    {
        if (ID == C.roll)
        {
            printf("\nYou are eligeable to vote %s, use your vote wisely.\n\n\n",C.name);
        }    
    }
    fclose(ptr);
    int ch, num = 1, index = 1;
    FILE *Cand, *Record;
    Cand = fopen("Candidates.txt","r");
    Record = fopen("Record.txt","r");
    rewind(Cand);
    printf("Enter the number that appears in front to vote to the person.\n");
    printf("Names:\n\n");
    while ((fread(&ch,sizeof(ch),1,Cand))==1)
    {
        rewind(Record);
        while ((fread(&C,sizeof(C),1,Record))==1)
        {
            if (ch==C.roll)
            {
                printf("%d. %s\n",num, C.name);
                num++; 
            }
                
        }
            
    }
    printf("Enter your vote: ");
    scanf("%d",&vote);

    rewind(Cand);
    while ((fread(&ch,sizeof(ch),1,Cand))==1)
    {
        if(index==vote)
        {
            *(VoteCount+vote) = *(VoteCount+vote) + 1;
        }
        index++;
    }
    
}

void varification()
{
    system("cls");
    int ID,count;
    head();
    printf("\nWell come to voting system.");
    printf("\n\nPlease enter your roll no: ");
    scanf("%d",&ID);
    FILE *ptr = fopen("Record.txt","r");
    count = 0;
    while ((fread(&C,sizeof(C),1,ptr))==1)
    {
    
        if (C.roll == ID)
        {
            count++;
        }
            
    }
    if(count != 0)
    {
        give_vote(ID);
                
    }
    else
    {
        printf("Sorry, You are not reegistered so you cannot vote.\n\n\n");
    }
}

void result()
{
    int ch, num = 1, index = 1;
    FILE *Cand, *Record;
    Cand = fopen("Candidates.txt","r");
    Record = fopen("Record.txt","r");
    rewind(Cand);
    printf("Enter the number that appears in front to vote to the person.\n");
    printf("Names:\n\n");
    while ((fread(&ch,sizeof(ch),1,Cand))==1)
    {
        rewind(Record);
        while ((fread(&C,sizeof(C),1,Record))==1)
        {
            if (ch==C.roll)
            {
                printf("%s(%d) got %d votes.\n",C.name,C.roll,*(VoteCount+num));
                num++; 
            }
                
        }
            
    }   
}