add_executable(FinalProject
        main.cpp
        Window.cpp Window.h
        Input.h
        Time.cpp Time.h
        gl_wraps/gl.h
        gl_wraps/Shader.cpp gl_wraps/Shader.h
        gl_wraps/Uniform.h
        gl_wraps/GLContext.h gl_wraps/GLContext.cpp
        gl_wraps/GLObject.h
        gl_wraps/GLBuffer.h
        gl_wraps/GLVertexArray.h
        gl_wraps/GLTexture.h
        gl_wraps/TextureCubemap.h
        gl_wraps/Texture2D.h
        objects/Node.cpp objects/Node.h
        objects/Group.cpp objects/Group.h
        objects/Transform.cpp objects/Transform.h
        objects/Camera.cpp objects/Camera.h
        objects/controls/Trackball.cpp objects/controls/Trackball.h
        objects/geometries/Geometry.h objects/geometries/Geometry.cpp
        objects/geometries/Mesh.cpp objects/geometries/Mesh.h
        objects/geometries/Robot.cpp objects/geometries/Robot.h
        objects/geometries/Skybox.cpp objects/geometries/Skybox.h
        objects/geometries/BezierCurve.cpp objects/geometries/BezierCurve.h
        objects/geometries/Terrain.cpp objects/geometries/Terrain.h
        objects/geometries/LSystem.cpp objects/geometries/LSystem.h
        objects/controls/FreeMover.cpp objects/controls/FreeMover.h
        objects/controls/FreeRotator.cpp objects/controls/FreeRotator.h
        objects/controls/FreeFlying.h
        objects/controls/TerrainWalker.cpp objects/controls/TerrainWalker.h
        materials/Material.h
        materials/FlatMaterial.h
        materials/PhongMaterial.h
        materials/CartoonMaterial.h
        materials/ReflectionMapMaterial.h
        materials/SkyboxMaterial.h
        materials/HeightMapMaterial.h)
target_link_libraries(FinalProject GLEW::glew_s glfw glm stb_image)