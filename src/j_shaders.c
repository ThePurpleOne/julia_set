/*
	* CODE J_SHADERS
	* Author : Jonas S.
	* Date   : 26/03/2022
	! SHADER MANAGEMENT
*/

#include "../include/j_shaders.h"

/**
 * @brief Read the shaders from files and return an array of strings
 * 		  containing the shaders
 *
 * @param fpath_vertex
 * @param fpath_fragment
 * @return char** array[0] = vertex shader,
 * 				  array[1] = fragment shader
 */
char** j_shader_read(char* fpath_vertex, char* fpath_fragment)
{
	char line[200] = { 0 };

	// ! READING VERTEX SHADER
	char  buff_vertex[5000] = { 0 };
	FILE* fp_vertex			= fopen(fpath_vertex, "r");
	if (fp_vertex == NULL)
	{
		fprintf(stderr, "Failed to open file %s\n", fpath_vertex);
		return NULL;
	}
	while (!feof(fp_vertex))
	{
		fgets(line, 200, fp_vertex);
		strcat(buff_vertex, line);
	}

	// ! READING FRAGMENT SHADER
	char  buff_fragment[5000] = { 0 };
	FILE* fp_fragment		  = fopen(fpath_fragment, "r");
	if (fp_fragment == NULL)
	{
		fprintf(stderr, "Failed to open file %s\n", fpath_fragment);
		return NULL;
	}
	while (!feof(fp_fragment))
	{
		fgets(line, 200, fp_fragment);
		strcat(buff_fragment, line);
	}

	fclose(fp_vertex);
	fclose(fp_fragment);

	char** output_array	   = malloc(sizeof(char*) * 2);
	char*  output_vertex   = strdup(buff_vertex);
	char*  output_fragment = strdup(buff_fragment);

	output_array[0] = output_vertex;
	output_array[1] = output_fragment;

	return output_array;
}

int j_shader_compile(unsigned int type, const char* source)
{
	unsigned int id	 = glCreateShader(type);
	const char*	 src = (const char*)source;
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	// ! ERRORS MANAGEMENT
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		printf("Failed to compile %s shader!\n",
			   (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		printf("%s\n", message);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int j_shader_create(const char* vertex_shader,
							 const char* fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int fs = j_shader_compile(GL_FRAGMENT_SHADER, fragment_shader);
	unsigned int vs = j_shader_compile(GL_VERTEX_SHADER, vertex_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}
