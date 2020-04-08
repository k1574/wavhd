#ifndef __WAVHD_H
#define __WAVHD_H

typedef struct {
	/* RIFF header "RIFF. */
	char chunkId[4];
	unsigned long chunkSize;

	/* "WAVE" characters. */
	char format[4];

	/* "fmt" characters. */
	char subchunk1Id[4];

	/* 16 for PCM. */
	unsigned long subchunk1Size;

	/* For PCM = 1(Linear quantization). */
	unsigned short audioFormat;
	
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	
	/* "data". */
	char subchunk2Id[4];
	
	/* Num of byte in data field. */
	unsigned long subchunk2Size;

	/* WAV data. */
} WaveHeader ;

#endif
