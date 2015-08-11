#ifndef SNDBACKSOUND_H
#define SNDBACKSOUND_H

#include "defines.h"
#include "sound.h"

class SND_API SndBackSound : public SndSound
{
	friend class SndManager;
private:
	float backsvolume;

protected:
	// Atualiza o Volume dos Backs
	void SetBacksVolume(float volume);

	// Atualiza o Volume do Som
	virtual void UpdateVolume();

	//Atualiza o Source
	virtual void UpdateSource();

public:
	// Contrutor Padrão
	SndBackSound();

	// Destrutor Padrão
	~SndBackSound();

	// Configura o Volume do som(0%-100%)
	void SetVolume(float volume);

};

#endif

