#include <shader.h>

unsigned int compile_shader(const char* vertex_src, const char* fragment_src){
    // Declare vars
    unsigned int vertex_shader, fragment_shader;
    int success;
    char info[512]; // To store error messages

    // First vertex shader
    vertex_shader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertex_shader, 1, (const char**)&vertex_src, NULL);
    glad_glCompileShader(vertex_shader);
    glad_glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glad_glGetShaderInfoLog(vertex_shader, 512, NULL, info);
        log_error("VERTEX SHADER COMPILATION", info);
        return 0;
    }

    // Then fragment Shader
    fragment_shader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragment_shader, 1, (const char**)&fragment_src, NULL);
    glad_glCompileShader(fragment_shader);
    glad_glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glad_glGetShaderInfoLog(fragment_shader, 512, NULL, info);
        log_error("FRAGMENT SHADER COMPILATION", info);
        return 0;
    }

    // Create program
    Shader program = glad_glCreateProgram();
    glad_glAttachShader(program, vertex_shader);
    glad_glAttachShader(program, fragment_shader);
    glad_glLinkProgram(program);

    // Check for linking errors
    glad_glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glad_glGetProgramInfoLog(program, 512, NULL, info);
        log_error("SHADER PROGRAM LINKING", info);
        return 0;
    }

    glad_glDeleteShader(vertex_shader);
    glad_glDeleteShader(fragment_shader);

    return program;
}

Shader shader_create(const char* vertex_path, const char* fragment_path){
    Shader shader;

    FILE* vertex_file = fopen(vertex_path, "r");
    FILE* fragment_file = fopen(fragment_path, "r");

    // Check if opening files was succesful
    if (vertex_file == NULL) {
        log_error("VERTEX SHADER", "Failed to open file");
        return 0;
    }
    if (fragment_file == NULL) {
        log_error("FRAGMENT SHADER", "Failed to open file");
        return 0;
    }

    // Get the length of the files
    fseek(vertex_file, 0L, SEEK_END);
    unsigned long vertex_file_length = ftell(vertex_file);
    rewind(vertex_file);
    fseek(fragment_file, 0L, SEEK_END);    
    unsigned long fragment_file_length = ftell(fragment_file);    
    rewind(fragment_file);

    // Create buffers to store file contents
    char vertex_src[vertex_file_length + 1];
    char fragment_src[fragment_file_length + 1];

    // Add terminating zeroes to buffers
    vertex_src[vertex_file_length] = '\0';
    fragment_src[fragment_file_length] = '\0';

    // Read from files into buffers
    unsigned long vertex_bytes_read = fread(vertex_src, sizeof(char), vertex_file_length, vertex_file);
    unsigned long fragment_bytes_read = fread(fragment_src, sizeof(char), fragment_file_length, fragment_file);

    // Check if read was succesful
    if(vertex_bytes_read != vertex_file_length){
        log_error("VERTEX SHADER", "Failed to read file");
        return 0;
    }
    if(fragment_bytes_read != fragment_file_length){
        log_error("FRAGMENT SHADER", "Failed to read file");
        return 0;
    }

    // Try and compile shaders
    shader = compile_shader(vertex_src, fragment_src);

    return shader;
}

void shader_use(Shader shader){
    glad_glUseProgram(shader);
}

void shader_set_bool(Shader shader, const char* name, unsigned char value){
    glad_glUniform1i(glad_glGetUniformLocation(shader, name), (int)value);
}

void shader_set_int(Shader shader, const char* name, int value){
    glad_glUniform1i(glad_glGetUniformLocation(shader, name), value);
}

void shader_set_float(Shader shader, const char* name, float value){
    glad_glUniform1f(glad_glGetUniformLocation(shader, name), value);
}

void shader_set_vec3(Shader shader, const char* name, vec3 value){
    glad_glUniform3fv(glad_glGetUniformLocation(shader, name), 1, value);
}

void shader_set_mat4(Shader shader, const char* name, mat4 value){
    glad_glUniformMatrix4fv(glad_glGetUniformLocation(shader, name), 1, GL_FALSE, &value[0][0]);
}
