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
void set_init(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS]);
void player_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos);
void robots_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS]);
void scrap(int board[][HORIZONTAL],int status[][HORIZONTAL],int r_xpos[ROBOTS],int r_ypos[ROBOTS]);

int main(void)
{
  int board[VERTICAL][HORIZONTAL];
  int status[VERTICAL][HORIZONTAL];
  int p_xpos,p_ypos;
  int r_xpos[ROBOTS],r_ypos[ROBOTS];
  
  board_init(board,status);
  set_init(board,status,&p_xpos,&p_ypos,r_xpos,r_ypos);
  cre_board(board);
  while(1){
    player_move(board,status,&p_xpos,&p_ypos);
    robots_move(board,status,&p_xpos,&p_ypos,r_xpos,r_ypos);
    scrap(board,status,r_xpos,r_ypos);
    cre_board(board);
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
void set_init(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS])
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
  while(count<ROBOTS){
    r_ypos[count] = 1+rand()%(VERTICAL-2);
    r_xpos[count] = 1+rand()%(HORIZONTAL-2);
    if(status[r_ypos[count]][r_xpos[count]]==EMPTY){
      board[r_ypos[count]][r_xpos[count]] = '+';
      status[r_ypos[count]][r_xpos[count]] = ROBOT;
      count++;
    }
  }
}
void player_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos)
{
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
    board[p_y][p_x] = '@';
    status[p_y][p_x] = PLAYER;
    *p_ypos = p_y;
    *p_xpos = p_x;
  }else{
    p_y = *p_ypos;
    p_x = *p_xpos;
    board[p_y][p_x] = '@';
  }
}
void robots_move(int board[][HORIZONTAL],int status[][HORIZONTAL],int *p_xpos,int *p_ypos,int r_xpos[ROBOTS],int r_ypos[ROBOTS])
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
      board[r_ypos[i]][r_xpos[i]] = '+';
      status[r_ypos[i]][r_xpos[i]] = ROBOT;
    }
  }
}
void scrap(int board[][HORIZONTAL],int status[][HORIZONTAL],int r_xpos[ROBOTS],int r_ypos[ROBOTS])
{
  int i,j;
  
  for(i=0;i<ROBOTS;i++){
    for(j=i+1;j<ROBOTS;j++){
      if(r_ypos[i] == r_ypos[j] && r_xpos[i] == r_xpos[j]){
	board[r_ypos[i]][r_xpos[i]] = '*';
	status[r_ypos[i]][r_xpos[i]] = SCRAP;
      }
    }
  }
}

