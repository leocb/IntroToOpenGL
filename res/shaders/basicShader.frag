#version 120

// varying are interpolated values passed from the vertex shader to the fragment shader
varying vec2 texCoord0;
varying vec3 normal0;

// uniforms are written by the CPU and read by the GPU (correct?)
uniform sampler2D diffuse;



void main()
{
  // we don't need to interpolate texCoord0 in the frag shader, it does it automatically
  gl_FragColor = texture2D(diffuse, texCoord0)
    * clamp(dot(-vec3(0.0, 0.0, 1.0), normal0), 0.0, 1.0);
}