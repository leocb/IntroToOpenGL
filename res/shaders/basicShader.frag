#version 120

// varying are values passed from the vertex shader to the fragment shader (correct?)
varying vec2 texCoord0;

// uniforms are written by the CPU and read by the GPU (correct?)
uniform sampler2D diffuse;

void main()
{
  // we don't need to interpolate texCoord0 in the frag shader, it does it automatically
  gl_FragColor = texture2D(diffuse, texCoord0);
}