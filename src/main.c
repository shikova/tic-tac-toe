#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "game.h"

int main(int argc, char const *argv[])
{
  SDL_Surface *window=NULL,*menu=NULL;
  SDL_Rect posBackground;
  SDL_Event event;
  int continuer=1;
  if (SDL_Init(SDL_INIT_VIDEO)<0)
  {
    EXIT_FAILURE;
  }
  SDL_WM_SetIcon(IMG_Load("data/logo.png"),NULL);
  window=SDL_SetVideoMode(WINDOW_L, WINDOW_H, 32, SDL_HWSURFACE);
  if (window==NULL)
  {
    SDL_Quit();
    EXIT_FAILURE;
  }
  SDL_WM_SetCaption("TIC TAC TOE", NULL);

  menu=IMG_Load("data/menu.png");

  posBackground.x=0;
  posBackground.y=0;
  while (continuer)
  {

    SDL_WaitEvent(&event);

      switch (event.type)
      {

        case SDL_QUIT:
        continuer=0;
        break;
        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
          continuer=0;
          break;
          case SDLK_SPACE:
          printf("Y\n");
          play(window);
          break;

        }
      }
      SDL_FillRect(window, NULL, SDL_MapRGB(window->format,0,0,0));
      SDL_BlitSurface(menu,NULL,window,&posBackground);

      SDL_Flip(window);
  }
  SDL_FreeSurface(menu);
  SDL_Quit();
  return 0;
}
