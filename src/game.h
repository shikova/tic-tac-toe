#ifndef GAME_HEADER
#define GAME_HEADER

typedef struct winwin
{
  int win=0;
  int winDiago1=0;
  int winDiago2=0;
  int winColum=0;
  int winRow=0;
  SDL_Rect pos;
}WinW;

  void play(SDL_Surface* window);
  void change(int i,int j,int* turne,int **Tab);
  WinW cheekWin(int **Tab);


#endif
