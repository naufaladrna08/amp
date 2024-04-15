#include <engine/Mesh.hpp>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
  m_vertices = vertices;
  m_indices = indices;
  m_textures = textures;

  SetupMesh();
}

Mesh::~Mesh() {
  // delete m_buffer;
}

void Mesh::Draw(GLShader* shader) {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;

  for (unsigned int i = 0; i < m_textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);

    std::string number;
    std::string name = m_textures[i].type;

    if (name == "texture_diffuse") {
      number = std::to_string(diffuseNr++);
    } else if (name == "texture_specular") {
      number = std::to_string(specularNr++);
    }

    shader->SetInt((name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
  }

  m_buffer->Bind();
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  m_buffer->Unbind();

  glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh() {
  m_buffer = new GLBuffer();
  m_buffer->BufferData(m_vertices.size() * sizeof(Vertex), &m_vertices[0], m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

  m_buffer->Bind();
  m_buffer->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
  m_buffer->VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
  m_buffer->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));
  m_buffer->Unbind();
}