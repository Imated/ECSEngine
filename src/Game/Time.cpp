#include "Time.h"
#include "Rendering/Window.h"

float Time::time;
float Time::deltaTime;
int Time::frameCount;
float Time::totalTime;

void Time::startFrame()
{
    time = Window::GetTime();
}

void Time::endFrame()
{
    deltaTime = Window::GetTime() - time;
    totalTime += deltaTime;
    frameCount++;
    INFO(("\nFPS: " + std::to_string(1 / deltaTime) + "\nFrames: " + std::to_string(frameCount) + "\nAccumulated Time:" + std::to_string(totalTime)).c_str());
}
