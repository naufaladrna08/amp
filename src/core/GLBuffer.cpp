#include <core/GLBuffer.hpp>

GLBuffer::GLBuffer() {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_ibo);
  glGenBuffers(1, &m_vbo);
}

GLBuffer::~GLBuffer() {
  // glDeleteVertexArrays(1, &m_vao);
  // glDeleteBuffers(1, &m_ibo);
  // glDeleteBuffers(1, &m_vbo);
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

  this->Unbind();
}

void GLBuffer::VertexAttribPointer(unsigned int index, int size, unsigned int type, bool normalized, int stride, const void* pointer) {
  this->Bind();
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  this->Unbind();
}