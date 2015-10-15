#pragma once

#include <iostream>
#include <string>
#include <u_engine_includes.h>

class Texture
{
public:
    // Static textures go here
    static Texture *dirt, *stone;
private:
    GLuint texture;
    GLuint load(const std::string& filepath);
public:
    Texture(const std::string& file);
    static void DESTROY();
    static void LOAD();
    void enable();
    void disable();
};