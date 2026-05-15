#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position.x, position.y, 0.0, 1.0);
    //gl_Position = vec4(position.xy + vec2(0.5, 0.0), 0.0, 1.0);
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
    color = texture(u_Texture, TexCoord);
};