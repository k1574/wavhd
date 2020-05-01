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
	(ui)wh.subchunk1Size = 16 ;
	(ui)wh.audioFormat = 1 ;
	(ui)wh.numChannels = 1 ;
	(ui)wh.sampleRate = 48000 ;
	(ui)wh.bitsPerSample = 32 ;
	/* It means read until reaching EOF. */
	(ui)wh.subchunk2Size = 0 ;
	ARGBEGIN {
	case 'f' :
		(ui)wh.audioFormat = atoi( EARGF(usage()) ) ;
	break;
	case 'n' :
		(ui)wh.numChannels = atoi( EARGF(usage()) ) ;
	break;
	case 's' :
		(ui)wh.sampleRate = atoi( EARGF(usage()) ) ;
	break;
	case 'd' :
		(ui)wh.bitsPerSample = atoi( EARGF(usage()) ) ;
	break;
	case 'S' :
		(ui)wh.subchunk2Size = atoi( EARGF(usage()) ) ;
	break;
	default:
		usage();
	} ARGEND
	
	if(argc)
		usage();

	(ui)wh.byteRate = (ui)wh.sampleRate * (ui)wh.numChannels * (ui)wh.bitsPerSample/8 ;
	(ui)wh.blockAlign = (ui)wh.numChannels * (ui)wh.bitsPerSample/8 ;
	(ui)wh.chunkSize = 4 + (8+(ui)wh.subchunk1Size)+(8+(ui)wh.subchunk2Size) ;

	fwrite(&wh, sizeof wh, 1, stdout);

	return 0 ;
}
