#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>

using namespace std;

int arr[4][4] = { 0 };

void mergeTilesud()
{
    for (int c = 0; c < 4; ++c)
    {
        for (int r = 0; r < 4 - 1; ++r)
        {
            if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c])
            {
                arr[r][c] *= 2;
                arr[r + 1][c] = 0;
            }
        }
    }
}


void mergeTilesrl()
{
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4 - 1; ++c)
        {
            if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1])
            {
                arr[r][c] *= 2;
                arr[r][c + 1] = 0;
            }
        }
    }
}



void moveTilesRight()
{
    for (int r = 0; r < 4; r++)
    {
        int column = 3;
        for (int c = 3; c >= 0; c--)
        {
            if (arr[r][c] != 0)
            {
                arr[r][column] = arr[r][c];
                if (column != c)
                {
                    arr[r][c] = 0;
                }
                column--;
            }
        }
    }
}

void moveTilesLeft()
{

    for (int r = 0; r < 4; ++r)
    {
        int column = 0;
        for (int c = 0; c < 4; c++)
        {
            if (arr[r][c] != 0)
            {
                arr[r][column] = arr[r][c];
                if (column != c)
                {
                    arr[r][c] = 0;
                }
                column++;
            }
        }
    }
}
void moveTilesUp()
{

    for (int c = 0; c < 4; c++)
    {
        int row = 0;
        for (int r = 0; r < 4; r++)
        {
            if (arr[r][c] != 0)
            {
                arr[row][c] = arr[r][c];
                if (row != r)
                {
                    arr[r][c] = 0;
                };
                row++;
            }
        }
    }
}
void moveTilesDown()
{

    for (int c = 0; c < 4; c++)
    {
        int row = 3;
        for (int r = 3; r >= 0; r--)
        {
            if (arr[r][c] != 0)
            {
                arr[row][c] = arr[r][c];
                if (row != r)
                {
                    arr[r][c] = 0;
                }
                row--;
            }
        }
    }
}


void upArrow()
{
    moveTilesUp();
    mergeTilesud();
    moveTilesUp();
}

void leftArrow()
{
    moveTilesLeft();
    mergeTilesrl();
    moveTilesLeft();
}

void rightArrow()
{
    moveTilesRight();
    mergeTilesrl();
    moveTilesRight();
}

void downArrow()
{
    moveTilesDown();
    mergeTilesud();
    moveTilesDown();
}

void grid()
{
    cout << "________________________________" << endl;
    cout << "|\t|\t|\t|\t|" << endl;
    cout << "|" << setw(4) << arr[0][0] << "\t|" << setw(4) << arr[0][1] << "\t|" << setw(4) << arr[0][2] << "\t|" << setw(4) << arr[0][3] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
    cout << "|\t|\t|\t|\t|" << endl;
    cout << "|" << setw(4) << arr[1][0] << "\t|" << setw(4) << arr[1][1] << "\t|" << setw(4) << arr[1][2] << "\t|" << setw(4) << arr[1][3] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
    cout << "|\t|\t|\t|\t|" << endl;
    cout << "|" << setw(4) << arr[2][0] << "\t|" << setw(4) << arr[2][1] << "\t|" << setw(4) << arr[2][2] << "\t|" << setw(4) << arr[2][3] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
    cout << "|\t|\t|\t|\t|" << endl;
    cout << "|" << setw(4) << arr[3][0] << "\t|" << setw(4) << arr[3][1] << "\t|" << setw(4) << arr[3][2] << "\t|" << setw(4) << arr[3][3] << "\t|" << endl;
    cout << "|_______|_______|_______|_______|" << endl;
}

int main()
{
    srand(time(0));

    int r = rand() % 4;
    int c = rand() % 4;

    arr[r][c] = 2;
    arr[2][2] = 2;

    grid();

    while (true)
    {

        if (_kbhit())
        {

            char key = _getch();

            if ((key == 'w') || (key == 72) || (key == 'W'))
                upArrow();

            else if ((key == 's') || (key == 80) || (key == 'S'))
                downArrow();

            else if ((key == 'a') || (key == 75) || (key == 'A'))
                leftArrow();

            else if ((key == 'd') || (key == 77) || (key == 'D'))
                rightArrow();

            system("cls");
            grid();

        }
    }
}
