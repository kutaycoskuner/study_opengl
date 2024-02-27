# Ubo problem

- problem 
    - uniform buffer object is not transmitted to shader
    - tespit: renderdocs > pipeline state > fs > uniforms and ubos: not there
    - opengl ile karsilastiriyorum
    - hata1: member variable olan ubo_matrices i ayni isimde application icerisinde lokal degisken olarak yaratiyorum.
        - ilgili kodlari debug yaptigimda: implicit constructor call not supported hatasi aldim
        - problemi kolaylastirmak icin, tek shadera indirgedim
        - problemi chatgpt ye sorarak cozdum. Map edilen verinin member degiskenine ulasmak icin once kontrol etmek gerekiyormus. 
        - su an renderdoc uzerinde matrislerin aktarildigini goruyorum. ama veriler dogru degil
    - hata2: binding isleminde problem var veriyi tam almiyor. bu glm nin value pointer kullanmasindan kaaynali diye tahmin ediyorum
        - degerleri karsilastirmak icin oncelikle shadera ayni degerleri ubo olarak degil de uniform olarak gonderecegim
        - degerler arasinda fark var bind edilme yerini degistirecegim
        - farklari renderdocs uzerinden 2 farkli screenshot alarak yanyana yapistirdim ve markladim.
        - fark ettim ki column ve row majorlar farkli
    - problemler cozuldu

    - 08.08-09.24