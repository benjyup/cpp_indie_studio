//
// Created by peixot_b on 31/05/17.
//

#include "Sound.hpp"
#include "irrKlang.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Sound::Sound()
{
  _soundEngine = irrklang::createIrrKlangDevice();
  _soundEngine->setSoundVolume(0.1);
}

Sound::~Sound()
{
  _soundEngine->drop();
}

irrklang::ISoundEngine *Sound::get_soundEngine() const
{
  return _soundEngine;
}

void			Sound::setMenuMusic()
{
  _soundEngine->stopAllSounds();
  _soundEngine->play2D("./gfx/inmenu.ogg", true);
}

void			Sound::setGameMusic()
{
  _soundEngine->stopAllSounds();
  _soundEngine->play2D("./gfx/ingame.ogg", true);
}

void			Sound::setVolume(irrklang::ik_f32 volume)
{
  _soundEngine->setSoundVolume(volume);
}

void			Sound::setGameMusicWin()
{
  _soundEngine->stopAllSounds();
  _soundEngine->play2D("./gfx/end_level.ogg", false);
}

void			Sound::selectionSound()
{
  _soundEngine->play2D("./gfx/selectionSound.ogg", false);
}

void			Sound::bombSound()
{
  _soundEngine->play2D("./gfx/explosion.ogg", false);
}

void			Sound::loseSound()
{
  _soundEngine->play2D("./gfx/losesound.ogg", false);
}