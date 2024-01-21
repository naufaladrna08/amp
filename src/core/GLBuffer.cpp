#include <core/GLBuffer.hpp>

GLBuffer::GLBuffer() {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_ibo);
  glGenBuffers(1, &m_vbo);
}

GLBuffer::~GLBuffer() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_ibo);
  glDeleteBuffers(1, &m_vbo);
}

void GLBuffer::Bind() {
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void GLBuffer::BindVAO() {
  glBindVertexArray(m_vao);
}

void GLBuffer::Unbind() {
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLBuffer::BufferData(unsigned int vertex_size, const void* vertex_data, unsigned int element_size, const void* element_data, unsigned int usage) {
  this->Bind();

  glBufferData(GL_ARRAY_BUFFER, vertex_size, vertex_data, usage);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_size, element_data, usage);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  this->Unbind();
}