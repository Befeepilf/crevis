#ifndef FILE_OBJ_PARSER_H
#define FILE_OBJ_PARSER_H

#include "file/file.hpp"
#include "renderer/mesh.hpp"

class OBJParser
{
    public:
        static Mesh* parse(File* file);
};

#endif // FILE_OBJ_PARSER_H