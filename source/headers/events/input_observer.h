#pragma once
#include "../events/events.h"

#include <functional>
#include <vector>
#include <iostream>
#include <set>

// Observer pattern
// Listener (Observer) Interface
class InputListener {
public: 
    //virtual void onKeyPress(int key) = 0; = 0 gelirse implementation zorunlu demek
    //virtual void onKeyRelease(int key) = 0;
    virtual void onMultipleKeyPress(std::vector<int> keys);
    virtual void onUIEvent(const UIEvent& event, const std::vector<int>& params);
};

// Speaker (Observable) interface
class InputSpeaker {
public:
    void addListener(InputListener* listener);
    void removeListener(InputListener* listener);

    void notifyMultipleKeyPress(std::vector<int> keys);
    void notifyUIEvent(const UIEvent& event, const std::vector<int>& params);
    //void notifyKeyPress(int key);
    //void notifyKeyRelease(int key);

private:
    std::vector<InputListener*> listeners;
};


