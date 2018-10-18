#version 120

// atributes are values stored in the GPU memory written by the OpenGL buffers
attribute vec3 position;
attribute vec2 texCoord;

// varying are values passed from the vertex shader to the fragment shader (correct?)
varying vec2 texCoord0;

void main()
{
  gl_Position = vec4(position, 1.0);
  texCoord0 = texCoord;
}