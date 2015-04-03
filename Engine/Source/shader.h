#ifndef SHADER
#define SHADER

#include <string>

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    private:
        // Check compilation or linking failed and print the error logs
        GLvoid checkCompileErrors(GLuint object, std::string type);
    public:
        // Shader program object id
        GLuint ID;
        // Compiles the shader from given source
        GLvoid Compile(const GLchar *vertexSource, const GLchar *fragmentSource);
        // Utility functions
        GLvoid SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
        GLvoid SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
        GLvoid SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
        GLvoid SetVector2f(const GLchar *name, glm::vec2 &value, GLboolean useShader = false);
        GLvoid SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
        GLvoid SetVector3f(const GLchar *name, glm::vec3 &value, GLboolean useShader = false);
        GLvoid SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
        GLvoid SetVector4f(const GLchar *name, glm::vec4 &value, GLboolean useShader = false);
        GLvoid SetMatrix4(const GLchar *name, glm::mat4 &matrix, GLboolean useShader = false);
        // Sets the current shader as active
        Shader &Use();
};

#endif SHADER