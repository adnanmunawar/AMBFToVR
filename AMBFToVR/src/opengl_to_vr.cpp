#include <iostream>
#include <openvr.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Function prototypes
bool InitOpenVR();
void SubmitTextureToSteamVR(GLuint textureID);
void RenderLoop();
void CleanupOpenVR();

// Global OpenVR objects
vr::IVRSystem *vrSystem = nullptr;
vr::IVRCompositor *vrCompositor = nullptr;

int main() {
  // Initialize OpenGL context (using GLFW in this example)
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Setup OpenGL version and profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and OpenGL context
  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL SteamVR Example", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Initialize OpenVR
  if (!InitOpenVR()) {
    std::cerr << "Failed to initialize OpenVR" << std::endl;
    return -1;
  }

  // Main render loop
  RenderLoop();

  // Clean up OpenVR and GLFW
  CleanupOpenVR();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

bool InitOpenVR() {
  vr::EVRInitError vrInitError = vr::VRInitError_None;
  vrSystem = vr::VR_Init(&vrInitError, vr::VRApplication_Scene);

  if (vrInitError != vr::VRInitError_None) {
    std::cerr << "Failed to initialize OpenVR: " << vr::VR_GetVRInitErrorAsEnglishDescription(vrInitError) << std::endl;
    return false;
  }

  vrCompositor = vr::VRCompositor();
  if (!vrCompositor) {
    std::cerr << "Failed to get VR Compositor" << std::endl;
    return false;
  }

  return true;
}

void SubmitTextureToSteamVR(GLuint textureID) {
  // Define texture info to be submitted to OpenVR
  vr::Texture_t leftEyeTexture = { (void*)(uintptr_t)textureID, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };

  // Submit to left and right eyes
  vrCompositor->Submit(vr::Eye_Left, &leftEyeTexture);
  vrCompositor->Submit(vr::Eye_Right, &leftEyeTexture);

  // You can use different textures for each eye if you prefer
}

void RenderLoop() {
  GLuint textureID;

  // Create an OpenGL texture (this is just a placeholder texture)
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Render loop
  while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
    // Render your OpenGL scene here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Submit the OpenGL texture to SteamVR
    SubmitTextureToSteamVR(textureID);

    // Swap buffers and poll events
    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
  }

  // Clean up OpenGL texture
  glDeleteTextures(1, &textureID);
}

void CleanupOpenVR() {
  if (vrSystem) {
    vr::VR_Shutdown();
    vrSystem = nullptr;
  }
}
