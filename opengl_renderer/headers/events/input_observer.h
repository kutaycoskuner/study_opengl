#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include <set>

// Observer pattern
// Listener (Observer) Interface
class InputListener {
public: 
    //virtual void onKeyPress(int key) = 0;
    //virtual void onKeyRelease(int key) = 0;
    virtual void onMultipleKeyPress(std::vector<int> keys) = 0;
};

// Speaker (Observable) interface
class InputSpeaker {
public:
    void addListener(InputListener* listener);
    void removeListener(InputListener* listener);

    void notifyMultipleKeyPress(std::vector<int> keys);
    //void notifyKeyPress(int key);
    //void notifyKeyRelease(int key);

private:
    std::vector<InputListener*> listeners;
};