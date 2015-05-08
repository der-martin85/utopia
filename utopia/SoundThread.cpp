/*
 * SoundThread.cpp
 *
 *  Created on: 08.05.2015
 *      Author: Martin Ringwelski
 */

#include "SoundThread.h"

SoundThread* SoundThread::startThread() {
	SoundThread* ret = new SoundThread();
	if (ret != NULL) {
		ret->thread = SDL_CreateThread(SoundThread::threadMethod, "SoundThread", (void *)(ret));
		if (ret->thread == NULL) {
			delete ret;
			return NULL;
		}
	}
	return ret;
}

SoundThread::SoundThread():
		thread(NULL)
{
}

SoundThread::~SoundThread() {
	SDL_WaitThread(thread, NULL);
}

int SoundThread::threadMethod(void* param) {
	SoundThread* t = (SoundThread*)param;
	return 0;
}
