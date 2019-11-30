# CSE 167 Final Project

## Project Structure
```
.
├─cmake                             # Find*.cmake to find modules
├─deps                              # 3rd librarys to build
│  └─stb_image                      # https://github.com/nothings/stb
├─meshes                            # 3D models
├─shaders                           # GLSL shaders
├─src                               # Sources
│  ├─gl_wraps                       # C++ wrapper for OpenGL
│  └─objects                        # Scene graph
│      ├─animators                  # Animating nodes
│      ├─controls                   # User control
│      └─geometries                 # Geometry nodes
└─textures                          # Textures
```

## Build & Run
Use CMake to configure cross-platform build.
Run the executable in the repo `.` so that it can find the shaders/, meshes/, textures/.

## OpenGL Wrappers (src/gl_wraps)
- [x] `GLObject` handle `glGen*`, `glDelete*`
- [x] `Shader` compile, bind, use shaders, set uniforms
- [ ] `GLBuffer` bind, upload buffers
- [x] `GLVertexArray` bind vertex arrays, set vertex attributes
- [ ] `GLTexture` bind textures, set filter and wrap options
- [ ] `GLContext` create window and initialize OpenGL context

## Scene Graph (src/objects)
- `Node`: base class for node in the graph
    - `Transform` member for world-model transformation
    - `draw` draw the tree, `update` update the tree in game loop
    - graph is strict tree structure
        - `addChild` another `Node` as child nodes
        - `parent` member to find its parent in the tree
        - `std::list<std::unique_ptr<Node>>` to store child nodes, raw pointers as handles to them
    - `cull` to cull object before rendering
    - tree structure can be deep copied
        - OpenGL objects are not copyable, use std::shared_ptr to share them
        - `clone` deep copy a std::unique_ptr of unknown type, must be implemented for each concrete class
- `Camera`: camera is node in the graph
- `Skybox`: skybox is also a node
- `controls/`: various nodes whose transform user can change, so its child nodes (e.g. camera) can be moved
    - `FreeFlying`: freely movable by W,A,S,D and mouse
- `geometries/`: various geometries like bezier curve, mesh, wireframe, robot
    - `Terrain` implements procedurally generated terrain with Diamond Square Algorithm

## Window (src/Window.h)
- `loop`, `draw`, `update` handle game loop
- `initialize*` initialize shader and scene graph
- `*Callback` handle events