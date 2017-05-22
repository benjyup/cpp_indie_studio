//
// Created by vincent on 05/05/17.
//

# include "GameEngine.hpp"
# include "GameState.hpp"

int 		main(void) {
  std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio");
  std::shared_ptr<is::IGameState> gameState = std::make_shared<is::GameState>();

  // load the intro
  // game.ChangeState( CIntroState::Instance() );

  engine->ChangeState(gameState);

  engine->getDevice()->setResizable(true);
  irr::gui::IGUIEnvironment* env = engine->getDevice()->getGUIEnvironment();
  irr::gui::IGUISkin* skin = env->getSkin();
  irr::gui::IGUIFont* font = env->getFont("fonthaettenschweiler.bmp");
  if (font)
    skin->setFont(font);
  skin->setFont(env->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
  env->addButton(irr::core::rect<irr::s32>(10,240,110,240 + 32), 0, 101, L"Quit", L"Exits Program");
  
  // main loop
  while (engine->Running())
    {
      engine->HandleEvents();
      engine->Update();
      engine->Draw();
      env->drawAll();
    }

  // cleanup the engine
  return 0;
}
