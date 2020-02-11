#include "common.h"

void ReadOptimizedObs( CStream *s, vector<CLASS> *cache, const OBJECT *object )
{
	static unsigned char buf[4096];
	size_t nleft = object->size, ncur;
	char filename[16];

	sprintf(filename, "%08x.oor", object->offset);
	FILE *f = fopen(filename, "w");
	if(f == NULL)
		throw "failed to open output sound file";
	while(nleft) {
		ncur = nleft > 4096 ? 4096 : nleft;
		s->read(buf, ncur);
		if(fwrite(buf, 1, ncur, f) != ncur) {
			fclose(f);
			throw "failed to write output sound file";
		}
		nleft -= ncur;
	}
	if(fclose(f) != 0)
		throw "failed to close output sound file";
}
