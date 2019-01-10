#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include"GetStations.h"
typedef struct Time
{
    int hour;
    int min;
}Time;
typedef struct DB
{
    int count;
    struct train *start;
}database;
typedef struct train
{
    //FILE*fp;
    struct train *next;
    struct station *start;
    char tNo[6];
    char tName[40];
    int NOS;
    int dist;
    char week[8];
    Time late;
}train;
typedef struct station
{
    struct station *next;
    short sNo;//nth station from source
    char sName[30];
    char sCode[6];
    Time arr;
    Time dep;
    int dist;//distance from source
}station;
database*initDB()
{
    database*h=(database*)malloc(sizeof(database));
    h->start=NULL;
    h->count=0;
    return h;
}
train*initTrain()
{
    train * t=(train*)malloc(sizeof(train));
    t->next=NULL;
    //t->fp=NULL;
    t->dist=0;
    t->NOS=0;
    strcpy(t->tNo,"\0");
    strcpy(t->tName,"\0");
    t->start=NULL;
    strcpy(t->week,"0000000\0");
    return t;
}
station *createStationNode()
{
    station*s=(station*)malloc(sizeof(station));
    s->next=NULL;
    s->arr.hour=0;
    s->arr.min=0;
    s->dep.hour=0;
    s->dep.min=0;
    s->dist=0;
    strcpy(s->sCode,"\0");
    s->sNo=0;
    strcpy(s->sName,"\0");
    return s;
}
train*loadTrain(train*t,char tempNo[])
{
    char tFile[17]="Trains/";
    strcpy(t->tNo,tempNo);
    strcat(tFile,tempNo);
    strcat(tFile,".txt");
    FILE*fp=fopen(tFile,"r");
    fscanf(fp,"%s",t->tName);
    fscanf(fp,"%d",&(t->NOS));
    fscanf(fp,"%s",t->week);
    station *currs,*s;
    while(!feof(fp))
    {
        s=createStationNode();
        fscanf(fp,"%d",&(s->sNo));
        fscanf(fp,"%s",s->sCode);
        fscanf(fp,"%s",s->sName);
        fscanf(fp,"%d",&(s->arr.hour));
        char c;
        fscanf(fp,"%c",&c);
        fscanf(fp,"%d",&(s->arr.min));
        fscanf(fp,"%d",&(s->dep.hour));
        fscanf(fp,"%c",&c);
        fscanf(fp,"%d",&(s->dep.min));
        fscanf(fp,"%d",&(s->dist));
        if(t->start==NULL)
        {
            t->start=s;
            currs=s;
        }
        else
        {
            currs->next=s;
            currs=s;
        }
    }
    fclose(fp);
    return t;
}
database*loadDB(database*h)
{
    FILE*TNOS=fopen("TrainNos.txt","r");
    char tempNo[10];
    train*currt,*t;
    while(!feof(TNOS))
    {
        fscanf(TNOS,"%s",tempNo);
        t=initTrain();
        t=loadTrain(t,tempNo);
        if(h->start==NULL)
        {
            h->start=t;
            currt=t;
        }
        else
        {
            currt->next=t;
            currt=t;
        }
    }
    return h;
}
Time getCurrentTime()
{
    time_t t;
    Time currentTime;
    time(&t);
    char c[20];
    strcpy(c,ctime(&t));
    currentTime.hour=(c[11]-48)*10+(c[12]-48);
    currentTime.min=(c[14]-48)*10+(c[15]-48);
    return currentTime;
}
void display(database *h)
{
    train *t=h->start;
    while(t!=NULL)
    {
        printf("Train info :\n%s %s\nNo of stations-%d\n\n",t->tName,t->tNo,t->NOS);
        station*s=t->start;
        while(s!=NULL)
        {
            printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
            printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
            printf("Dist-%4d|\n",s->dist);
            //printf("------------------------------------------------------------------\n");
            s=s->next;
        }
        t=t->next;
        printf("\n\n\n");
    }
}
void displayTrain(database *h)
{
    GT:printf("\nChoose the train to see schedule :\n\n");
    Sleep(600);
    printTrains(h);
    char tr[6];
    printf("->");
    scanf("%s",tr);
    train *t=h->start;
    int i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tr)==0)
        {
            i=1;
            break;
        }
        t=t->next;
    }
    if(i==0)
    {
        printf("\nNo such train. Please Re-enter your choice.\n");
        goto GT;
    }
    printf("Train info :\n%s %s\nNo of stations-%d\n\n",t->tName,t->tNo,t->NOS);
    station*s=t->start;
    while(s!=NULL)
    {
        printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
        printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
        printf("Dist-%4d|\n",s->dist);
        //printf("------------------------------------------------------------------\n");
        s=s->next;
    }
    printf("\n\n\n");
}
int timeComp(Time t1,Time t2)
{
    int a=t1.hour*60+t1.min;
    int b=t2.hour*60+t2.min;
    if(a>b)
        return 1;
    else if(a<b)
        return -1;
    else
        return 0;
}
Time timeDifference(Time t1,Time t2)//t1 is larger
{
    Time d;
    if(t1.hour==t2.hour)
    {
        d.hour=0;
        d.min=t1.min-t2.min;
        return d;
    }
    else if(t1.min>=t2.min)
    {
        d.min=t1.min-t2.min;
        d.hour=t1.hour-t2.hour;
        return d;
    }
    else
    {
        d.hour=t1.hour-t2.hour-1;
        d.min=60-(t2.min-t1.min);
        return d;
    }
}
void spotTrain(database *h)
{
    printf("Choose the train number :\n\n");
    Sleep(500);
    printTrains(h);
    char a[6];
    printf("\n->");
    scanf("%s",a);
    train *t=h->start;
    while(strcmp(t->tNo,a)!=0)
        t=t->next;
    station *s=t->start,*s2;
    s2=s->next;
    Time currentTime=getCurrentTime();
    int i=0;
    while(s2!=NULL)
    {
        if(timeComp(currentTime,t->start->arr)==1&&timeComp(currentTime,t->start->dep)==-1)
        {
            printf("\nThe train is yet to start from source.\n");
            i=1;
            break;
        }
        else if(timeComp(s->dep,currentTime)==-1&&timeComp(s->next->arr,currentTime)==1)
        {
            Time diff=timeDifference(currentTime,s->dep);
            printf("\nThe train is between %s and %s.\nThe train departed %s %02d:%02d ago.\n",s->sName,s->next->sName,s->sName,diff.hour,diff.min);
            i=1;
            break;
        }
        else if(timeComp(s->arr,currentTime)==-1&&timeComp(s->dep,currentTime)==1)
        {
            printf("\nThe train is at %s.\n",s->sName);
            i=1;
            break;
        }
        else if(timeComp(s2->arr,currentTime)==-1&&timeComp(s2->dep,currentTime)==1)
        {
            printf("\nThe train is at %s.\n",s2->sName);
            i=1;
            break;
        }
         else if(timeComp(s->arr,currentTime)==0||timeComp(s->dep,currentTime)==0)
        {
            printf("\nThe train is at %s.\n",s->sName);
            i=1;
            break;
        }
        else if(timeComp(s2->arr,currentTime)==0||timeComp(s2->dep,currentTime)==0)
        {
            printf("\nThe train is at %s.\n",s2->sName);
            i=1;
            break;
        }
        s=s->next;
        s2=s->next;
    }
    if(i==0)
        printf("\nThe train is yet to start from source.\n");
}
void printTrains(database*h)
{
    train*t=h->start;
    while(t!=NULL)
    {
        printf("%25s %s\n",t->tName,t->tNo);
        t=t->next;
    }
}
void liveStation(database*h)
{
    printf("Choose the station and enter the Station code:\n\n");
    //display all stations here
    printf("->");
    char a[5],c[6];
    scanf("%s",a);
    printf("\nEnter the time for which you want to see live status(in HH:MM format):\n->");
    scanf("%s",c);
    Time b,ct;
    ct=getCurrentTime();
    b.hour=(c[0]-48)*10+(c[1]-48);
    b.min=(c[3]-48)*10+(c[4]-48);
    train*t=h->start;
    int i=0;
    while(t!=NULL)
    {
        station*s=t->start;
        while(s!=NULL)
        {
            if(strcmp(s->sCode,a)==0&&timeComp(s->dep,ct)>=1)
            {
                Time d=timeDifference(s->dep,ct);
                if(timeComp(b,d)>=0)
                {
                    i=1;
                    printf("%25s %s\n Arr- %02d:%02d Dep- %2d:%2d\n\n",t->tName,t->tNo,s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
                    break;
                }
            }
            s=s->next;
        }
        t=t->next;
    }
    if(i==0)
        printf("No trains in the provided time.\n");
}
void trainBetweenStations(database *h)
{
    train *t=h->start;
    char from[5],to[5];
    int i;
    printf("\nFROM:\t");
    scanf("%s",from);
    printf("TO:\t");
    scanf("%s",to);
    int u=0;
    while(t!=NULL)
    {
        i=0;
        station*s=t->start,*s1;
        while(s!=NULL)
        {
            if(!strcmp(s->sCode,from))
            {
                i++;
                s1=s;
            }
            if(!strcmp(s->sCode,to))
            {
                    if(!i)
                        break;
                    u=1;
                    printf("\n\n\nTrain info :\n%s %s\nNo of stations in between-%d\n",t->tName,t->tNo,((s->sNo)-(s1->sNo)));
                    printf("%s\tArrival: %02d:%02d\tDeparture: %02d:%02d\n",s1->sName,s1->arr.hour,s1->arr.min,s1->dep.hour,s1->dep.min);
                    printf("%s\tArrival: %02d:%02d\tDeparture: %02d:%02d\n\n",s->sName,s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
            }
            s=s->next;
        }
        t=t->next;
    }
    if(u==0)
    {
        printf("No trains found.\n\n\n");
        return;
    }
    printf("Do you want to see schedule ?(Y/N)\n->");
    char choice;
    scanf("%c",&choice);
    if(choice=='N'||choice=='n')
        return;
    GT:printf("\nChoose the train to see schedule :\n");
    char tr[6];
    printf("->");
    scanf("%s",tr);
    t=h->start;
    i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tr)==0)
        {
            i=1;
            break;
        }
        t=t->next;
    }
    if(i==0)
    {
        printf("\nNo such train. Please Re-enter your choice.\n");
        goto GT;
    }
    printf("Train info :\n%s %s\nNo of stations-%d\n",t->tName,t->tNo,t->NOS);
    station*s=t->start;
    while(s!=NULL)
    {
        printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
        printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
        printf("Dist-%4d|\n",s->dist);
        s=s->next;
    }
    printf("\n\n");
    printf("Want to see another ?(Y/N)\n->");
    scanf("%s",tr);
    if(!strcmp(tr,"y"))
        goto GT;
    if(!strcmp(tr,"Y"))
        goto GT;
}
void showSpecialTrains(database*h)
{
    int i=0;
    train*t=h->start;
    while(t!=NULL)
    {
        if(t->tNo[0]=='0')
        {
            printf("%25s %s\n",t->tName,t->tNo);
            i=1;
        }
        t=t->next;
    }
    if(i==0)
        printf("No special train at the moment.\n\n");
}
void admin(database*h)
{
    int j=1;
    G:
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t     Username : ");
    char uname[30];
    char pw[20];
    scanf("%s",uname);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t    Username : %s\n",uname);
    printf("\t\t\t    Password : ");
    int i=0;
    char c;
    while(1)
    {
        c=getch();
        if(c==8)
        {
            printf("\b \b");
            i--;
            continue;
        }
        if(c==13)
            break;
        pw[i++]=c;
        printf("*");
    }
    pw[i]='\0';
    if(strcmp("jiit62",uname)!=0||strcmp("sdflab",pw)!=0)
    {
        if(j==3)
        {
            printf("\n\nWrong input 3 times. Login failed.\n");
            Sleep(100);
            return;
        }
        printf("\n\nWrong username or password. Please re-enter.\n");
        j++;
        Sleep(200);
        goto G;
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t  Login Successful!!!\n\n\n\n\n\n\n\n\n\n\n\n\n");
    Sleep(750);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    int choice=1;
    while(choice)
    {
        printf("Enter your choice : \n1: Change train LATE status\n2: Cancel a train\n0: Return to Main Menu\n\n->");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            {
                admin_lateTrain(h);
                break;
            }
        case 2:
            {
                admin_cancelTrain(h);
                break;
            }
        default:
            break;
        }
    }
}
void admin_lateTrain(database*h)
{
    printf("Choose the Train No. to update Late Status :\n");
    Sleep(1000);
    printTrains(h);
    char tNo[6];
    G:printf("\nEnter Train No. :\n->");
    scanf("%s",tNo);
    train*t=h->start;
    int i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tNo)==0)
         {
             i=1;
            break;
         }
         t=t->next;
    }
    if(i==0)
    {
        printf("Invalid Code. Please Enter again.\n");
        goto G;
    }
    station*s=t->start;
    printf("Enter the time for which the train is late (in HH:MM format) : ");
    char tm1[6];
    scanf("%s",tm1);
    Time tm;
    tm.hour=(tm1[0]-48)*10+(tm1[1]-48);
    tm.min=(tm1[3]-48)*10+(tm1[4]-48);
    while(s!=NULL)
    {
        if((s->arr.min+tm.min)>=60)
        {
            s->arr.min=s->arr.min+tm.min-60;
            s->arr.hour=s->arr.hour+tm.hour+1;
        }
        else
        {
            s->arr.min=s->arr.min+tm.min;
            s->arr.hour=s->arr.hour+tm.hour;
        }
        if((s->dep.min+tm.min)>=60)
        {
            s->dep.min=s->dep.min+tm.min-60;
            s->dep.hour=s->dep.hour+tm.hour+1;
        }
        else
        {
            s->dep.min=s->dep.min+tm.min;
            s->dep.hour=s->dep.hour+tm.hour;
        }
        s->arr.hour=s->arr.hour%24;
        s->dep.hour=s->dep.hour%24;
        s=s->next;
    }
    printf("The updated schedule is :\n");
    s=t->start;
    while(s!=NULL)
    {
        printf("%2d| %20s |%4s |",s->sNo,s->sName,s->sCode);
        printf("ARR-%02d:%02d | DEP-%02d:%02d | ",s->arr.hour,s->arr.min,s->dep.hour,s->dep.min);
        printf("Dist-%4d|\n",s->dist);
        s=s->next;
    }
    Sleep(2000);
}
void admin_cancelTrain(database*h)
{
    g:printf("Choose the train to cancel :\n\n");
    train *t=h->start;
    printTrains(h);
    printf("\n\nEnter choice :\n->");
    char tr[6];
    scanf("%s",tr);
    int i=0;
    while(t!=NULL)
    {
        if(strcmp(t->tNo,tr)==0)
        {
            i=1;
            break;
        }
        t=t->next;
    }
    if(i==0)
    {
        printf("Invalid choice. Please re-enter.\n");
        goto g;
    }
    train*temp=h->start;
    while(temp!=NULL)
    {
        if(temp->next==t)
        {
            temp->next=t->next;
            free(t);
        }
        temp=temp->next;
    }
    printf("The revised list of trains is :\n");
    Sleep(1000);
    printTrains(h);
    Sleep(1000);
    printf("\n\n");
}
int main()
{
    database *h=initDB();
    h=loadDB(h);
    //display(h);
    printf(" \n\t\t  Welcome to JIIT Railways Enquiry System.\n\n");
    int ch=1;
    while(ch!=0 )
    {
        printf("\n\n\nEnter your choice\n");
        printf("1: Display all trains\n2: Spot your train\n3: Display train schedule\n4: Display everything\n5: Train Between Stations\n6: Live Station\n7: Show all stations\n8: Show Special Trains\n9: Admin Login\n0: Quit the program\n->");
        scanf("%d",&ch);
        switch(ch)
        {
            case 0:
            {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t  Shutting down.\n\n\n\n\n\n\n\n\n\n\n\n\n");
                Sleep(600);
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t  Shutting down..\n\n\n\n\n\n\n\n\n\n\n\n\n");
                Sleep(600);
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t  Shutting down...\n\n\n\n\n\n\n\n\n\n\n\n\n");
                Sleep(600);
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;
            }
            case 1:
                {
                    printTrains(h);
                    break;
                }
            case 2:
                {
                    spotTrain(h);
                    break;
                }
            case 3:
                {
                    displayTrain(h);
                    break;
                }
            case 4:
                {
                    display(h);
                    break;
                }
            case 5:
                {
                    trainBetweenStations(h);
                    break;
                }
            case 6:
                {
                    liveStation(h);
                    break;
                }
            case 7:
                {
                    printAllStations();
                    break;
                }
            case 8:
                {
                    showSpecialTrains(h);
                    break;
                }
            case 9:
                {
                    admin(h);
                    break;
                }
            default :
                {
                    break;
                }
        }
    }
    return 0;
}
