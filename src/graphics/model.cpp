#include <beyrl/graphics/model.hpp>

namespace beyrl {

Model::Model(void *verticies, size_t verticiesSize, unsigned indicies[], size_t indexCount, layout const &layout) : m_vao(), m_vbo(), m_ibo(), m_vertCount(indexCount) {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    bind();
    glBufferData(GL_ARRAY_BUFFER, verticiesSize, verticies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned), indicies, GL_STATIC_DRAW);

    for (int i = 0; i < layout.elements.size(); i++) {
        glVertexAttribPointer(i, layout.elements[i].count, layout.elements[i].type, GL_FALSE, layout.stride, (const void*)layout.elements[i].offset);
        glEnableVertexAttribArray(0);
    }
}

Model::~Model() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Model::bindVAO() const { glBindVertexArray(m_vao); }
void Model::bindVBO() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo); }
void Model::bindIBO() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo); }

void Model::bind() const {
    bindVAO();
    bindVBO();
    bindIBO();
}

}