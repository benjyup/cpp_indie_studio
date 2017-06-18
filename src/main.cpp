//
// Created by vincent on 05/05/17.
//

# include "GameEngine.hpp"
# include "GameState.hpp"
# include "MenuState.hpp"
# include "IntroState.hpp"

int 		main(void) {

  try {
      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio",
										1900, 1000, 0, false);
      engine->PushState(new is::IntroState);

      core::array<SJoystickInfo> joystickInfo;
      if(engine->getDevice()->activateJoysticks(joystickInfo))
	{
	  std::cout << "Joystick support is enabled and " << joystickInfo.size() << " joystick(s) are present." << std::endl;

	  for(u32 joystick = 0; joystick < joystickInfo.size(); ++joystick)
	    {
	      std::cout << "Joystick " << joystick << ":" << std::endl;
	      std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'" << std::endl;
	      std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
	      std::cout << "\tButtons: " << joystickInfo[joystick].Buttons << std::endl;

	      std::cout << "\tHat is: ";

	      switch(joystickInfo[joystick].PovHat)
		{
		  case SJoystickInfo::POV_HAT_PRESENT:
		    std::cout << "present" << std::endl;
		  break;

		  case SJoystickInfo::POV_HAT_ABSENT:
		    std::cout << "absent" << std::endl;
		  break;

		  case SJoystickInfo::POV_HAT_UNKNOWN:
		  default:
		    std::cout << "unknown" << std::endl;
		  break;
		}
	    }
	}
      else
	{
	  std::cout << "Joystick support is not enabled." << std::endl;
	}

      core::stringw tmp = L"Irrlicht Joystick Example (";
      tmp += joystickInfo.size();
      tmp += " joysticks)";
      engine->getDevice()->setWindowCaption(tmp.c_str());
      while (engine->Running())
	{
	  engine->HandleEvents();
	  engine->Update();
	  engine->Draw();
	}
    } catch (const std::exception &e) {
      if (!std::string(e.what()).empty())
	std::cerr << "Error: " << e.what() << std::endl;
    }

  // cleanup the engine
  return 0;
}
