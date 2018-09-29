#include <iostream>
#include <ctime>
#include <conio.h>
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
    int type;
} _ElementsCoordinates[2500];


// Konfiguracja

int N=10;                               // N wielkość planszy
int Elements=4;                         // Elements ilość różnych elementów

// Kordynaty

int y1=0;                              
int x1=0;

// Wynik

int score=0;

void randomElements()                   // Generowanie typu elementu do struktury 
{
    int count=0;                        // Literator
    int randType;                       // Rodzaj elementu

    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
                randType=rand()%Elements;       //Generuje
                _ElementsCoordinates[count].type=randType;

                if (j>=2)                       
                {                               //Sprawdza wiersz czy sa 3 powtarzające sie elementy
                    while(_ElementsCoordinates[count].type==_ElementsCoordinates[count-1].type && _ElementsCoordinates[count-1].type==_ElementsCoordinates[count-2].type) 
                    {
                    randType=rand()%Elements;
                    _ElementsCoordinates[count].type=randType;
                    }
                }
                if (i>=2)
                {                               //Sprawdza kolumne czy sa 3 powtarzające sie elementy
                    while(_ElementsCoordinates[count].type==_ElementsCoordinates[count-N].type && _ElementsCoordinates[count-N].type==_ElementsCoordinates[count-2*N].type) 
                    {
                    randType=rand()%Elements;
                    _ElementsCoordinates[count].type=randType;
                    }
                }

            count++;
        }

    } 
}
void boardDraw()                        // Rysowanie planszy
{
    int count=0;

    HANDLE hOut;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    
    system("CLS");
    SetConsoleTextAttribute(hOut,7);

    cout<<endl<<endl<<endl;

    cout<<"                         "<<char(218);                    // Górne oobramowanie
    for (int i=0; i<N; i++)
        cout<<char(196);
    cout<<char(191)<<endl;

    for (int k=0; k<N; k++)             // Środkowe obramowanie
    {
        cout<<"                         "<<char(179);
        for (int l=0; l<N; l++)
        {
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );    // Standardowy kolor

            switch (_ElementsCoordinates[count].type)
            {
                case 0:
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);           //Kolor dla 1 elementu
                    break;
                case 1:
                    SetConsoleTextAttribute( hOut, FOREGROUND_RED);             //Kolor dla 2 elementu
                    break;
                case 2:
                    SetConsoleTextAttribute( hOut, FOREGROUND_BLUE);            //Kolor dla 3 elementu
                    break;
                case 3:
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED );  //Kolor dla 4 elementu
                    break;
                default:
                    break;
            }

             if (l==x1 && k==y1)
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );                // Kolor dla elementu gracza
            if (_ElementsCoordinates[count++].type!=10)
                cout<<char(158);
            else
                cout<<" ";
            
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        }
        cout<<char(179);
        cout<<endl;
    }                               
    cout<<"                         "<<char(192);
    for (int i=0; i<N; i++)             // Dolne obramowanie
        cout<<char(196);
    cout<<char(217);

    cout<<endl<<endl;
    cout<<"               SCORE: "<<score<<endl;
}
void gravity()                  // Grawitacja dla elementów
{
    for (int k=0; k<N; k++)
        for (int j=N; j>=0; j--)
            for (int i=N; i>=0; i--)
            {
                if (_ElementsCoordinates[i+j*N].type>10)                    // Jeżeli wartość nie będzie w zakresie elementów to wygeneruje nową wartość 
                    _ElementsCoordinates[i+j*N].type=rand()%Elements;

                if (_ElementsCoordinates[i+j*N].type==10)
                {
                    _ElementsCoordinates[i+j*N].type=_ElementsCoordinates[i+j*N-N].type;            // Grawitacja (przesuwanie elementów w dół)
                    _ElementsCoordinates[i+j*N-N].type=10;
                    if (_ElementsCoordinates[i+j*N].type!=_ElementsCoordinates[i+j*N-N].type)
                    {
                    Sleep(100);                                             // Animacja
                    boardDraw(); 
                    }
                }
            }   
    
      
        
        for (int i=N*N; i>=0; i--)
            if (_ElementsCoordinates[i].type==10)
            {
                _ElementsCoordinates[i].type=rand()%Elements;               // Generuje nowe elementy na górze mapy
                Sleep(100);
                boardDraw();   
            }
    
}
void check()            // Sprawdzenie czy są 3 takie same elementy obok siebie
{
    int boolean=true;
    while(boolean)
    {  
        boolean=false;
        int count=0;

        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
            {
                if (j>=2)       // Sprawdza poziomo                                                  
                    if(_ElementsCoordinates[count].type==_ElementsCoordinates[count-1].type && _ElementsCoordinates[count-1].type==_ElementsCoordinates[count-2].type)      
                    {   
                        boolean=true;            
                        _ElementsCoordinates[count].type=10;
                        _ElementsCoordinates[count-1].type=10;
                        _ElementsCoordinates[count-2].type=10;
                        score+=10;          // Zwiększa wynik              
                    }
                if (i>=2)      // Sprawdza pionowo                        
                    if(_ElementsCoordinates[count].type==_ElementsCoordinates[count-N].type && _ElementsCoordinates[count-N].type==_ElementsCoordinates[count-2*N].type) 
                    {
                        boolean=true;
                        _ElementsCoordinates[count].type=10;
                        _ElementsCoordinates[count-N].type=10;
                        _ElementsCoordinates[count-2*N].type=10;
                        score+=10;          // Zwiększa wynik              
                    }
            count++;
            }  
        gravity();      // Tworzy nowe elementy 
    }
}
void exchange()                         // Zamiana elementów
{
    int change;
    int click=getch();
    if (click == 0|| click ==224) click = getch();
        switch (click)
        {
            case 80:
                if (y1<N-1)
                {
                    change = _ElementsCoordinates[x1+y1*N].type;             // Dół  
                    _ElementsCoordinates[x1+y1*N].type=_ElementsCoordinates[x1+N+y1*N].type;
                    _ElementsCoordinates[x1+N+y1*N].type=change;
                }
                break;
            
            case 72:
                if (y1>0)
                {                   
                    change = _ElementsCoordinates[x1+y1*N].type;             // Góra 
                    _ElementsCoordinates[x1+y1*N].type=_ElementsCoordinates[x1-N+y1*N].type;
                    _ElementsCoordinates[x1-N+y1*N].type=change;
                }
                break;  
            case 75: 
                if (x1>0)      
                {                                
                    change = _ElementsCoordinates[x1+y1*N].type;              // Lewo
                    _ElementsCoordinates[x1+y1*N].type=_ElementsCoordinates[x1-1+y1*N].type;
                    _ElementsCoordinates[x1-1+y1*N].type=change;
                }
                break;
            case 77:   
                if (x1<N-1)
                {                 
                    change = _ElementsCoordinates[x1+y1*N].type;              // Prawo        
                    _ElementsCoordinates[x1+y1*N].type=_ElementsCoordinates[x1+1+y1*N].type;
                    _ElementsCoordinates[x1+1+y1*N].type=change;
                }
                break;
        }
    check();
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
                exchange();
                break;
            case 80:                    // Dól
                if (y1<N-1)               
                    y1++;
                break;
            case 72:                    // Góra
                if (y1>0)
                    y1--;
                break;  
            case 75:                    // Lewo                    
                if (x1>0)   
                    x1--;
                break;
            case 77:                    // Prawo
                if (x1<N-1)
                    x1++;
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
