// Program to implement an interactive Tic Tac Toe game in C++ language

// NAME               - PRIYANSHU GOYAL
// UNIVERSITY ROLL NO - 2014787

#include<iostream>
#include<string>
#include<iomanip>
#include<time.h>
#include<conio.h>
using namespace std;

// structure to store the present date
typedef struct date_info
{
    int d,m,y;   // d will store no of days of the month, m will store current month, y will store the current year
}date;

// Function that will initialize, the grid of the game to '.', each time a new game begins
void setGrid(char gr[][3])   // grid - formal parameter - 2D array that stores the current grid (board) of the game
{
    for(int i = 0; i < 3; i++)      // i keeps track of number of rows of grid
    {
        for(int j = 0; j < 3; j++)  // j keeps track of number of columns of grid
        {
            gr[i][j] = '.';         // storing '.' at the ith row and jth column of the grid
        }
    }
}

/* Function that will calculate the present date and store it in a structure, whose address
   this function takes as a parameter in a pointer of type date*/
void return_date(date* d)   // d is a pointer - stores address of a date type structure
{
    time_t present;
    time(&present);
    struct tm *point = localtime(&present);   // using inbuilt function to store the current date and storing its address
    d->d = point->tm_mday;
    d->m = point->tm_mon + 1;                 // using structure pointer to store current month
    d->y = point->tm_year + 1900;
}

// Function to print the assignment title, name, and date
void frontDesign()
{
    date today;   // today is a structure of type date to store present date
    return_date(&today);
    cout<<"\n\t\t\t\t      _____________________________________________";
    cout<<"\n\t\t\t\t     |                                             |";
    cout<<"\n\t\t\t\t     |      ASSIGNMENT TITLE - TIC TAC TOE GAME    |";
    cout<<"\n\t\t\t\t     |                                             |";
    cout<<"\n\t\t\t\t     |              PREPARED BY -                  |";
    cout<<"\n\t\t\t\t     |                                             |";
    cout<<"\n\t\t\t\t     |      NAME                - PRIYANSHU GOYAL  |";
    cout<<"\n\t\t\t\t     |      SEMESTER            - 3rd              |";
    cout<<"\n\t\t\t\t     |      SECTION            -  A                |";
    cout<<"\n\t\t\t\t     |      UNIVERSITY ROLL NO. - 2014787          |";
    cout<<"\n\t\t\t\t     |      ASSIGNMENT DATE     - 09/09/2020       |";
    cout<<"\n\t\t\t\t     |      TODAY'S DATE        - "<<setw(2)<<setfill('0')<<today.d<<"/"<<setw(2)<<setfill('0')<<today.m<<"/"<<setw(4)<<today.y<<"       |";
    cout<<"\n\t\t\t\t     |_____________________________________________|\n\n";
    cout<<"\n\n\n\t\t\t\t\t  Welcome To The  Tic Tac Toe Game\n\n";
    cout<<"\nPress any key to begin the game\n";
    getch();         // inbuilt function - takes a charcter as an input from the user without showing it on screen
    system("cls");   // inbuilt function that will clear the entire screen
}

// Function that will print the updated grid, every time a player makes a turn
void dispGrid(char grid[][3])   // grid - formal parameter - 2D array that stores the current grid (board) of the game
{
    cout<<"\t\t\t";
    for(int i = 0; i < 3; i++)       // i keeps track of no of rows
    {
        for(int j = 0; j < 3; j++)   // j keeps track of no of columns
        {
            if(j < 2 && i < 2)
                cout<<"_"<<grid[i][j]<<"_"<<"|";
            else if(i < 2)
                cout<<"_"<<grid[i][j]<<"_";
            else if(j < 2)
                cout<<" "<<grid[i][j]<<" "<<"|";
            else
                cout<<" "<<grid[i][j]<<" ";
        }
        cout<<endl<<"\t\t\t";
    }
    cout<<"__________________________________________________________________\n\n\n";
}

// Function to input row and column number every time a player makes a turn
void inputRowCol(int *r, int *c, char cur, char grid[][3])
{

    // r, c, cur, grid are formal parameters
    // r - pointer, stores address of row no,  c - pointer,stores address of column no
    // cur - stores character(0 or X) of current chance, grid - stores the grid (board) of the game

    int row = *r,  col = *c;   // row stores row no, col stores col no
    while((row < 0 || row > 2) || (col < 0 || col > 2))
    {
        cout<<"\n\t\t\t"<<"Choose a row no (0 to 2):\n";
        cin>>row;
        if((row < 0) || (row > 2))
        {
            cout<<endl<<"\t\t\t"<<row<<" is not a valid row\n";
            continue;
        }
        cout<<"\n\t\t\tChoose a column no (0 to 2):\n";
        cin>>col;
            col = (int)col;
        if((col < 0) || (col > 2))
        {
            cout<<"\n\t\t\t"<<col<<" is not a valid column\n";
            continue;
        }
        if(grid[row][col] != '.')
        {
            cout<<"\n\t\t\tThis location is already occupied\n";
            row = -1;
            col = -1;
        }
    }
    grid[row][col] = cur;   // storing the chracter(0 or X) of current chance at entered row and column in the grid
    *r = row;               // changing the value of row no at its address
    *c = col;
}

// Function to check whether any player has won the game
int check(int r, int c, char current_ch, char grid[][3])
{

    //  r - stores row no, c - stores column no,
    //  current_ch - stores current entered character(0 or X), grid - stores the current board of the game

    int st = 1;   //  to store status of game (1 if game is won, else 0)
    for(int i = 0; i < 3; i++)
    {
        if(grid[i][c] != current_ch)   // checking for win in the same column
        {
            st = 0;
            break;
        }
    }
    if(!st)
    {
        st = 1;
        for(int i = 0; i < 3; i++)
        {
            if(grid[r][i] != current_ch)   // checking for win in the same row
            {
                st = 0;
                break;
            }
        }
    }
    if(!st)
    {
        st = 1;
        for(int i = 0; i < 3; i++)
        {
            if(grid[i][2-i] != current_ch)   // checking for win in the right diagnol
            {
                st = 0;
                break;
            }
        }
    }
    if(!st && (r == c))
    {
        st = 1;
        for(int i = 0; i < 3; i++)
        {
            if(grid[i][i] != current_ch)   // checking for win in the left diagnol
            {
                st = 0;
                break;
            }
        }
    }
    return st;
}

/* Function to check whether the user wants to play the game again and returns 1 or 0 to
   start function depending on user's choice */
int playAgain()
{
    char playagain;  // variable to store the choice of user to play the game again or not
    cout<<"\n\t\t\tWould you like to play again (Y or N)\n";
    cin>>playagain;
    while(playagain != 'Y' && playagain != 'N')
    {
        cout<<endl<<"\t\t\t"<<playagain<<" is not a valid answer\n";
        cout<<"\n\t\t\tWould you like to play again (Y or N)\n";
        cin>>playagain;
    }
    if(playagain == 'Y')
        return 1;
    return 0;
}

// Recursive Function to play the tictactoe game by invoking other functions for input and ending game
void play(string p1, string p2, string first_p, char grid[][3], int chances)
{

    //   p1, p2, first, grid, chances are formal parameters
    //   p1 - stores player1 name, p2 - stores player2 name, first_p - stores first player name

    char current;   // current stores the current character (0 or X) of the current chance
    int row = -1, col = -1;
    if(chances == 9)    // Base Case
    {
        dispGrid(grid);
        cout<<"\n\t\t\tGame is over:\n";
        cout<<"\t\t\tIt is a tie\n";
        return;
    }
    cout<<endl;
    if(chances == 0)
        cout<<"\n\n\t\t\tInitially the game is :\n\n";
    else
        cout<<"\n\n\t\t\tUpdated game now is :\n\n";
    dispGrid(grid);   // calling dispGrid to display the updated grid after every turn
    chances++;
    cout<<endl<<"\n\t\t\tPlayer of current turn: "<<first_p<<endl;
    first_p == p1 ? current = 'X' : current ='O';
    inputRowCol(&row, &col, current, grid);   // calling inputRowCol to store enetered row, col no, chances, and update grid
    if(chances > 4)
    {
        if(check(row, col, current, grid) == 1)   // termination condition for play function
        {
            dispGrid(grid);
            cout<<"\n\t\t\tGame is over:\n";
            cout<<"\t\t\t"<<first_p<<" wins\n";
            return;
        }
    }
    if(first_p == p1)
    {
        first_p = p2;
        current = 'O';
    }
    else
    {
        first_p = p1;
        current = 'X';
    }
    row = -1;
    col = -1;
    play(p1, p2, first_p, grid, chances);
}

// Recursive Function that inputs player names, invokes fuction play to start game, also invokes playagain function
void start()
{

    // player1 - stores player1 name, player2 - stores player2 name, first - stores name of player who plays first

    string player1, player2, first;
    char grid[3][3];   // 2D array - accounts for the grid(board) of the game - to store 0, X
    int chances = 0;   // to store total number of chances played by both the players
    cout<<"\n\t\t\tEnter a name for the X player\n";
    getline(cin, player1);
    cout<<"\n\t\t\tEnter a name for the O player\n";
    getline(cin, player2);
    while(first != player1 && first != player2)
    {
        cout<<"\n\n\t\t\tWho plays first, "<<player1<<" or "<<player2<<" ? \n";
        getline(cin, first);
        if(first != player1 && first != player2)
            cout<<endl<<"\t\t\t"<<first<<" is not a registered player.\n";
    }
    setGrid(grid);   // passing 2D array to setGrid function to initializ it to '.'
    play(player1, player2, first, grid, chances);   // calling play function to play the game
    if(playAgain() == 0)    // Base Case
    {
        cout<<"\n\n\t\t\t\tGOODBYE THEN\n";
        return;
    }
    cin.ignore();
    system("cls");
    start();
}

int main()  //  Function from where the execution of program begins
{
    frontDesign();
    start();
}
