#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //gl_Position = vec4(position, 1.0);
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
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