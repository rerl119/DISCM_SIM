#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "Point.h"
#include "Program.h"
#include "ShaderClass.h"

// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Particle storage
std::vector<Point> particles;
std::mutex particlesMutex;

// Time management
std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;

// FPS display
float fps = 0.0f;
std::chrono::time_point<std::chrono::steady_clock> lastFpsTime;
int frameCount = 0;

// Shader program
Program* shaderProgram = nullptr;

// Initialize OpenGL
void initOpenGL() {
    glewInit();
    // Load and compile shaders
    shaderProgram = new Program("vertex_shader.glsl", "fragment_shader.glsl");
}

// Render particles
void renderParticles() {
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram->use();
    
    std::lock_guard<std::mutex> lock(particlesMutex);
    for (const auto& particle : particles) {
        // Render code for each particle
        glm::vec3 pos = particle.get_pos();
        // Draw particle at pos.x, pos.y
    }
    
    // Display FPS
    // renderText(fps);
}

// Update particles
void updateParticles(float deltaTime) {
    std::lock_guard<std::mutex> lock(particlesMutex);
    for (auto& particle : particles) {
        particle.move(deltaTime);
    }
}

// Add particles
void addParticles(int n, float x, float y, float theta, float velocity) {
    std::lock_guard<std::mutex> lock(particlesMutex);
    for (int i = 0; i < n; ++i) {
        particles.emplace_back(x, y, velocity, theta);
    }
}

// Calculate FPS
void calculateFps() {
    frameCount++;
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFpsTime).count();
    if (elapsedTime >= 500) {
        fps = frameCount / (elapsedTime / 1000.0f);
        frameCount = 0;
        lastFpsTime = currentTime;
    }
}

// Main rendering loop
void mainLoop(GLFWwindow* window) {
    lastFrameTime = std::chrono::steady_clock::now();
    lastFpsTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        auto currentFrameTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - lastFrameTime).count() / 1000.0f;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();
        updateParticles(deltaTime);
        renderParticles();

        glfwSwapBuffers(window);
        calculateFps();
    }
}

// Input handling
void inputHandler(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        if (/* some condition to add particles */) {
            addParticles(10, 100.0f, 100.0f, 45.0f, 50.0f);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Simulate input polling rate
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Physics Simulator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    initOpenGL();

    std::thread inputThread(inputHandler, window);
    mainLoop(window);

    inputThread.join();
    glfwDestroyWindow(window);
    glfwTerminate();

    delete shaderProgram;
    return 0;
}
