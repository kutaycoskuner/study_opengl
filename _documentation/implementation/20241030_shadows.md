# Implementation of shadows


# 
- create test scene
- design: application initialize fonksiyonu icerisine uygun fbo ve texture yaratma ifadelerini yerlestir
    - sonraki adimda directional isigi almak icin orthografik kamera renderi gerekli. directional icin orthographic camera gerekiyor ama orthographic projection icin fonksiyonum yoktu
        - solution: chatgpt ye benim perspective projection matrislerini verip orthografikleri sitedim
    - problem: look at direction ve look at target camera fonksiyonlari
        - solution: free fonksiyon olarak yazdim
    - problem: shadowpass frame bufferi bind edip renderladigimda orjinal frame buffer siyah cikiyor.
        - solution: binding, depth test ve gl_none ifadelerini shadowpass fonksiyonu icersiine enkapsule ettim
    - problem: light view projection dogru calismiyor.
        - analysis: 
            - vertex inputlar dogru outputlar yanlis
            - camera lookat de problem var. row/clumn major degistirdim
                - lookattarget ve crossproduct carpimparini kontrol ediyorum.
                    - sag el cross p carpiminin dogru olup olmadigini kontrol etmek icin
                        - 3 parmagini acarak 3 aksi temsilen yerlestir. Orta parmagin yuzune bakacak sekilde z aksi
                        - yatay (bas parmak) x aksi, dikey ise y aksi.
                        - cross product in hangi yone baktigini anlamak icin sag eli bir akstan diger aksa cevirip bas parmagin baktigin yone bakmalisin
            - hata olasiliklari
                - 1. cross product
                - 2. col/row major
                - 3. orthographic hesabi col row major problemi
            - light view matrixe sadece projectionu gonderdim. Isik 000 da iken z+ ya bakan durum.
                - kupleri +z ye yerlestirerek renderdoctan depthbuffer i kontrol ettim. Gormek istedigim sey bir kareydi. Ortographic projection calisiyor.
            - light view de calisiyor.
            - problem: depth pass cizimde gecmiyor overlay uzerinden gorundugu kadariyla
                - renderdocs overlay
                - problem lookatdirection fonksiyonundaki col/row major matrixiymis

- [implementation-part-2] using shadow map on shader to identify shadows
    - todo: shaderi bos shadow fonksiyonuyla beraber yaziyorum. 
    - multiple lights shaderimdan derivate ederek shadow fonksiyonlu light-shadow shaderini olusturdum. Shadow fonksiyonuun ici bostu
    - draw primitive fonksiyonunun icine yeni, shadowmap texture ve light_position matrisini gonderdim
    - problem: golge goremiyorum.
        - cozum: eksik dokumantasyon

- [implementation-part-3]
    - ilk golgeyi aldiktan sonra iyilestirme calismalari
        - shadow bias
        - peter panning (front face cull on depth map)
        - repeating texture to clamp value to avoid shadow repetition and texture end
        - pcf (percentaage close filtering)

- [additional-implementation-rotating-light-shadow]
    - problem: golge ve isik farkli yonde donuyor biri cw digeri ccw
        - attempt: kamerayi kolay hesap yapabilecegim 0, 10, 10 noktasina cektim.
            - isigi kamera biraz sag ve sola yerlestirdim golgeler dogru dusuyor.
            - fakat hareket ettiginde bozuluyor.
            - tespit: matrisleri vektore surekli push back yapip ilk matrisi okudugu icin animasyonda calismiyor.
            - post mortem niye bu kadar uzun surdu nerede hata yaptim?