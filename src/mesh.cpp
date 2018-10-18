#include "mesh.h"

Mesh::Mesh(Vertex *vertices, unsigned int numVertices)
{
  m_drawCount = numVertices;

  // generate a new vertex array
  glGenVertexArrays(1, &m_vertexArrayObject);

  // start bind
  glBindVertexArray(m_vertexArrayObject);

  // Creat a new buffer for position
  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);

  // pass the data to the GPU
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
  // tell the GPU to treat it as an simple continuosly array (no skips, simple stride)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // end bind
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