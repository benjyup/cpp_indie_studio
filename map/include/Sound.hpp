//
// Created by peixot_b on 31/05/17.
//

#ifndef MAP_SOUND_HPP
#define MAP_SOUND_HPP


#include "irrKlang.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Sound
{
 public:
  Sound();
  virtual ~Sound();

  irrklang::ISoundEngine	*get_soundEngine() const;

  void				setVolume(irrklang::ik_f32 volume);
  void				setMenuMusic();
  void				setGameMusic();
  void				setGameMusicWin();

  void				bombSound();
  void				selectionSound();
  void				loseSound();

 private:
  irrklang::ISoundEngine* _soundEngine;
};


#endif //MAP_SOUND_HPP
