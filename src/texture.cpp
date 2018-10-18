#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string &fileName)
{
  int width, height, numComponents;
  unsigned char *imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

  if (imageData == NULL)
    std::cerr << "Texture loading failed for texture: " << fileName << std::endl;

  // Create the texture
  glGenTextures(1, &m_texture);

  // bind so we can modify some parameters
  glBindTexture(GL_TEXTURE_2D, m_texture);

  // Texture repeat
  // GL_REPEAT set it to repeat
  // GL_XX to mirror when repeat?
  // GL_CLAMP to not repeat (better performance?)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Texture filtering
  // GL_LINEAR for smooth filtering
  // GL_XX to make it look like the nDS (blocky textures)
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // how to interp the texture
  // (type, mipmap, how to store the pixels in the GPU, width, height, no idea, input format, how are they stored (type), the image Data)
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

  // clean image data from cpu memory (RAM) and leave it only in GPU memory
  stbi_image_free(imageData);
};

Texture::~Texture()
{
  glDeleteTextures(1, &m_texture);
};

void Texture::bind(unsigned int unit)
{
  assert(unit >= 0 && unit <= 31);

  // SOON
  glActiveTexture(GL_TEXTURE0 + unit);
  // Bind so all next texture operations use this texture
  glBindTexture(GL_TEXTURE_2D, m_texture);
}