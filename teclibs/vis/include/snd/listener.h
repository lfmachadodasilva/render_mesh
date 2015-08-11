#ifndef SNDLISTENER_H
#define SNDLISTENER_H

#include "defines.h"

class SND_API SndListener
{
private:
	float gain;
	float rolloff;
	float position[3];
	float velocity[3];
	float orientation[6];

public:
	
	// Contrutor padrão
	SndListener();

	// Destrutor padrão
	~SndListener(){}

	// Configura a nova posicao
	void SetPosition(float * position);
	void SetPosition(float xposition, float yposition, float zposition);

	// Configura a nova velocidade
	void SetVelocity(float * velocity);
	void SetVelocity(float xvelocity, float yvelocity, float zvelocity);

	// Configura a nova orientacao
	void SetOrientation(float * orientation);
	void SetOrientation(float xorientation, float yorientation, float zorientation, float xup, float yup, float zup);
};

#endif
