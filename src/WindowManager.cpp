#include "WindowManager.h"

// Storage and easy access to window size information (TODO: implement for multiple scenes in the future)
WindowManager::WindowManager() 
    : screenWidth(0), screenHeight(0) {} // Initialized to 0 by default

void WindowManager::setScreenWidth(int width) {
    screenWidth = width;
}

void WindowManager::setScreenHeight(int height) {
    screenHeight = height;
}

int WindowManager::getScreenWidth() const {
    return screenWidth;
}

int WindowManager::getScreenHeight() const {
    return screenHeight;
}