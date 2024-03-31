# Instancing Monitoring
- start: 31-Mar-2024

# 
- method 1: No instance
    - 5000 draw 27 ms, 35 fps

- method 2: multiple draw call + loop transform assignment
    * 5000 draw 12 ms, 80 fps

- method 3: multiple draw call + uniform buffer memory link
    - 5000 draw, 7.5ms, 134 fps

- method 4: single draw call + all uniform buffer memory link
    - 5000 draw, 7.5ms, 134 fps

- method 5: (n x mesh) draw call + data as vbo
    - 5000 draw, 7.0ms, 140 fps

acerola 
- 2.2m tri 4.3m vrts 523 fps 