#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

float vertices[] = {0.0,  0.5,  0.0, 1.0f, 0.0f, 0.0f,

                    -0.5, -0.5, 0.0, 0.0f, 1.0f, 0.0f,

                    0.5,  -0.5, 0.0, 0.0f, 0.0f, 1.0f};

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "void main() {\n"
                                 "gl_Position = vec4(aPos, 1.0);\n"
                                 "ourColor = aColor;\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "void main() {\n"
                                   "FragColor = vec4(ourColor, 1.0);}\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Window!", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Couldnt load opengl" << std::endl;
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 640, 480);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  int success;
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << "Vertex Shader compilation error!\n";
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << "Fragment Shader compilation error!\n";
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    std::cout << "Shader program linking failed!\n";
  }

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    //
    // float timeValue = glfwGetTime();
    // float greenValue = sin(timeValue) / 2.0f + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(shaderProgram,
    // "ourColor"); glUniform4f(vertexColorLocation, 0.0f, greenValue,
    // 0.0f, 1.0f);
    //
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
