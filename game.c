#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// function for printing board
void DisplayGrid(char **board, int size)
{
	printf("\n  ");
    for(int i=0 ; i<size ; i++){
		printf("   %d", i+1);
	}
	printf("\n");
    for(int i=0 ; i<size ; i++){
        printf("   ");
        for(int j=0 ; j<size ; j++){
            printf(" ---");
        }
        printf("\n %d ", i+1);
        for(int j=0 ; j<size ; j++){
            printf("| %c ", board[i][j]);
            if(j == size-1){
                printf("|");
            }
        }
        printf("\n");
    }
    printf("   ");
    for(j=0 ; j<R ; j++){
		printf(" ---");
    }
}
void InitializeBoard(char **board, int R, int i, int j){
	for(i=0 ; i<R ; i++){
        for(j=0 ; j<R ; j++){
            board[i][j] = ' ';
        }
    }
}
void InitializeVisited(int R, int i, int j, bool **Visited){
	for(i=0 ; i<R ; i++){
        for(j=0 ; j<R ; j++){
            Visited[i][j] = false;
        }
    }
}
void InitializeEaterBoard(int R, int i, int j, char **EaterBoard){
	for(i=0 ; i<R ; i++){
        for(j=0 ; j<R ; j++){
            EaterBoard[i][j] = ' ';
        }
    }
}
bool BoardFull(char **board, int R, int i, int j){
	for(i=0 ; i<R ; i++){
        for(j=0 ; j<R ; j++){
            if(board[i][j] == ' '){
            	return true;
			}
        }
    }
    return false;
}
bool PasserWin(char **board, int R, int FirstRow, int i, char **NewBoard, bool **Visited){
	if(FirstRow == R-1){
		if(board[FirstRow][i] == 'P'){
			NewBoard[FirstRow][i] = 'P';
			return true;
		}
	}
	if(FirstRow>=0 && FirstRow<R && i>=0 && i<R){
		if(board[FirstRow][i] == 'P'){
			NewBoard[FirstRow][i] = 'P';
			Visited[FirstRow][i] = true;
			//Down
			if(Visited[FirstRow+1][i] == false && PasserWin(board, R, FirstRow+1 , i, NewBoard, Visited)){
				NewBoard[FirstRow+1][i] = 'P';
				return true;
			}
			//Down Right
			if(Visited[FirstRow+1][i+1] == false && PasserWin(board, R, FirstRow+1 , i+1, NewBoard, Visited)){
				NewBoard[FirstRow+1][i+1] = 'P';
				return true;
			}
			//Down Left
			if(Visited[FirstRow+1][i-1] == false && PasserWin(board, R, FirstRow+1 , i-1, NewBoard, Visited)){
				NewBoard[FirstRow+1][i-1] = 'P';
				return true;
			}
			//Right
			if(Visited[FirstRow][i+1] == false && PasserWin(board, R, FirstRow , i+1, NewBoard, Visited)){
				NewBoard[FirstRow][i+1] = 'P';
				return true;
			}
			//Left
			if(Visited[FirstRow][i-1] == false && PasserWin(board, R, FirstRow , i-1, NewBoard, Visited)){
				NewBoard[FirstRow][i-1] = 'P';
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
bool LineFilled(char **board, int R, int SameRow, int i, char **EaterBoard){
	for(i=0 ; i<R ; i++){
		if(board[SameRow][i] != 'E'){
			return false;
		}
		else{
			EaterBoard[SameRow][i] = board[SameRow][i];
		}
	}
	return true;
}
void PlayGame(char **board, int R, int i, int j, char **NewBoard, bool **Visited, char **EaterBoard){
	int x1, y1;
	int x2, y2;
    do{
    	DisplayGrid(board, R, i, j);
		do{
			printf("\n\n~~~ Passer Turn ~~~");
	    	printf("\nEnter (X,Y) Coordinates : ");
	    	scanf("%d %d", &x1, &y1);
			if(x1<1 || x1>R || y1<1 || y1>R){
				printf("\n\t~~~Out of Grid Size~~~\n");
			}
			else if(board[x1-1][y1-1] == 'E'){
				printf("\n\t~~~Already Occupied By Eater~~~\n");
			}
			else if(board[x1-1][y1-1] == 'P'){
				printf("\n\t~~~Already Occupied By Passer!~~~\n");
			}
			else{
				printf("\n\t~~~Passer Marker Placed!~~~\n");
			}
		}while(x1<1 || x1>R || y1<1 || y1>R || board[x1-1][y1-1] == 'E' || board[x1-1][y1-1] == 'P');
		board[x1-1][y1-1] = 'P';
		
		//Function for Passer!
		for(i=0 ; i<R ; i++){
			InitializeVisited(R, i, j, Visited);
			if(PasserWin(board, R, 0 , i, NewBoard, Visited) == true){
				printf("\n\n~~~ Passer Won! ~~~");
				DisplayGrid(NewBoard, R, i, j);
				return;
			}
			else{
				InitializeBoard(NewBoard, R, i, j);
			}
		}
		
		if(BoardFull(board, R, i, j) == false){
			break;
		}
		
		do{
	    	printf("\n\n~~~ Eater Turn ~~~");
	    	printf("\nEnter (X,Y) Coordinates : ");
	    	scanf("%d %d", &x2, &y2);
			if(x2<1 || x2>R || y2<1 || y2>R){
				printf("\n\t~~~Out of Grid Size~~~\n");
			}
			else if(board[x1-1][y1-1] == 'E'){
				printf("\n\t~~~Already Occupied By Eater~~~\n");
			}
			else{
				printf("\n\t~~~Eater Marker Placed!~~~\n");
			}
		}while(x2<1 || x2>R || y2<1 || y2>R || board[x1-1][y1-1] == 'E');
		board[x2-1][y2-1] = 'E';
		
		//Function for Eater!
		for(i=0 ; i<R ; i++){
			InitializeEaterBoard(R, i, j, EaterBoard);
			if(LineFilled(board, R, i, j, EaterBoard) == true){
				printf("\n\n~~~ Eater Won! ~~~");
				DisplayGrid(EaterBoard, R, i, j);
				return;
			}
		}
	}while(BoardFull(board, R, i, j) == true);
	
	if(BoardFull(board, R, i, j) == false){
		printf("\n\n~~~ Board Full! Eater Won! ~~~\n");
		DisplayGrid(board, R, i, j);
		printf("\n\n");
	}
}
int main (){
    int R;
    do{
	    printf("Enter Grid Size : ");
	    scanf("%d", &R);
		if(R<3){
			printf("\n\t~~~ Grid Size Must Be Greater Than 3 ~~~\n\n");
		}
	}while(R<3);

    char *board[R], *NewBoard[R], *EaterBoard[R];
    bool *Visited[R];
    int i, j;
    for(i = 0; i < R; i++){
        board[i] = (char*)malloc(R * sizeof(char));
        NewBoard[i] = (char*)malloc(R * sizeof(char));
        EaterBoard[i] = (char*)malloc(R * sizeof(char));
        Visited[i] = (bool*)malloc(R * sizeof(bool));
	}
    InitializeBoard(board, R, i, j);
    InitializeBoard(NewBoard, R, i, j);
    PlayGame(board, R, i, j, NewBoard, Visited, EaterBoard);
}