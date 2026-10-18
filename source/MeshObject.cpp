#include "MeshObject.h"

#include <GL/gl.h>
#include <GL/glext.h>

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
    meshPointer = mesh;

    if constexpr (bakcPropagated == false)
    {
        genBuffers();
        loadData();
    }
}

template<int Size, bool bakcPropagated>
MeshObject<Size, INDEXED, bakcPropagated>::MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<int> &eboData)
    :MeshObject<Size, BASIC, true>(shaderP, mesh)
{
    eboDataPointer = eboData;
    if(bakcPropagated == false)
    {
        this->genBuffers();
        this->loadData();
    } 
}

template<int Size, MeshObject_T type, bool bakcPropagated>
inline void MeshObject<Size, type, bakcPropagated>::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    this->bindArrays();
    shaderProgram->makeCurrent();
    glDrawArrays(GL_TRIANGLES, 0, meshPointer.size());
}

template<int Size, MeshObject_T type, bool bakcPropagated>
inline void MeshObject<Size, type, bakcPropagated>::loadData()
{
    this->bindArrays();
    glBufferData(GL_ARRAY_BUFFER, meshPointer.size() * sizeof(meshPointer[0]), meshPointer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)0);
    glVertexAttribPointer(1, Size, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INDEXED, bakcPropagated>::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    bindArrays();
    this->shaderProgram->makeCurrent();
    glDrawElements(GL_TRIANGLES, this->eboDataPointer.size(), GL_UNSIGNED_INT, 0);
}

template<int Size, bool bakcPropagated>
inline void MeshObject<Size, INDEXED, bakcPropagated>::loadData()
{
    std::cout << "data size" << this->meshPointer.data() << '\n';
    std::cout << "EBO size" << this->eboDataPointer.size() << '\n';
    this->bindArrays();
    glBufferData(
        GL_ARRAY_BUFFER,
        this->meshPointer.size() * sizeof(MeshData<Size>), 
        this->meshPointer.data(), 
        GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)0);
    glVertexAttribPointer(1, Size, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        this->eboDataPointer.size() * (sizeof(int)), 
        this->eboDataPointer.data(), 
        GL_STATIC_DRAW); 

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}


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