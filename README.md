# Landscape Generator
A Random Terrain Generator and renderer, coded from scratch, using only windows.h. 

A Graphics project for 5th Sem of BCT at Tribhuvan University

## Significances
- No Graphics Libraries used, everything coded from _scratch_, using only **windows.h** (We used glm but only for Simplex random generation so bear with us 😋)
- Perlin Noise used for random surface generation.
- Marching Cubes algorithm used for discretizing the generated surface i.e. creating required triangular mesh.
- The mesh is rendered via coding and projection mapping. 
- These concepts have been employed to build a 3D image in this project.
- Phong’s illumination model for realistic lighting 
- Gouraud shading for rasterizing mesh 

## Controls
- **W,A,S,D** - move Up, Left, Down, Right
- **I, K**    - move Forward , Backward
- **T,F,G,H,R,Y** - move Light Up, Left, Down, Right, Backward, Forward (Suggested to _pause_ the daylight cycle first)
- **J, L, U, O**    - rotate Left, Right, forward, backward
- **B** - generate terrain
- **Z** - toggle Wireframe
- **X** - toggle Coloring
- **C** - toggle Shading (if coloring is on)
- **V** - pause/play Daylight Cycle
