#pragma once

// Storage and easy access to window size information (TODO: implement for multiple scenes in the future)
class WindowManager {
private:
    int screenWidth;
    int screenHeight;

public:
    WindowManager();

    void setScreenWidth(int width);
    void setScreenHeight(int height);

    int getScreenWidth() const;
    int getScreenHeight() const;
};
