#version 430 core
layout(location = 0) in vec4 vOffset;
layout(location = 1) in vec4 vColor;

out vec4 fColor;

void main(void)
{
    // Declare a hard-coded array of positions
    const vec4 vertices[3] = vec4[3](
        vec4( 0.25, -0.25, 0.5, 1.0),
        vec4(-0.25, -0.25, 0.5, 1.0),
        vec4( 0.25, 0.25, 0.5, 1.0));

    gl_Position = vertices[gl_VertexID] + vOffset; //Set position of the vertex.

    fColor = vColor; //Send the color as retrieved from the fetching stage to the fragment shader.
}