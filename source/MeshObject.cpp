#include "MeshObject.h"
#include "debugInfo.h"

template<int Size, MeshObject_T type>
MeshObject<Size, type>::MeshObject()
    :vertex(nullptr), fragment(nullptr)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER ,VBO);

    if constexpr (type == INDEXED)
    {
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_BINDING, EBO);
    }

    if constexpr (type == INSTANCED)
    {
        P_MESHINFO("ISNTANCED MESH NOT SUPPORTED");
    }
}

template<int Size, MeshObject_T type>
MeshObject<Size, type>::MeshObject(std::vector<Shader*> shaders,Mesh &mesh) : MeshObject<Size, type>()
{
    int size = shaders.size();
    if(size <= 1) vertex = shaders[0];
    if(size <= 2) fragment = shaders[1];
    if(&mesh != nullptr) meshPointer = &mesh;
}

