#ifndef GL_BUFFER_HPP
#define GL_BUFFER_HPP
#include <glad/glad.h>

class GLBuffer {
  public: 
    GLBuffer();
    ~GLBuffer();

    void Bind();
    void BindVAO();
    void Unbind();

    void BufferData(unsigned int vertex_size, const void* vertex_data, unsigned int element_size, const void* element_data, unsigned int usage);
    void VertexAttribPointer(unsigned int index, int size, unsigned int type, bool normalized, int stride, const void* pointer);

    inline unsigned int& getVAO() { return m_vao; }
    inline unsigned int& getIBO() { return m_ibo; }
    inline unsigned int& getVBO() { return m_vbo; }

  private:
    unsigned int m_vao, m_ibo, m_vbo;
};

#endif 