#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"

void play(SDL_Surface* window)
{
  int i,j,contuner=1,turne=0;
  int now=0,ex=0,FPS=60,dt=0;
  float delta_s=0;
  WinW win;
  SDL_Surface *surface=NULL,*X=NULL,*O=NULL,*blank=NULL,*WIN=NULL;
  int **Tab =NULL;
  SDL_Event event;
  SDL_Rect position,surfacepos;
  Tab=(int**)calloc(NB_BLOC_H, sizeof(int*));
  if (Tab==NULL)
  {
    printf("err allocation Tab!\n");
    EXIT_FAILURE;
  }
  for (i = 0; i < NB_BLOC_L; i++)
  {
    Tab[i]=(int*)calloc(NB_BLOC_L, sizeof(int));
    if (Tab[i]==NULL)
    {
      printf("err allocation Tab!\n");
      EXIT_FAILURE;
    }
  }
  O=IMG_Load("data/OO.png");
  X=IMG_Load("data/XX.png");
  blank=IMG_Load("data/blank.png");

  surface=IMG_Load("data/bbackground.png");
  for (i = 0; i < NB_BLOC_L; i++)

    for ( j = 0; j < NB_BLOC_H; j++)
    printf("%d\n",Tab[i][j] );
  SDL_EnableKeyRepeat(100, 100);
  surfacepos.x=0;surfacepos.y=0;
  SDL_BlitSurface(surface,NULL,window,&surfacepos);

  while (contuner)
  {
    now =SDL_GetTicks();
    dt=now-ex;
    if(dt>FPS)
{
    SDL_WaitEvent(&event);
    switch (event.type)
     {
      case SDL_QUIT:
        contuner=0;
        break;
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
        contuner=0;
        break;

        // turne == 0 -> X turne,turne =1 -> O turn
        case SDLK_KP1:
        change(2, 0,&turne,Tab);
        break;
        printf("Y1\n");
        break;
        case SDLK_KP2:
        //TODO
        change(2,1 ,&turne,Tab);
        printf("Y2\n");
        break;
        case SDLK_KP3:
        //TODO
        change(2, 2,&turne,Tab);
        printf("Y3\n");

        break;
        case SDLK_KP4:
        //TODO
        change(1, 0,&turne,Tab);
        break;
        case SDLK_KP5:
        //TODO
        change(1, 1,&turne,Tab);
        break;
        case SDLK_KP6:
        //TODO
        change(1, 2,&turne,Tab);
        break;
        case SDLK_KP7:
        //TODO
        change(0, 0,&turne,Tab);
        break;
        case SDLK_KP8:
        //TODO
        change(0, 1,&turne,Tab);
        break;

        case SDLK_KP9:
        //TODO
        change(0,2,&turne,Tab);
        break;

      }
      break;
    }
    printf("--------\n");

    for (i = 0; i < NB_BLOC_L; i++){
printf("\n" );
      for ( j = 0; j < NB_BLOC_H; j++)
      printf("%d|",Tab[i][j] );}
      printf("\n--------\n");

  //  SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));
    for (i = 0; i < NB_BLOC_L; i++)
    {
      for ( j = 0; j < NB_BLOC_H; j++)
      {
        position.x=j*TAILLE_BLOC;
        position.y=i*TAILLE_BLOC;
        switch (Tab[i][j])
        {
          case 1:
          SDL_BlitSurface(blank,NULL,window,&position);
          SDL_BlitSurface(X,NULL,window,&position);
          break;
          case 2:
          SDL_BlitSurface(blank,NULL,window,&position);
          SDL_BlitSurface(O,NULL,window,&position);
          break;
        }
      }
    }


  win=cheekWin(Tab);
  if (win.winDiago1==1)
  {
    WIN=IMG_Load("data/windiago1.png");
  }
  if (win.winDiago2==1)
  {
    WIN=IMG_Load("data/windiago2.png");
  }if (win.winColum==1) {
    WIN=IMG_Load("data/wincolum.png");
  }
  if (win.winRow==1) {
    WIN=IMG_Load("data/winrow.png");
  }
  SDL_BlitSurface(WIN,NULL,window,&win.pos);
  if (win.win==1)
  {

    //contuner=0;
    printf("presse space to replay\n");
  }
  SDL_Flip(window);
  ex=now;
}else
{
  SDL_Delay(FPS-dt);
}
}

  SDL_EnableKeyRepeat(0, 0);


  for ( i = 0; i < 3; i++)
  {
    free(Tab[i]);

  }
  free(Tab);
  SDL_FreeSurface(WIN);
  SDL_FreeSurface(O);
  SDL_FreeSurface(X);
  SDL_FreeSurface(surface);


}
void change(int i,int j,int* turne,int **Tab)
 {

  if (*turne==0&&Tab[i][j]==0)
  {
  Tab[i][j]=1;
  *turne=1;
  }
  else if(*turne==1&&Tab[i][j]==0)
  {
  Tab[i][j]=2;
  *turne=0;
  }
}
WinW cheekWin(int **Tab)
{
  int i;
  WinW win;
  win.pos.x=0;
  win.pos.y=0;
  if (Tab[0][0]==Tab[1][1]&&Tab[1][1]==Tab[2][2]&&Tab[0][0]!=0)
   {
    if (Tab[1][1]==1)
    {
      printf("X win\n");
    } else if (Tab[1][1]==2) {
      printf("O win\n");
    }
    win.win=1;

    win.winDiago1=1;
  }
  if (Tab[0][2]==Tab[1][1]&&Tab[1][1]==Tab[2][0]&&Tab[0][2]!=0)
  {
    if (Tab[1][1]==1)
    {
      printf("X win\n");
    } else if (Tab[1][1]==2)
    {
      printf("O win\n");
    }
    win.win=1;

    win.winDiago2=1;

    }
  for ( i = 0; i < NB_BLOC_H; i++)
   if(Tab[0][i]==Tab[1][i]&&Tab[1][i]==Tab[2][i]&&Tab[0][i]!=0)
  {
    if (Tab[i][1]==1||Tab[1][i]==1)
    {
      printf("X win\n");
    } else if (Tab[i][1]==2||Tab[1][i]==2)
    {
      printf("O win\n");
    }
    win.win=1;

    win.pos.x=i*TAILLE_BLOC+40;
    win.pos.y=0;
    win.winColum=1;
  }
  for ( i = 0; i < NB_BLOC_H; i++)
    if (Tab[i][0]==Tab[i][1]&&Tab[i][1]==Tab[i][2]&&Tab[i][0]!=0)
    {
      if (Tab[i][1]==1||Tab[1][i]==1)
      {
        printf("X win\n");
      } else if (Tab[i][1]==2||Tab[1][i]==2)
      {
        printf("O win\n");
      }
      win.pos.y=i*TAILLE_BLOC+40;
      win.pos.x=0;
      win.win=1;
      win.winRow=1;
    }


return win;
}
