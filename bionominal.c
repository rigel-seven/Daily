#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


enum Config {
	DEFAULT_LINES = 10,
	DEFAULT_SPACE = ' ',
	DEFAULT_CMD_WIDTH = 80,
	DEFAULT_BUFFER_SIZE = 1024
};

enum Slash {
	SLASH = '/',
	BACKSLASH = '\\',
	NONE = ' '
};


struct Binominal
{
	uint32_t current_line;
	char buffer[DEFAULT_CMD_WIDTH];
	char slash_buffer[DEFAULT_CMD_WIDTH];
};


typedef struct Binominal Binominal;

uint32_t factorial(uint32_t n)
{
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

uint32_t ratio(uint32_t n, uint32_t k)
{
	return (uint32_t)(
	(
	(double)factorial(n)
	) / (
	((double)factorial(k)) * ((double)factorial(n - k))
	)
	);
}

int slash_generator(int n)
{
	return (n == SLASH) ? BACKSLASH : SLASH;
}



void print_bionominal(Binominal *bio)
{
	putchar('\n');

}


void binominal_extract(Binominal *bio)
{
	uint32_t bio_start = DEFAULT_CMD_WIDTH / 2 - bio->current_line + 1;
	int lastSlash = NONE;
	memset(bio->buffer, ' ', sizeof(bio->buffer));
	memset(bio->slash_buffer, ' ', sizeof(bio->slash_buffer));	
	for (uint32_t i = 0; i != bio->current_line; i++)
	{
		char temp[DEFAULT_BUFFER_SIZE] = {0};
		snprintf(temp, 1, "%d", ratio(bio->current_line, i++));
		bio->buffer[bio_start] = temp[0];
		lastSlash = NONE?SLASH:slash_generator(lastSlash);
		if(bio->current_line != 1){
			bio->slash_buffer[bio_start++] = lastSlash;
		} else {
			bio_start++;
		}
		i++;
		bio->buffer[bio_start] = ' ';
		bio->slash_buffer[bio_start++] = ' ';
	}
	bio->buffer[DEFAULT_CMD_WIDTH] = '\n';
	bio->slash_buffer[DEFAULT_CMD_WIDTH] = '\n';
	puts(bio->slash_buffer);
	puts(bio->buffer);
}


int main() {
	Binominal bio = { 2 };
	binominal_extract(&bio);
	return 0;
}
