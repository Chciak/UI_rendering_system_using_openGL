#include "MeshObject.h"

#include <GL/gl.h>
#include <GL/glext.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <iostream>
#include <glm/glm.hpp>

template<int Size, MeshObject_T type, bool bakcPropagated>
MeshObject<Size, type, bakcPropagated>::~MeshObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

template<int Size, bool bakcPropagated>
MeshObject<Size, INDEXED, bakcPropagated>::~MeshObject()
{
    glDeleteBuffers(1, &EBO);
}

template<int Size, bool bakcPropagated>
MeshObject<Size, INSTANCED, bakcPropagated>::~MeshObject()
{
    glDeleteBuffers(1, &instanceVBO);
}


template<int Size, MeshObject_T type, bool bakcPropagated>
MeshObject<Size, type, bakcPropagated>::MeshObject()
{
    VAO = 0;
    VBO = 0;
    shaderProgram = nullptr;
} 

template<int Size, MeshObject_T type, bool bakcPropagated>
MeshObject<Size, type, bakcPropagated>::MeshObject(ShaderProgram &shaderP,Mesh &mesh) 
    :MeshObject<Size, type, bakcPropagated>()
{
    shaderProgram = &shaderP;
    meshPointer = &mesh;

    if constexpr (bakcPropagated == false)
    {
        genBuffers();
        loadData();
    }
}

template<int Size, bool bakcPropagated>
MeshObject<Size, INDEXED, bakcPropagated>::MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<unsigned int> &eboData)
    :MeshObject<Size, BASIC, true>(shaderP, mesh)
{
    eboDataPointer = &eboData;
    if constexpr (bakcPropagated == false)
    {
        this->genBuffers();
        this->loadData();
    } 
}

template<int Size, bool bakcPropagated>
MeshObject<Size, INSTANCED, bakcPropagated>::MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<unsigned int> &eboData, std::vector<glm::mat4> &transformation)
    :MeshObject<Size, INDEXED, true>(shaderP, mesh, eboData)
{
    offsetDataPointer = &transformation;
    if constexpr (bakcPropagated == false)
    {
        this->genBuffers();
        this->loadData();
    }
}

template<int Size, MeshObject_T type, bool bakcPropagated>
inline void MeshObject<Size, type, bakcPropagated>::render()
{
    this->bindArrays();
    shaderProgram->makeCurrent();
    glDrawArrays(GL_TRIANGLES, 0, meshPointer->size());
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INDEXED, bakcPropagated>::render()
{
    this->bindArrays();
    this->shaderProgram->makeCurrent();
    glDrawElements(GL_TRIANGLES, this->eboDataPointer->size(), GL_UNSIGNED_INT, 0);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INSTANCED, bakcPropagated>::render()
{
    bindArrays();
    this->shaderProgram->makeCurrent();
    glDrawElementsInstanced(GL_TRIANGLES, this->eboDataPointer->size(), GL_UNSIGNED_INT, 0, this->offsetDataPointer->size());
}

template<int Size, MeshObject_T type, bool bakcPropagated>
inline void MeshObject<Size, type, bakcPropagated>::loadData()
{
    this->bindArrays();
    glBufferData(GL_ARRAY_BUFFER, meshPointer->size() * sizeof(meshPointer->at(0)), meshPointer->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)0);
    glVertexAttribPointer(1, Size, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INDEXED, bakcPropagated>::loadData()
{
    bindArrays();
    glBufferData(
        GL_ARRAY_BUFFER,
        this->meshPointer->size() * sizeof(MeshData<Size>), 
        this->meshPointer->data(), 
        GL_STATIC_DRAW);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        this->eboDataPointer->size() * (sizeof(int)), 
        this->eboDataPointer->data(), 
        GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, (3 + Size) * sizeof(float), (void*)0);
    glVertexAttribPointer(1, Size, GL_FLOAT, GL_TRUE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INSTANCED, bakcPropagated>::loadData()
{
    
    MeshObject<Size, INDEXED, true>::bindArrays();
    glBufferData(
        GL_ARRAY_BUFFER,
        this->meshPointer->size() * sizeof(MeshData<Size>), 
        this->meshPointer->data(), 
        GL_STATIC_DRAW);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        this->eboDataPointer->size() * (sizeof(int)), 
        this->eboDataPointer->data(), 
        GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, (3 + Size) * sizeof(float), (void*)0);
    glVertexAttribPointer(1, Size, GL_FLOAT, GL_TRUE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        this->offsetDataPointer->size() * sizeof(glm::mat4),
        this->offsetDataPointer->data(),
        GL_STATIC_DRAW);

    for (unsigned int i = 0; i < 4; i++)
    {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(
            2 + i,
            4,
            GL_FLOAT, 
            GL_TRUE, 
            sizeof(glm::mat4),
            (void*)(i * sizeof(glm::vec4))
        );
        glVertexAttribDivisor(2 + i, 1);
    }
}

//  bind buffer definitions
template<int Size, MeshObject_T type, bool bakcPropagated>
inline void MeshObject<Size, type, bakcPropagated>::bindArrays()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER ,VBO);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INDEXED, bakcPropagated>::bindArrays()
{
    MeshObject<Size, BASIC, true>::bindArrays();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INSTANCED, bakcPropagated>::bindArrays()
{
    MeshObject<Size, INDEXED, true>::bindArrays();
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
}

// gen buffer definitions
template<int Size, MeshObject_T type, bool bakcPropagated>
inline void MeshObject<Size, type, bakcPropagated>::genBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INDEXED, bakcPropagated>::genBuffers()
{
    MeshObject<Size, BASIC, true>::genBuffers();
    glGenBuffers(1, &(this->EBO));
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INSTANCED, bakcPropagated>::genBuffers()
{
    MeshObject<Size, INDEXED, true>::genBuffers();
    glGenBuffers(1, &(this->instanceVBO));
}