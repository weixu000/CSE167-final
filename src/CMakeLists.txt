add_executable(FinalProject
        main.cpp
        Window.cpp Window.h
        Time.cpp Time.h
        gl_wraps/Shader.cpp gl_wraps/Shader.h
        gl_wraps/GLContext.h gl_wraps/GLContext.cpp
        gl_wraps/GLObject.h
        gl_wraps/GLBuffer.h
        gl_wraps/GLVertexArray.h
        gl_wraps/GLTexture.h
        objects/Node.h objects/Node.cpp
        components/Component.h
        objects/Transform.cpp objects/Transform.h
        objects/controls/Trackball.cpp objects/controls/Trackball.h
        objects/geometries/Geometry.h objects/geometries/Geometry.cpp
        objects/geometries/Mesh.cpp objects/geometries/Mesh.h
        objects/geometries/Robot.cpp objects/geometries/Robot.h
        objects/geometries/Wireframe.cpp objects/geometries/Wireframe.h
        objects/Camera.cpp objects/Camera.h
        objects/controls/FreeFlying.cpp objects/controls/FreeFlying.h
        objects/animators/HumanoidAnimator.cpp objects/animators/HumanoidAnimator.h
        objects/Skybox.cpp objects/Skybox.h
        objects/geometries/BezierCurve.cpp objects/geometries/BezierCurve.h
        objects/controls/ControlTriple.cpp objects/controls/ControlTriple.h
        objects/animators/ConstraintAnimator.cpp objects/animators/ConstraintAnimator.h)
target_link_libraries(FinalProject GLEW::glew_s GLFW3::GLFW3 glm stb_image)