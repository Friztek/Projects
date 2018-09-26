#include <iostream>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;


void MaximizeOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // This gets the value Windows uses to identify your output window
    ShowWindow(consoleWindow, SW_MAXIMIZE); // this mimics clicking on its' maximize button
}
 
void RestoreOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // Same as above
    ShowWindow(consoleWindow, SW_RESTORE); // this mimics clicking on its' maximize for a second time, which puts it back to normal
}

struct _elementsCoordinates{            //Struktura z informacjami o elementach
    int x;
    int y;
    int type;
} _ElementsCoordinates[2500];


//Konfiguracja

int N=20;                               // N wielkość planszy
int Elements=5;                         // Elements ilość różnych elementów
int y1=0;
int x1=0;

void randomElements()                   // Generowanie typu elementu do struktury 
{
    int count=0;


    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
        {
            int randType=rand()%Elements;                   
            _ElementsCoordinates[count].x=i;
            _ElementsCoordinates[count].y=j;
            _ElementsCoordinates[count++].type=randType;
        }

}

void boardDraw()                        // Rysowanie planszy
{
    HANDLE hOut;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    
    system("CLS");
    SetConsoleTextAttribute(hOut,7);

    cout<<endl;

    cout<<char(218);                    // Górne oobramowanie
    for (int i=0; i<N; i++)
        cout<<char(196);
    cout<<char(191)<<endl;

    for (int i=0; i<N; i++)             // Środkowe obramowanie
    {
        cout<<char(179);
        for (int j=0; j<N; j++)
        {
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );    // Standardowy kolor
            if (i==x1 && j==y1)
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE );                 // Kolor dla elementu gracza
            cout<< _ElementsCoordinates[j+i*10].type;
        }
        cout<<char(179);
        cout<<endl;
    }                               
    cout<<char(192);
    for (int i=0; i<N; i++)             // Dolne obramowanie
        cout<<char(196);
    cout<<char(217);
}

void control()                          // Sterowanie
{   
    system("CLS");
    while(true)
    {
        boardDraw();
        char klik=getch();
        switch (klik)
        {
            case 13:                    // Enter
                break;
            case 80:
                if (x1<N-1)             // Prawo
                    x1++;
                break;

            case 72:                    // Lewo
                if (x1>0)
                    x1--;
                break;  
            case 75:                    // Dół
                if (y1>0)   
                    y1--;
                break;
            case 77:                    //Góra
                if (y1<N-1)
                    y1++;
                break;
            }
    }
}


int main()
{
    MaximizeOutputWindow();
    srand(time(NULL));
    randomElements();
    control();

   return 0; 
}
