#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define ROBOTS 5
#define VERTICAL 20
#define HORIZONTAL 40
#define EMPTY 1
#define WALL 2
#define ROBOT 3
#define SCRAP 4
#define PLAYER 5

void board_init(int board[][HORIZONTAL],int status[][HORIZONTAL]);
void cre_board(int board[][HORIZONTAL]);
void set_init(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS],int level);
void player_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos);
void robots_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS],int *flag,int *score);
void scrap(int board[][HORIZONTAL],int status[][HORIZONTAL],int r_xpos[ROBOTS],int r_ypos[ROBOTS],int *flag,int *score);
void game_over(int board[][HORIZONTAL]);
int check_clear(int status[][HORIZONTAL]);

int main(void)
{
  int board[VERTICAL][HORIZONTAL];
  int status[VERTICAL][HORIZONTAL];
  int p_xpos,p_ypos;
  int flag = 0;
  static int level = 1;
  static int score = 0;
  int r_xpos[ROBOTS*level],r_ypos[ROBOTS*level];
  
  board_init(board,status);
  set_init(board,status,&p_xpos,&p_ypos,r_xpos,r_ypos,level);
  cre_board(board);
  while(flag == 0){
    printf("(LEVEL:%d SCORE:%d):",level,score);
    player_move(board,status,&p_xpos,&p_ypos);
    robots_move(board,status,&p_xpos,&p_ypos,r_xpos,r_ypos,&flag,&score);
    scrap(board,status,r_xpos,r_ypos,&flag,&score);
    if(flag == 1) game_over(board);
    else if(flag == 2){
      flag = check_clear(status);
      if(flag==3){
	score += level*10;
	level++;
	main();
      }
      cre_board(board);
    }else cre_board(board);
  }
}

void board_init(int board[][HORIZONTAL],int status[][HORIZONTAL])
{
  int x,y;
  
  for(y=0;y<VERTICAL;y++){
    for(x=0;x<HORIZONTAL;x++){
      board[y][x] = ' ';
      status[y][x] = EMPTY;
      if(y==0 || y==VERTICAL-1){
	board[y][x] = '-';
	status[y][x] = WALL;
      }
      if(x==0 || x==HORIZONTAL-1){
	board[y][x] = '|';
	status[y][x] = WALL;
      }
      if(y==0 && x==0 || y==0 && x==HORIZONTAL-1 || y==VERTICAL-1 && x==0 || y==VERTICAL-1 && x==HORIZONTAL-1){
	board[y][x] = '+';
	status[y][x] = WALL;
      }
    }
  }
}

void cre_board(int board[][HORIZONTAL])
{
  int x,y;
  
  printf("\n");
  
  for(y=0;y<VERTICAL;y++){
    for(x=0;x<HORIZONTAL;x++){
      printf("%c",board[y][x]);
    }
    printf("\n");
  }
}
void set_init(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS],int level)
{
  int p_y,p_x;
  int count = 0;
  
  srand((unsigned)time(NULL));
  p_y = 1+rand()%(VERTICAL-2);
  p_x = 1+rand()%(HORIZONTAL-2);
  board[p_y][p_x] = '@';
  status[p_y][p_x] = PLAYER;
  *p_xpos = p_x;
  *p_ypos = p_y;
  while(count<ROBOTS*level){
    r_ypos[count] = 1+rand()%(VERTICAL-2);
    r_xpos[count] = 1+rand()%(HORIZONTAL-2);
    if(status[r_ypos[count]][r_xpos[count]]==EMPTY){
      board[r_ypos[count]][r_xpos[count]] = '+';
      status[r_ypos[count]][r_xpos[count]] = ROBOT;
      count++;
      if(count == 40) break;
    }
  }
}
void player_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos)
{
  int i;
  int dir;
  int p_y,p_x;
  int x,y;

  p_y = *p_ypos;
  p_x = *p_xpos;
  scanf("%d",&dir);
  board[p_y][p_x] = ' ';
  status[p_y][p_x] = EMPTY;
  
  switch(dir){
  case 0:
    y = 1+rand()%(VERTICAL-2);
    x = 1+rand()%(HORIZONTAL-2);
    while(status[y][x]!=EMPTY){
      y = 1+rand()%(VERTICAL-2);
      x = 1+rand()%(HORIZONTAL-2);
    }
    p_y = y;
    p_x = x;
    break;
  case 1:
    p_y = p_y+1;
    p_x = p_x-1;
    break;
  case 2:
    p_y = p_y+1;
    p_x = p_x;
    break;
  case 3:
    p_y = p_y+1;
    p_x = p_x+1;
    break;
  case 4:
    p_y = p_y;
    p_x = p_x-1;
    break;
  case 5:
    p_y = p_y;
    p_x = p_x;
    break;
  case 6:
    p_y = p_y;
    p_x = p_x+1;
    break;
  case 7:
    p_y = p_y-1;
    p_x = p_x-1;
    break;
  case 8:
    p_y = p_y-1;
    p_x = p_x;
    break;
  case 9:
    p_y = p_y-1;
    p_x = p_x+1;
    break;
  }
  if(p_y!=0 && p_x!=0 && p_y!=VERTICAL-1 && p_x!=HORIZONTAL-1){
    if(status[p_y][p_x]==EMPTY){
      board[p_y][p_x] = '@';
      status[p_y][p_x] = PLAYER;
      *p_ypos = p_y;
      *p_xpos = p_x;
    }else{
      p_y = *p_ypos;
      p_x = *p_xpos;
      board[p_y][p_x] = '@';
      status[p_y][p_x] = PLAYER;
    }
  }else{
    p_y = *p_ypos;
    p_x = *p_xpos;
    board[p_y][p_x] = '@';
    status[p_y][p_x] = PLAYER;
  }
}
void robots_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS],int *flag,int *score)
{
  int i;

  for(i=0;i<ROBOTS;i++){
    if(status[r_ypos[i]][r_xpos[i]] == ROBOT){
      board[r_ypos[i]][r_xpos[i]] = ' ';
      status[r_ypos[i]][r_xpos[i]] = EMPTY;
      if(r_xpos[i] < *p_xpos) r_xpos[i] += 1;
      if(r_xpos[i] > *p_xpos) r_xpos[i] -= 1;
      if(r_ypos[i] < *p_ypos) r_ypos[i] += 1;
      if(r_ypos[i] > *p_ypos) r_ypos[i] -= 1;
      if(status[r_ypos[i]][r_xpos[i]] == PLAYER) *flag = 1;
      if(status[r_ypos[i]][r_xpos[i]] == SCRAP){
	*flag = 2;
	*score += 1;
      }else{
	board[r_ypos[i]][r_xpos[i]] = '+';
	status[r_ypos[i]][r_xpos[i]] = ROBOT;
      }
    }
  }
}
void scrap(int board[][HORIZONTAL],int status[][HORIZONTAL],int r_xpos[ROBOTS],int r_ypos[ROBOTS],int *flag,int *score)
{
  int i,j;
  
  for(i=0;i<ROBOTS;i++){
    for(j=i+1;j<ROBOTS;j++){
      if(r_xpos[i] == r_xpos[j] && r_ypos[i] == r_ypos[j]){
	if(status[r_ypos[i]][r_xpos[i]] == ROBOT) *score += 2; 
	board[r_ypos[i]][r_xpos[i]] = '*';
	status[r_ypos[i]][r_xpos[i]] = SCRAP;
	*flag = 2;
      }
    }
  }
}
void game_over(int board[][HORIZONTAL])
{
  cre_board(board);
  printf("GAME OVER\n");
}
int check_clear(int status[][HORIZONTAL])
{
  int x,y;
  int count = 0;

  for(y=0;y<VERTICAL;y++){
    for(x=0;x<HORIZONTAL;x++){
      if(status[y][x] == ROBOT) count++;
    }
  }
  if(count == 0) return 3;

  return 0;
}
