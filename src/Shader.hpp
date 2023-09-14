#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <GL/glew.h>

std::pair <std::string, std::string> ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream ss[2];
    ShaderType Type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                Type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                Type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)Type] << line << '\n';
        }
    }
    return make_pair(ss[0].str(), ss[1].str());
}

unsigned int CompileShaderProgram (unsigned int ShaderType, const std::string& ShaderSourceString) {
    unsigned int ShaderId = glCreateShader(ShaderType);
    const char* ShaderSource = ShaderSourceString.c_str();
    glShaderSource(ShaderId, 1, &ShaderSource, nullptr);
    glCompileShader(ShaderId);
    int CompileResult;
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &CompileResult);
    if (CompileResult == GL_FALSE) {
        int lenght;
        glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(ShaderId, lenght, &lenght, message);
        std::cout << (ShaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << ' ' << "shader failed to compile" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(ShaderId);
        return 0;
    }
    return ShaderId;
}

unsigned int CreateShaderProgram (const std::string& VertexShader, const std::string& FragmentShader) {
    unsigned int ShaderProgram = glCreateProgram();
    unsigned int VertexShaderProgram = CompileShaderProgram(GL_VERTEX_SHADER, VertexShader);
    unsigned int FragmentShaderProgram = CompileShaderProgram(GL_FRAGMENT_SHADER, FragmentShader);
    glAttachShader(ShaderProgram, VertexShaderProgram);
    glAttachShader(ShaderProgram, FragmentShaderProgram);
    glLinkProgram(ShaderProgram);
    glValidateProgram(ShaderProgram);
    glDeleteShader(VertexShaderProgram);
    glDeleteShader(FragmentShaderProgram);
    return ShaderProgram;
}