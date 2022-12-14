#ifndef WIN32
#include <unistd.h>
#else

#include <Windows.h>

#endif

#include "arcanoid.h"
#include <time.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))



BOOL NOT_AROUND(int h,int x, int y) {
    for (int i = -BLOCK*2; i < BLOCK*2; i++) {
        if (Level_arr[h][x + i][y] == 1)
            return FALSE;
    }
    return TRUE;
}
void genarate_level() {

        for (int i = 0; i < AREA_HEIGHT; ++i) {
            for (int j = 0; j < AREA_WIDTH; ++j) {
                Level_arr[GAME_LEVEL][i][j] = 0;
            }
        }


    int count = 0;


        while (count < GAME_LEVEL * 5) {
            int x = 2+ rand() %58;
            int y = 2+rand() % 13;

            if (Level_arr[GAME_LEVEL][x][y] == 0 && NOT_AROUND(GAME_LEVEL,x,y)) {
                count++;
                
                
             //   printf("%d %d ", x, y);
                Level_arr[GAME_LEVEL][x][y] = 1;
            }
          
        }
        count = 0;
    }
char* get_string(int* len, char rep ) {
    printf("ENTER USERNAME (5 chars):\n");
    *len = 0; 
    int capacity = 1; 
    char* s = (char*)malloc(sizeof(char)); 

    char c = getchar(); 

 
    while (c!='\n') {
        s[(*len)++] = c; 

    
        if (*len >= capacity) {
            capacity *= 2; 
            s = (char*)realloc(s, capacity * sizeof(char)); 
        }

        c = getchar();       
    }

    s[*len] = '\0'; 

    return s;
}



int main() {
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!enableDrawMode(hConsole)) {
        printf("Failed to initialize drawing. Exit");
        return -1;
    }


   // printf(SYS "0;Arcanoid" ESC "0x5C");
  
    clearCon();
    setDrawingColor(BORDER_COLOR);
    resetColor();
    genarate_level();
    GAME_LEVEL = 1;
    USERNAME_LEN = 5;
    GAME_SCORE = 0;
    onBuffer();
    hideCursor();
    FILE  *score_board,*write_score;
    int score_board_len = 0;
    int i = 0;
    char name[5];
    int score = 0;
    score_board = fopen("scoreboard.txt", "r");
    while (!feof(score_board))
    {   
        fscanf(score_board, "%s %d", &name, &score);
        SCOREBOARD[i].name = name;
        SCOREBOARD[i].score = score;
        i++;
        printf("%s %d", name, score);
    }
   // while (fscanf(score_board, "%s%d",
  //      scoreboard[score_board_len].name, &scoreboard[score_board_len].score != EOF)) {
  //      score_board_len++;
  //  }
    USERNAME = get_string(&USERNAME_LEN, '\n');
    while (GAME_LEVEL<10 && !GAME_OVER){
        genarate_level();
        BLOCK_COUNT = GAME_LEVEL * 5 ;
        GAME_OVER = !roundLoop(GAME_LEVEL, hConsole);
        if(!GAME_OVER) {
            GAME_LEVEL++;
        }
        else {
            int choice = 0;
            printf("%d", GAME_OVER);
            printf("GAME OVER TRY AGAIN?\n 1 - YES\n 0 - NO\n");
            scanf("%d", &choice);
           
            if (choice) {
                GAME_LEVEL = 1;
                GAME_SCORE = 0;
                GAME_OVER = FALSE;
            }
            
        }
    }
   /// system("dir");
    write_score = fopen("scoreboard.txt", "a");
    fprintf(write_score, "%s %d\n", USERNAME, GAME_SCORE);
    fclose(write_score);
    offBuffer();
    showCursor();
    return 0;
}