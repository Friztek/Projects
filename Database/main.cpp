#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct _menu
{
    string element;
} _Menu[4];

struct _osoba
{
    char Nazwisko[20], Imie[20], Pesel[11];
    unsigned long long dzienUrodzenia, miesiacUrodzenia, rokUrodzenia;
    int dzienRozp, miesiacRozp, rokRozp, Id;
    float Wzrost;
    string plec;
} _Osoba[1000];

struct _wybory
{
    string wybor;
} _Wybory[4];

struct _rosmal
{
    string rosmal;
} _Rosmal[2];

char Nazwisko[20], Imie[20], Pesel[11];
int dzienUrodzenia, miesiacUrodzenia, rokUrodzenia, dzienRozp, miesiacRozp, rokRozp, Id, MaxId;
float Wzrost;
string plec;

bool warunek1;
int ile=0;
int ileNazw=0;
int pozi=0;
int pozii=0;
string dane_all[1000];
string nazwiska[1000];
int Mezczyzi[1000];
int Kobiety[1000];
int k=0;
int m=0;
int licz_el=4;
int poz=0;
unsigned long long daty[1000];
unsigned long long pomocdaty[1000];

fstream plik;


void drukuj(int licz_el, int pozycja, string tekst, int help)
{
    _Menu[0].element = "Wyswietl";
    _Menu[1].element = "Dodaj";
    _Menu[2].element = "Usun";
    _Menu[3].element = "Wyjdz";
    _Wybory[0].wybor = "Wedlug Id";
    _Wybory[1].wybor = "Wedlug Nazwiska";
    _Wybory[2].wybor = "Wedlug Daty urodzenia";
    _Wybory[3].wybor = "Wedlug Plci";
    _Rosmal[0].rosmal="Rosnaco";
    _Rosmal[1].rosmal="Malejaco";

    system("CLS");
    cout<<tekst<<endl;
    if (help==0)
        cout<<endl;
    if (help==1)
        cout<<"  Id  Nazwisko     Imie         DataUro     DataRozp    Pesel         Wzr  Plec"<<endl<<endl;
        for(int i=0; i<licz_el; i++)
        {
            if(i==pozycja)
                cout<<"* ";
            else
                cout<<"  ";
            if (help==0)
                cout<<_Menu[i].element<<endl;
            else if (help==1)
                cout<<dane_all[i]<<endl;
            else if (help==2)
                cout<<_Wybory[i].wybor<<endl;
            else if (help==3)
                cout<<_Rosmal[i].rosmal<<endl;
        }
}

void wybieranie()
{
    poz=0;
    char klik;
    bool warunek=true;
    drukuj(4, poz, " ------------------------------ MENU WYBORU ----------------------------------",0);
    do{
        klik=getch();
        switch (klik)
        {
            case 72:
                poz--;
                break;
            case 80:
                poz++;
                break;
        }
        if(poz<0)
            poz+=licz_el;
        else poz%=licz_el;
            drukuj(4, poz, " ------------------------------ MENU WYBORU ----------------------------------",0);
        if(klik==13)
        {
            cout<<"Wcisnieto: "<<_Menu[poz].element<<endl;
            Sleep(600);
            warunek = false;
        }
    } while(warunek);
}

void wybieranie2()
{
    pozi=0;
    char klik;
    bool warunek=true;
    drukuj(ile,pozi," ------------------------- WYBIERZ REKORD DO USUNIECIA -------------------------",1);
    do{
        klik=getch();
        switch (klik)
        {
            case 72:
                pozi--;
                break;
            case 80:
                pozi++;
                break;
        }
        if(pozi<0)
            pozi+=ile;
        else pozi%=ile;
            drukuj(ile,pozi," ------------------------- WYBIERZ REKORD DO USUNIECIA -------------------------",1);
        if(klik==13)
        {
            plik.open("dane.txt", ios::out | ios::trunc);
            for (int i=0; i<ile; i++)
            {
                if ((i==0 || i==pozi) || (i==1 && pozi==0))
                    1+1;
                else
                    plik<<endl;
                if (i!=pozi)
                    plik<<dane_all[i];
            }
            Sleep(600);
            warunek = false;
            plik.close();
        }
    } while(warunek);
}

void wybieranie3()
{
    pozi=0;
    char klik;
    bool warunek=true;
    drukuj(4, pozi, " ------------------------- Wybierz metode wyswietlania -------------------------",2);
    do{
        klik=getch();
        switch (klik)
        {
            case 72:
                pozi--;
                break;
            case 80:
                pozi++;
                break;
        }
        if(pozi<0)
            pozi+=4;
        else pozi%=4;
            drukuj(4, pozi, " ------------------------- Wybierz metode wyswietlania -------------------------",2);
        if(klik==13)
        {
            cout<<"Wcisnieto: "<<_Wybory[pozi].wybor<<endl;
            Sleep(600);
            warunek = false;
        }
    } while(warunek);
}

void wybieranie4()
{
    pozii=0;
    char klik;
    bool warunek=true;
    drukuj(2, pozii, " ------------------------- Wybierz metode wyswietlania -------------------------",3);
    do{
        klik=getch();
        switch (klik)
        {
            case 72:
                pozii--;
                break;
            case 80:
                pozii++;
                break;
        }
        if(pozii<0)
            pozii+=2;
        else pozii%=2;
            drukuj(2, pozii, " ------------------------- Wybierz metode wyswietlania -------------------------",3);
        if(klik==13)
        {
            cout<<"Wcisnieto: "<<_Rosmal[pozii].rosmal<<endl;
            Sleep(600);
            warunek = false;
        }
    } while(warunek);
}
void wczytaj()
{
     plik.open("dane.txt",ios::in);
     ileNazw=m=k=0;
     while (!plik.eof())
     {
        plik>>Id;
        plik>>_Osoba[Id].Nazwisko>>_Osoba[Id].Imie>>_Osoba[Id].dzienUrodzenia>>_Osoba[Id].miesiacUrodzenia>>_Osoba[Id].rokUrodzenia>>_Osoba[Id].dzienRozp>>_Osoba[Id].miesiacRozp>>_Osoba[Id].rokRozp>>_Osoba[Id].Pesel>>_Osoba[Id].Wzrost>>_Osoba[Id].plec;
        string R;
        ostringstream convert;
        convert << Id;
        R = convert.str();
        if (_Osoba[Id].plec=="M")
            Mezczyzi[m++]=ileNazw;
        else
            Kobiety[k++]=ileNazw;
        daty[ileNazw]=(_Osoba[Id].dzienUrodzenia + _Osoba[Id].miesiacUrodzenia * 100 + _Osoba[Id].rokUrodzenia * 10000)*1000;
        pomocdaty[ileNazw]=daty[ileNazw]+ileNazw;
        nazwiska[ileNazw++]=_Osoba[Id].Nazwisko + R;
     }
     MaxId=Id;
     plik.close();
}

void wyswietlId()
{
    string liniki[1000];
    int i=0;
    Sleep(700);
    system("CLS");
    plik.open("dane.txt",ios::in);
    cout<<" Id  Nazwisko     Imie         DataUro     DataRozp    Pesel         Wzr  Plec"<<endl<<endl;
    while (!plik.eof())
    {
        string dane;
        getline(plik, dane);
        if (pozii==0)
            cout<<" "<<dane<<endl;
        if (pozii==1)
            liniki[i++]=dane;
    }
    plik.close();
    if (pozii==1)
        for (int j=i-1; j>=0; j--)
            cout<<" "<<liniki[j]<<endl;
    getch();
}
void pomocNazwiska(int i)
{
    int wynik[1000];
    sort(nazwiska, nazwiska+ileNazw);
    string pomoc=nazwiska[i];
    int ileLiter=0;
    int litera=0;
    while(isalpha(pomoc[litera++]))
        ileLiter++;
    pomoc.erase(0,ileLiter);
    wynik[i]=atoi(pomoc.c_str());
    cout<<" "<<wynik[i];
    int pomoc2=0;
    for (int j=wynik[i]; j>=1; j/=10)
        pomoc2++;
    if (pomoc2==0)
        pomoc2=1;
    for (int j=0; j<4-pomoc2; j++)
        cout<<" ";
    cout<<_Osoba[wynik[i]].Nazwisko;

    for (int j=0; j<13-strlen(_Osoba[wynik[i]].Nazwisko); j++)
        cout<<" ";
    cout<<_Osoba[wynik[i]].Imie;
    for (int j=0; j<13-strlen(_Osoba[wynik[i]].Imie); j++)
        cout<<" ";
    cout<<_Osoba[wynik[i]].dzienUrodzenia<<" "<<_Osoba[wynik[i]].miesiacUrodzenia<<" "<<_Osoba[wynik[i]].rokUrodzenia;
    if (_Osoba[wynik[i]].dzienUrodzenia<10 && _Osoba[wynik[i]].miesiacUrodzenia<10)
        cout<<"    ";
    else if (_Osoba[wynik[i]].dzienUrodzenia>=10 && _Osoba[wynik[i]].miesiacUrodzenia>=10)
        cout<<"  ";
    else
        cout<<"   ";
    cout<<_Osoba[wynik[i]].dzienRozp<<" "<<_Osoba[wynik[i]].miesiacRozp<<" "<<_Osoba[wynik[i]].rokRozp;
    if (_Osoba[wynik[i]].dzienRozp<10 && _Osoba[wynik[i]].miesiacRozp<10)
        cout<<"    ";
    else if (_Osoba[wynik[i]].dzienRozp>=10 && _Osoba[wynik[i]].miesiacRozp>=10)
        cout<<"  ";
    else
        cout<<"   ";
    cout<<_Osoba[wynik[i]].Pesel<<"   "<<_Osoba[wynik[i]].Wzrost<<"   "<<_Osoba[wynik[i]].plec<<endl;

}
void wyswietlNazwiska()
{
    system("CLS");
    cout<<" Id  Nazwisko     Imie         DataUro     DataRozp    Pesel         Wzr  Plec"<<endl<<endl;
    if (pozii==1)
        for (int i=0; i<ileNazw; i++)
            pomocNazwiska(i);
    else
        for (int i=ileNazw-1; i>0; i--)
            pomocNazwiska(i);
    getch();

}

void wyswietlPlec()
{
    string linijki[1000];
    int i=0;
    system("CLS");
    plik.open("dane.txt",ios::in);
    cout<<" Id  Nazwisko     Imie         DataUro     DataRozp    Pesel         Wzr  Plec"<<endl<<endl;
    while (!plik.eof())
    {
        string dane;
        getline(plik, dane);
        linijki[i++]=dane;
    }
    plik.close();
    if (pozii==1)
        for (int i=0; i<k; i++)
            cout<<" "<<linijki[Kobiety[i]]<<endl;
    for (int i=0; i<m; i++)
        cout<<" "<<linijki[Mezczyzi[i]]<<endl;
    if (pozii==0)
        for (int i=0; i<k; i++)
            cout<<" "<<linijki[Kobiety[i]]<<endl;
    getch();
}
void wyswietlDateUrodzenia()
{
    sort(pomocdaty, pomocdaty+ileNazw);
    sort(daty, daty+ileNazw);
    int wynik[1000];
    for (int i=0; i<ileNazw; i++)
        wynik[i]=pomocdaty[i]-daty[i];

    string liniki[1000];
    int i=0;
    Sleep(700);
    system("CLS");
    plik.open("dane.txt",ios::in);
    cout<<" Id  Nazwisko     Imie         DataUro     DataRozp    Pesel         Wzr  Plec"<<endl<<endl;
    while (!plik.eof())
    {
        string dane;
        getline(plik, dane);
        liniki[i++]=dane;
    }
    plik.close();
    if (pozii==0)
        for (int j=0; j<i; j++)
            cout<<" "<<liniki[wynik[j]]<<endl;
    else
        for (int j=i-1; j>0; j--)
            cout<<" "<<liniki[wynik[j]]<<endl;

    getch();
}

void dodaj()
{
    system("CLS");

    do{
        warunek1=true;
        cout<<"Podaj Nazwisko: ";
        cin.clear();
        cin.sync();
        cin.getline(Nazwisko,20);
        if (!isalpha(Nazwisko[0]))
            warunek1=false;

        for (int i=0; i<strlen(Nazwisko); i++)
            if (!isalpha(Nazwisko[i]))
                warunek1=false;

        if (!warunek1)
                cout<<"Prosze podac poprawne Nazwisko!"<<endl;
    } while (!warunek1);
    cout<<Nazwisko<<endl;

    do{
        warunek1=true;
        cout<<"Podaj Imie: ";
        cin.clear();
        cin.sync();
        cin.getline(Imie,20);
        if (!isalpha(Imie[0]))
            warunek1=false;

        for (int i=0; i<strlen(Imie); i++)
            if (!isalpha(Imie[i]))
                warunek1=false;

        if (!warunek1)
                cout<<"Prosze podac poprawne Imie!"<<endl;
    } while (!warunek1);
    cout<<Imie<<endl;

    do{
        warunek1=true;
        cout<<"Podaj Date Urodzenia (dd mm rrrr): ";
        cin.clear();
        cin.sync();
        cin>>dzienUrodzenia>>miesiacUrodzenia>>rokUrodzenia;
        if ((dzienUrodzenia<1 || dzienUrodzenia>31 ) || (miesiacUrodzenia<1 || miesiacUrodzenia>12) || (rokUrodzenia>2018 || rokUrodzenia<1900))
            warunek1=false;

        if (!warunek1)
            cout<<"Prosze podac dobra date!"<<endl;
    } while(!warunek1);
    cout<<dzienUrodzenia<<" : "<<miesiacUrodzenia<< " : "<<rokUrodzenia<<endl;

    int pomoc1[2];
    if (rokUrodzenia>=2000)
    {
        pomoc1[0]=(rokUrodzenia-2000)/10;
        pomoc1[1]=(rokUrodzenia-2000)-pomoc1[0]*10;
    }
    else
    {
        pomoc1[0]=(rokUrodzenia-1900)/10;
        pomoc1[1]=(rokUrodzenia-1900)-pomoc1[0]*10;
    }

    do{
        warunek1=true;
        cout<<"Podaj Date rozpoczecia pracy (dd mm rrrr): ";
        cin.clear();
        cin.sync();
        cin>>dzienRozp>>miesiacRozp>>rokRozp;
        if ((dzienRozp<1 || dzienRozp>31 ) || (miesiacRozp<1 || miesiacRozp>12) || (rokRozp>2018 || rokRozp<1900))
            warunek1=false;

        if (!warunek1)
            cout<<"Prosze podac dobra date!"<<endl;
    } while(!warunek1);
    cout<<dzienRozp<<" : "<<miesiacRozp<< " : "<<rokRozp<<endl;

    do{
        warunek1=true;
        cout<<"Podaj Wzrost (cm): ";
        cin.clear();
        cin.sync();
        cin>>Wzrost;
        if (Wzrost<50 || Wzrost > 250)
            warunek1=false;
        if (!warunek1)
                cout<<"Prosze podac poprawny wzrost!"<<endl;
    } while (!warunek1);

    cout<<Wzrost<<endl;

    do{
        warunek1=false;
        cout<<"Podaj swoja plec: ";
        cin.clear();
        cin.sync();
        cin>>plec;
        if (plec[0]=='k')
            plec[0]='K';
        if (plec[0]=='m')
            plec[0]='M';

        if (plec[0]=='K' || plec[0]=='M')
            warunek1=true;

        if (!warunek1)
                cout<<"Prosze podac poprawna plec!"<<endl;
    } while (!warunek1);

    do{
        warunek1=true;
        cout<<"Podaj Pesel: ";
        cin>>Pesel;
        if ((((Pesel[0]-48)+(Pesel[1]-48)*3+(Pesel[2]-48)*7+(Pesel[3]-48)*9+(Pesel[4]-48)+(Pesel[5]-48)*3+(Pesel[6]-48)*7+(Pesel[7]-48)*9+(Pesel[8]-48)+(Pesel[9]-48)*3+(Pesel[10]-48))%10!=0)||(strlen(Pesel)!=11))
            warunek1=false;
        if (Pesel[0]-48!=pomoc1[0] || Pesel[1]-48!=pomoc1[1])
            warunek1=false;
        for (int i=0; i<10; i++)
            if (isalpha(Pesel[i]))
                warunek1=false;
        if (!warunek1)
                cout<<"Prosze podac poprawny Pesel!"<<endl;
    } while (!warunek1);

    plik.open("dane.txt",ios::app);
    plik<<endl;
    plik<<++MaxId;
    int pomoc=0;
    for (int i=MaxId; i>=1; i/=10)
        pomoc++;
    if (pomoc==0)
        pomoc=1;
    for (int i=0; i<4-pomoc; i++)
        plik<<" ";
    plik<<Nazwisko;
    for (int i=0; i<13-strlen(Nazwisko); i++)
        plik<<" ";
    plik<<Imie;
    for (int i=0; i<13-strlen(Imie); i++)
        plik<<" ";
    plik<<dzienUrodzenia<<" "<<miesiacUrodzenia<<" "<<rokUrodzenia;
    if (dzienUrodzenia<10 && miesiacUrodzenia<10)
        plik<<"    ";
    else if (dzienUrodzenia>=10 && miesiacUrodzenia>=10)
        plik<<"  ";
    else
        plik<<"   ";
    plik<<dzienRozp<<" "<<miesiacRozp<<" "<<rokRozp;
    if (dzienRozp<10 && miesiacRozp<10)
        plik<<"    ";
    else if (dzienRozp>=10 && miesiacRozp>=10)
        plik<<"  ";
    else
        plik<<"   ";

    plik<<Pesel<<"   "<<Wzrost<<"   "<<plec[0];
    plik.close();
    poz=99;
    pozi=99;
}

void usun()
{
    system("CLS");
    plik.open("dane.txt",ios::in);
    ile=0;
    while (!plik.eof())
    {
        string dane;
        getline(plik, dane);
        dane_all[ile++]=dane;
    }
    plik.close();
    wybieranie2();
    system("CLS");
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"                               ---USUNIETO---";
    Sleep(1000);
}

void koniec()
{
    system("CLS");
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"                               ---WYCHODZENIE---"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    exit(0);
}
int main()
{
    while(poz!=3)
    {
        wczytaj();
        wybieranie();
        if (poz==1)
            dodaj();
        else if (poz==2)
            usun();
        else if (poz==3)
            koniec();
        else if (poz==0)
        {
            wybieranie3();
            wybieranie4();
            if (pozi==0)
                wyswietlId();
            else if (pozi==1)
                wyswietlNazwiska();
            else if (pozi==2)
                wyswietlDateUrodzenia();
            else if (pozi==3)
                wyswietlPlec();
        }
    }
    return 0;
}
