#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "vector.h"
#include "mesh.h"

struct Shader
{
	std::string vertex;
	std::string fragment;
};

void parser(const char* fileName, Mesh& obj);
Shader shaderParser(const char* vertexFileName, const char* fragmentFileName);

#endif // !PARSER_H
