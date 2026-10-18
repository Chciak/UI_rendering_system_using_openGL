#pragma  once

#include <functional>
#include <glad/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>
#include "ShaderProgram.h"
#include <glm/glm.hpp>

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
    Mesh *meshPointer;

    public:
    MeshObject(MeshObject const &) = delete;
    MeshObject& operator=(const MeshObject&) = delete;

    MeshObject();
    MeshObject(ShaderProgram &shaderP, Mesh &mesh);
    virtual ~MeshObject();

    virtual inline void bindArrays();
    virtual inline void genBuffers();
    virtual inline void render();
    virtual inline void loadData();
};

template<int Size, bool bakcPropagated>
class MeshObject <Size, INDEXED, bakcPropagated> : public MeshObject<Size, BASIC, true>
{
    protected:

    typedef std::vector<MeshData<Size>> Mesh;

    GLuint EBO;
    std::vector<int> *eboDataPointer;

    public:
    MeshObject(MeshObject &) = delete;
    MeshObject& operator=(const MeshObject&) = delete;

    MeshObject() : MeshObject<Size, BASIC, true>(){};
    MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<int> &eboDataPointer);
    virtual ~MeshObject() override;

    virtual inline void bindArrays() override;
    virtual inline void genBuffers() override;
    virtual inline void render() override;
    virtual inline void loadData() override;
};

template<int Size, bool bakcPropagated>
class MeshObject <Size, INSTANCED, bakcPropagated> : public MeshObject<Size, INDEXED, true>
{
    typedef std::vector<MeshData<Size>> Mesh;

    GLuint instanceVBO;
    std::vector<glm::mat4> *offsetDataPointer;
    public:

    MeshObject(MeshObject &) = delete;
    MeshObject& operator=(const MeshObject&) = delete;

    MeshObject() : MeshObject<Size, INDEXED, true>(){};
    MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<int> &eboDataPointer, std::vector<glm::mat4> &transformation);
    ~MeshObject() override;

    inline void bindArrays() override;
    inline void genBuffers() override;
    inline void render() override;
    inline void loadData() override;

};

template class MeshObject<3, INSTANCED, false>;
template class MeshObject<3, INDEXED, true>;
template class MeshObject<3, INDEXED, false>;
template class MeshObject<3, BASIC, false>;
template class MeshObject<3, BASIC, true>;
