//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include <memory>
#include "SoundComponent.hpp"

namespace BBM
{	
	float SoundComponent::volume = 0.75;

	SoundComponent::SoundComponent(WAL::Entity &entity, \
const std::map<SoundComponent::soundIndex, std::string> &soundPath)
		: WAL::Component(entity),
		  _soundIndex(IDLE),
		  _soundPath(soundPath)
	{
		for (int i = 0; i <= DEATH; i++) {
			this->_isLoad[static_cast<soundIndex>(i)] = false;
		}
		for (auto &soundPath : soundPath)
		{
			this->_isLoad[soundPath.first] = true;
			this->_soundList[soundPath.first] = std::make_unique<RAY::Audio::Sound>(soundPath.second);	
		}
	}

	WAL::Component *SoundComponent::clone(WAL::Entity &entity) const
	{
		return new SoundComponent(entity, this->_soundPath);
	}

	void SoundComponent::playSound()
	{   
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		if (!this->_soundList[this->_soundIndex].get()->isPlaying())
			this->_soundList[this->_soundIndex].get()->play();
	}

	void SoundComponent::stopSound()
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		if (this->_soundList[this->_soundIndex].get()->isPlaying())
			this->_soundList[this->_soundIndex].get()->stop();
	}

	void SoundComponent::pauseSound()
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		this->_soundList[this->_soundIndex].get()->pause();
	}

	void SoundComponent::setVolume(float &volumeUpdate)
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		if (volumeUpdate >= 0)
			this->volume = volumeUpdate;
			this->_soundList[this->_soundIndex].get()->setVolume(this->volume);
	}

	void SoundComponent::setPitch(float &pitch)
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return;
		this->_soundList[this->_soundIndex].get()->setPitch(pitch);
	}

	bool SoundComponent::isPlaying()
	{
		if (!this->_isLoad.at(this->_soundIndex))
			return (false);
		return (this->_soundList[this->_soundIndex].get()->isPlaying());
	}
	
	void SoundComponent::setIndex(soundIndex index)
	{
		this->_soundIndex = index;
	}

	SoundComponent::soundIndex SoundComponent::getIndex()
	{
		return (this->_soundIndex);
	}

} // namespace WAL
