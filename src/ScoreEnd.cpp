//
// greg
//

#include "ScoreEnd.hpp"

namespace is
{ 
    const irr::s32		            ScoreEnd::BUTTON_WIDTH = 250;
    const irr::s32		            ScoreEnd::BUTTON_HEIGHT = 75;
    const std::vector<std::string>  ScoreEnd::TEXT_END = {"The Winner is :", "MA BITE"};
    ScoreEnd::ScoreEnd()
    {

    }
    ScoreEnd::~ScoreEnd()
    {

    }
    void ScoreEnd::Init(GameEngine *engine)
    {
        this->_engine = engine;
        this->_driver = engine->getDriver();
        this->_sceneManager = engine->getSceneManager();
        this->_gui = engine->getGuiEnv();
        this->_ScoreEndReceiver.setEngine(this->_engine);
        this->_engine->getDevice()->setEventReceiver(&this->_ScoreEndReceiver);
        if (this->_gui != NULL)
            this->_font = _gui->getFont("./gfx/font_space.bmp");
        //if (!(this->_wallpaper = _engine->getDriver()->getTexture("./gfx/menuWallpaper.png")))
            //throw IndieStudioException();
        this->_buttons = {
            {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_MENU_BUTTON, L"Return to the menu", L"Return to the menu"},
            {engine->getWindowSize().X / 2 - BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT - 15 - BUTTON_HEIGHT, engine->getWindowSize().X / 2 + BUTTON_WIDTH / 2, engine->getWindowSize().Y - 15 - BUTTON_HEIGHT - 15, (irr::s32)Button::GUI_ID_BOUTON::GUI_ID_REPLAY_BUTTON, L"Play new game", L"Play new game"}
        };
        this->drawButtons();
        this->drawWinner();
    }
    void ScoreEnd::drawButtons()
    {
        for (auto &it : this->_buttons)
        {  
            it.set(this->_gui->addButton({it.getX(), it.getY(), it.getX2(), it.getY2()}, 0, it.getId(), it.getText().c_str(), it.getHint().c_str()));
            it->setUseAlphaChannel(true);
        }
        for (irr::s32 i = 0; i < irr::gui::EGDC_BUTTON_TEXT; ++i)
        {
            if (i != irr::gui::EGDC_BUTTON_TEXT)
            {
                irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
                col.set(50, 43, 50, 251);
                _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
            }
            else 
            {
                irr::video::SColor col = _gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
                col.set(255, 255, 255, 255);
                _gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);     
            }
        }
    }
    void ScoreEnd::drawWinner()
    {
        auto it = TEXT_END.begin();
        irr::core::rect<irr::s32> rec(this->_engine->getWindowSize().X / 2 - 40, this->_engine->getWindowSize().Y / 2 - 100, this->_engine->getWindowSize().X / 2 + 40, this->_engine->getWindowSize().Y / 2);
        while (it != TEXT_END.end())
        {
            irr::gui::IGUIStaticText *text = this->_gui->addStaticText(irr::core::stringw(it->c_str()).c_str(), rec);
            text->setOverrideFont(this->_font);
            this->_text.push_back(text);
            rec += irr::core::position2di(17, 20);
            it++;
        }
    }
    void ScoreEnd::Cleanup()
    {

    }
    void ScoreEnd::Pause()
    {

    }
    void ScoreEnd::Resume()
    {
        this->_engine->getDevice()->setEventReceiver(&this->_ScoreEndReceiver);
        this->drawButtons();
    }
    void ScoreEnd::HandleEvents()
    {

    }
    void ScoreEnd::Update()
    {

    }
    void ScoreEnd::Draw()
    {
        this->_driver->beginScene();
        //if (this->_wallpaper)
            //this->_driver->draw2DImage(this->_wallpaper, irr::core::vector2d<irr::s32>(0, 0));
        for (auto &button : this->_buttons)
        {
            button->setOverrideFont(this->_font);
            button->draw();
        }
        for (auto &text : this->_text)
        {
            text->draw();
        }
        this->_driver->endScene();
    }
    void ScoreEnd::ChangeState(GameEngine *engine, IGameState *state)
    {
        this->_engine->ChangeState(state);
    }
}