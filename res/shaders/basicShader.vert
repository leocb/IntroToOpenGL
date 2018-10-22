#version 120

// atributes are values stored in the GPU memory written by the OpenGL buffers
attribute vec3 position;
attribute vec2 texCoord;

// varying are values passed from the vertex shader to the fragment shader (correct?)
varying vec2 texCoord0;

// uniforms are set by the CPU
uniform mat4 transform;

void main()
{
  gl_Position = transform * vec4(position, 1.0); // this "1.0" is the multiplier of the tranform
  texCoord0 = texCoord;
}