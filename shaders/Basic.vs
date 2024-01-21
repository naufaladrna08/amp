#version 330 core 
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
uniform vec4 uColor;

uniform mat4 uModel;
uniform mat4 uProjection;

void main() {
  gl_Position = uProjection * uModel * vec4(aPos, 1.0);
  vertexColor = uColor;
}