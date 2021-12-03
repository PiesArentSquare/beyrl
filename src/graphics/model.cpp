#include <beyrl/graphics/model.hpp>

#include "gl_context.hpp"

#include "objparser.hpp"

namespace beyrl {

void Model::init(void *verticies, size_t verticiesSize, unsigned indicies[], size_t indexCount, layout const &layout) {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    bind();
    glBufferData(GL_ARRAY_BUFFER, verticiesSize, verticies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned), indicies, GL_STATIC_DRAW);

    for (int i = 0; i < layout.elements.size(); i++) {
        unsigned type;
        switch(layout.elements[i].type) {
            case vectype::Float:
                type = GL_FLOAT;
                break;
            case vectype::Int:
                type = GL_INT;
                break;
            case vectype::UInt:
                type = GL_UNSIGNED_INT;
                break;
        }

        glVertexAttribPointer(i, layout.elements[i].count, type, GL_FALSE, layout.stride, (const void*)layout.elements[i].offset);
        glEnableVertexAttribArray(i);
    }
}

Model::Model(void *verticies, size_t verticiesSize, unsigned indicies[], size_t indexCount, layout const &layout) : m_vao(), m_vbo(), m_ibo(), m_vertCount(indexCount) {
    init(verticies, verticiesSize, indicies, indexCount, layout);
}

Model::Model(std::string const &objPath) : m_vao(), m_vbo(), m_ibo() {
    auto [vertices, indicies] = obj_parser().parse(objPath);
    m_vertCount = indicies.size();
    init(vertices.data(), sizeof(vertices[0]) * vertices.size(), indicies.data(), indicies.size(), obj_layout);
}

Model::~Model() {}

void Model::bindVAO() const { glBindVertexArray(m_vao); }
void Model::bindVBO() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo); }
void Model::bindIBO() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo); }

void Model::bind() const {
    bindVAO();
    bindVBO();
    bindIBO();
}

}