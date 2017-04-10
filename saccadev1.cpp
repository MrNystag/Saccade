#include <stdlib.h>
# include <stdio.h>
# include <iostream>
# include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


using std::cerr;
using std::endl;

class SystemManager {
    public:
        // Here we will just have a couple public members for example purposes.
        bool running;
        SDL_Event events;
        void inputManager(); // Handle input.
        void renderingManager(); // Handle drawing pretty pictures.
};
void SystemManager::inputManager() {
    while(SDL_PollEvent(&events)) {
        if(events.type == SDL_QUIT)
            running = false;
    }
}
void SystemManager::renderingManager() {
    // Draw pretty pictures...
}
int main( int argc, char *argv[ ] ) {
    SDL_Surface *screen;
    SystemManager sysMgr;
    sysMgr.running = true;
    int lastrender = 0;
    char* afficher;
    if( SDL_Init( SDL_INIT_JOYSTICK | SDL_INIT_VIDEO ) == -1 )
    {
        printf( "Can't init SDL: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }
    atexit( SDL_Quit );
    screen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE );
    if( !screen)
    {
        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }
    if (TTF_Init() != 0)
   {
      cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
      SDL_Quit();
      exit(1);
   }

   // Load a font
   TTF_Font *font;
   font = TTF_OpenFont("angelina.TTF", 24);
   if (font == NULL)
   {
      cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
      TTF_Quit();
      SDL_Quit();
      exit(2);
   }

   // Write text to surface
   SDL_Surface *text;
   SDL_Color text_color;
   text = TTF_RenderText_Solid(font,
   "1",
   text_color);

   if (text == NULL)
   {
      cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
    SDL_Rect position;
    SDL_Surface *rectangle = NULL;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 12, 12, 16, 1, 0, 0, 0);
    position.x = screen->w/2;
    position.y = screen->h/2;
    SDL_Event event;
    int val = 0;

    while(sysMgr.running)
    {
        val = rand()%9;
    sprintf(afficher, "%d", val);
    printf("%d - %s", val, afficher);
    sysMgr.inputManager();
    sysMgr.renderingManager();
    text_color;
    text = TTF_RenderText_Solid(font,afficher,text_color);
    TTF_SizeText(font,"Hello World!",&val,&val);
    SDL_BlitSurface(text, NULL, screen, &position);
   // SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
   // SDL_BlitSurface(rectangle, NULL, screen, &position); // Collage de la surface sur l'écran

    SDL_Flip(screen); // Mise à jour de l'écran
   // SDL_Delay( 100 );
   // SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
   // SDL_BlitSurface(rectangle, NULL, screen, &position); // Collage de la surface sur l'écran

    SDL_Delay(((rand()%10)*200));

    text_color;
    text = TTF_RenderText_Solid(font,afficher,text_color);
    SDL_BlitSurface(text, NULL, screen, &position);
    position.x = rand()%screen->w;
            }
  return EXIT_SUCCESS;
}
