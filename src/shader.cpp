#include "shader.h"
#include <fstream>
#include <iostream>

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
static std::string loadShader(const std::string &fileName);
static GLuint createShader(const std::string &text, GLenum shaderType);

Shader::Shader(const std::string &fileName)
{
  m_program = glCreateProgram();

  // Load shaders from file
  m_shaders[0] = createShader(loadShader(fileName + ".vert"), GL_VERTEX_SHADER);
  m_shaders[1] = createShader(loadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

  // Attach shaders to program
  for (unsigned int i = 0; i < NUM_SHADERS; i++)
    glAttachShader(m_program, m_shaders[i]);

  // bind attrib indexes (ATTENTION HERE, the indexes should be the same when creating the bindings (mesh.cpp))
  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");

  // Link and validate
  glLinkProgram(m_program);
  checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

  glValidateProgram(m_program);
  checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

  // Get the handler for the "transform" uniform
  m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
};

// Destructor
Shader::~Shader()
{
  for (unsigned int i = 0; i < NUM_SHADERS; i++)
  {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
};

// Binder
void Shader::bind()
{
  glUseProgram(m_program);
}

// Update with the transform
void Shader::update(const Transform &transform)
{
  glm::mat4 model = transform.getModel();
  glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

// Shader Compiler
static GLuint createShader(const std::string &text, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);

  if (shader == 0)
    std::cerr << "Error: Shader creation failed!" << std::endl;

  const GLchar *shaderSourceStrings[1];
  GLint shaderSourceStringLengths[1];
  shaderSourceStrings[0] = text.c_str();
  shaderSourceStringLengths[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);

  checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

  return shader;
};

// Shader file loading and checking for errors

static std::string loadShader(const std::string &fileName)
{
  std::ifstream file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if (file.is_open())
  {
    while (file.good())
    {
      getline(file, line);
      output.append(line + "\n");
    }
  }
  else
  {
    std::cerr << "Unable to load shader: " << fileName << std::endl;
  }

  return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = {0};

  if (isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if (success == GL_FALSE)
  {
    if (isProgram)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);

    std::cerr << errorMessage << ": " << error << "'" << std::endl;
  }
}
