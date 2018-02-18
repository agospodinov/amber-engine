#version 130

attribute vec3 mdl_Position;
attribute vec3 mdl_Normal;
attribute vec2 mdl_TexCoords;
uniform mat4 mdl_ModelView;
uniform mat4 mdl_Projection;
out vec2 fwd_TexCoords;

void main(void)
{
    gl_Position = mdl_Projection * mdl_ModelView * vec4(mdl_Position, 1.0);
    fwd_TexCoords = mdl_TexCoords;
}
