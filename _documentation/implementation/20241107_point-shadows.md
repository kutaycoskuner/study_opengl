# Implementation point shadows

- <>


for(unsigned int i = 0; i < 6; i++)
{
    GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, face, depthCubemap, 0);
    BindViewMatrix(lightViewMatrices[i]);
    RenderScene();  
}


unsigned int depthCubemap;
glGenTextures(1, &depthCubemap);


const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
                     SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);


glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
glDrawBuffer(GL_NONE);
glReadBuffer(GL_NONE);
glBindFramebuffer(GL_FRAMEBUFFER, 0);  


- <problem: gpu driver farkli render>
    - solution
    - update gpu driver before make a backup
    - on nvidia settings
        - visual studio
        - renderdocs
        - choose use nvidia (same card) for debug ve release binaries

- <prep: point light sahnesi olusturdum>
    - I have created a one side open prism to form a room space that could show shadows from point light 
    - looking to room from single perspective

- <design: deciding on where to create cubemap, where to hold data>
    - initialized the cubemp on initialize function of application 4.4 for search 
    - created a drawShadowCubemap function
        - this function is using project perspective function to create 6 light space matrices on mat4 vector

- <creating shadow cubemap drawing shaders> 
    - need 3 shaders: vrtx, geo, frag

- <progress report>
    - when I added my cmake to scene and shaders I lost my progress on scene.
    - I remade the test scene as well as handling problems.
    - todo: problem vs_out not matching on shader, implement shadows on point lights