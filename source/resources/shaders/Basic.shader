#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTexCoord

out vec2 TexCoord

void main()
{
    gl_Position = position;
    TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, TexCoord) * u_Color;
};