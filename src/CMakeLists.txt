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
        components/geometries/Geometry.h components/geometries/Geometry.cpp
        components/geometries/Mesh.cpp components/geometries/Mesh.h
        components/geometries/Robot.cpp components/geometries/Robot.h
        components/geometries/Wireframe.cpp components/geometries/Wireframe.h
        objects/Camera.cpp objects/Camera.h
        objects/controls/FreeFlying.cpp objects/controls/FreeFlying.h
        objects/animators/HumanoidAnimator.cpp objects/animators/HumanoidAnimator.h
        objects/Skybox.cpp objects/Skybox.h
        components/geometries/BezierCurve.cpp components/geometries/BezierCurve.h
        objects/controls/ControlTriple.cpp objects/controls/ControlTriple.h
        objects/animators/ConstraintAnimator.cpp objects/animators/ConstraintAnimator.h)
target_link_libraries(FinalProject GLEW::glew_s GLFW3::GLFW3 glm stb_image)