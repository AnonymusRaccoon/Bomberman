//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include "MusicComponent.hpp"

namespace BBM
{
	float MusicComponent::volume = 0.75;

	MusicComponent::MusicComponent(WAL::Entity &entity, const std::string &musicPath)
		: WAL::Component(entity),
		  _music(RAY::Audio::Music(musicPath)),
		  _musicPath(musicPath)
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
		}
	}

	void MusicComponent::stopMusic(void)
	{
		if (this->_music.isPlaying())
			this->_music.stop();
	}

	void MusicComponent::pauseMusic(void)
	{
		this->_music.pause();
	}

	void MusicComponent::setVolume(float volumeUpdate)
	{
		if (volumeUpdate >= 0 && volumeUpdate <= 1) {
			this->volume = volumeUpdate;
			this->_music.setVolume(this->volume);
		}
	}

	void MusicComponent::setPitch(float pitch)
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

	void MusicComponent::turnDownVolume()
	{
		this->setVolume(MusicComponent::volume - 0.1);
	}

	void MusicComponent::turnUpVolume()
	{
		this->setVolume(MusicComponent::volume + 0.1);
	}

} // namespace WAL
