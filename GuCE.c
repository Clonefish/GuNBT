#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <assert.h>

#define CHUNK 1024

unsigned char * inflatenbt(FILE * source, long * rsize)
{
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];
	
	unsigned char * inflated = NULL;
	long size = 0;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit2(&strm, 16 + MAX_WBITS);
	if (ret != Z_OK)
		return NULL;
	
	do
	{
		strm.avail_in = fread(in, 1, CHUNK, source);
		if (ferror(source))
		{
			(void)inflateEnd(&strm);
 			return NULL;
		}
		if (strm.avail_in == 0)
			break;
		strm.next_in = in;
		
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR);
			printf("ret: %i", ret);
			switch (ret)
			{
				case Z_NEED_DICT:
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return NULL;
			}
			have = CHUNK - strm.avail_out;
			inflated = realloc(inflated, have + size);
			memcpy(inflated + size, out, have);
			size += have;
		} while (strm.avail_out == 0);
	} while (ret != Z_STREAM_END);

	(void)inflateEnd(&strm);
	if(Z_STREAM_END)
	{
		*rsize = size;
		return inflated;
	}
	else
		return NULL;
}

/*int main(int argc, char ** argv)
{
	FILE * fp;
	fp = fopen("level.dat", "rb");
	if(fp == NULL)
	{
		printf("Error reading file!\n");
		return 1;
	}
	long size;
	unsigned char * buffer = inflatef(fp, &size);
	if(buffer == NULL)
	{
		printf("ERROR!\n");
		fclose(fp);
		return 1;
	}
	printf("Size %i\n", (int)size);
	int i;
	for(i = 0; i < size; i++)
	{
		printf("%c", buffer[i]);
	}
	printf("\n");
	
	fclose(fp);
}*/

