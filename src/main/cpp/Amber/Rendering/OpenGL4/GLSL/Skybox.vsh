#version 130

attribute vec3 mdl_Position;
uniform mat4 mdl_ModelView;
uniform mat4 mdl_Projection;
out vec3 fwd_TexCoord;

void main(void)
{
    gl_Position = mdl_Projection * mdl_ModelView * vec4(mdl_Position, 1.0);
    fwd_TexCoord = mdl_Position;
}
