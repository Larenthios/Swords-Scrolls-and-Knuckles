#ifndef MOUSE_HPP
# define MOUSE_HPP

# include <iostream>
# include <functional>
# include <OISMouse.h>
# include <Overlay/OgreOverlay.h>
# include <Overlay/OgreOverlayManager.h>
# include "Input.hpp"

class Mouse : public Input<OIS::Mouse, OIS::MouseListener> {
private:
  std::map<OIS::MouseButtonID, std::function<void(OIS::MouseEvent const &)>> keysCallbacks;
  std::vector<std::function<void(Ogre::Real, Ogre::Real)>> moveCallbacks;

  static Mouse mouseInstance;

  Mouse(void);

protected:
  virtual bool mouseMoved(OIS::MouseEvent const &);
  virtual bool mousePressed(OIS::MouseEvent const &, OIS::MouseButtonID);
  virtual bool mouseReleased(OIS::MouseEvent const &, OIS::MouseButtonID);

public:
  Mouse(Mouse const &) = delete;
  Mouse(Mouse &&) = delete;
  virtual ~Mouse(void) = default;
  Mouse &operator=(Mouse const &) = delete;
  Mouse &operator=(Mouse &&) = delete;

  /// Register a mouse button callback
  void registerCallback(OIS::MouseButtonID, std::function<void(OIS::MouseEvent const &)> const &);

  /// Register a mouse-move event callback
  void registerMouseMoveCallback(std::function<void(Ogre::Real x, Ogre::Real)> const &);

  /// Clear all mouse callback
  void clearCallbacks(void);

  static Mouse &getMouse(void);
};

#endif // !MOUSE_HPP
