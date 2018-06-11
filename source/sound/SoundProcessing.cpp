#include "SoundProcessing.hpp"
#include "EmitSoundEvent.hpp"
#include "Sound.hpp"

namespace nexc {

	void SoundProcessing::configure() {
		subscribe<EmitSoundEvent>([](const EmitSoundEvent& ev) {
			sf::Sound sound;
			sound.setBuffer(ev.sound->internal);
			sound.play();
		});
	}

}
