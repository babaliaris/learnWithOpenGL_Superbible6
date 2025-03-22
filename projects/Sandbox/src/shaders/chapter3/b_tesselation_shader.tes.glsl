#version 430 core
layout(triangles, equal_spacing, cw) in;


in TCS_OUT {
    vec4 color;
}data_in[];

out TES_OUT {
    vec4 color;
}data_out;


void main(void)
{
    gl_Position =  (gl_TessCoord.x * gl_in[0].gl_Position +
                    gl_TessCoord.y * gl_in[1].gl_Position +
                    gl_TessCoord.z * gl_in[2].gl_Position);

    data_out.color = data_in[0].color;
}