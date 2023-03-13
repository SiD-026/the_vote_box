#include<iostream.h>
#include<string.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<iomanip.h>
#include<ctype.h>
  class candidate
  {
    public:
    char name[30];
    char party[30];
    int cno;
    int votes;
    static int tvotes;

    candidate()
    {
      cno=0;
      votes=0;
    }

    void print()
    {
  // To Print One Entry of Record.


     cout<<setw(11)<<cno;
     cout<<setw(32)<<name;
     cout<<setw(31)<<party;
     cout<<endl;
    }

    void res()
    {
     cout<<setw(6)<<cno;
     cout<<setw(27)<<name;
     cout<<setw(21)<<party;
     cout<<setw(18)<<votes;
     cout<<endl;
    }

    void getdetails()
    {
     gotoxy(14,13);
     {
     cout<<endl;
     } cleardevice();
       setcolor(2);
      settextstyle(10,0,5);
      outtextxy(105,40,"Add Candidate");
      {
      gotoxy(25,13);
      cout<<"Cno:"<<cno<<endl;
      gotoxy(25,16);
      cout<<"Name:"; gets(name);
      gotoxy(25,19);
      cout<<"Party:"; gets(party);

		    }
    }

  }Q,E[4],R;

  //Function Prototypes
  void results();
  void addcandidate();
  void vsettings();
  void candidate_menu();
  void voting();
  void clearcandidate();
  void menu();
  void voting_menu();
  void startcampaign(int);
  //Static Declaration
  int candidate::tvotes=0;

  //Global Variables Declaration
  char campfile[50]="null";
  fstream fa;
  int del=3000;
  int pass=123;

  //Function Definition

  void checkfile(int s)
  {
   cleardevice();
   if(s==1)
   {
    gotoxy(1,1);
    cout<<"File doesn't exist: Add Candidate to list";
    cout<<endl;
    getch();
    addcandidate();
   }
   if(s==2)
   {
    gotoxy(1,1);
    cout<<"Error Opening file!! \nPress any key to exit";
    getch();
    exit(0);
   }
   if(s==3)
   {
    gotoxy(1,1);
    cout<<"File doesn't exist, Start new campaign!!";
    cout<<endl<<"Redirecting in ";
      for(int i=5;i>0;i--)
      {
       cout<<i<<" seconds";
       delay(1000);
       cout<<"\b\b\b\b\b\b\b\b\b";
      }
      startcampaign(1);
   }
   if(s>3)
   {
   gotoxy(1,1);
   cout<<"File Error!!\nPress any key to return to Voting Menu";
   getch();
   voting_menu();
   }
  }


  int passd()
  {
    char ch;
    int r=0;
    char passd[20];
    for(;;)
    {
      cleardevice();
      gotoxy(4,15);
      cout<<"Enter the password to perform function:";
      r=0;
      for(int i=0;;i++)
      {
	ch=getch();
       if(ch==13)
       {
	 passd[r]='\0';
	 break;
       }
       if(ch==8)
       {
	 if(i>0)
	 {
	   cout<<ch<<" "<<ch;
	   i-=2;r--;
	 }
	 else
	 i--;
      }
      else
      {
	cout<<"*";
	passd[r]=ch;
	r++;
     }
    }
    if(strcmp("tvb",passd)==0)
    return 0;
    else
    {
      cout<<endl<<"!! INVALID PASSWORD !!";
      cout<<endl<<"Redirecting to menu in ";
      for(int i=5;i>0;i--)
      {
       cout<<i<<" seconds";
       delay(1000);
       cout<<"\b\b\b\b\b\b\b\b\b";
      }
      menu();
      getch();
    }
   }
 }



  void clearcandidate()
  {
    passd();
    cleardevice();
    gotoxy(1,1);
    remove("loc.dat");
    ifstream f("loc.dat",ios::binary);
    if(!f)
    cleardevice();
    gotoxy(34,15);
    cout<<"Wipe Complete";
    getch();
    candidate_menu();
  }

  void listcandidate(int c)
  {
    cleardevice();
    ifstream fin;
    fin.open("loc.dat",ios::in|ios::binary);
    if(!fin)
    {
      if(c==0)
      checkfile(3);
      else
      checkfile(1);
    }
    setcolor(2);
    settextstyle(10,0,5);
    outtextxy(55,30,"List Of Candidate");
    gotoxy(10,10);
    cout<<"Cno";
    gotoxy(40,10);
    cout<<"Name";
    gotoxy(70,10);
    cout<<"Party";
    cout<<endl;
    while(!(fin.read((char*)&Q,sizeof(Q)).eof()))
    {
      Q.print();
    }
    fin.close();
    if(c==0)
    {
      return;
    }
    getch();
    candidate_menu();
  }

 int fileline()
  {
    int g=0;   //seri.
    fstream fin;
    fin.open("loc.dat",ios::in|ios::binary);
    while(fin.read((char*)&Q,sizeof(Q)))
    g++;
    fin.close();
    g+=1;
    return g;
  }

  void addcandidate()
  {
    cleardevice();
    char q;
    do
    {
      ofstream fout("loc.dat",ios::app|ios::binary|ios::out);
      if(!fout) checkfile(2);
      Q.cno=fileline();
      Q.getdetails();
      fout.write((char*)&Q,sizeof(Q));
      gotoxy(25,22);
      cout<<"Add Another Candidate? (Y/N) : ";
      cin>>q;
      fout.close();
    }while(q=='Y'||q=='y');
    candidate_menu();
  }

  void loadcandidate()
  {
    //If new campaign is created , current campaign candidates
    //are selected from listofcandidates file
    cleardevice();
    listcandidate(0);
    cout<<endl;
    gotoxy(5,25);
    cout<<"Load three candidates for campaign"<<endl;
    cout<<"    Select Candidate by cno: ";
    int select[3];
    for(int i=0;i<3;i++)
    {
     cin>>select[i];
     if(select[i]==pass)
     menu();
    }
    fa.open(campfile,ios::out);
    if(!fa) checkfile(7);
    ifstream sel;
    sel.open("loc.dat",ios::in|ios::binary);
    if(!sel) checkfile(7);
    int j=0;
    while(!(sel.read((char*)&Q,sizeof(Q)).eof()))
    {
     for(i=0;i<3;i++)
     {
       if(Q.cno==select[i])
       E[j++]=Q;
     }
    }
    //To add Nota
    E[3].cno=4;
    strcpy(E[3].name,"NOTA");
    strcpy(E[3].party,"None of the Above");

    for(i=0;i<4;i++)
    E[i].cno=i+1;

    for(i=0;i<4;i++)
    {
     fa.write((char*)&E[i],sizeof(E[i]));
    }
    fa.close();
    sel.close();
    voting();
  }

  void voting()
  {
   int o;
   do
   {
    cleardevice();
    setcolor(2);
    settextstyle(10,0,7);
    outtextxy(170,5,"Voting");
    gotoxy(10,10);
    cout<<"Cno";
    gotoxy(40,10);
    cout<<"Name";
    gotoxy(70,10);
    cout<<"Party";
    cout<<endl;
    for(int i=0;i<4;i++)
    E[i].print();
    cout<<endl<<"Choose  YOUR candidate: ";
    cin>>o;
    for(int j=0;j<4;j++)
    {
     if(o==E[j].cno)
     {
      E[j].votes++;
      E[j].tvotes++;
     }
     else if(o==pass)
     menu();
     else if(o>4)
     {
       cout<<"Invalid Choice!!!";
       delay(del);
     }
    }
    if(o<=4)
    {
    ofstream vote;
    vote.open(campfile,ios::out);
    if(!vote) checkfile(5);
    for(j=0;j<4;j++)
    vote.write((char*)&E[j],sizeof(E[j]));
    vote.close();
    cout<<endl;
    cout<<"Your vote has been recorded";
    cout<<endl;
    delay(del);
    }
   }while(1);
  }

  void resvoting()
  {
  ifstream fin(campfile,ios::in);
  if(!fin) checkfile(3);
  for(int i=0;i<4;i++)
  {
    fin.read((char*)&E[i],sizeof(E));
  }
  voting();

  }

  void results()
  {
    cleardevice();
    passd();
    startcampaign(3);
    cleardevice();
    gotoxy(1,1);
    fstream r;
    r.open(campfile,ios::in);
    if(!r) checkfile(4);
    setcolor(2);
    settextstyle(10,0,7);
    outtextxy(145,13,"Results");
    gotoxy(5,10);
    cout<<"Cno";
    gotoxy(30,10);
    cout<<"Name";
    gotoxy(50,10);
    cout<<"Party";
    gotoxy(70,10);
    cout<<"Votes";
    cout<<endl;
    candidate S[4];
    int k=0;
    R.tvotes=0;
    int high=0,temp=0;
    while(!(r.read((char*)&R,sizeof(R)).eof()))
    {
      E[k++]=R;
      if(temp<R.votes)
      {
       high=k-1;
       temp=R.votes;
      }
      R.res();
      R.tvotes+=R.votes;
    }
    cout<<"\n\n";
    cout<<"Total Votes: "<<R.tvotes<<endl;
    cout<<E[high].name<<" has scored the highest number of votes, and is in the leading right now!";
    getch();
    r.close();
    voting_menu();
  }

  void startcampaign(int status)
  {
    if(status==2)
    passd();
    cleardevice();
    gotoxy(1,1);
    cout<<"Choose file name"<<endl;
    cout<<"1.campaign_one"<<endl;
    cout<<"2.campaign_two"<<endl;
    cout<<"Enter your choice: ";
    int sc; cin>>sc;


    //file name assign

    if(sc==1)
    strcpy(campfile,"campaign_one.txt");
    else if(sc==2)
    strcpy(campfile,"campaign_two.txt");
    else
    {
    cout<<"\n***Invalid Choice***";
    delay(del);
    voting_menu();
    }
    //file access
    if(status<=2)
    {
     fa.open(campfile,ios::out);
     if(!fa)
     {
     checkfile(3);
     }
     fa.close();
    }
     if(status==1)
     {
      loadcandidate();
     }

    else if(status==2)
    {
      resvoting();
    }
    else if(status==3)
    return;
  }
  void removecamp()
  {
   remove(campfile);
   cout<<endl<<"Clear Complete!!!";
   getch();
   voting_menu();
  }

  void vsettings()
  {
    cleardevice();
    gotoxy(1,1);
    cout<<"1.Erase files"<<endl;
    cout<<"2.Adjust delay"<<endl;
    cout<<"3.Change Password"<<endl;
    cout<<"4.Back"<<endl;
    cout<<"Option: ";
    int p; cin>>p;
    if(p==1)
    {
     cout<<"Choose files to Erase"<<endl;
     startcampaign(3);
     removecamp();
    }
    if(p==2)
    {
     cout<<"The current delay is "<<del/1000<<" seconds.";
     cout<<endl;
     cout<<"New Delay(in seconds): "; cin>>del;
     del=del*1000;
    }
    if(p==3)
    {
      cout<<"Enter Existing Password: ";
      int t; cin>>t;
      if(pass==t)
      {
	cout<<"Enter new password: ";
	cin>>pass;
      }
      else
      {
      cout<<"Error";
      delay(del);
      voting_menu();
      }
    }

    if(p==4)
    voting_menu();

    else
    {
     cout<<"Invalid Choice!!";
     vsettings();
    }

    getch();
    voting_menu();
  }

  void candidate_menu()
  {

    //UI code here
      cleardevice();
      int cm;
      setcolor(1);
      settextstyle(10,0,8);
	//title
      outtextxy(90,0,"VoteBox");
      //sub
      settextstyle(1,0,4);
      setcolor(12);
      outtextxy(60,180,"CANDIDATE:");
      //div1
      settextstyle(6,0,2);
      outtextxy(240,210,"1.LIST OF CANDIDATES   ^");
      //div2
      outtextxy(240,240,"2.ADD CANDIDATE        +");
      //div3
      outtextxy(240,270,"3.Clear File           -");
      //div4
      outtextxy(240,300,"4.Back                 <");
      //div5
      outtextxy(240,330,"5.Exit         	 X");
      gotoxy(7,25);
      cout<<" Enter Your Choice: ";
      gotoxy(29,25);
      cin>>cm;
      if(cm==1)
      listcandidate(cm);
      if(cm==2)
      addcandidate();
      if(cm==3)
      clearcandidate();
      if(cm==4)
      menu();
      if(cm==5)
      exit(1);
      if(cm>4||cm==0)
      {
	gotoxy(17,18);
	cout<<"...............!!invalid command!!..................";
	delay(del);
	candidate_menu();
       }
  }

  void voting_menu()
  {
    //UI Code Here
     cleardevice();
     int vm;
     setcolor(2);
      settextstyle(10,0,8);
	//title
      outtextxy(90,0,"VoteBox");
      //sub
      settextstyle(1,0,4);
      setcolor(20);
      outtextxy(155,180,"VOTING:");
      //div1
      settextstyle(6,0,2);
      outtextxy(260,210,"1.NEW POLL");
      //div2
      outtextxy(260,240,"2.RESUME POLL");
      //div3
      outtextxy(260,270,"3.RESULTS");
      //div4
      outtextxy(260,300,"4.SETTING");
      //div5
      outtextxy(260,330,"5.BACK");
      //div6
      outtextxy(260,360,"6.EXIT");
     gotoxy(10,25);
     cout<<" Enter Your Choice: ";
     gotoxy(30,27);
     cin>>vm;
    if(vm==1||vm==2)
    startcampaign(vm);
    if(vm==3)
    results();
    if(vm==4)
    vsettings();
    if(vm==5)
    menu();
    if(vm==6)
    exit(1);
     if(vm>6||vm==0)
      {
       gotoxy(17,20);
       cout<<"...............!!invalid command!!..................";
       delay(del);
       voting_menu();
    }

  }

void menu()
{
    int gdriver = DETECT,gmode;
    initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
      setcolor(2);
      int m;
      settextstyle(10,0,8);
	//title
      outtextxy(90,0,"VoteBox");
      settextstyle(1,0,4);
      //sub
      setcolor(20);
      outtextxy(100,180,"MAIN MENU:");
      //div1
      settextstyle(0,0,2);
      outtextxy(270,220,"1.CANDIDATE");
      //div2
      outtextxy(270,250,"2.VOTING");
      //div3
      outtextxy(270,280,"3.EXIT");
      //div4
      gotoxy(10,25);
      cout<<"Enter Your Choice: ";
      cin>>m;
      if(m==1)
      candidate_menu();
      if(m==2)
      voting_menu();
      if(m==3)
      exit(0);
      else
      {
       gotoxy(17,18);
       cout<<"...............!!invalid command!!..................";
       delay(del);
       menu();
      }
}

void main()
{
menu();
getch();

}
