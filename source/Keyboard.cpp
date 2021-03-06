#include <iostream>
#include "Keyboard.hpp"

/// Singleton

Keyboard Keyboard::keyboardInstance;

Keyboard &Keyboard::getKeyboard(void)
{
  return (keyboardInstance);
}

Keyboard::KeyboardKey Keyboard::getKeys(void) {
  return (KeyboardKey());
}

// Default constructor

Keyboard::Keyboard(void)
  : Input<OIS::Keyboard, OIS::KeyListener>()
{}

// Protected functions

bool Keyboard::keyPressed(OIS::KeyEvent const &ke) {
  try {
    keys.at(ke.key)(false);
  }
  catch (std::out_of_range const &) {}
  return (true);
}

bool Keyboard::keyReleased(OIS::KeyEvent const &ke) {
  try {
    keys.at(ke.key)(true);
  }
  catch (std::out_of_range const &) {}
  return (true);
}

// Public functions

void Keyboard::registerCallback(OIS::KeyCode ke, std::function<void(bool)> const &fn) {
  keys[ke] = fn;
}

void Keyboard::clearCallbacks(void) {
  keys.clear();
}

// KeyboardKey

bool Keyboard::KeyboardKey::operator[](OIS::KeyCode const &kc) {
  return (Keyboard::getKeyboard()->isKeyDown(kc));
}
