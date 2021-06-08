//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include "MusicComponent.hpp"

namespace BBM
{
	MusicComponent::MusicComponent(WAL::Entity &entity, const std::string &musicPath)
		: WAL::Component(entity),
		  _musicPath(musicPath),
		  _music(RAY::Audio::Music(musicPath))
	{
	}

	WAL::Component *MusicComponent::clone(WAL::Entity &entity) const
	{
		return new MusicComponent(entity, this->_musicPath);
	}

	void MusicComponent::playMusic(void)
	{   
		if (!this->_music.isPlaying()) {
			this->_music.play();
			this->_music.updateMusicStream();
		}
	}

	void MusicComponent::stopMusic(void)
	{
		if (!this->_music.isPlaying()) {
			this->_music.stop();
			this->_music.updateMusicStream();
		}
	}

	void MusicComponent::pauseMusic(void)
	{
		this->_music.pause();
	}

	void MusicComponent::setVolume(float &volumeUpdate)
	{
		if (volumeUpdate >= 0) {
			this->_music.setVolume(volume);
		}
	}

	void MusicComponent::setPitch(float &pitch)
	{
		this->_music.setPitch(pitch);
	}

	bool MusicComponent::isPlaying(void)
	{
		return (this->_music.isPlaying());
	}

	void MusicComponent::updateMusicStream(void)
	{
		this->_music.updateMusicStream();
	}

} // namespace WAL
