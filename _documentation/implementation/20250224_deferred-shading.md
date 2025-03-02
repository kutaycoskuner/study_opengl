# Deferred shading


- created shaaders and scene
- add application a bool to control deferred shading
- deferred shading geometry ve lighting pass adinda iki adimdan olusuyor.
- geometry pass de position, normal, albedo ve specularlari ckartiyoruz

- shader i yaptim.
- yeni kullanacagi shader olarak isaretledim ama renderdocs da 4 outputu goremiyorum.
    - dogru bufferi aktive etmedigimden goremiyormusum. su ana kadar hep tek buffer kullanmaktan kaynakli
    - drawScene fonksiyonu icinde atanan msaa bufferini b_deferred shading ile farkli bir conditiona alarak yeni bufferi koydum.
    - kolaylik olsun die her birine dogrudan renk veridm. su an ciziyor ama sadece frame in yarisina 
    - vertex shader input ve outputlarinin fragmenttakilerle tutmadigini fark ettim onu duzeltince duzeldi

    - geometry den sonra lighting ve lightbox u d yarattim
    - bir sonrkai impolementasyonda objeyeait texturelari degil bir onceki passten gelen texturelari gondermem gerkeiyor. Bu yuzden yeni bir fonksiyon olup kod icerisinde yeni bir condition aakisi yaratmaya karar verdim.

    -  drawDeferredLightingPass icinde msaa uzerine quad cizdirdim. kullandigim texture degiskenlerini kullanarak

    - isiklarin pozisyon ve rengini degistirecegim random