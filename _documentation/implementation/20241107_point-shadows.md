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
    - shadow_transform_matrices in shaderlara gonderilip gondeirlmedigini renderdoctan kontrol ettim.
    - shaderlarin talep ettigi butun uniformlar gonderiliyor mu onlara bakiyorum.
    - butun uniformlar gonderiliyor

- <problem: when there is no directional light, scene is not drawing>
    - error: Block "VS_OUT" mismatch between shader stages
        - renderdocs 
            - primitive callari yapmiyor.
            - sorun tespiti -> m_light space matrix kontrolu yapip return yapiyordu.
            - texture viewr overlay
            - mesh viwer vs input, output
        - shaderlari aktive ettim
            - verilen linking erroru aratip break point koy
            - call stackten hangi shaaderin hata verdigine bak
            - shader parametrelerini shadercompiledesc ile degistirdim.
                - yeni parametreler eklendiginde signature u degil sadece logic i degistirmek yetecek
                - errorleri daha detayli yazabiliyorum

- <writing plight shaders>
    - problem: shadow_transform_matrices 2 and 3 passing values as nan
    - bu look at directiondaki alignment problemi. iki vektor ayni veya tam zit yone bakinca bu problemi aliyorsun
    - varsyilan durum ayarlayarak simdilik ustunden atladim
    - problem: render shaderi yazdim fakat cubemap i shadera gonderemiyorum. renderdocda cubemap i goremiyorum
        - sampleri renderdocta gormuyordu. Hesaplamada kullanilmadigi icinmis
        - bin icerisindeki debug ciftmis nedenini anlayamadim.
            - binaries yeniden generate ettirdim su an renderdoc ve sln ayni bin i kullaniyor
        - renderdocs geometry shader outputlari yanlis gorunuyor
            - ya matrisler yanlis hesaplaniyor ya matrisleri yanlis gonderiyoruz
            - cpu ve gpu kodunu karsilastirdigimizda matrislerin farkli oldguun gorduk
            - garip bir sekilde debug dosyasini geri atiyor
            - boyu belli oldugu icin arraya cevirerek gonderdik. arrayler dogru geciyor. 
            - fakat geo shader hala dogru transformasyonu yapmiyor.
                - trivial case -> default case view translate olmadan z+ veya z- ye baktiginda projectionda problem olup olmadigini gorebiliriz cunku view identity matris gidiyor.
                - projectionda problem varmis -> aspect ratio set edilmemis

- <problem: shadowmap oryantasyonlari yanlis>
    - opengl cubemap is left hand unlikely to rst of the system I found it on the documentation.
    - first I set object on each axis with different rotation to understand behaviour
    - temporary fix 
        - reversed -z on shader
        - reversed shaadow matrice z faces
        - reversed shadow matrice  y ups

- <problem: face culling scene is not working>
