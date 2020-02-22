#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<ctype.h>
#include<process.h>
#include<stdlib.h>
#include<time.h>

fstream f,f1,f2,f3,f4,f5,f6,f7,f8,w,o;

//**********************************************************
//	CLASS NAME : Hotel
//	DETAILS    : IT CONTROLS OVER ALL FUNCTIONING
//                   OF THE HOTEL
//**********************************************************
class HOTEL
{
	char array[100];
	struct bill_restaurant_bar
	{
	  long brestaurant,bbar;
	} b[100];
	struct booking_data
	{
	  long charge;
	  unsigned int roomno;
	  char name[25],address[75],telno[10],roomtype[15];
	  int d1,m1,y1,t1;
	} d;
	struct check_out_data
	{  long charge;
	  char name[25],address[75],telno[10],otime[6],roomtype[15];
	unsigned  int roomno;
	  int d1,m1,y1,d2,m2,y2,t2;
	} C;
	struct cancellation_data
	{
	  char name[25],address[75],telno[10];
	} D;
	struct worker_data
	{
	    char name[20];
	    char add1[25],add2[25];
	    char telno[12];
	   unsigned int id;
	    float salary;
	}wd;
	struct worker_cancel
	{
        char name[20];
	    char add1[25],add2[25];
	    char telno[12];
	  unsigned  int id;
	}wc;

	public:
	void booking();
	void check_in();
	void check_out();
	void cancellation();
	void taxi_service();
	void restaurant();
	void bar();
	void worker();
	void workerout();
	void view_data();
	void hoteling();
	void meals();
	void employee();

} 	H;


//**********************************************************
//	FUNCTION NAME 	  : BOOKING
//**********************************************************

void HOTEL::booking ()
{   textcolor(GREEN);
	clrscr();
	int c=0;
	//FINDING AN UNOCCUPIED ROOM
	f.open("ARRAY.DAT",ios::in|ios::binary);
	f.read((char *)&array,sizeof(array));
	while(array[c]!='e') c++;
	array[c]='o';
	f.close();
	f.open("ARRAY.DAT",ios::out|ios::binary);
	f.write((char *)&array,sizeof(array));
	f.close();
	f1.open("HOTEL.DAT",ios::app|ios::binary);
	d.roomno=c+1;
	//DATA OF THE CUSTOMER
	cout<<"ENTER THE REQUIRED DATA\n"
	    <<"NAME :: ";
	gets(d.name);
	int l=strlen(d.name);
	for(int i=0;i<l;i++) d.name[i]=toupper(d.name[i]);
	cout<<"ADDRESS(R) :: ";
	gets(d.address);
	cout<<"TEL. NO.(R) :: ";
	gets(d.telno);
    cout<<"DATE WHEN YOU WILL CHECK-IN(dd/mm/yyyy) :: ";
	cin>>d.d1>>d.m1>>d.y1;
	cout<<"\n\nROOM TYPES  "<<"\t"
	    <<"CODES"<<"\t"<<"CHARGE PER DAY\n"
	    <<"ROYAL SUITE "<<"\t"<<"1.   "<<"\t"<<"Rs 20,000\n"
	    <<"SUPER DELUXE"<<"\t"<<"2.   "<<"\t"<<"Rs 15,000\n"
	    <<"DELUXE      "<<"\t"<<"3.   "<<"\t"<<"Rs 10,000\n"
	    <<"DOUBLE BED  "<<"\t"<<"4.   "<<"\t"<<"Rs  5,000\n"
	    <<"SINGLE BED  "<<"\t"<<"5.   "<<"\t"<<"Rs  2,000\n";
	int roomcode;
	REDO:
	cout<<"ROOM CODE :: ";
	cin>>roomcode;
	switch(roomcode)
	{
	  case 1 : strcpy(d.roomtype,"ROYAL SUITE");
		   d.charge=20000;
		   break;
	  case 2 : strcpy(d.roomtype,"SUPER DELUXE");
		   d.charge=15000;
		   break;
	  case 3 : strcpy(d.roomtype,"DELUXE");
		   d.charge=10000;
		   break;
	  case 4 : strcpy(d.roomtype,"DOUBLE BED");
		   d.charge=5000;
		   break;
	  case 5 : strcpy(d.roomtype,"SINGLE BED");
		   d.charge=2000;
		   break;
	  default: cout<<"ENTER THE RIGHT CODE\n";
		   goto REDO;
	}
	clrscr();
	cout<<"YOUR ROOM NO. IS :: "<<d.roomno<<"\n";
	gotoxy(25,25);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	//COPYING THE RECORD OF THE CUSTOMER INTO A FILE
	f1.write((char *)&d,sizeof(d));
	f1.close();
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : CHECH IN
//**********************************************************
void HOTEL::check_in()
{   textcolor(BLUE);
	clrscr();
	int rn;
	char ans;
	cout<<"HAVE YOU BOOKED IN ADVANCE ?(Y/N)::";
	cin>>ans;
	if(ans=='n'||ans=='N')
	{
	  cout<<"THEN YOU FIRST HAVE TO BOOK";
	  gotoxy(25,25);
	  cout<<"PRESS ANY KEY TO CONTINUE";
	  getch();
	  booking();
	}
	clrscr();
	cout<<"ROOM NUMBER   :: ";
	cin>>rn;
	f1.open("HOTEL.DAT",ios::in|ios::binary);
	do f1.read((char *)&d,sizeof(d)); while(d.roomno!=rn);
	cout<<"NAME          :: "<<d.name<<"\n"
	    <<"ADDRESS(R)    :: "<<d.address<<"\n"
	    <<"TEL. NO.(R)   :: "<<d.telno<<"\n"
	    <<"CHECK-IN DATE :: "<<d.d1<<'/'<<d.m1<<'/'<<d.y1<<"\n"
	    <<"ROOM TYPE     :: "<<d.roomtype;
	gotoxy(25,25);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	f1.close();
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : CHECK OUT
//**********************************************************
void HOTEL::check_out()
{
	textcolor(CYAN);
	clrscr();
	int rn;
	cout<<"ROOM NUMBER :: ";
	cin>>rn;
	cout<<"CHECK-OUT DATE (d/mm/yyyy) :: ";
	cin>>C.d2>>C.m2>>C.y2;
	cout<<"CHECK-OUT TIME (in form of with (:) 07:30 , 22:55 etc) :: ";
	gets(C.otime);
	clrscr();
	fstream e;
	f1.open("HOTEL.DAT",ios::in|ios::binary);
	do{ f1.read((char *)&d,sizeof(d)); }while(d.roomno!=rn);
	gotoxy(25,1); cout<<"**** BILL ****\n\n";
	cout<<endl;
	cout<<"\t\tROOM NUMBER       :: "<<d.roomno<<"\n"
	    <<"\t\tNAME              :: "<<d.name<<"\n"
	    <<"\t\tADDRESS(R)        :: "<<d.address<<"\n"
	    <<"\t\tTEL. NO.(R)       :: "<<d.telno<<"\n"
	    <<"\t\tROOM PRICE        :: "<<d.charge<<"\n"
	    <<"\t\tROOM TYPE         :: "<<d.roomtype<<"\n"
	    <<"\t\tCHECK-IN DATE     :: "<<d.d1<<'/'<<d.m1<<'/'<<d.y1<<"\n"
	    <<"\t\tCHECK-OUT DATE    :: "<<C.d2<<'/'<<C.m2<<'/'<<C.y2<<"\n"
	    <<"\t\tCHECK-OUT TIME    :: "<<C.otime<<"\n";
	//COPYING THE RECORD OF THE CUSTOMER INTO ANOTHER FILE
	f2.open("CUSTOMER.DAT",ios::app|ios::binary);
    strcpy(C.name,d.name);
	strcpy(C.address,d.address);
	strcpy(C.telno,d.telno);
	strcpy(C.telno,d.telno);
    C.d1=d.d1;
    C.m1=d.m1;
    C.y1=d.y1;
    C.d2;
    C.m2;
    C.y2;
    C.otime;
    strcpy(C.roomtype,d.roomtype);
    C.charge=d.charge;
    C.roomno=d.roomno;
    f2.write((char *)&C,sizeof(C));
	f2.close();
	//CALCULATING NO. OF DAYS THE CUSTOMER OCCUPIED THE ROOM
	//AND PRINTING THE TARIFF
	long tariff;
	unsigned int t;
    d.m1=(d.m1+9)%12;
    d.y1=d.y1-d.m1/10;
    d.t1=365*d.y1+d.y1/4-d.y1/100+d.y1/400+(d.m1*306+5)/10+(d.d1-1);
    C.m2=(C.m2+9)%12;
    C.y2=C.y2-C.m2/10;
    C.t2=365*C.y2+C.y2/4-C.y2/100+C.y2/400+(C.m2*306+5)/10+(C.d2-1);
    t=(C.t2-d.t1);
    cout<<"\t\tNO. OF DAYS       :: "<<t<<'\n';
    tariff=500*t;
	cout<<"\t\tTARIFF            :: Rs "<<tariff<<'\n';
	f1.close();
	//SHOWING THE CUSTOMER'S RESTAURANT AND BAR BILL
	f8.open("BILL.DAT",ios::in|ios::binary);
	f8.read((char *)&b,sizeof(b));
	cout<<"\t\tRESTAURANT CHARGE :: Rs "<<b[rn-1].brestaurant<<'\n'
	    <<"\t\tBAR CHARGE        :: Rs "<<b[rn-1].bbar<<'\n'
	    <<"\t\tTOTAL             :: Rs "<<b[rn-1].brestaurant+b[rn-1].bbar+tariff+d.charge;
	b[rn-1].bbar=b[rn-1].brestaurant=0;
	tariff=0;
	t=0;
	d.m1=d.y1=d.t1=0;
	C.m2=C.y2=C.t2=0;
	C.m1=C.y1=0;
	f8.close();
	f8.open("BILL.DAT",ios::out|ios::binary);
	f8.write((char *)&b,sizeof(b));
	f8.close();
	//DELETING THE RECORD OF THE CUSTOMER
	f1.open("HOTEL.DAT",ios::in|ios::binary);
	e.open("F.DAT",ios::out|ios::binary);
	f1.read((char *)&d,sizeof(d));
	while(f1)
	{
	  if(d.roomno!=rn)
	  {
	    e.write((char *)&d,sizeof(d));
	    f1.read((char *)&d,sizeof(d));
	  }
	  else f1.read((char *)&d,sizeof(d));
	}
	e.close();
	f1.close();
	f1.open("HOTEL.DAT",ios::out|ios::binary);
	e.open("F.DAT",ios::in|ios::binary);
	e.read((char *)&d,sizeof(d));
	while(e)
	{
	  f1.write((char *)&d,sizeof(d));
	  e.read((char *)&d,sizeof(d));
	}
	e.close();
	f1.close();
	//MAKING THE ROOM OCCUPIED BY THE CUSTOMER AS UNOCCUPIED
	f.open("ARRAY.DAT",ios::in|ios::binary);
	f.read((char *)&array,sizeof(array));
	array[rn-1]='e';
	f.close();
	f.open("ARRAY.DAT",ios::out|ios::binary);
	f.write((char *)&array,sizeof(array));
	f.close();
	gotoxy(25,25);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : CANCELLATION
//**********************************************************
void HOTEL::cancellation()
{
	textcolor(WHITE);
	clrscr();
	int rn;
	cout<<"ROOM NUMBER  :: ";
	cin>>rn;
	f1.open("HOTEL.DAT",ios::in|ios::binary);

	do f1.read((char*)&d,sizeof(d)); while(d.roomno!=rn);
	cout<<"NAME         :: "<<d.name<<"\n"
	    <<"ADDRESS(R)   :: "<<d.address<<"\n"
	    <<"TEL. NO.(R)  :: "<<d.telno<<"\n"
	    <<"ROOM TYPE    :: "<<d.roomtype<<"\n"
	    <<"CANCELLED\n";
	//COPYING THE RECORD OF THE CUSTOMER INTO ANOTHER FILE
	f3.open("CANCEL.DAT",ios::app|ios::binary);
	strcpy(D.name,d.name);
	strcpy(D.address,d.address);
	strcpy(D.telno,d.telno);
	f3.write((char *)&D,sizeof(D));
	f3.close();
	f1.close();
	//MAKING THE ROOM ALLOTED TO THE CUSTOMER AS EMPTY
	f.open("ARRAY.DAT",ios::in|ios::binary);
	f.read((char *)&array,sizeof(array));
	array[rn-1]='e';
	f.close();
	f.open("ARRAY.DAT",ios::out|ios::binary);
	f.write((char *)&array,sizeof(array));
	f.close();
	fstream e;
	//DELETING THE RECORD OF THE CUSTOMER
	f1.open("HOTEL.DAT",ios::in|ios::binary);
	e.open("F1.DAT",ios::out|ios::binary);
	f1.read((char *)&d,sizeof(d));
	while(f1)
	{
	  if(d.roomno!=rn)
	  {
	    e.write((char *)&d,sizeof(d));
	    f1.read((char *)&d,sizeof(d));
	  }
	  else f1.read((char *)&d,sizeof(d));
	}
	e.close();
	f1.close();
	f1.open("HOTEL.DAT",ios::out|ios::binary);
	e.open("F1.DAT",ios::in|ios::binary);
	e.read((char *)&d,sizeof(d));
	while(e)
	{
	  f1.write((char *)&d,sizeof(d));
	  e.read((char *)&d,sizeof(d));
	}
	e.close();
	f1.close();
	gotoxy(25,25);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : FREEE TAXI SERVICE
//**********************************************************
void HOTEL::taxi_service()
{ int choice;

	textcolor(DARKGRAY);textbackground(LIGHTGRAY);
	cout<<"\t1)I am staying in this hotel\n";
	cout<<"\t2)I am not staying in this hotel\n";
	cin>>choice;
	clrscr();
	if(choice==1)
	{
	  char n[25],t[6],date[11];
	  int x,room;
	  cout<<"ROOM NUMBER :: ";
	  cin>>room;
	  cout<<"NAME        :: ";
	  gets(n);
	  int l=strlen(n);
	  for(int i=0;i<l;i++) n[i]=toupper(n[i]);
	  //VERIFYING THE ENTERED DATA
	  f1.open("HOTEL.DAT",ios::in|ios::binary);
	  f1.read((char *)&d,sizeof(d));
	  while(f1)
	  {
	    if(d.roomno==room && strcmp(d.name,n)==0)
	    {
	      f1.close();
	      goto PROCEED;
	    }
	    f1.read((char *)&d,sizeof(d));
	  }
	  f1.close();
	  clrscr();
	  cout<<"SORRY.ENTERED DATA IS NOT MATCHING THE ACTUAL DATA"
	      <<"\nYOU CAN NOT USE THIS FACILITY";
	  gotoxy(25,25);
	  cout<<"PRESS ANY KEY TO CONTINUE";
	  getch();
	  return;
	  PROCEED:
	  cout<<"NO. OF TAXIS NEEDED      :: ";
	  cin>>x;
	  cout<<"TAXI(s) NEEDED ON (date)(in form of with (/) d/mm/yyyy) :: ";
	  gets(date);
	  cout<<"TAXI(s) NEEDED AT (time)(in form of with (:) 07:30 , 22:55 etc) :: ";
	  gets(t);
	  clrscr();
	  if(x==1)
	    cout<<"A TAXI WILL BE WAITING FOR YOU AT "<<t
		<<" ON "<<date<<" OUTSIDE THE HOTEL GATE";
	  else
	    cout<<x<<" TAXIS WILL BE WAITING FOR YOU AT "<<t
		<<" ON "<<date<<" OUTSIDE THE HOTEL GATE";
	  gotoxy(25,25);
	  cout<<"PRESS ANY KEY TO CONTINUE";
	  getch();
	}
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : RESTAURANT
//**********************************************************
void HOTEL::restaurant()
{   clrscr();
	cout<<"\t\t\tWELCOME TO THE RESTAURANT"<<'\n'<<"\t\t\tPLEASE TAKE YOUR SEAT"<<'\n';
	gotoxy(25,15);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
	int price[113]={245,245,245,245,240,240,240,240,235,235,250,235,235,
	220,215,230,215,240,250,250,250,250,250,250,250,255,245,245,245,245,
	250,240,240,360,290,360,290,370,295,360,290,360,290,250,360,290,360,
	290,250,370,290,360,290,250,250,280,245,290,235,265,240,290,300,256,
	240,265,270,255,255,240,240,235,220,25,30,25,30,35,35,25,30,35,25,35,
	25,25,30,100,105,105,100,105,100,105,125,105,105,100,105,110,115,100,
	100,100,105,105,105,105,125,105,120,120,100};
	char food[113][30]={"SHAHI PANEER","KADAI PANEER","CHEESE KORMA",
	"MALAI KOFTA","MATAR PANEER","PALAK PANEER","MIX VEG.","ALOO GOBI",
	"ALOO JEERA","CHANA MASALA","MATAR MUSHROOM","RAJMA MAKHANI",
	"DAL MAKHANI","MIXED RAITA","BUNDI RAITA","PINEAPPLE RAITA",
	"SALAD(GREEN)","DUM ALOO","MUSHROOM PANEER","MUTTON MASALA",
	"MUTTON MUGHLAI","MUTTON KORMA","MUTTON DO PYAZA","MUTTON SAGH",
	"MUTTON DAHI","MUTTON ROGAN JOSH","MUTTON CURRY","KADAI MUTTON",
	"KEEMA LEVER","KEEMA MATAR","KEEMA EGG","BRAIN CURRY","EGG CURRY",
	"BUTTER CHICKEN","BUTTER CHICKEN(1/2)","KADAI CHICKEN",
	"KADAI CHICKEN(1/2)","BUTTER CHICKEN(BL)","BUTTER CHICKEN(BL)(1/2)",
	"CHICKEN MUGHLAI","CHICKEN MUGHLAI(1/2)","CHICKEN MASALA",
	"CHICKEN MASALA(1/2)","CHICKEN MASALA(1/4)","CHICKEN SAGH",
	"CHICKEN SAGH(1/2)","CHICKEN DAHI","CHICKEN DAHI(1/2)",
	"CHICKEN DAHI(1/4)","CHICKEN KORMA","CHICKEN KORMA(1/2)",
	"CHICKEN DO PYAZA","CHICKEN DO PYAZA(1/2)","FISH CURRY",
	"CHICKEN CURRY","CHICKEN CURRY(1/2)","CHICKEN CURRY(1/4)",
	"CHILLI CHICKEN","TANDOORI ALOO","CHICKEN TIKKA","SEEKH KABAB",
	"FISH TIKKA","CHICKEN TANDOORI","CHICKEN TANDOORI(1/2)",
	"PANEER TIKKA","CHICKEN SEEKH KABAB","CHICKEN HARA KABAB",
	"CHICKEN BIRYANI","MUTTON BIRYANI","PANEER PULAO","VEG.PULAO",
	"JEERA RICE","STEAMED RICE","RUMALI ROTI","ROTI","NAN","ALOO NAN",
	"PANEER NAN","KEEMA NAN","PARANTHA","ALOO PARANTHA",
	"PANEER PARANTHA","PUDINA PARANTHA","BUTTER NAN","LACHCHA PARANTHA",
	"MISSI ROTI","KHASTA ROTI","VEG.BURGER","PANEER BURGER",
	"CHEESE SANDWICH","VEG.PATTI","CHICKEN PATTI","TEA","COFFEE",
	"COLD COFFEE","PINEAPPLE","STRAWBERRY","CHOCOLATE","BLACK FOREST",
	"DOUBLE STORIED","TRIPLE STORIED","SOFT CONE","VANILLA","STRAWBERRY",
	"CHOCOLATE","CHOCO CHIPS","MANGO","TUTTI FRUITY","LICHI",
	"PISTA BADAM","CHOCOLATE PISTA BADAM","CHOCO DIP","CHOCOLATE LICHI"};
	START:
	textcolor(RED);textbackground(WHITE);
	clrscr();
	gotoxy(31,1); cout<<"*********";
	gotoxy(31,2); cout<<"MENU CARD";
	gotoxy(31,3); cout<<"*********";
	gotoxy(31,5); cout<<"VEGETARIAN";
	for(int i=0;i<15;i++)
	{
	  gotoxy(15,i+7); cout<<i+1;
	  gotoxy(30,i+7); cout<<food[i];
	  gotoxy(55,i+7); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	{
	for(i=15;i<19;i++)
	  gotoxy(15,i-14); cout<<i+1;
	  gotoxy(30,i-14); cout<<food[i];
	  gotoxy(55,i-14); cout<<price[i];
	}
	gotoxy(33,7); cout<<"MUTTON";
	for(i=19;i<33;i++)
	{
	  gotoxy(15,i-10); cout<<i+1;
	  gotoxy(30,i-10); cout<<food[i];
	  gotoxy(55,i-10); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(31,1); cout<<"CHICKEN";
	for(i=33;i<54;i++)
	{
	  gotoxy(15,i-30); cout<<i+1;
	  gotoxy(25,i-30); cout<<food[i];
	  gotoxy(55,i-30); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	for(i=54;i<58;i++)
	{
	  gotoxy(15,i-53); cout<<i+1;
	  gotoxy(30,i-53); cout<<food[i];
	  gotoxy(55,i-53); cout<<price[i];
	}
	gotoxy(31,7); cout<<"BAR-BE-QUE";
	for(i=58;i<73;i++)
	{
	  gotoxy(15,i-49); cout<<i+1;
	  gotoxy(30,i-49); cout<<food[i];
	  gotoxy(55,i-49); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(30,1); cout<<"ROTI-NAN-PARANTHA";
	for(i=73;i<92;i++)
	{
	  gotoxy(15,i-70); cout<<i+1;
	  gotoxy(30,i-70); cout<<food[i];
	  gotoxy(55,i-70); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(30,1); cout<<"BEVERAGES";
	for(i=92;i<95;i++)
	{
	  gotoxy(15,i-89); cout<<i+1;
	  gotoxy(30,i-89); cout<<food[i];
	  gotoxy(55,i-89); cout<<price[i];
	}
	gotoxy(30,8) ;cout<<"PASTRIES";
	for(i=95;i<101;i++)
	{
	  gotoxy(15,i-85); cout<<i+1;
	  gotoxy(30,i-85); cout<<food[i];
	  gotoxy(55,i-85); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(30,1); cout<<"ICE-CREAMS";
	for(i=101;i<113;i++)
	{
	  gotoxy(15,i-98); cout<<i+1;
	  gotoxy(30,i-98); cout<<food[i];
	  gotoxy(55,i-98); cout<<price[i];
	}
	gotoxy(25,25);cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	int answ,fc,fch[113],fe=0,z=-1;
	char fi[113][30],answe;
	RETRY:
	clrscr();
	cout<<"PRESS 0 TO GO BACK TO MENU CARD\n"
	    <<"PRESS 1 TO CONTINUE ";
	cin>>answ;
	switch(answ)
	{
	  case 0 : goto START;

	  case 1 : clrscr();
		   do
		   {
		     z++;
		     cout<<"ENTER THE FOOD CODE YOU WANT TO HAVE :: ";
		     cin>>fc;
		     fch[z]=price[fc-1];
		     fe+=price[fc-1];
		     strcpy(fi[z],food[fc-1]);
		     cout<<"DO YOU WANT MORE(Y/N) :: ";
		     cin>>answe;
		   } while(answe=='y' || answe=='Y');
		   clrscr();
		   for(int y=0;y<z+1;y++)
		   {
		     cout<<fi[y];
		     gotoxy(40,y+1); cout<<fch[y]<<"\n";
		   }
		   cout<<"TOTAL";
		   gotoxy(40,y+1); cout<<fe<<"\n";
		   cout<<"ARE YOU STAYING IN THIS HOTEL (Y/N) ? ";
		   char ans;
		   cin>>ans;

		   if(ans=='y' || ans=='Y')
		   {
		     char na[25];
		     int rn;
		     cout<<"ROOM NO. :: ";
		     cin>>rn;
		     cout<<"NAME     :: ";
		     gets(na);
		     for(i=0;na[i]!='\0';i++) na[i]=toupper(na[i]);
		     //VERIFYING THE ENTERED DATA
		     f1.open("HOTEL.DAT",ios::in|ios::binary);
		     f1.read((char *)&d,sizeof(d));
		     while(f1)
		     {
		       if(d.roomno==rn && strcmp(d.name,na)==0)
		       {
			 f1.close();
			 goto BILL;
		       }
		       f1.read((char *)&d,sizeof(d));
		     }
		     f1.close();
		     cout<<"ENTERED DATA IS NOT MATCHING THE ACTUAL DATA";
		     gotoxy(25,25); cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		     BILL:
		     //ENTERING THE RESTAURANT CHARGE INTO THE FILE
		     f8.open("BILL.DAT",ios::in|ios::binary);
		     f8.read((char *)&b,sizeof(b));
		     b[rn-1].brestaurant = 0;
		     b[rn-1].brestaurant+=fe;
		     f8.close();
		     f8.open("BILL.DAT",ios::out|ios::binary);
		     f8.write((char *)&b,sizeof(b));
		     f8.close();
		     cout<<"THE RESTAURANT BILL HAS BEEN ENTERED INTO YOUR RECORD";
		   }
		   else
		   {
		     gotoxy(25,25);
		     cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		   }
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   break;
	  default: cout<<"YOU HAVE PRESSED A WRONG KEY\nRETRY\n";
		   getch();
		   goto RETRY;
	}
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : BAR
//**********************************************************
void HOTEL::bar()
{   clrscr();
	cout<<"\t\t\t WELCOME TO THE BAR"<<'\n'<<"\t\t\tPLEASE TAKE YOUR SEAT"<<'\n';
	gotoxy(25,15);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
	char bottle[32][20]={"RED LABEL","BLACK LABEL","GOLD LABEL",
	"SIGNATURE","SEAGRAMS","8 PM","CHIVAS REGAL","MC DOWELL","BLACK DOG",
	"BAGPIPER","PETER SCOT","JOHNY WALKER","KINGFISHER","FOSTERS",
	"BUD WEISER","HAYWARD 2000","HAYWARD 5000","VORIAN 6000","RED WINE",
	"WHITE WINE","PORT WINE","IRISH CREAM","OLD MONK","BACARDI",
	"BLUE RIBAND","SMIRNOFF","VO DE FRANCE","LEMAR DE VONCON",
	"VINTAGE BUBBLY","KINGFISHER","BAGPIPER","EVIAN BRAND"};
	int cost[32]={1500,4000,6000,3000,2500,2000,5000,1500,4000,1500,
	2000,6000,1000,1500,1000,1000,1500,1500,500,550,600,4000,1500,1000,
	1000,1500,5000,5500,8000,150,150,80};
	START:
	textcolor(MAGENTA);
	clrscr();
	gotoxy(18,1); cout<<"CODE";
	gotoxy(35,1); cout<<"BRAND";
	gotoxy(59,1); cout<<"PRICE";
	gotoxy(35,4); cout<<"WHISKY";
	for(int i=0;i<12;i++)
	{
	  gotoxy(20,i+6); cout<<i+1;
	  gotoxy(35,i+6); cout<<bottle[i];
	  gotoxy(60,i+6); cout<<cost[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(35,1); cout<<"BEER";
	for(i=13;i<18;i++)
	{
	  gotoxy(20,i-10); cout<<i+1;
	  gotoxy(35,i-10); cout<<bottle[i];
	  gotoxy(60,i-10); cout<<cost[i];
	}
	gotoxy(35,10); cout<<"WINE";
	for(i=18;i<22;i++)
	{
	  gotoxy(20,i-6); cout<<i+1;
	  gotoxy(35,i-6); cout<<bottle[i];
	  gotoxy(60,i-6); cout<<cost[i];
	}
	gotoxy(35,18); cout<<"RUM";
	for(i=22;i<26;i++)
	{
	  gotoxy(20,i-2); cout<<i+1;
	  gotoxy(35,i-2); cout<<bottle[i];
	  gotoxy(60,i-2); cout<<cost[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(35,1); cout<<"CHAMPAIGNE";
	for(i=26;i<29;i++)
	{
	  gotoxy(20,i-23); cout<<i+1;
	  gotoxy(35,i-23); cout<<bottle[i];
	  gotoxy(60,i-23); cout<<cost[i];
	}
	gotoxy(35,8); cout<<"SODA";
	for(i=29;i<31;i++)
	{
	  gotoxy(20,i-19); cout<<i+1;
	  gotoxy(35,i-19); cout<<bottle[i];
	  gotoxy(60,i-19); cout<<cost[i];
	}
	gotoxy(35,14); cout<<"WATER";
	gotoxy(20,16); cout<<"32";
	gotoxy(35,16); cout<<"EVIAN BRAND";
	gotoxy(60,16); cout<<"80";
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	int answ,fc,fch[32],fe=0,z=-1;
	char fi[32][20],answe;
	RETRY:
	clrscr();
	cout<<"PRESS 0 TO GO BACK TO THE LIST OF ITEMS\n"
	    <<"PRESS 1 TO CONTINUE ";
	cin>>answ;
	switch(answ)
	{
	  case 0 : clrscr();
		   goto START;

	  case 1 : clrscr();
		   do
		   {
		     z++;
		     cout<<"ENTER THE CODE YOU WANT TO HAVE :: ";
		     cin>>fc;
		     fch[z]=cost[fc-1];
		     fe+=cost[fc-1];
		     strcpy(fi[z],bottle[fc-1]);
		     cout<<"DO YOU WANT MORE(Y/N) :: ";
		     cin>>answe;
		   } while(answe=='y'||answe=='Y');
		   clrscr();
		   for(int y=0;y<z+1;y++)
		   {
		     cout<<fi[y];
		     gotoxy(40,y+1);
		     cout<<fch[y]<<"\n";
		   }
		   cout<<"TOTAL";
		   gotoxy(40,y+1);
		   cout<<fe<<"\n";
		   cout<<"ARE YOU STAYING IN THIS HOTEL (Y/N) ? ";
		   char ans;
		   cin>>ans;
		   if(ans=='y' || ans=='Y')
		   {
		     char na[25];
		     int rn;
		     cout<<"ROOM NO. :: ";
		     cin>>rn;
		     cout<<"NAME     :: ";
		     gets(na);
		     int l=strlen(na);
		     for(i=0;i<l;i++) na[i]=toupper(na[i]);
		     //VERIFYING THE ENTERED DATA
		     f1.open("HOTEL.DAT",ios::in|ios::binary);
		     f1.read((char *)&d,sizeof(d));
		     while(f1)
		     {
		       if(d.roomno==rn && strcmp(d.name,na)==0)
		       {
			 f1.close();
			 goto BILL;
		       }
		       f1.read((char *)&d,sizeof(d));
		     }
		     f1.close();
		     cout<<"ENTERED DATA IS NOT MATCHING THE ACTUAL DATA";
		     gotoxy(25,25); cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		     BILL:
		     //ENTERING THE BAR CHARGE INTO THE FILE
		     f8.open("BILL.DAT",ios::in|ios::binary);
		     f8.read((char *)&b,sizeof(b));
		     b[rn-1].bbar = 0;
		     b[rn-1].bbar+=fe;
		     f8.close();
		     f8.open("BILL.DAT",ios::out|ios::binary);
		     f8.write((char *)&b,sizeof(b));
		     f8.close();
		     gotoxy(25,30);
		     cout<<"THE BAR BILL HAS BEEN ENTERED INTO YOUR RECORD";
		   }
		   else
		   {
		     gotoxy(25,25);
		     cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		   }
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   break;
	  default: cout<<"YOU HAVE PRESSED A WRONG KEY\nRETRY\n"
		      <<"\n\n\n\nPRESS ANY KEY TO CONTINUE\n";
		   getch();
		   goto RETRY;
	}
	clrscr();
}//**********************************************************
//	FUNCTION NAME 	  : WORKER DATA INPUT
//**********************************************************
void HOTEL::worker()
{clrscr();
textcolor(BROWN);
textbackground(WHITE);
w.open("WORKER.DAT",ios::app|ios::binary);
cout<<"ENTER A EMPLOYEE NAME \n";
cin>>wd.name;
cout<<"ENTER A TEMP ADDRSSS \n";
cin>>wd.add2;
cout<<"ENTER A PERMANENT ADDRESS \n";
cin>>wd.add1;
cout<<"ENETR A PHONE NO. \n";
cin>>wd.telno;
wd.salary=5000;
srand(time(0));
wd.id=rand();
clrscr();
cout<<"ID is "<<wd.id<<"  SALARY PER MONTH IS "<<wd.salary;
gotoxy(25,15);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
    w.write((char *)&wd,sizeof(wd));
	w.close();
}
//**********************************************************
//	FUNCTION NAME 	  : WORKER REMOVE
//**********************************************************
void HOTEL::workerout()
{   textcolor(BLACK);
    textbackground(WHITE);
	clrscr();
	int no;
	cout<<"ID NUMBER  :: ";
	cin>>no;
	w.open("WORKERCANCEL.DAT",ios::in|ios::binary);

	do w.read((char*)&wd,sizeof(wd)); while(wd.id!=no);
	cout<<"NAME                :: "<<wd.name<<"\n"
        <<"ID NO.              :: "<<wd.id<<"\n"
	    <<"TEMP ADDRESS(R)     :: "<<wd.add2<<"\n"
	    <<"TEL. NO.(R)         :: "<<wd.telno<<"\n"
	    <<"PERMANENT ADDRESS   :: "<<wd.add1<<"\n"
	    <<"BYE\n";
	//COPYING THE RECORD OF THE WORKER INTO ANOTHER FILE
	o.open("WORKERCANCEL.DAT",ios::app|ios::binary);
	strcpy(wc.name,wd.name);
	strcpy(wc.add1,wd.add1);
	strcpy(wc.add2,wd.add2);
	strcpy(wc.telno,wd.telno);
	wc.id=wd.id;
	o.write((char *)&wc,sizeof(wc));
	o.close();
	w.close();
    //DELETING THE RECORD OF THE CUSTOMER
    fstream e;
		w.open("WORKER.DAT",ios::in|ios::binary);
	e.open("W.DAT",ios::out|ios::binary);
	w.read((char *)&wd,sizeof(wd));
	while(w)
	{
	  if(wd.id!=no)
	  {
	    e.write((char *)&wd,sizeof(wd));
	    w.read((char *)&wd,sizeof(wd));
	  }
	  else w.read((char *)&wd,sizeof(wd));
	}
	e.close();
	w.close();
	w.open("WORKER.DAT",ios::out|ios::binary);
	e.open("W.DAT",ios::in|ios::binary);
	e.read((char *)&wd,sizeof(wd));
	while(e)
	{
	  w.write((char *)&wd,sizeof(wd));
	  e.read((char *)&wd,sizeof(wd));
	}
	e.close();
	w.close();
	gotoxy(25,25);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : RECORDS
//**********************************************************
void HOTEL::view_data()
{   int choice;
    clrscr();
	START:
    cout<<"\t\t\t<Which data you want to view>?"<<"\n\n\n"
	    <<"\t\t\t1)HOTEL          "<<"\n\n"
        <<"\t\t\t2)CHECK OUT      "<<"\n\n"
        <<"\t\t\t3)CANCELLED      "<<"\n\n"
        <<"\t\t\t4)WORKER IN       "<<"\n\n"
        <<"\t\t\t5)WORKER OUT     "<<"\n\n"
        <<"\t\t\t6)<===MAIN MENU ?"<<"\n\n";
    cin>>choice;
    clrscr();
	switch(choice)
	{
	  case 1 : textcolor(BROWN);
		   clrscr();
		   //DATA OF PEOPLE STAYING IN THE HOTEL
		   f1.open("HOTEL.DAT",ios::in|ios::binary);
		   f1.read((char *)&d,sizeof(d));
		   while(f1)
		   {
         cout<<"ROOM NO.         :: "<<d.roomno<<"\n"
			 <<"NAME             :: "<<d.name<<"\n"
			 <<"ADDRESS          :: "<<d.address<<"\n"
			 <<"TEL.NO           :: "<<d.telno<<"\n"
			 <<"CHECK-IN DATE    :: "<<d.d1<<'/'<<d.m1<<'/'<<d.y1<<"\n"
			 <<"ROOM TYPE        :: "<<d.roomtype<<"\n"
			 <<"ROOM CHARGE      :: "<<d.charge<<"\n\n\n";
		     getch();
		     f1.read((char *)&d,sizeof(d));
		   }
		   f1.close();
		   clrscr();
		   goto START;
	  case 2 : textcolor(LIGHTRED);
		   clrscr();
		   //DATA OF PEOPLE WHO HAVE CHECKED-OUT
		   f2.open("CUSTOMER.DAT",ios::in|ios::binary);
		   f2.read((char *)&C,sizeof(C));
		   while(f2)
		   {
		     cout<<"ROOM NO.     :: "<<C.roomno<<"\n"
			 <<"NAME             :: "<<C.name<<"\n"
			 <<"ADDRESS          :: "<<C.address<<"\n"
			 <<"TELEPHONE NO.    :: "<<C.telno<<"\n"
			<<"CHECK-IN DATE     :: "<<C.d1<<'/'<<C.m1<<'/'<<C.y1<<"\n"
			 <<"CHECK-OUT DATE   :: "<<C.d2<<'/'<<C.m2<<'/'<<C.y2<<"\n"
			 <<"CHECK-OUT TIME   :: "<<C.otime<<"\n"
			 <<"ROOM TYPE        :: "<<C.roomtype<<"\n"
             <<"ROOM CHARGE      :: "<<C.charge<<"\n\n\n";
			 getch();
		     f2.read((char *)&C,sizeof(C));
		   }
		   clrscr();
		   f2.close();
		   goto START;
	  case 3 : textcolor(YELLOW);
		   clrscr();
		   //DATA OF PEOPLE WHO HAVE CANCELLED
		   f3.open("CANCEL.DAT",ios::in|ios::binary);
		   f3.read((char *)&D,sizeof(D));
		   while(f3)
		   {
		     cout<<"NAME        :: "<<D.name<<"\n"
			 <<"ADDRESS         :: "<<D.address<<"\n"
			 <<"TELEPHONE NO.   :: "<<D.telno<<"\n\n\n";
		     getch();
		     f3.read((char *)&D,sizeof(D));
		   }
		   clrscr();
		   f3.close();
		   goto START;
       case 4: textcolor(BROWN);
		   clrscr();
		   //DATA OF WORKER
           w.open("WORKER.DAT",ios::in|ios::binary);
		   w.read((char *)&wd,sizeof(wd));
		   while(w)
		   {
             cout<<"ID             :: "<<wd.id<<"\n"
		     <<"NAME               :: "<<wd.name<<"\n"
			 <<"TEMP ADDRESS       :: "<<wd.add2<<"\n"
			 <<"PERMANENT ADDRESS  :: "<<wd.add1<<"\n"
			 <<"TELEPHONE NO.      :: "<<wd.telno<<"\n\n\n";
		     getch();
		     w.read((char *)&wd,sizeof(wd));
		   }
		   clrscr();
		   w.close();
		   goto START;
        case 5:textcolor(LIGHTBLUE);
		   clrscr();
		   //DATA OF WORKER WHO HAVE REMOVE
		   o.open("WORKERCANCEL.DAT",ios::in|ios::binary);
		   o.read((char *)&wc,sizeof(wc));
		   while(o)
		   {
             cout<<"ID             :: "<<wc.id<<"\n"
		     <<"NAME               :: "<<wc.name<<"\n"
			 <<"TEMP ADDRESS       :: "<<wc.add2<<"\n"
			 <<"PERMANENT ADDRESS  :: "<<wc.add1<<"\n"
			 <<"TELEPHONE NO.      :: "<<wc.telno<<"\n\n\n";
		     getch();
		     o.read((char *)&wc,sizeof(wc));
		   }
		   clrscr();
		   o.close();
		   goto START;
	  }
		   clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : HOTELING MENU
//**********************************************************
void HOTEL::hoteling()
{ clrscr(); int choice;
    cout<<"\t\t\t   <HOTELING MENU>    "<<"\n\n"
        <<"\t\t\t1)  BOOKING       "<<"\n\n"
        <<"\t\t\t2)  CHECK IN      "<<"\n\n"
        <<"\t\t\t3)  CHECK OUT     "<<"\n\n"
        <<"\t\t\t4)  CANCELLED     "<<"\n\n"
        <<"\t\t\t5)  TAXI SERVICE  "<<"\n\n"
        <<"\t\t\t6)  BACK          "<<"\n\n";
      cin>>choice;
      switch(choice)
      {
     case 1:booking();
		break;
	 case 2:check_in();
		break;
	 case 3:check_out();
		break;
	 case 4:cancellation();
		break;
    case 5:taxi_service();
		break;
      } clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : MEALS MENU
//**********************************************************
void HOTEL::meals()
{ clrscr();
    int choice;
    cout<<"\t\t\t   <MEALS MENU>  "<<"\n\n"
        <<"\t\t\t1) RESTAURANT "<<"\n\n"
	    <<"\t\t\t2)    BAR     "<<"\n\n"
	    <<"\t\t\t3)    BACK    "<<"\n\n";
	    cin>>choice;
	    switch(choice)
	    {
	       case 1:restaurant();
		break;
	       case 2:bar();
		break;
	    }
	     clrscr();
}
//**********************************************************
//	FUNCTION NAME 	  : EMPLOYEE SELECTION MENU
//**********************************************************
void HOTEL::employee()
{  clrscr();
    int choice;
    cout<<"\t\t\t  <SELECTION MENU> "<<"\n\n"
        <<"\t\t\t1)   WORKER   "<<"\n\n"
        <<"\t\t\t2) WORKER-OUT  "<<"\n\n"
        <<"\t\t\t3)    BACK    "<<"\n\n";
        cin>>choice;
        switch(choice)
        {
        case 1:worker();
        break;
        case 2:workerout();
        break;
        }
         clrscr();
}
void main()
{clrscr();
gotoxy(1,2);
cout<<"********************************************************************************\n\n";
cputs("                          COMPUTER SCIENCE PROJECT WORK\n");gotoxy(1,6);textcolor(BLUE);
cputs("                          WELCOME TO THE RA.1 SOFTWARES \n");
gotoxy(1,9);textcolor(GREEN);
cputs("                          SCHOOL:-ARMY PUBLIC SCHOOL NO-2 \n");
gotoxy(1,12);textcolor(CYAN);
cputs("                          SUBJECT TEACHER:-MR.M.K.RAHA \n");
gotoxy(1,15);textcolor(RED);
cputs("                          PROJECT ON HOTEL MANAGEMENT \n");
gotoxy(1,18);textcolor(MAGENTA);
cputs("                          BY SUSHIL SHARMA \n");
gotoxy(1,19);textcolor(BROWN);
cputs("                          CLASS XII B \n");
gotoxy(1,20);textcolor(YELLOW);
cputs("                          YEAR: 2016-2017 \n");textcolor(LIGHTGRAY);
cout<<"\n********************************************************************************\n";
gotoxy(30,24);
cout<<"LOADING!!!!!";
getch();
clrscr();
char password[6];
int strength=0;
cout<<"\t\t\t\tLOGIN MENU\n\n";
cout<<" PLEASE ENTER YOUR USER PASSWORD ";
while(strength<6)
    {password[strength]=getch();
    cout<<"*";
    ++strength;}
   if (strcmp(password,"sushil")==0)
    {clrscr();
    cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t    * WELCOME TO RESORT *    ";
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t    * ULTIMATE PARADISE *    ";
	cout<<"\n\t\t\t****************************";
    gotoxy(25,15);
	cout<<"PRESS ANY KEY TO CONTINUE";
	getch();
	clrscr();
	// MAIN OPTIONS
	// FOR GOING TO THE SPECIFIED OPTION
	LABEL:
	    clrscr();
	int menu;
	cout<<endl;
	cout<<"\n\t\t\t\t*************";
    cout<<"\n\t\t\t\t* MAIN MENU *";
    cout<<"\n\t\t\t\t*************"<<endl;
	cout<<"\t\t\t\t1. HOTELING "<<"\n\n"
	    <<"\t\t\t\t2. MEALS     "<<"\n\n"
        <<"\t\t\t\t3. EMPLOYEE  "<<"\n\n"
        <<"\t\t\t\t4. RECORDS   "<<"\n\n"
        <<"\t\t\t\t5.   EXIT    "<<"\n\n";
        cin>>menu;
        switch(menu)
        {case 1:H.hoteling();
            break;
	    case 2:H.meals();
            break;
            case 3:H.employee();
            break;
            case 4:H.view_data();
            break;
            case 5:exit(0);
         } goto LABEL;}
else
    {  cout<<"\ninvalid!!!!!!!!! login attempt.Please try again.\n"<<'\n';
    }
getch();
}
