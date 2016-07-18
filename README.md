# 3D Engine

### OpenGL renderer written in C++ with SDL2.

A 3D renderering engine, written as a tool to drive my understanding of OpenGL and 3d graphics in general.

####Requirements
* C++11
* cmake - build tool
* OpenGL
* SDL2 - Window creation, input handling
* Assimp - Loading models

####Building

To perform an out-of-source build, first navigate to the root directory and then run the following commands.

```
mkdir build
cd build
cmake -DGAME=<game> ..
make
```

where <game> is one of the test scenes in the ```game``` folder (see below). Then rendering can be started by running the created ```3dengine``` binary.

####Example scenes

There are a few example scenes in the ```game``` folder that show different aspects of the rendering engine.

All scenes render in a 1280x720 window, with a frame cap of 240fps. Frame rate is output to stdout. In all scenes the camera can be controlled with the familiar ```w``` ```a``` ```s``` ```d``` controls. ```space``` raises the camera and ```ctrl``` lowers it. Clicking the screen will allow the mouse to be captured for mouselook. ```esc``` will release the mouse. In some scenes there is a object that can be controlled independently from the camera in order to test various lighting behaviours. This object can be controlled with ```i``` ```j``` ```k``` ```l``` for movement, ```o``` to raise, ```p``` to lower and the arrow keys for rotation.

| Name                  | Description                                                        |
| :-------------------- | :----------------------------------------------------------------- |
| ```showcase```        | A mix of different objects to show a mix of features of the engine. |
| ```cubemap_test```    | Testing of the skybox via cubemaps. |
| ```normal_test```     | Testing of normal mapping. Cubes on the left have no normal maps whereas the ones on the right do. Small cube can be moved to position light. |
| ```reflection_test``` | Testing of realtime recursive reflection. Cube mirror can be moved. |
| ```shadow_test```     | Testing of realtime directionallight shadows. |
| ```shadow_test2```     | Testing of realtime spotlight shadows. Light can be moved/rotated. (Note player has a model that also casts a shadow.) |
| ```texture_test```    | Test of various textures wrapped on a cube and on the "Suzanne" monkey head model. |
