
// AUTHOR: Aaron Cox
// DESCRIPTION: Not done, experemental. Buggy and poorly designed.

#ifndef AUDIO_H
#define AUDIO_H

#include <map>

struct Mix_Chunk;

struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;

struct Sound
{
	friend class Audio;
	void Play(int loops = 0);
protected:
	Mix_Chunk *m_sound;
};

struct Song
{
	friend class Audio;
	void Play(int loops = 0);
protected:
	Mix_Music *m_song;
};

class Audio
{
public:



public:

	Sound *LoadSound(const char *filename, const char *name);
	Sound *GetSound(const char *name);

	Song *LoadSong(const char *filename, const char *name);
	Song *GetSong(const char *name);

	bool IsPaused();
	void PauseSong();
	void ResumeSong();
	void StopSong();

	static void CreateSingleton()	{ sm_instance = new Audio(); }
	static void DeleteSingleton()	{ delete sm_instance; }
	static Audio* GetInstance()		{ return sm_instance; }

protected:

	Audio(void);
	virtual ~Audio(void);

	// singleton
	static Audio* sm_instance;

	std::map<const char *, Sound *> m_sounds;
	std::map<const char *, Song *> m_songs;


private:

};

#endif