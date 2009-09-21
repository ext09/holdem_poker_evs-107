#include <stdio.h>
#include "menu.h"

int MainMenu()
{
    int choice;
    while(1)
    {
        printf("1-start game, 2-settings, 3-quit:\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                StartMenu();
                break;
            case 2:
                SettingsMenu();
                break;
            case 3:
                return choice;
        }
    }
}
int StartMenu()
{
    printf("smth1\n");
    return 0;
}
int SettingsMenu()
{
    int SCR_WIDTH=640, SCR_HEIGHT=480, COL_DEPTH=32;
    int choice, option;
    FILE *set_file;

    printf(":: Settings Menu ::\n\n");
    set_file = fopen("settings.cfg", "r+");
    if(set_file==NULL)
    {
        printf("Configuration file is missing. Creating a new one with basic options\n");
        set_file = fopen("settings.cfg", "w");
        fprintf(set_file, "%d\n%d\n%d", SCR_WIDTH, SCR_HEIGHT, COL_DEPTH);
    }
    while(1)
    {
        fscanf(set_file, "%d\n%d\n%d", &SCR_WIDTH, &SCR_HEIGHT, &COL_DEPTH);
        printf("Screen Resolution: %dx%d, %d bit\t", SCR_WIDTH, SCR_HEIGHT, COL_DEPTH);
        printf("change - 1\n\n");
        printf("some other info bla bla bla\n\n");
        printf("exit - 0\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("change resolution: 640x480 - 1, 1024x768-2, 1280x1024-3:");
                scanf("%d", &option);
                switch(option)
                {
                    case 1:
                        SCR_WIDTH = 640;
                        SCR_HEIGHT = 480;
                        break;
                    case 2:
                        SCR_WIDTH = 1024;
                        SCR_HEIGHT = 768;
                        break;
                    case 3:
                        SCR_WIDTH = 1280;
                        SCR_HEIGHT = 1024;
                        break;
                }
                break;
            case 0:
                fclose(set_file);
                return 0;
        }
    }
}
