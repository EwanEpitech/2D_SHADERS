uniform vec2[100] points; // the position of the points
uniform sampler2D texture; // the texture to sample from

void main(void)
{
    vec2 uv = gl_FragCoord.xy; // get the current pixel position
    float sum = 0.0;

    for (int i = 0; i < 100; i++) {
        vec2 p = points[i]; // get the position of the i-th point
        float d = distance(p, uv); // calculate the distance between the point and the current pixel
        sum += 1.0 / d; // add the distance to the sum
    }
    if (sum > 0.6)
        gl_FragColor = vec4(1, 0, 0, 1.0); // set the color of the pixel
    else
        gl_FragColor = vec4(1, 1, 1, 1.0); // set the color of the pixel
    //
    // to add color, use other if statements, like this:
    // else if (sum > 0.5) {
    //    gl_FragColor = vec4(0, 1, 0, 1.0);
    // }
    //
}