#include "mesh.h"
#include <vector>

Mesh::Mesh(Vertex *vertices, unsigned int numVertices)
{
  m_drawCount = numVertices;

  // generate a new vertex array
  glGenVertexArrays(1, &m_vertexArrayObject);

  // start bind so GL calls affect this vertex array
  glBindVertexArray(m_vertexArrayObject);

  // Use vectors to serialize data to the GPU
  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> texCoords;

  positions.reserve(numVertices);
  texCoords.reserve(numVertices);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    positions.push_back(*vertices[i].getPos());
    texCoords.push_back(*vertices[i].getTexCoord());
  }

  // Creat a new buffer for position and texCoords (create a total of 2 array buffers)
  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

  // First we'll send the vertex positions
  // start bind so GL calls affect the first (POSITION_VB) buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
  // pass the data to the GPU
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
  // tell the GPU to treat it as an simple continuosly array (no skips, simple stride)
  glEnableVertexAttribArray(0); // the index should correspond to the glBindAttribLocation in the shader.cpp attribute name
  // tell the GPU some stuff about our data, the index (used for attribute binding), the size, type, if it should be normalized, the stride (only if it isn't sequential), and where it begins
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // the index (first paramenter) should be the same as above

  // Again, but for texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);                          // notice the index change (and what it corresponds to in the shader.cpp file)
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // index changed here too

  // end the vertex array binding (not necessary but good practice?)
  glBindVertexArray(0);
};

Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &m_vertexArrayObject);
};

void Mesh::draw()
{
  // bind
  glBindVertexArray(m_vertexArrayObject);
  // draw
  glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
  // unbind
  glBindVertexArray(0);
};