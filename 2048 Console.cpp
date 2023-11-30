#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int arr[4][4] = {0};

void mergeTiles()
{
    
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4 - 1; ++c)
        {
            if (arr[r][c] == arr[r][c + 1])
            {
                arr[r][c] *= 2;
                arr[r][c + 1] = 0;
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
                }
                ;
            }
        }
    }
}

void upArrow()
{
    moveTilesUp();
    mergeTiles();
    moveTilesUp();
}

void leftArrow()
{
    moveTilesLeft();
    mergeTiles();
    moveTilesLeft();
}

void rightArrow()
{
    moveTilesRight();
    mergeTiles();
    moveTilesRight();
}

void downArrow()
{
    moveTilesDown();
    mergeTiles();
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

    grid();

    rightArrow();
    system("clear");
    grid();
}
