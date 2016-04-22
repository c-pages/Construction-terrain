#version 120

uniform sampler2D texture;
uniform float blur_radius;

void main()
{
    vec2 offx = vec2(blur_radius, 0.0);
    vec2 offy = vec2(0.0, blur_radius);

    // https://software.intel.com/en-us/blogs/2014/07/15/an-investigation-of-fast-real-time-gpu-based-image-blur-algorithms
    // 7x7 convolution kernel with Gauss distribution values
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * .172 +

                 texture2D(texture, gl_TexCoord[0].xy - offx)        * .109 +
                 texture2D(texture, gl_TexCoord[0].xy + offx)        * .109 +
                 texture2D(texture, gl_TexCoord[0].xy - offy)        * .109 +
                 texture2D(texture, gl_TexCoord[0].xy + offy)        * .109 +

                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * .068 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * .068 +
                 texture2D(texture, gl_TexCoord[0].xy - offy + offy) * .068 +
                 texture2D(texture, gl_TexCoord[0].xy + offy + offy) * .068 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offx ) * .02 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offx ) * .02 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offy ) * .02 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy ) * .02 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offx - offy) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offx - offy) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offx + offy) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offx + offy) * .012 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offy - offx) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy - offx) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offy + offx) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy + offx) * .012 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offy - 2*offx) * .002 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy - 2*offx) * .002 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offy + 2*offx) * .002 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy + 2*offx) * .002 +

                 texture2D(texture, gl_TexCoord[0].xy - 3*offx ) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offx ) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy - 3*offy ) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offy ) * .001 +

                 texture2D(texture, gl_TexCoord[0].xy - 3*offx - offy) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offx - offy) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy - 3*offx + offy) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offx + offy) * .001 +

                 texture2D(texture, gl_TexCoord[0].xy - 3*offy - offx) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offy - offx) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy - 3*offy + offx) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offy + offx) * .001 ;

    gl_FragColor =  gl_Color * pixel ;
}



