# Blending sahnesi
- start: 03-Jul-2024

- problem: blending sahnesinde pencere ve otlar yuklenmiyor
    - cozum: 
        - render_doc: dan baktim view_proj matrix yuklenmiyor fakat texturelari duzgun ekliyordu
        - matrisleri teker teker gonderdigim icin view_pos kalibini degistirmistim 
        - blending shaderi icindeki view_proj matrix yerine view ve proj matrisleri ayri ayri gonderdim.