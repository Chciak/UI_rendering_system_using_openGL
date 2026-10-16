#include "MeshObject.h"
#include "debugInfo.h"

#include <GL/gl.h>
#include <GL/glext.h>

template<int Size, MeshObject_T type>
MeshObject<Size, type>::MeshObject()
    :shaderProgram(nullptr)
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
MeshObject<Size, type>::MeshObject(ShaderProgram &shaderP,Mesh &mesh) 
    : MeshObject<Size, type>()
{

    shaderProgram = &shaderP;
    meshPointer = &mesh;
    render = [this]()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        this->bindArrays();
        shaderProgram->makeCurrent();
        glDrawArrays(GL_TRIANGLES, 0, meshPointer->size());
    };

    loadData = [this]()
    {
        this->bindArrays();
        glBufferData(GL_ARRAY_BUFFER, meshPointer->size() * sizeof((*meshPointer)[0]), meshPointer->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)0);
        glVertexAttribPointer(1, Size, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    };

    loadData();
}

template<int Size, MeshObject_T type>
void MeshObject<Size, type>::bindArrays()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER ,VBO);
    
    if(type == INDEXED)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_BINDING, EBO);
    }
}


