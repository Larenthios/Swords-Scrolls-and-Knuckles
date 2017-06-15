#include "LevelScene.hpp"
#include "Game.hpp"
#include "UIOverlayMenu.hpp"

UIOverlayMenu::UIOverlayMenu(Renderer &renderer)
  : UIOverlay("mainmenu")
  , bg(static_cast<Ogre::PanelOverlayElement *>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "BG")))
{
  std::clog << "Init Overlay Menu" << std::endl;

  Ogre::OverlayManager *manager(Ogre::OverlayManager::getSingletonPtr());
  width = 0.5f;
  height = 0.1f;

  // Background
  bg->setMaterialName("HUD/MainMenuBG");

  // Play button
  std::unique_ptr<UIButton> play(new UIButton(manager, "Play", [&renderer]() {
    std::clog << "Going to level scene" << std::endl;
    renderer.switchScene([&renderer]() {
      LevelScene::createWallMesh();
      return static_cast<Scene *>(new LevelScene(renderer));
    });
  }));
  play->init(manager, "HUD/Black", "HUD/Green", width, height, 0.5f - width / 2.0f, 0.3f);

  // Credit button
  std::unique_ptr<UIButton> credits(new UIButton(manager, "Credits", []() {
    std::clog << "In Credits button" << std::endl;
  }));
  credits->init(manager, "HUD/Black", "HUD/Yellow", width, height, 0.5f - width / 2.0f, 0.5f);

  // Exit button
  std::unique_ptr<UIButton> exit(new UIButton(manager, "Exit", []() {
    throw Game::GameQuitException();
  }));
  exit->init(manager, "HUD/Black", "HUD/Red", width, height, 0.5f - width / 2.0f, 0.7f);

  // Linking everything together
  bg->addChild(play->getPanel());
  bg->addChild(credits->getPanel());
  bg->addChild(exit->getPanel());
  overlay->add2D(bg);

  buttons["Play"] = std::move(play);
  buttons["Credits"] = std::move(credits);
  buttons["Exit"] = std::move(exit);
}

UIOverlayMenu::~UIOverlayMenu()
{
  Ogre::OverlayManager::getSingleton().destroyOverlayElement(bg);
}
