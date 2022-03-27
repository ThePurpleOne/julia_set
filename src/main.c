/*
	* CODE MAIN
	* Author : Jonas S.
	* Date   : 19/03/2022
	! JULIA SET
	! docs : https://docs.gl/
*/

//#include <GL/gl.h>
#include "../include/j_shaders.h"
#include "../include/sdl_abstract.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define ANGULAR_SPEED 0.01f
#define PI			  3.14

int main()
{
	SDL_Window* window = NULL;
	SDL_Event	event;

	// ! LOOP AND EVENTS VARIABLES
	bool	 running_loop = true;
	uint32_t first_ticks, ms_loop;
	float	 fps = 0;

	if (SDL_SpawnAll(&window) == 0)
	{
		printf("SDL STUFF SUCCESSFULLY SPAWNED!\n");
	}

	SDL_GLContext gl_ctx = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed: %s", glewGetErrorString(err));
		exit(1);
	}


	// !-------------------------------
	// ! ----- SHADERS MANAGEMENT -----
	// !-------------------------------
	char** shaders = j_shader_read("src/shaders/julia_vertex.glsl",
								   "src/shaders/julia_fragment.glsl");

	unsigned int shader_program = j_shader_create(shaders[0], shaders[1]);

	// !-------------------------------
	// ! -------- SHAPE TO DRAW -------
	// !-------------------------------
	float positions[] = { -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f };
	unsigned int indices[] = { 0, 1, 2, 1, 3, 2 };

	// !-------------------------------
	// ! ----- VERTEX ARRAY OBJECT ----
	// !-------------------------------
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// !-------------------------------
	// ! ---- VERTEX BUFFER OBJECT ----
	// !-------------------------------
	unsigned int vbo; // VERTEX BUFFER OBJECT
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, positions,
				 GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);


	// !-------------------------------
	// ! ----- INDEX BUFFER OBJECT ----
	// !-------------------------------
	unsigned int ibo; // INDEX BUFFER OBJECT
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices,
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(shader_program);

	glClearColor(0.1f, 0.1f, 0.1f, 0.8f);

	double teta = 0.0;

	while (running_loop)
	{
		first_ticks = SDL_GetTicks();

		// !-------------------------------
		// ! ------------ EVENT -----------
		// !-------------------------------
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: // QUIT ON ESCAP
						running_loop = false;
						break;
				}
			}
		}

		// !-------------------------------
		// ! ----------- UPDATE -----------
		// !-------------------------------
		glUseProgram(shader_program);
		if (teta < PI * 2)
			teta += ANGULAR_SPEED;
		else
			teta = 0;
		// printf("TETA :  %f\n", teta);

		int vertexColorLocation = glGetUniformLocation(shader_program, "teta");
		glUniform1f(vertexColorLocation, teta);

		// !-------------------------------
		// ! ------------ DRAW ------------
		// !-------------------------------
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window);

		// !-------------------------------
		// ! ------------- FPS ------------
		// !-------------------------------
		ms_loop = SDL_GetTicks() - first_ticks;
		ms_loop = ms_loop == 0 ? 1 : ms_loop;
		// Cap at 1 to avoir division by 0
		// if Time taken to render smaller than needed frame time
		if (ms_loop < FRAME_TIME)
		{
			SDL_Delay(FRAME_TIME - ms_loop);
		}
		ms_loop = SDL_GetTicks() - first_ticks;
		fps		= 1000.0f / ms_loop;
		printf("%.0f FPS\r", fps);
	}

	// FREE AND DELETE SHADERS
	glDeleteProgram(shader_program);
	free(shaders[0]);
	free(shaders[1]);
	free(shaders);

	SDL_GL_DeleteContext(gl_ctx);
	SDL_killAll(&window);

	return 0;
}
