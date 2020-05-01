#ifndef __WAVHD_H
#define __WAVHD_H

typedef char byte;

typedef struct {
	byte b[4];
} b4 ;

typedef struct {
	byte b[2];
} b2 ;

typedef struct {
	/* RIFF header "RIFF. */
	char chunkId[4];
	b4 chunkSize;

	/* "WAVE" characters. */
	char format[4];

	/* "fmt" characters. */
	char subchunk1Id[4];

	/* 16 for PCM. */
	b4 subchunk1Size;

	/* For PCM = 1(Linear quantization). */
	b2 audioFormat;
	
	b2 numChannels;
	b4 sampleRate;
	b4 byteRate;
	b2 blockAlign;
	b2 bitsPerSample;
	
	/* "data". */
	char subchunk2Id[4];
	
	/* Num of byte in data field. */
	b4 subchunk2Size;

	/* WAV data. */
} WaveHeader ;

#endif
