#ifndef MESH_H
#define MESH_H

#include <string>
#include "obj_loader.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

//// ===================================== VERTEX =====================================
class Vertex
{
public:
  Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord, const glm::vec3 &normal = glm::vec3(0, 0, 0))
  {
    this->pos = pos;
    this->texCoord = texCoord;
    this->normal = normal;
  }

  inline glm::vec3 *getPos() { return &pos; };
  inline glm::vec3 *getNormal() { return &normal; };
  inline glm::vec2 *getTexCoord() { return &texCoord; };

protected:
private:
  glm::vec3 pos;
  glm::vec2 texCoord;
  glm::vec3 normal;
};

//// ====================================== MESH ======================================
class Mesh
{
public:
  Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices);
  Mesh(const std::string &fileName);

  void draw();

  virtual ~Mesh();

protected:
private:
  Mesh(const Mesh &other) {}
  void operator=(const Mesh &other) {}

  void initMesh(const IndexedModel &model);

  enum
  {
    POSITION_VB,
    TEXCOORD_VB,
    INDEX_VB,
    NORMAL_VB,
    NUM_BUFFERS
  };

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_drawCount;
};

#endif // !MESH_H