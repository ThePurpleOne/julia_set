/*
	* HEADER SDL_ABSTRACT
	* Author : Jonas S.
	* Date   : 26/03/2022
	! SDL ABSTRACTION LAYER TO MAKE IT EASIER TO USE
*/

#ifndef _SDL_ABSTRACT_H_
#define _SDL_ABSTRACT_H_

#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>

// DEFINES
#define FPS		   200
#define FRAME_TIME (1000 / FPS)

#define WINDOW_NAME	  "Testing OPENGL"
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

// PROTOTYPE FUNCTIONS
int32_t SDL_SpawnAll(SDL_Window** pp_win_);
void	SDL_killAll(SDL_Window** pp_win_);

#endif