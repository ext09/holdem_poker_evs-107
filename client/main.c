#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;

SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = { 0, 0, 0 };

Mix_Music *music = NULL;

int false=1;
int true=0;
int quit=0;

int init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
    {
        return false;
    }

    if( TTF_Init() == -1 )
    {
        return false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 8192 ) == -1 )
    {
        return false;
    }

    SDL_WM_SetCaption( "Poker 1-EVS-107", NULL);

    return true;
}

int load_files()
{
    background = IMG_Load ( "background.jpg" );

    font = TTF_OpenFont( "CALIFI.ttf", 30 );

    if( background == NULL )
    {
        return false;
    }

    if( font == NULL )
    {
        return false;
    }

    music = Mix_LoadMUS( "music.mp3" );

    if( music == NULL )
    {
        return false;
    }

    if(Mix_FadeInMusic(music,0,2000)==-1)
    {
        printf("Mix_FadeInMusic: %s\n", Mix_GetError());
    }

    return true;
}

void apply_surface( int x, int y,SDL_Surface* source,SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface( source, NULL, destination,&offset);
}

void clean_up()
{
    SDL_FreeSurface( background );

    Mix_FreeMusic( music );

    TTF_CloseFont( font );

    Mix_CloseAudio();

    TTF_Quit();

    SDL_Quit();
}

int main( int argc, char* args[] )
{
    int quit = false;

    if( init() == false )
    {
        return false;
    }

    if( load_files() == false )
    {
        return false;
    }

    apply_surface( 0, 0, background, screen );

    message = TTF_RenderText_Solid( font, "Start game", textColor );

    if( message == NULL )
    {
        return false;
    }

    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 100, message, screen );

    SDL_FreeSurface( message );

    message = TTF_RenderText_Solid( font, "Options", textColor );

    if( message == NULL )
    {
        return false;
    }

    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 200, message, screen );

    SDL_FreeSurface( message );

    message = TTF_RenderText_Solid( font, "Exit", textColor );

    if( message == NULL )
    {
        return false;
    }

    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 300, message, screen );

    SDL_FreeSurface( message );

    message = TTF_RenderText_Solid( font, "Press 9 to play/pause the music", textColor );

    if( message == NULL )
    {
        return false;
    }

    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 400, message, screen );

    SDL_FreeSurface( message );

        message = TTF_RenderText_Solid( font, "Press 0 to stop the music", textColor );

    if( message == NULL )
    {
        return false;
    }

    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 500, message, screen );

    SDL_FreeSurface( message );

    if( SDL_Flip( screen ) == -1 )
    {
        return false;
    }

    while( quit == false )
    {
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_KEYDOWN )
            {
                if( event.key.keysym.sym == SDLK_6)
                {
                    Mix_RewindMusic();
                    if(Mix_SetMusicPosition(60.0)==-1)
                    {
                        return false;
                    }
                }
                else if( event.key.keysym.sym == SDLK_9 )
                {
                    if( Mix_PlayingMusic() == 0 )
                    {
                        if( Mix_PlayMusic( music, -1 ) == -1 )
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if( Mix_PausedMusic() == 1 )
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                }
                else if( event.key.keysym.sym == SDLK_0 )
                {
                    Mix_HaltMusic();
                }
            }
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }

        }
    }

    clean_up();

    return 0;
}



