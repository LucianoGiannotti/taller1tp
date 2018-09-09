/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "Contra.h"
#include "Timer.h"
#include "Player.h"

#define VERSION 1.0
#define ERROR -1


size_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    fprintf(stderr, "Cannot determine size of %s: %s\n", filename, strerror(errno));
    return ERROR;
}

void show_version() {
	printf("Version: %.1f\n", VERSION);
}

void show_help() {
	char archivo_help[] = "help.txt";
	FILE *fp = fopen(archivo_help, "r");
	if (!fp) return;

	size_t size_archive = fsize(archivo_help);
	char buffer[size_archive + 1];

	size_t read_bytes = fread(buffer, sizeof(char), size_archive, fp);
	if (size_archive != read_bytes) {
		printf("Error: %s\n", strerror(errno));
		return;
	}
	buffer[size_archive] = '\0';

	puts(buffer);
	fclose(fp);
}


int main( int argc, char* argv[] ) {
	bool help, version, log_level, input;
	help = version = log_level = input = false;
	char* log_level_mode;
	char* input_file;
	log_level_mode = NULL;
	input_file = NULL;
	int flag = 0;

	log_level_mode = argv[1];
	input_file = argv[2];
	input = true;
	struct option opts[] = {
		{"version", no_argument, 0, 'V'},
		{"help", no_argument, 0, 'h'},
		{"log level", required_argument, 0, 'l'},
		{"input", required_argument, 0, 'i'}
	};

	while ((flag = getopt_long(argc, argv, "Vhoi:", opts, NULL)) != -1) {
		switch (flag) {
			case 'V' :
				version = true;
				break;
			case 'h' :
				help = true;
				break;
			case 'l' :
				log_level_mode = optarg;
				log_level = true;
				break;
			case 'i' :
				input_file = optarg;
				input = true;
				break;
		}
	}

	if (help) {
		show_help();
	} else if (version) {
		show_version();
	} else {
		Contra game;
		//Start the game
		cout << log_level_mode << endl;
		cout << input_file << endl;
		if( !game.init() ) {
			printf( "Failed to initialize!\n" );
		}
		else {
			//Load media
			if( !game.loadMedia() ) {
				printf( "Failed to load media!\n" );
			}
			else {
				game.run();
			}
		}
	}
	return EXIT_SUCCESS;
}

