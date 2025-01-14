#pragma once

// Storage and easy access to window size information
class WindowManager {
private:
    int screenWidth;
    int screenHeight;

public:
    WindowManager(int width, int height) 
        : screenWidth(width), screenHeight(height) {}

    int getScreenWidth() const { return screenWidth; }
    int getScreenHeight() const { return screenHeight; }
};