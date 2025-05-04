#pragma once

class Time
{
public:
    static void startFrame();
    static void endFrame();
    static float deltaTime;
    static float totalTime;
    static int frameCount;

private:
    static float time;
};
