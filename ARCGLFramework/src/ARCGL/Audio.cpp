#include "ARCGL\audio.h"
#include "SDL\SDL.h"
#include "SDL\SDL_mixer.h"

#include <iostream>

// initialising singleton
Audio* Audio::sm_instance = NULL;

Audio::Audio(void)
{
	int				audio_rate		= 22050;
	unsigned short	audio_format	= AUDIO_S16SYS;
	int				audio_channels	= 2;
	int				audio_buffers	= 4096;

	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers); 

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG );

}

Audio::~Audio(void)
{
	for(auto iter = m_sounds.begin(); iter != m_sounds.end(); iter++)
	{
		Mix_FreeChunk(iter->second->m_sound);
	}

	for(auto iter = m_songs.begin(); iter != m_songs.end(); iter++)
	{
		Mix_FreeMusic(iter->second->m_song);
	}

	Mix_CloseAudio();
	Mix_Quit();
}

Sound *Audio::LoadSound(const char *filename, const char *name)
{
	auto iter = m_sounds.find(name);
	if( iter == m_sounds.end() )
	{
		try
		{
			//SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
			//Mix_Chunk *mixChunk = Mix_LoadWAV_RW(rw, 1);
			Mix_Chunk *mixChunk = Mix_LoadWAV(filename);
			if( mixChunk == NULL )
			{
				
			}
			else
			{
				Sound *snd = new Sound();
				snd->m_sound = mixChunk;
				m_sounds[name] = snd;
				return snd;
			}
		}
		catch(std::exception e)
		{	
			std::cout << "failed to load sound" << std::endl;
		}
	}
	else
	{
		return iter->second;
	}

	return NULL;
}
Sound *Audio::GetSound(const char *name)
{
	auto iter = m_sounds.find(name);
	if( iter == m_sounds.end() )
		return NULL;

	return iter->second;
}

Song *Audio::LoadSong(const char *filename, const char *name)
{
	auto iter = m_songs.find(name);
	if( iter == m_songs.end() )
	{
		Mix_Music *mix = Mix_LoadMUS(filename);
		if( mix == NULL )
		{
			
		}
		else
		{
			Song *song = new Song();
			song->m_song = mix;
			m_songs[name] = song;
			return song;
		}
	}
	else
	{
		return iter->second;
	}

	return NULL;
}
Song *Audio::GetSong(const char *name)
{
	auto iter = m_songs.find(name);
	if( iter == m_songs.end() )
		return NULL;

	return iter->second;
}


void Sound::Play(int loops)
{
	Mix_PlayChannel(-1, m_sound, loops);
}
void Song::Play(int loops)
{
	Mix_PlayMusic( m_song, loops );
}

bool Audio::IsPaused()
{
	return Mix_PausedMusic() == 1;
}
void Audio::PauseSong()
{
	if( !IsPaused() )
		Mix_PauseMusic();
}
void Audio::ResumeSong()
{
	if( IsPaused() )
		Mix_ResumeMusic();
}
void Audio::StopSong()
{
	Mix_HaltMusic();
}

