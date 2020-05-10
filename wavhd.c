#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg/arg.h"
#include "wavhd.h"

char *argv0;
typedef unsigned int ui;

void
usage(void)
{
	fprintf(stderr, "Usage: %s [-a audio_format] [-n num_of_chan]"
		"[-s sample_rate] [-d deepness_bits] [-S size_in_bytes]\n", argv0);
	exit(1);
}

ui
islittleendian(void)
{
	unsigned short buf = 1;
	if( *((char*)&buf)==1 )
		return 1 ;
	else
		return 0 ;
}

int
main(int argc, char *argv[])
{
	char *opt_a, *opt_n, *opt_s, *opt_d, *opt_S;
	argv0 = argv[0] ;
	WaveHeader wh = {
		.chunkId = {'R','I','F','F',}, .format = { 'W','A','V','E'},
		.subchunk1Id = {'f','m','t',' '}, .subchunk2Id = {'d','a','t','a'},
	} ;
	/* Setting up the standard values,
		those are the most popular. */
	wh.subchunk1Size = 16 ;
	wh.audioFormat = 1 ;
	wh.numChannels = 1 ;
	wh.sampleRate = 48000 ;
	wh.bitsPerSample = 32 ;
	/* It means read until reaching EOF. */
	wh.subchunk2Size = 0 ;
	ARGBEGIN {
	case 'f' :
		wh.audioFormat = atoi( EARGF(usage()) ) ;
	break;
	case 'n' :
		wh.numChannels = atoi( EARGF(usage()) ) ;
	break;
	case 's' :
		wh.sampleRate = atoi( EARGF(usage()) ) ;
	break;
	case 'd' :
		wh.bitsPerSample = atoi( EARGF(usage()) ) ;
	break;
	case 'S' :
		wh.subchunk2Size = atoi( EARGF(usage()) ) ;
	break;
	default:
		usage();
	} ARGEND
	
	if(argc)
		usage();

	wh.byteRate = wh.sampleRate * wh.numChannels * wh.bitsPerSample/8 ;
	wh.blockAlign = wh.numChannels * wh.bitsPerSample/8 ;
	wh.chunkSize = 4 + (8+wh.subchunk1Size)+(8+wh.subchunk2Size) ;

	fwrite(&wh, sizeof wh, 1, stdout);

	return 0 ;
}
