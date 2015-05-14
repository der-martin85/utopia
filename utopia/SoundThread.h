/*
 * SoundThread.h
 *
 *  Created on: 08.05.2015
 *      Author: Martin Ringwelski
 */

#ifndef SOUND_SOUNDTHREAD_H_
#define SOUND_SOUNDTHREAD_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <pthread.h>
#include <vector>
#include <string>
#include "Settings.h"

class SoundThread {
public:
	static SoundThread* startThread(Settings* settings);

	~SoundThread();
	void quitThread() {
		quit = true;
	}
private:
	SoundThread(Settings* settings);

	static int threadMethod(void* param);

	SDL_Thread* thread;
	pthread_mutex_t mutex;
	pthread_cond_t condition;

	bool quit;
	Settings* settings;
	std::vector<std::string>	musicFiles;
	Mix_Music *music;

};

#endif /* SOUND_SOUNDTHREAD_H_ */
