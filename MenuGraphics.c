
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


SDL_Surface *background = NULL;
SDL_Surface *textSurface = NULL;
SDL_Surface *textSurface1 = NULL;
SDL_Surface *textSurface2 = NULL;
SDL_Surface *screen = NULL;

TTF_Font *font = NULL;
SDL_Color textColor = { 0, 0, 0 };


SDL_Surface *load_image( char* filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename);

    if ( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if ( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 93, 161, 48 ) );
        }
        return optimizedImage;
    }
}

    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
    {
        SDL_Rect offset;

        offset.x = x;
        offset.y = y;

        SDL_BlitSurface( source, clip, destination, &offset );
    }

    int init()
    {
        if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        {
            return 0;
        }

        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

        if ( screen == NULL )
        {
            return 0;
        }

        if ( TTF_Init() == -1 )
        {
            return 0;
        }

        SDL_WM_SetCaption( "TTF Test", NULL );

        return 1;
    }

    int load_files()
    {
        background = load_image( "41331632_14.jpg" );

        font = TTF_OpenFont( "CALIFI.ttf", 36 );


        if ( background == NULL )
        {
            return 0;
        }

        if ( font == NULL )
        {
            return 0;
        }
        return 1;
    }

    void clean_up()
    {
        SDL_FreeSurface( background );
        SDL_FreeSurface( textSurface );
        SDL_FreeSurface( textSurface1 );
        SDL_FreeSurface( textSurface2 );

        TTF_CloseFont( font );

        TTF_Quit();

        SDL_Quit();
    }

    int main( int argc, char *argv[])
    {
        int quit = 0;

        if ( init() == 0 )
        {
            return 1;
        }

        if ( load_files() == 0 )
        {
            return 1;
        }

        textSurface = TTF_RenderText_Solid(font, "Start game", textColor);
        textSurface1 = TTF_RenderText_Solid(font, "Settings", textColor);
        textSurface2 = TTF_RenderText_Solid(font, "Quit", textColor);

        if (textSurface == NULL)
        {
            return 0;
        }

        if (textSurface1 == NULL)
        {
            return 0;
        }

        if (textSurface2 == NULL)
        {
            return 0;
        }

        apply_surface( 0, 0, background, screen, NULL);
        apply_surface( 150, 100, textSurface, screen, NULL );
        apply_surface( 150, 150, textSurface1, screen, NULL );
        apply_surface( 150, 200, textSurface2, screen, NULL );

        SDL_Flip(screen);

        if ( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        SDL_Delay(3000);
        clean_up();
        return 0;

    }
