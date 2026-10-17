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
    float data[Size];
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

template<int Size, MeshObject_T type, bool bakcPropagated>
class MeshObject
{
    protected:

    typedef std::vector<MeshData<Size>> Mesh;

    GLuint VAO, VBO;

    ShaderProgram *shaderProgram;
    Mesh meshPointer;

    public:
    MeshObject();
    MeshObject(ShaderProgram &shaderP, Mesh &mesh);
    virtual inline void bindArrays();
    virtual inline void genBuffers();
    std::function<void()> render;
    std::function<void()> loadData;
};

template<int Size, bool bakcPropagated>
class MeshObject <Size, INDEXED, bakcPropagated> : public MeshObject<Size, BASIC, true>
{
    typedef std::vector<MeshData<Size>> Mesh;

    GLuint EBO;
    std::vector<int> eboDataPointer;

    public:
    MeshObject() : MeshObject<Size, BASIC, true>(){};
    MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<int> &eboDataPointer);
    inline void bindArrays() override;
    inline void genBuffers() override;
};

template class MeshObject<3, INDEXED, false>;
template class MeshObject<3, BASIC, false>;
template class MeshObject<3, BASIC, true>;
