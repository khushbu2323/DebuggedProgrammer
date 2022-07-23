#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#define GAMEBOARD_SIZE 4
#define GAMEWINDOW_WIDTH	800
#define GAMEWINDOW_HEIGHT	500
#define GAMEBOARD_WIDTH		400
#define Y_AXIS_OF_BOARD 20
#define X_AXIS_OF_BOARD 100

// this struct will define scoreboard structure 
struct PlayerScoreBoard{
	double FinalTime;
	int FinalScore;
	int FinalSize;
};
//This Function is use to provide game instruction on same screen
void Write_Game_Instructions(SDL_Surface *GameScreen, int X_Cord, int Y_Cord, const char *GameText, SDL_Surface *BitMapOfChar) {
	int Point_On_X_Axis, Point_On_Y_Axis, Cord;
	SDL_Rect screen, dimension;
	screen.w = 8;
	screen.h = 8;
	dimension.w = 8;
	dimension.h = 8;
	while(*GameText) {
		Cord = *GameText & 255;
		Point_On_X_Axis = (Cord % 16) * 8;
		Point_On_Y_Axis = (Cord / 16) * 8;
		screen.x = Point_On_X_Axis;
		screen.y = Point_On_Y_Axis;
		dimension.x = X_Cord;
		dimension.y = Y_Cord;
		SDL_BlitSurface(BitMapOfChar, &screen, GameScreen, &dimension);
		X_Cord += 8;
		GameText++;
		};
	};




// this function will draw single pixel on gameborad
void DesignPixel(SDL_Surface *Game_Area, int X_Cord, int Y_Cord, Uint32 pixelcolor) {
	int byteperpixel = Game_Area->format->BytesPerPixel;
	Uint8 *pixel = (Uint8 *)Game_Area->pixels + Y_Cord * Game_Area->pitch + X_Cord * byteperpixel;
	*(Uint32 *)pixel = pixelcolor;
};



// This function is used to draw horizontal and vertical line of shapes
void DrawOuterLines(SDL_Surface *GameScreen, int X_Cord, int Y_Cord, int length, int x_axis, int y_axis, Uint32 pixelcolor) {
	for(int i = 0; i < length; i++) {
		DesignPixel(GameScreen, X_Cord, Y_Cord, pixelcolor);
		X_Cord += x_axis;
		Y_Cord += y_axis;
		};
	};

// This fucntion will draw instruction box using lines
void DrawInstructionBox(SDL_Surface *GameScreen, int X_Cord, int Y_Cord, int Rect_Length, int Rect_Width,
                   Uint32 BoundaryColor, Uint32 RectangleColor) {
	int i;
	DrawOuterLines(GameScreen, X_Cord, Y_Cord, Rect_Width, 0, 1, BoundaryColor);
	DrawOuterLines(GameScreen, X_Cord + Rect_Length - 1, Y_Cord, Rect_Width, 0, 1, BoundaryColor);
	DrawOuterLines(GameScreen, X_Cord, Y_Cord, Rect_Length, 1, 0, BoundaryColor);
	DrawOuterLines(GameScreen, X_Cord, Y_Cord + Rect_Width - 1, Rect_Length, 1, 0, BoundaryColor);
	for(i = Y_Cord + 1; i < Y_Cord + Rect_Width - 1; i++)
		DrawOuterLines(GameScreen, X_Cord + 1, i, Rect_Length - 2, 1, 0, RectangleColor);
	};

//It wil find a center point to align text properly in instruction box
void FindMiddlePoint(SDL_Surface *GameScreen, int X_Cord, int Y_Cord, int Box_width, const char *Num, SDL_Surface *BitMapOfChar) {
	int Num_Size = strlen(Num);
	Write_Game_Instructions(GameScreen, (X_Cord + Box_width / 2) - Num_Size*4, Y_Cord + Box_width / 2, Num, BitMapOfChar);
}


int FindSquareNumber(int val) {
	int num = 0;
	while (val != 0) {
		val = val/2;
		num++;
	}

	return num;
}
//This function will design gameboard with given user Block_size
void DesignGameBoard(SDL_Surface *GameScreen, int **block, int sizeofboard, Uint32 BoundaryColor, Uint32 RectangleColor, SDL_Surface *BitMapOfChar) {
	int boardwidth = (GAMEBOARD_WIDTH / sizeofboard) - 2;
	int X_Cord, Y_Cord;
	char Num[5];
	for (int i = 0; i < sizeofboard; i++) {
		for (int j = 0; j < sizeofboard; j++) {
			X_Cord = X_AXIS_OF_BOARD + (GAMEBOARD_WIDTH / sizeofboard)*i;
			Y_Cord = Y_AXIS_OF_BOARD + (GAMEBOARD_WIDTH / sizeofboard)*j;
			int squareValue_of_color = FindSquareNumber(block[i][j]);
			DrawInstructionBox(GameScreen, Y_Cord, X_Cord, boardwidth, boardwidth, BoundaryColor, SDL_MapRGB(GameScreen->format, 10, 50 + 20 * squareValue_of_color, 0 + 10*squareValue_of_color));
			if(block[i][j] == 0) sprintf(Num, "");
			else sprintf(Num, "%d", block[i][j]);
			FindMiddlePoint(GameScreen, Y_Cord, X_Cord, boardwidth, Num, BitMapOfChar);
		}
	}
}
//This Function will design a ScoreBoard with latest Score of game
void DesignScoreBoard(SDL_Surface *GameScreen, unsigned int ScoreValue, SDL_Surface *BitMapOfChar) {
	int X_Cord = X_AXIS_OF_BOARD;
	int Y_Cord = Y_AXIS_OF_BOARD + GAMEBOARD_WIDTH + 100;
	int width = 40;
	char Num[18];
	sprintf(Num, "User Score Is: %u", ScoreValue);
	FindMiddlePoint(GameScreen, Y_Cord, X_Cord, width, Num, BitMapOfChar);
}

int** CreateBlock(int Block_Size) {
	int **block;
	block = new int *[Block_Size];
	for (int i = 0; i < Block_Size; ++i) block[i] = new int[Block_Size];

	for (int i = 0; i < Block_Size; i++) {
		for (int j = 0; j < Block_Size; j++) {
			block[i][j] = 0;
		}
	}
	int X_Cord = rand() % Block_Size;
	int Y_Cord = rand() % Block_Size;
	block[X_Cord][Y_Cord] = 2;
	X_Cord = rand() % Block_Size;
	Y_Cord= rand() % Block_Size;
	block[X_Cord][Y_Cord] = 2;

	return block;
}

//This function will return a winning flag if user create 2048 then its a wiining stage
bool WinnigCheck(int **&block, int Block_Size) {
	bool winflag = 0;

	for (int i = 0; i < Block_Size; i++) {
		for (int j = 0; j < Block_Size; j++) {
			if (block[i][j] == 2048) winflag = 1;
		}
	}

	return winflag;
}

//It will check for zeros on gameboard blocks
bool CheckZero(int **&block, int Block_Size) {
	bool Zeroflag = 0;

	for (int i = 0; i < Block_Size; i++) {
		for (int j = 0; j < Block_Size; j++) {
			if (block[i][j] == 0) Zeroflag = 1;
		}
	}

	return Zeroflag;
}

//check Player lossing stage on gameboard
bool Check_For_Lose(int **&block, int Block_Size) {
	bool LoseFlag = 1;

	for (int i = 0; i < Block_Size; i++) {
		for (int j = 0; j < Block_Size - 1; j++) {
			if (block[i][j] == block[i][j + 1]) LoseFlag = 0;
		}
	}
	for (int i = 0; i < Block_Size - 1; i++) {
		for (int j = 0; j < Block_Size; j++) {
			if (block[i][j] == block[i + 1][j]) LoseFlag = 0;
		}
	}

	if (CheckZero(block, Block_Size)) LoseFlag = 0;

	return LoseFlag;
}

//Check Randome Moves For user on gameborad
bool CheckForRandomMoves(int **&block, int **&backTab, int Block_Size) {
	int RandomFlag = 0;
	for (int i = 0; i < Block_Size; ++i) {
		for (int j = 0; j < Block_Size; ++j) {
			if (block[i][j] != backTab[i][j]) RandomFlag = 1;
		}
	}
	return RandomFlag;
}

//Place Two Randomly on Game Board
void RandomPointOnBoard(int **&block, int Block_Size) {

	if (CheckZero(block, Block_Size)) {
		int Points[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		int RandomPointvalue = Points[rand() % 10];

		int X_Cord = rand() % Block_Size;
		int Y_Cord = rand() % Block_Size;
		if (block[X_Cord][Y_Cord] == 0) block[X_Cord][Y_Cord] = 2;
		else {
			while (block[X_Cord][Y_Cord] != 0) {
				X_Cord = rand() % Block_Size;
				Y_Cord = rand() % Block_Size;
			}
			block[X_Cord][Y_Cord] = RandomPointvalue;
		}
	}
}

//Drive points in all direction
void UpwardMove(int **&block, int Block_size) {
	for (int i = 1; i < Block_size; i++) {
		for (int j = 0; j < Block_size; j++) {
			if (block[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (block[k - 1][j] == 0) {
						block[k - 1][j] = block[k][j];
						block[k][j] = 0;
					}
				}
			}
		}
	}
}
//Drvie Point to Upward direction
void MoveUp(int **&block, int Block_size, unsigned int &ScoreValue) {
	UpwardMove(block, Block_size);
	
	for (int i = 1; i < Block_size; i++) {
		for (int j = 0; j < Block_size; j++) {
			if (block[i][j] != 0) {
				if (block[i - 1][j] == block[i][j]) {
					block[i - 1][j]+= block[i][j];
					ScoreValue += block[i - 1][j];
					block[i][j] = 0;
				
				}
			}
		}
	}

	UpwardMove(block, Block_size);
}

//user random move on board
void CascadeBot(int **&block, int Block_size) {
	for (int i = 0; i < Block_size; i++) {
		for (int j = Block_size - 2; j >= 0; j--) {
			if (block[j][i] != 0) {
				for (int k = j; k < Block_size - 1; ++k) {
					if (block[k + 1][i] == 0) {
						block[k + 1][i] = block[k][i];
						block[k][i] = 0;
					}
				}
			}
		}
	}
}
void DriveBot(int **&block, int Block_size, unsigned int &ScoreValue) {
	CascadeBot(block, Block_size);

	for (int i = 0; i < Block_size; i++) {
		for (int j = Block_size - 2; j >= 0; j--) {
			if (block[j][i] != 0) {
				if (block[j][i] == block[j + 1][i]) {
					block[j + 1][i] += block[j][i];
					ScoreValue += block[j + 1][i];
					block[j][i] = 0;
				}
			}
		}
	}

	CascadeBot(block, Block_size);
}

//user move in right direction
void CascadeRight(int **&block, int Block_size) {

	for (int i = 0; i < Block_size; i++) {
		for (int j = Block_size - 2; j >= 0; j--) {
			if (block[i][j] != 0) {
				for (int k = j; k < Block_size - 1; ++k) {
					if (block[i][k + 1] == 0) {
						block[i][k + 1] = block[i][k];
						block[i][k] = 0;
					}
				}
			}
		}
	}
}
void DriveRight(int **&block,int Block_size, unsigned int &ScoreValue) {
	CascadeRight(block, Block_size);

	for (int i = 0; i < Block_size; i++) {
		for (int j = Block_size - 2; j >= 0; j--) {
			if (block[i][j] != 0) {
				if (block[i][j] == block[i][j + 1]) {
					block[i][j + 1] += block[i][j];
					ScoreValue += block[i][j + 1];
					block[i][j] = 0;
				}
			}
		}
	}
	
	CascadeRight(block, Block_size);
}

//user move in left direction
void CascadeLeft(int **&block, int Block_size) {
	for (int i = 0; i < Block_size; i++) {
		for (int j = 1; j < Block_size; j++) {
			if (block[i][j] != 0) {
				for (int k = j; k > 0; --k) {
					if (block[i][k - 1] == 0) {
						block[i][k - 1] = block[i][k];
						block[i][k] = 0;
					}
				}
			}
		}
	}
}
void DriveLeft(int **&block, int Block_size, unsigned int &ScoreValue) {

	CascadeLeft(block, Block_size);

	for(int i = 0; i < Block_size; i++) {
		for (int j = 1; j < Block_size; j++) {
			if (block[i][j] != 0) {
				if (block[i][j] == block[i][j - 1]) {
					block[i][j - 1] += block[i][j];
					ScoreValue += block[i][j - 1];
					block[i][j] = 0;
				}
			}
		}
	}

	CascadeLeft(block, Block_size);
}

//this frunction will duplicate the array
void Duplicate_Blocks(int **&Block1,int **&Block2, int Block_size) {
	for (int i = 0; i < Block_size; i++) {
		for (int j = 0; j < Block_size; j++) Block1[i][j] = Block2[i][j];
	}
}

//
void Drive(SDL_Event Method, int **&block, int Block_size, int **&Back_Tab, unsigned int &ScoreValue, unsigned int &Final_Score) {
	int **Check_Tab_Move = CreateBlock(Block_size);
	int ScoreCheck = Final_Score;
	Duplicate_Blocks(Check_Tab_Move, Back_Tab, Block_size);

	Duplicate_Blocks(Back_Tab, block, Block_size);
	Final_Score = ScoreValue;
	

	if (Method.key.keysym.sym == SDLK_UP) MoveUp(block, Block_size, ScoreValue);
	else if (Method.key.keysym.sym == SDLK_DOWN) DriveBot(block, Block_size, ScoreValue);
	else if (Method.key.keysym.sym == SDLK_LEFT) DriveLeft(block, Block_size, ScoreValue);
	else if (Method.key.keysym.sym == SDLK_RIGHT) DriveRight(block, Block_size, ScoreValue);

	if (CheckForRandomMoves(block, Back_Tab, Block_size)) {
		RandomPointOnBoard(block, Block_size);
	}
	else {
		Duplicate_Blocks(Back_Tab, Check_Tab_Move, Block_size);
		Final_Score = ScoreCheck;
	}

	for (int i = 0; i < Block_size; ++i)
		delete[] Check_Tab_Move[i];
	delete[] Check_Tab_Move;
}

//Sorting of rank using score
void OrderedByScore(PlayerScoreBoard *&block, int Block_size) {
	PlayerScoreBoard scorehelper;
	for (int i = 0; i < Block_size - 1; i++) {
		for (int j = 0; j < Block_size - 1 - i; j++) {
			if (block[j].FinalScore > block[j + 1].FinalScore) {
				scorehelper = block[j];
				block[j] = block[j + 1];
				block[j + 1] = scorehelper;
			}
		}
	}

	for (int i = 0; i < Block_size / 2; i++) {
		scorehelper = block[i];
		block[i] = block[Block_size - i - 1];
		block[Block_size - i - 1] = scorehelper;
	}
}

//sorting of rank using time
void OrderedByTime(PlayerScoreBoard *&block, int Block_size) {
	PlayerScoreBoard scorehelper;
	for (int i = 0; i < Block_size - 1; i++) {
		for (int j = 0; j < Block_size - 1 - i; j++) {
			if (block[j].FinalTime > block[j + 1].FinalTime) {
				scorehelper = block[j];
				block[j] = block[j + 1];
				block[j + 1] = scorehelper;
			}
		}
	}
}

//this function will find user rank
PlayerScoreBoard *UserRanking(PlayerScoreBoard *block, int count, int Block_size, int File_Length) {
	PlayerScoreBoard *Position = new PlayerScoreBoard[count];
	int j = 0;
	for (int i = 0; i < File_Length; i++) {
		if (block[i].FinalSize == Block_size) {
			Position[j].FinalScore = block[i].FinalScore;
			Position[j].FinalTime = block[i].FinalTime;
			Position[j].FinalSize = block[i].FinalSize;
			j++;
		}
	}
	return Position;
}
// this function will store updated score to file 
void StoreToFile(int ScoreValue, double usertime, int Block_size) {
	FILE *winnerdataList = fopen("scoreList.txt", "a");
	fprintf(winnerdataList, "%u %.1lf %d\n", ScoreValue, usertime, Block_size);

	fclose(winnerdataList);
}

//this will generate player scoreboard
PlayerScoreBoard *openFile(int &Rank_data_Lines){
	FILE *winnerdataList = fopen("scoreList.txt", "r");
	int ch = 0;

	if (winnerdataList == NULL)
	{
		return 0;
	}

	while (!feof(winnerdataList))
	{
		ch = fgetc(winnerdataList);
		if (ch == '\n')
		{
			Rank_data_Lines++;
		}
	}

	PlayerScoreBoard *Score_List = new PlayerScoreBoard [Rank_data_Lines];
	fseek(winnerdataList, 0, SEEK_SET);
	for (int i = 0; i < Rank_data_Lines; i++) {
		fscanf(winnerdataList, "%d %lf %d", &Score_List[i].FinalScore, &Score_List[i].FinalTime, &Score_List[i].FinalSize);
	}
	fclose(winnerdataList);

	return Score_List;
}

// Main Function
int main(int argc, char **argv) {
	int Block_size = 4;
	bool game_start = 0;
	unsigned int ScoreValue = 0;
	unsigned int Final_Score = ScoreValue;
	int display_size = 0;
	srand(time(NULL));
	int** block;
	int** Back_Tab;
	int File_Length = 0;
	PlayerScoreBoard *scoreList;

	int temp1, temp2, Quit_Game, game_frames, window_rendrer;
	double value_difference, International_clock, frame_per_sec_Timer, frame_per_sec, Frame_Distance, net_speed;
	SDL_Event Method;
	SDL_Surface *GameScreen, *BitMapOfChar;
	SDL_Surface *Estimated_time;
	SDL_Texture *game_sprites;
	SDL_Window *game_window;
	SDL_Renderer *game_renderer;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}


	window_rendrer = SDL_CreateWindowAndRenderer(GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, 0,
	                                 &game_window, &game_renderer);
	if(window_rendrer != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(game_renderer, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT);
	SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(game_window, "2048 Game Window");


	GameScreen = SDL_CreateRGBSurface(0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	game_sprites = SDL_CreateTexture(game_renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT);


	//this function will disable cursor disability
	SDL_ShowCursor(SDL_DISABLE);

	BitMapOfChar = SDL_LoadBMP("./cs8x8.bmp");
	if(BitMapOfChar == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(GameScreen);
		SDL_DestroyTexture(game_sprites);
		SDL_DestroyWindow(game_window);
		SDL_DestroyRenderer(game_renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(BitMapOfChar, true, 0x000000);

	char GameText[128];
		char Text[128];

	int BlackBaground = SDL_MapRGB(GameScreen->format, 0,0,0);
	int blue = SDL_MapRGB(GameScreen->format, 143,72,143);

	block = CreateBlock(Block_size);
	Back_Tab = CreateBlock(Block_size);
	Duplicate_Blocks(block, Back_Tab, Block_size);	
	scoreList = openFile(File_Length);

	game_frames = 0;
	frame_per_sec_Timer = 0;
	frame_per_sec = 0;
	Quit_Game = 0;
	International_clock = 0;
	Frame_Distance = 0;
	net_speed = 1;


	


	while(!Quit_Game) {

		//This will display game board size from 4 to 10 
		if (!game_start) {
		
			if (Block_size >= 10) Block_size = 10;
			if (Block_size <= 3) Block_size = 3;

			SDL_FillRect(GameScreen, NULL, BlackBaground);
			DrawInstructionBox(GameScreen, 4, 2, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
			sprintf(GameText, "Select The Size of GameBoard");
			Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 26, GameText, BitMapOfChar);
			DrawInstructionBox(GameScreen, 8, 40, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
			sprintf(GameText,"\030 - Use UP-Arrow for Larger, \031 - Use Down-Arrow for Smaller  use Enter - for confirm");
			Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 52, GameText, BitMapOfChar);

			DrawInstructionBox(GameScreen, GAMEWINDOW_WIDTH/2 - 100, GAMEWINDOW_HEIGHT/2 - 36, 200, 36, BlackBaground, blue);
			sprintf(GameText, "Size: %d", Block_size);
			Write_Game_Instructions(GameScreen, GAMEWINDOW_WIDTH/2  -  strlen(GameText) * 4, GAMEWINDOW_HEIGHT / 2 - 20, GameText, BitMapOfChar);

		
			while (SDL_PollEvent(&Method)) {
				switch (Method.type) {
				case SDL_KEYDOWN:
					if (Method.key.keysym.sym == SDLK_ESCAPE) Quit_Game = 1;
					else if (Method.key.keysym.sym == SDLK_UP) Block_size++;
					else if (Method.key.keysym.sym == SDLK_DOWN) Block_size--;
					else if (Method.key.keysym.sym == SDLK_RETURN) { 
						game_start = 1; 
						block = CreateBlock(Block_size);
						Back_Tab = CreateBlock(Block_size);
						Duplicate_Blocks(block, Back_Tab, Block_size);
						temp1 = SDL_GetTicks();
						Final_Score = 0;
						ScoreValue = 0;
						International_clock = 0;
					}
					break;
				case SDL_QUIT:
					Quit_Game = 1;
					break;
				};
			};

			SDL_UpdateTexture(game_sprites, NULL, GameScreen->pixels, GameScreen->pitch);
			SDL_RenderCopy(game_renderer, game_sprites, NULL, NULL);
			SDL_RenderPresent(game_renderer);
		}
		//display game Window
		else if(game_start && !Check_For_Lose(block, Block_size) && !WinnigCheck(block, Block_size)){
		
			//Game timer
			temp2 = SDL_GetTicks();
			value_difference = (temp2 - temp1) * 0.001;
			temp1 = temp2;
			International_clock += value_difference;
			frame_per_sec_Timer += value_difference;
			if (frame_per_sec_Timer > 0.5) {
				frame_per_sec = game_frames * 2;
				game_frames = 0;
				frame_per_sec_Timer -= 0.5;
			};

			SDL_FillRect(GameScreen, NULL, BlackBaground);


			DesignGameBoard(GameScreen, block, Block_size, BlackBaground, blue, BitMapOfChar);
			DesignScoreBoard(GameScreen, ScoreValue, BitMapOfChar);
		
			//info GameText
			DrawInstructionBox(GameScreen, 4, 4, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
			sprintf(GameText, "Play 2048,       = %.1lf s  %.0lf game_frames ", International_clock, frame_per_sec);
			Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 10, GameText, BitMapOfChar);
			sprintf(GameText, "use Esc - Exit, use Arrows - Move,press u - Back Move, press n - start New game");
			Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 26, GameText, BitMapOfChar);

			SDL_UpdateTexture(game_sprites, NULL, GameScreen->pixels, GameScreen->pitch);
			//game rendrer function
			SDL_RenderCopy(game_renderer, game_sprites, NULL, NULL);
			SDL_RenderPresent(game_renderer);

			while(SDL_PollEvent(&Method)) {
				switch(Method.type) {
					case SDL_KEYDOWN:
						if (Method.key.keysym.sym == SDLK_ESCAPE) Quit_Game = 1;
						else if (Method.key.keysym.sym == SDLK_UP || Method.key.keysym.sym == SDLK_DOWN ||
							Method.key.keysym.sym == SDLK_LEFT || Method.key.keysym.sym == SDLK_RIGHT) Drive(Method, block, Block_size, Back_Tab, ScoreValue, Final_Score);
						else if (Method.key.keysym.sym == SDLK_u) { 
							Duplicate_Blocks(block, Back_Tab, Block_size); 
							ScoreValue = Final_Score;
						}
						else if (Method.key.keysym.sym == SDLK_n) { 
							for (int i = 0; i < Block_size; ++i)
								delete[] block[i];
							delete[] block;

							for (int i = 0; i < Block_size; ++i)
								delete[] Back_Tab[i];
							delete[] Back_Tab;
							game_start = 0; 
						}
						else if (Method.key.keysym.sym == SDLK_r) {	//Display rank board


							bool show_ranking = 0;
							int amountBoard = 0;
							int startShow = 0;
							int limit = 10;
							for (int i = 0; i < File_Length; i++) if (Block_size == scoreList[i].FinalSize) amountBoard++;
							PlayerScoreBoard *sizeRanking = UserRanking(scoreList, amountBoard, Block_size, File_Length);
							while (!show_ranking) {

								SDL_FillRect(GameScreen, NULL, BlackBaground);
								DrawInstructionBox(GameScreen, 4, 4, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
								sprintf(GameText, "game winner card for %dx%d", Block_size, Block_size);
								Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 10, GameText, BitMapOfChar);
								sprintf(GameText, "esc -  go back,  press t to ordered by time  and score to sort by points");
								Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 26, GameText, BitMapOfChar);

							
								//set start of ranking
								if (startShow <= 0) startShow = 0;	
								if (startShow >= amountBoard - 10) startShow = amountBoard - 10;	
								if (amountBoard <= 10) {
									startShow = 0;
									limit = amountBoard;
								}	

								//check there is winner list
								if (File_Length == 0 || limit == 0) {
									sprintf(GameText, "Winner list in empty");
									Write_Game_Instructions(GameScreen, GAMEWINDOW_WIDTH / 2 - strlen(GameText) * 4, GAMEWINDOW_HEIGHT / 2 + 16, GameText, BitMapOfChar);
								}
								
								int placeShow = 0;								
								for (int i = startShow; placeShow < limit; i++) {
									DrawInstructionBox(GameScreen, GAMEWINDOW_WIDTH / 2 - 200, GAMEWINDOW_HEIGHT / 2 - 190 + placeShow * 40, 400, 40, BlackBaground, blue);
									sprintf(GameText, "%d. Your : %.1lfs Your ScoreValue: %d",startShow + placeShow + 1, sizeRanking[i].FinalTime, sizeRanking[i].FinalScore);
									Write_Game_Instructions(GameScreen, GAMEWINDOW_WIDTH / 2 - strlen(GameText) * 4, GAMEWINDOW_HEIGHT / 2 - 200 + 26 + placeShow * 40, GameText, BitMapOfChar);
									placeShow++;
								}

								while (SDL_PollEvent(&Method)) {
									switch (Method.type) {
									case SDL_KEYDOWN:
										if (Method.key.keysym.sym == SDLK_ESCAPE) show_ranking = 1;
										if (Method.key.keysym.sym == SDLK_t) OrderedByTime(sizeRanking, amountBoard);
										if (Method.key.keysym.sym == SDLK_p) OrderedByScore(sizeRanking, amountBoard);
										else if (Method.key.keysym.sym == SDLK_UP) startShow++;
										else if (Method.key.keysym.sym == SDLK_DOWN) startShow--;
										
										break;
									case SDL_QUIT:
										Quit_Game = 1;
										show_ranking = 1;
										break;
									};
								};

								SDL_UpdateTexture(game_sprites, NULL, GameScreen->pixels, GameScreen->pitch);
								SDL_RenderCopy(game_renderer, game_sprites, NULL, NULL);
								SDL_RenderPresent(game_renderer);
							}
							delete[] sizeRanking;
						}
						break;
					case SDL_KEYUP:
						net_speed = 1.0;
						break;
					case SDL_QUIT:
						Quit_Game = 1;
						break;
				};
			};
			game_frames++;
		}
		
		else if (Check_For_Lose(block, Block_size)) {
			double FinalTime = International_clock;
			while (!Quit_Game) {
				SDL_FillRect(GameScreen, NULL, BlackBaground);
				DrawInstructionBox(GameScreen, 4, 4, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
				sprintf(GameText, "You Lose: esc - Quit_Game");
				Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 26, GameText, BitMapOfChar);

				DrawInstructionBox(GameScreen, GAMEWINDOW_WIDTH / 2 - 200, GAMEWINDOW_HEIGHT / 2 - 36, 400, 36, BlackBaground, blue);
				sprintf(GameText, "Your : %.1lfs  Your ScoreValue: %u", FinalTime, ScoreValue);
				Write_Game_Instructions(GameScreen, GAMEWINDOW_WIDTH / 2 - strlen(GameText) * 4, GAMEWINDOW_HEIGHT / 2 - 20, GameText, BitMapOfChar);


				while (SDL_PollEvent(&Method)) {
					switch (Method.type) {
					case SDL_KEYDOWN:
						if (Method.key.keysym.sym == SDLK_ESCAPE) Quit_Game = 1;
						break;
					case SDL_QUIT:
						Quit_Game = 1;
						break;
					};
				};

				SDL_UpdateTexture(game_sprites, NULL, GameScreen->pixels, GameScreen->pitch);
				SDL_RenderCopy(game_renderer, game_sprites, NULL, NULL);
				SDL_RenderPresent(game_renderer);
			}
		}
		else if (WinnigCheck(block, Block_size)) {
			double FinalTime = International_clock;
			while (!Quit_Game) {
				SDL_FillRect(GameScreen, NULL, BlackBaground);
				DrawInstructionBox(GameScreen, 4, 4, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
				sprintf(GameText, "You Win: s - to save your , esc -  to Quit_Game");
				Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 26, GameText, BitMapOfChar);

				DrawInstructionBox(GameScreen, GAMEWINDOW_WIDTH / 2 - 200, GAMEWINDOW_HEIGHT / 2 - 36, 400, 36, BlackBaground, blue);
				sprintf(GameText, "Your : %.1lfs  Your ScoreValue: %u", FinalTime, ScoreValue);
				Write_Game_Instructions(GameScreen, GAMEWINDOW_WIDTH / 2 - strlen(GameText) * 4, GAMEWINDOW_HEIGHT / 2 - 20, GameText, BitMapOfChar);


				while (SDL_PollEvent(&Method)) {
					switch (Method.type) {
					case SDL_KEYDOWN:
						if (Method.key.keysym.sym == SDLK_ESCAPE) Quit_Game = 1;
						if (Method.key.keysym.sym == SDLK_s) { 
							StoreToFile(ScoreValue, FinalTime, Block_size); 

						

							while (!Quit_Game) {

								SDL_FillRect(GameScreen, NULL, BlackBaground);
								DrawInstructionBox(GameScreen, 4, 4, GAMEWINDOW_WIDTH - 8, 36, BlackBaground, blue);
								sprintf(GameText, "Score saved!");
								Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 10, GameText, BitMapOfChar);
								sprintf(GameText, "esc -  close game");
								Write_Game_Instructions(GameScreen, GameScreen->w / 2 - strlen(GameText) * 8 / 2, 26, GameText, BitMapOfChar);

								while (SDL_PollEvent(&Method)) {
									switch (Method.type) {
									case SDL_KEYDOWN:
										if (Method.key.keysym.sym == SDLK_ESCAPE) Quit_Game = 1;

										break;
									case SDL_QUIT:
										Quit_Game = 1;
										break;
									};
								};

								SDL_UpdateTexture(game_sprites, NULL, GameScreen->pixels, GameScreen->pitch);
								SDL_RenderCopy(game_renderer, game_sprites, NULL, NULL);
								SDL_RenderPresent(game_renderer);
							}
						}
						break;
					case SDL_QUIT:
						Quit_Game = 1;
						break;
					};
				};

				SDL_UpdateTexture(game_sprites, NULL, GameScreen->pixels, GameScreen->pitch);
				SDL_RenderCopy(game_renderer, game_sprites, NULL, NULL);
				SDL_RenderPresent(game_renderer);
			}
		}
	};
	
	//we are releasing memory here
	for (int i = 0; i < Block_size; ++i)
		delete[] block[i];
	delete[] block;

	for (int i = 0; i < Block_size; ++i)
		delete[] Back_Tab[i];
	delete[] Back_Tab;

	delete[] scoreList;

	SDL_FreeSurface(BitMapOfChar);
	SDL_FreeSurface(GameScreen);
	SDL_DestroyTexture(game_sprites);
	SDL_DestroyRenderer(game_renderer);
	SDL_DestroyWindow(game_window);

	SDL_Quit();
	return 0;
	};
