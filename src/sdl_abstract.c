/*
	* CODE SDL_ABSTRACT
	* Author : Jonas S.
	* Date   : 26/03/2022
	! SDL ABSTRACTION LAYER TO MAKE IT EASIER TO USE
*/

#include "../include/sdl_abstract.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Setup the basic SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @return int32_t
 */
int32_t SDL_SpawnAll(SDL_Window** pp_win_)
{
	// ! INIT SDL
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to Initialize SDL: %s", SDL_GetError());
		SDL_killAll(pp_win_);
		return EXIT_FAILURE;
	}

	// ! INIT WINDOW
	*pp_win_ = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
								WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (*pp_win_ == NULL)
	{
		printf("Unable to Initialize the Window: %s", SDL_GetError());
		SDL_killAll(pp_win_);
		return EXIT_FAILURE;
	}


	return 0;
}

/**
 * @brief Destroy and free the SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @param pp_ren Pointer to Renderer Pointer
 */
void SDL_killAll(SDL_Window** pp_win_)
{
	// Free the SDL window
	if (pp_win_)
	{
		SDL_DestroyWindow(*pp_win_);
		*pp_win_ = NULL;
	}
	printf("SDL STUFF DESTROYED AND FREED! \n");
}
