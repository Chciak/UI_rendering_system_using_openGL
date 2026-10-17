#include "MeshObject.h"
#include "debugInfo.h"

#include <GL/gl.h>
#include <GL/glext.h>
#include <cstddef>
#include <iterator>

template<int Size, MeshObject_T type, bool bakcPropagated>
MeshObject<Size, type, bakcPropagated>::MeshObject()
    :shaderProgram(nullptr)
{
    
}

template<int Size, MeshObject_T type, bool bakcPropagated>
MeshObject<Size, type, bakcPropagated>::MeshObject(ShaderProgram &shaderP,Mesh &mesh) 
    :MeshObject<Size, type, bakcPropagated>()
{

    shaderProgram = &shaderP;
    meshPointer = mesh;

    if(bakcPropagated == false)
    {
        render = [this]()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            this->bindArrays();
            shaderProgram->makeCurrent();
            glDrawArrays(GL_TRIANGLES, 0, meshPointer.size());
        };
    }

    if(bakcPropagated == false)
    {
        this->genBuffers();

        loadData = [this]()
        {
            this->bindArrays();
            glBufferData(GL_ARRAY_BUFFER, meshPointer.size() * sizeof(meshPointer[0]), meshPointer.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)0);
            glVertexAttribPointer(1, Size, GL_FLOAT, GL_FALSE, (3 + Size) * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
        };

        loadData();
    }
}

template<int Size, bool bakcPropagated>
MeshObject<Size, INDEXED, bakcPropagated>::MeshObject(ShaderProgram &shaderP, Mesh &mesh, std::vector<int> &eboData)
    :MeshObject<Size, BASIC, true>(shaderP, mesh)
{
    this->genBuffers();

    eboDataPointer = eboData;

    this->render = [this]()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        this->bindArrays();
        this->shaderProgram->makeCurrent();
        glDrawElements(GL_TRIANGLES, this->eboDataPointer.size(), GL_UNSIGNED_INT, 0);
    };

    this->loadData = [this]()
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
    };
    
    this->loadData();
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
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
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
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1,&(this->VBO));
    glGenBuffers(1, &(this->EBO));
}
