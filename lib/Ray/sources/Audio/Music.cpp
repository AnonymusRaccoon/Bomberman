/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Music
*/

#include "Audio/Music.hpp"
#include <raylib.h>

RAY::Cache<::Music> RAY::Audio::Music::_musicsCache(LoadMusicStream, UnloadMusicStream);

RAY::Audio::Music::Music(const std::string &path):
	_music(this->_musicsCache.fetch(path.c_str()))
{
}

bool RAY::Audio::Music::isPlaying(void)
{
	return IsMusicStreamPlaying(*_music);
}

RAY::Audio::Music &RAY::Audio::Music::play(void)
{
	PlayMusicStream(*_music);
	return *this;
}

RAY::Audio::Music &RAY::Audio::Music::stop(void)
{
	StopMusicStream(*_music);
	return *this;
}

RAY::Audio::Music &RAY::Audio::Music::pause(void)
{
	PauseMusicStream(*_music);
	return *this;
}

RAY::Audio::Music &RAY::Audio::Music::resume(void)
{
	ResumeMusicStream(*_music);
	return *this;
}

RAY::Audio::Music &RAY::Audio::Music::setVolume(float volume)
{
	SetMusicVolume(*_music, volume);
	return *this;
}

RAY::Audio::Music &RAY::Audio::Music::setPitch(float pitch)
{
	SetMusicPitch(*_music, pitch);
	return *this;
}

RAY::Audio::Music &RAY::Audio::Music::updateMusicStream(void)
{
	UpdateMusicStream(*_music);
	return *this;
}
