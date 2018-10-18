#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

//// ===================================== VERTEX =====================================
class Vertex
{
public:
  Vertex(const glm::vec3 &pos, const glm::vec2 &texCoord)
  {
    this->pos = pos;
    this->texCoord = texCoord;
  }

  inline glm::vec3 *getPos() { return &pos; };
  inline glm::vec2 *getTexCoord() { return &texCoord; };

protected:
private:
  glm::vec3 pos;
  glm::vec2 texCoord;
};

//// ====================================== MESH ======================================
class Mesh
{
public:
  Mesh(Vertex *vertices, unsigned int numVertices);

  void draw();

  virtual ~Mesh();

protected:
private:
  Mesh(const Mesh &other) {}
  void operator=(const Mesh &other) {}

  enum
  {
    POSITION_VB,
    TEXCOORD_VB,
    NUM_BUFFERS
  };

  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned int m_drawCount;
};

#endif // !MESH_H