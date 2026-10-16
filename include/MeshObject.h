#pragma  once

#include <functional>
#include <glad/gl.h>
#include <vector>
#include "ShaderProgram.h"


struct Coordinates
{
    float x,y,z;
};

template<int Size, bool hasUV = (Size == 2), bool hasMore = (Size > 2)>
struct MeshData : public Coordinates
{
    union
    {
        float data[Size];

        struct
        {
            float U;
            float V;
        };
    };
};

template<int Size>
struct MeshData<Size, true, false>
{
    Coordinates coordinates;
    union
    {
        float other[Size];
        
        struct
        {
            float U;
            float V;
        };
    };
};

template<int Size>
struct MeshData<Size, false, true>
{
    Coordinates coordinates;

    union
    {
        float other[Size];
        
        struct
        {
            float U;
            float V;
            float W;
        };

        struct
        {
            float r;
            float g;
            float b;
        };
    };
};

enum MeshObject_T
{
    BASIC,
    INDEXED,
    INSTANCED
};

template<int Size, MeshObject_T type>
class MeshObject
{
    typedef std::vector<MeshData<Size>> Mesh;

    GLuint VAO, VBO, EBO;
    ShaderProgram *shaderProgram;
    Mesh *meshPointer;

    public:
    MeshObject();
    MeshObject(ShaderProgram &shaderP, Mesh &mesh);
    void bindArrays();
    std::function<void()> render;
    std::function<void()> loadData;
};

template class MeshObject<3, BASIC>;
template class MeshObject<2, BASIC>;