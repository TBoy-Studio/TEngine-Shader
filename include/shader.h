#ifndef SHADER_H
#define SHADER_H

#include <cglm/cglm.h>
#include <stdio.h>
#include <glad/glad.h>

typedef unsigned int Shader;

Shader shader_create(const char* vertexPath, const char* fragmentPath);

void shader_use(Shader shader);

void shader_set_bool(Shader shader, const char* name, unsigned char value);

void shader_set_int(Shader shader, const char* name, int value);

void shader_set_float(Shader shader, const char* name, float value);

void shader_set_vec3(Shader shader, const char* name, vec3 value);

void shader_set_mat4(Shader shader, const char* name, mat4 value);

#endif
