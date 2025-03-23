#version 430 core
layout(triangles) in;
layout(points, max_vertices=3) out;


in TES_OUT {
    vec4 color;
}data_in[];

out GEO_OUT {
    vec4 color;
}data_out;


void main(void)
{
    for (int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[0].gl_Position;
        data_out.color = data_in[i].color;
        EmitVertex();
    }
}