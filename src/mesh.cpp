#include "mesh.h"
#include "obj_loader.h"
#include <vector>

// by file
Mesh::Mesh(const std::string &fileName)
{
  IndexedModel model = OBJModel(fileName).ToIndexedModel();
  initMesh(model);
};

// by data
Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices)
{

  IndexedModel model;

  for (unsigned int i = 0; i < numVertices; i++)
  {
    model.positions.push_back(*vertices[i].getPos());
    model.texCoords.push_back(*vertices[i].getTexCoord());
    model.normals.push_back(*vertices[i].getNormal());
    model.indices.push_back(indices[i]);
  }

  initMesh(model);
};

Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &m_vertexArrayObject);
};

void Mesh::initMesh(const IndexedModel &model)
{

  m_drawCount = model.indices.size();

  // generate a new vertex array
  glGenVertexArrays(1, &m_vertexArrayObject);

  // start bind so GL calls affect this vertex array
  glBindVertexArray(m_vertexArrayObject);

  // Creat a new buffer for position and texCoords (create a total of 2 array buffers)
  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

  // First we'll send the vertex positions
  // start bind so GL calls affect the first (POSITION_VB) buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
  // pass the data to the GPU
  glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
  // tell the GPU to treat it as an simple continuosly array (no skips, simple stride)
  glEnableVertexAttribArray(0); // the index should correspond to the glBindAttribLocation in the shader.cpp attribute name
  // tell the GPU some stuff about our data, the index (used for attribute binding), the size, type, if it should be normalized, the stride (only if it isn't sequential), and where it begins
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // the index (first paramenter) should be the same as above

  // Again, but for texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);                          // notice the index change (and what it corresponds to in the shader.cpp file)
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // index changed here too

  // Again for normals
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);                          // notice the index change (and what it corresponds to in the shader.cpp file)
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0); // index changed here too

  // Again for vertex indexes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

  // end the vertex array binding (not necessary but good practice?)
  glBindVertexArray(0);
};

void Mesh::draw()
{
  // bind
  glBindVertexArray(m_vertexArrayObject);
  // draw
  glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
  // unbind
  glBindVertexArray(0);
};