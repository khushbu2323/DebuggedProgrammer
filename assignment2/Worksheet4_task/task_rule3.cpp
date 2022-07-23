#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int Game_Board_Row, Game_Board_Col;
//This function is to create Grid Lines or seprator
int Create_Grid_line(int Game_Board_Col)
{
	cout << endl;
	for (int i = 0; i < Game_Board_Col; i++) {
		cout << "----";
	}
	cout << endl;
}
//This function will display GameBoard
void display_grid(int** initial_cell_Board, int Game_Board_Row, int Game_Board_Col){
   	Create_Grid_line(Game_Board_Col);
	for (int i = 0; i < Game_Board_Row; i++) {
		cout << "|";
		for (int j = 0; j < Game_Board_Col; j++) {
			cout << " " << initial_cell_Board[i][j] << " |";
		}
		Create_Grid_line(Game_Board_Col);
	}
}

// this function will returns the count of live cells
int live_neighbour_cell_count( int** initial_cell_Board,int r, int c,int Game_Board_Row,int Game_Board_Col)
{
	 int i, j, count = 0;
    for (i = r - 1; i <= r + 1; i++) {
        for (j = c - 1; j <= c + 1; j++) {
            if ((i == r && j == c) || (i < 0 || j < 0)
                || (i >= Game_Board_Row || j >= Game_Board_Col)) {
                continue;
            }
            if (initial_cell_Board[i][j] == 1) {
                count++;
			}
		}
	}

	return count;
}

//This function is for Rule 
void FinalGame( int Game_Board_Row, int Game_Board_Col,int Live_neighbour,int** initial_cell_Board,int** final_cell_Board)
{


    	for (int i = 0; i < Game_Board_Row; i++) {
		for (int j = 0; j < Game_Board_Col; j++) {
			Live_neighbour
				= live_neighbour_cell_count( initial_cell_Board,i, j,Game_Board_Row,Game_Board_Col);
			if (initial_cell_Board[i][j] == 1
				&& (Live_neighbour >3 )) {
				final_cell_Board[i][j] = 0;
			}
            else{
	final_cell_Board[i][j] = 1;
            }

		}
	}

	// print Next generation of game of life
	cout << "\nNext Generation of Game of Life:";
		display_grid(final_cell_Board,Game_Board_Row,Game_Board_Col);
	

}

void InitialiseGameOfLife(int Game_Board_Row, int Game_Board_Col ,int** initial_cell_Board)
{

	//This will Generate Random Values Of game of life Live and Dead Cells
	for (int i = 0; i < Game_Board_Row; i++) {
		for (int j = 0; j < Game_Board_Col; j++) {
			initial_cell_Board[i][j] = rand() % 2;
		}
	}

	// It will Print Initial Game Board
	cout << "Initial Stage:"<<endl;
    cout<<"A living cell with more than three living neighbours dies"<<endl;

		display_grid(initial_cell_Board,Game_Board_Row,Game_Board_Col);
}

int main()
{
    
    int** InitializationofGrid;
	int** RuleTwoFinalGrid;
    int Game_Board_Row, Game_Board_Col, i, j;
	 int Live_neighbour;
    
    cout << "Enter the number of rows for GameBoard" << endl;
    cin >> Game_Board_Row;
    cout << "Enter the number of columns for Gameboard" << endl;
    cin >> Game_Board_Col;

    InitializationofGrid = new int*[Game_Board_Row];
	 RuleTwoFinalGrid = new int*[Game_Board_Row];
    for(i=0; i<Game_Board_Row; i++){
        InitializationofGrid[i] = new int[Game_Board_Col];
		RuleTwoFinalGrid[i] = new int[Game_Board_Col];
    }
InitialiseGameOfLife(Game_Board_Row,Game_Board_Col,InitializationofGrid);
FinalGame(Game_Board_Row,Game_Board_Col,Live_neighbour,InitializationofGrid,RuleTwoFinalGrid);
	return 0;
}