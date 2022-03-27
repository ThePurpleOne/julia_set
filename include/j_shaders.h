/*
	* HEADER J_SHADERS
	* Author : Jonas S.
	* Date   : 26/03/2022
	! SHADER MANAGEMENT
*/

#ifndef _J_SHADERS_H_
#define _J_SHADERS_H_

#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>

// DEFINES

// PROTOTYPE FUNCTIONS
char**		 j_shader_read(char* fpath_vertex, char* fpath_fragment);
int			 j_shader_compile(unsigned int type, const char* source);
unsigned int j_shader_create(const char* vertex_shader,
							 const char* fragment_shader);

#endif