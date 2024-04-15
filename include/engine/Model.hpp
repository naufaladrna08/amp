#ifndef MODEL_HPP
#define MODEL_HPP

#include <engine/Mesh.hpp>
#include <vector>
#include <string>
#include <core/GLShader.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

class Model {
public:
  Model();
  Model(std::string path);
  ~Model();
  void loadModel(std::string path);
  void reloadModel(std::string path);
  void Draw(GLShader &shader);

private:
  std::vector<Mesh> m_meshes;
  std::string m_directory;
  std::vector<Texture> m_texturesLoaded;

  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
  unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif