#include "../../headers/events/input_observer.h"

void InputSpeaker::addListener(InputListener* listener) {
    listeners.push_back(listener);
}

void InputSpeaker::removeListener(InputListener* observer) {
    auto it = std::find(listeners.begin(), listeners.end(), observer);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

//void InputSpeaker::notifyKeyPress(int key) {
//    for (auto observer : listeners) {
//        observer->onKeyPress(key);
//    }
//}
//
//
//void InputSpeaker::notifyKeyRelease(int key) {
//    for (auto observer : listeners) {
//        observer->onKeyRelease(key);
//    }
//}

void InputSpeaker::notifyMultipleKeyPress(std::vector<int> keys) {
    for (auto observer : listeners) {
        observer->onMultipleKeyPress(keys);
    }
}

void InputSpeaker::notifyUIEvent(const UIEvent& event, const std::vector<int>& params) {
    for (auto observer : listeners) {
        observer->onUIEvent(event, params);
    }
}


void InputListener::onMultipleKeyPress(std::vector<int> keys) {
}

void InputListener::onUIEvent(const UIEvent& event, const std::vector<int>& params) {
}