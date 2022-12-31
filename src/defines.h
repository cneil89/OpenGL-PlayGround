#pragma once

#include "PlatformDetection.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/norm.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <memory>
#include <random>

const uint32_t SCR_WIDTH = 940;
const uint32_t SCR_HEIGHT = 680;

// View Ports for object placement
#define MIN_VP -5.0f
#define MAX_VP 5.0f
// MAX Point Lights
// NOTE: If changing this defines, makesure to change the max number define in shader.
#define MAX_PLIGHT 6

/// Debugbreak
#if defined(OGLPLAYGROUND_PLATFORM_WINDOWS)
#define OGLPLAYGROUND_DEBUGBREAK() __debugbreak()
#elif defined(OGLPLAYGROUND_PLATFORM_LINUX)
#include <signal.h>
#define OGLPLAYGROUND_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debug break yet!"
#endif