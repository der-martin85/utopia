/*
 * SoundThread.h
 *
 *  Created on: 08.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef SOUND_SOUNDTHREAD_H_
#define SOUND_SOUNDTHREAD_H_

#include "SDL2/SDL.h"

class SoundThread {
public:
	static SoundThread* startThread();
	~SoundThread();
private:
	SoundThread();

	static int threadMethod(void* param);

	SDL_Thread* thread;

};

#endif /* SOUND_SOUNDTHREAD_H_ */
