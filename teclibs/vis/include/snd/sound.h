#ifndef SOUND_H
#define SOUND_H

#include "defines.h"

#define MAX_NUM_BUFFERS 50

class SND_API SndSound
{
protected:

	static struct ALCcontext_struct *Context;
	static struct ALCdevice_struct *Device;

	unsigned int freq;
	unsigned int size;
	int	format;
	void	*data;
	
	int error;

	int LAST_TRACK;
	int CURRENT_TRACK;
	int NEXT_TRACK;
	int NEXTRANDOM_TRACK;
	bool TRANSITION;

	bool AUTOPLAY;
	bool RANDOM;
	int RANDOMTIME;
	int rmin_time;
	int rmax_time;
	float randomelapsedtime;

	float FADEIN;
	float FADEOUT;
	float elapsedtime;
	float checktime;
	
	void Fade(float time);
	int FADETIME;

	char* TrackNames[MAX_NUM_BUFFERS];

	unsigned int SndBuffers[MAX_NUM_BUFFERS];
	unsigned int bufferID;
	unsigned int SndSource;
	
	void InitSource();
	void InitBuffer();
	
	bool initsource;
	bool initbuffer;

	float volume;
	float globalvolume;
	
	// Efetua o efeito FadeIn
	void FadeIn(float time);

	// Efetua o efeito FadeOut
	void FadeOut(float time);

	// Escolhe um música e o tempo randomicamente
	void Random(float time);

	// Atualiza o Volume do Som
	virtual void UpdateVolume() = 0;

	// Atualiza o Source
	virtual void UpdateSource() = 0;

	// Atualiza o Volume Global
	void SetGlobalVolume(float volume);

	// Configura um track randomico para ser tocado
	void SetNextRandom();

public:
	float pitch;
	float gain;
	float tmpgain;
	float mingain;
	float maxgain;
	float coneoutergain;
	float coneinnergain;
	float coneouterangle;

	bool LOOP;

	int bufferid;

	int state;

	// Construtor Padrão
	SndSound();

	// Destrutor Padrão
	virtual ~SndSound();

	// Toca o som
	virtual void Play();

	// Para o som
	virtual void Stop();

	// Pausa o som
	virtual void Pause();
	
	// Liga ou desliga o Loop
	void SetLoop(bool option);
	
	// Define um tempo máximo e minimo para trocar de som
	void SetChangeTime(int min_time, int max_time);

	// Desliga a troca de som depois de um determinado tempo
	void SetChangeTimeOff();

	// Liga ou Desliga o Random
	void SetRandom(bool option);

	// Desliga ou Desliga o Autoplay
	void SetAutoplay(bool option);

	// Configura o valor do Gain
	void SetGain(float gain);

	// Configura o valor do Pitch
	void SetPitch(float pitch);

	// Escolhe o track atual
	void SetTrack(int number);

	// Configura o tempo de duração do efeito Fade
	void SetFadeTime(int time);

	// Pula para o próximo track
	void NextTrack();

	// Pula para o track anterior
	void PrevTrack();

	// Atualiza os valores que variam no tempo
	void UpdateVtime(float vtime);

	// Atualiza o volume do som
	virtual void SetVolume(float volume) = 0;

	// Adiciona um som
	bool AddTrack(char * sound);

	// Diz se o som está ou não em loop
	bool GetLoop();

	// Diz se o som está ou não em Random
	bool GetRandom();

	// Diz se o som está ou não em Autoplay
	bool GetAutoplay();

	// Retorna o numero do Track atual
	int GetCurrTrack();

	// Retorna o numero total de Tracks
	int GetTrackNumber();

	// Retorna o nome do Track atual
	char* GetCurrTrackFile(int track);

	// Retorna o Volume do Track
	float GetVolume();

	// Retorna o tempo de Random Minimo
	int GetRandomMin();

	// Retorna o tempo de Random Maximo
	int GetRandomMax();

	bool IsPlaying();
	bool IsPaused();
	bool IsStopped();
};

#endif
