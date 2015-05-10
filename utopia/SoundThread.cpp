/*
 * SoundThread.cpp
 *
 *  Created on: 08.05.2015
 *      Author: Martin Ringwelski
 */

#include "SoundThread.h"
#include <iterator>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <chrono>
#include <thread>

using namespace boost::filesystem;

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
		thread(NULL),
		quit(false),
		music(NULL)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condition, NULL);
}

SoundThread::~SoundThread() {
	pthread_mutex_lock(&mutex);
	quit = true;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&condition);
	SDL_WaitThread(thread, NULL);
	if (music != NULL) {
		Mix_FreeMusic( music );
	}
}

int SoundThread::threadMethod(void* param) {
	SoundThread* t = (SoundThread*)param;

	if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1) {
		return 0;
	}
	path p ("./sound/");

	try
	{
		if (exists(p)) {
			if (is_directory(p)) {
				directory_iterator it(p), eod;
				BOOST_FOREACH(path const &f, std::make_pair(it, eod)) {
				    if(is_regular_file(f))
				    {
				    	if (f.string().find(".mp3") != std::string::npos) {
				    		t->musicFiles.push_back(f.string());
				    	}
				    }
				}
			}
		} else {
			Mix_CloseAudio();
			return 0;
		}
	} catch (const filesystem_error& ex) {
		Mix_CloseAudio();
		return 0;
	}

	pthread_mutex_lock(&(t->mutex));
	while (!t->quit) {
		pthread_mutex_unlock(&(t->mutex));
		if( Mix_PlayingMusic() == 0 ) {
			if (t->music != NULL) {
				Mix_FreeMusic( t->music );
			}
			int numFile = rand() % t->musicFiles.size();
			t->music = Mix_LoadMUS( t->musicFiles[numFile].c_str() );

			if( Mix_PlayMusic( t->music, 1 ) == -1 ) {
				return 0;
			}
		}
		//pthread_cond_wait(&(t->condition), &(t->mutex));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		pthread_mutex_lock(&(t->mutex));
	}
	pthread_mutex_unlock(&(t->mutex));

	Mix_HaltMusic();
	Mix_CloseAudio();
	return 0;
}
