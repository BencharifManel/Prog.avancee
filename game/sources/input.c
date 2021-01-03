#include "../headers/input.h"


void getInput(Input *input){
    SDL_Event event;

    //Keymapping : pour les touche du clavier

    //SDL_PollEvent : test s'il y a des �v�nements en attente ou non
    while (SDL_PollEvent(&event)){
        //Test du type d'�v�nement
        switch (event.type){
            case SDL_QUIT:
                exit(0);
            break;

            //Quand une touche est enfonc�e, on active l'�v�nement correspondant
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        exit(0);
                    break;

                    case SDLK_DELETE:
                        input->erase = 1;
                    break;

                    case SDLK_SPACE:
                        input->jump = 1;
                    break;

                    case SDLK_v:
                        input->attack = 1;
                    break;

                    case SDLK_LEFT:
                        input->left = 1;
                    break;

                    case SDLK_RIGHT:
                        input->right = 1;
                    break;

                    case SDLK_DOWN:
                        input->down = 1;
                    break;

                    case SDLK_UP:
                        input->up = 1;
                    break;


                    case SDLK_RETURN:
                        input->enter = 1;
                    break;


                    default:
                    break;
                }
            break;

            //Quand la touche est relev�e, on d�sactive l'�v�nement correspondant
            case SDL_KEYUP:
                switch (event.key.keysym.sym){
                    case SDLK_DELETE:
                        input->erase = 0;
                    break;

                    case SDLK_SPACE:
                        input->jump = 0;
                    break;

                    case SDLK_LEFT:
                        input->left = 0;
                    break;

                    case SDLK_RIGHT:
                        input->right = 0;
                    break;

                    case SDLK_DOWN:
                        input->down = 0;
                    break;

                    case SDLK_UP:
                        input->up = 0;
                    break;

                    case SDLK_RETURN:
                        input->enter = 0;
                    break;

                    default:
                    break;
                }
            break;
        }

    }
}
