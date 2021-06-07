//
// Created by Tom Augier on 05/06/2021
//

#include <iostream>
#include <memory>
#include "SoundComponent.hpp"

namespace BBM
{
    SoundComponent::SoundComponent(WAL::Entity &entity, \
std::map<SoundComponent::soundIndex, std::string> &soundPath)
        : WAL::Component(entity),
          _soundIndex(IDLE),
          _soundPath(soundPath)
    {
        for (int i = 0; i <= DEATH; i++)
            this->_isLoad[static_cast<soundIndex>(i)] = false;
        /*for (int i = 0; i <= DEATH; i++) {
            if (soundPath.at(static_cast<soundIndex>(i)).empty()) {
                this->_isLoad[static_cast<soundIndex>(i)] = false;
            } else {
                this->_isLoad[static_cast<soundIndex>(i)] = true;
                this->_soundList[static_cast<soundIndex>(i)] = RAY::Audio::Sound(soundPath.at(static_cast<soundIndex>(i)));
            }
        }*/
    }

    SoundComponent::SoundComponent(WAL::Entity &entity)
		: Component(entity),
		  _soundList(),
		  _soundIndex()
	{}

    WAL::Component *SoundComponent::clone(WAL::Entity &entity) const
	{
		return new SoundComponent(entity);
	}

	void SoundComponent::playSound(void)
    {   
        if (!this->_isLoad.at(this->_soundIndex))
            this->_soundList[this->_soundIndex] = RAY::Audio::Sound(this->_soundPath.at(this->_soundIndex));
        if (!this->_soundList[this->_soundIndex].isPlaying())
            this->_soundList[this->_soundIndex].play();
    }

    void SoundComponent::stopSound(void)
    {
        if (!this->_isLoad.at(this->_soundIndex))
            return;
        if (this->_soundList[this->_soundIndex].isPlaying())
            this->_soundList[this->_soundIndex].stop();
    }

    void SoundComponent::pauseSound(void)
    {
        if (!this->_isLoad.at(this->_soundIndex))
            return;
        this->_soundList[this->_soundIndex].pause();
    }

	void SoundComponent::setVolume(float &volume)
    {
        if (!this->_isLoad.at(this->_soundIndex))
            return;
        if (volume >= 0)
            this->_soundList[this->_soundIndex].setVolume(volume);
    }

	void SoundComponent::setPitch(float &pitch)
    {
        if (!this->_isLoad.at(this->_soundIndex))
            return;
        this->_soundList[this->_soundIndex].setPitch(pitch);
    }

	bool SoundComponent::isPlaying(void)
    {
        if (!this->_isLoad.at(this->_soundIndex))
            return (false);
        return (this->_soundList[this->_soundIndex].isPlaying());
    }
    
    void SoundComponent::setIndex(soundIndex index)
    {
        this->_soundIndex = index;
    }

    SoundComponent::soundIndex SoundComponent::getIndex(void)
    {
        return (this->_soundIndex);
    }

} // namespace WAL
