#include "../headers/fileops.h"

/* bankSave - saves a bank to JSON file
 * @ret - 1 on success, 0 on failure
 */
int bankSave(struct Bank *b) {
	// Open the file
	FILE * fileptr;
	fileptr = fopen(b->fileName, "w");

	// Write the object's file name
	fputs("{\"", fileptr);
	fputs(b->fileName, fileptr);
	fputs("\": {\n", fileptr);

		// Bank properties
		char temp[10];

		sprintf(temp, "%d", b->count);
		fputs("\t", fileptr);
		fputs("\"count\":", fileptr);
		fputs(temp, fileptr);
		fputs(",\n", fileptr);

		sprintf(temp, "%d", b->relayCapacity);
		fputs("\t", fileptr);
		fputs("\"relayCapacity\":", fileptr);
		fputs(temp, fileptr);
		fputs(",\n", fileptr);

		sprintf(temp, "%d", b->wakeTime);
		fputs("\t", fileptr);
		fputs("\"wakeTime\":", fileptr);
		fputs(temp, fileptr);
		fputs(",\n", fileptr);

		sprintf(temp, "%d", b->lightDuration);
		fputs("\t", fileptr);
		fputs("\"lightDuration\":", fileptr);
		fputs(temp, fileptr);
		fputs(",\n", fileptr);

		sprintf(temp, "%d", b->sprayInterval);
		fputs("\t", fileptr);
		fputs("\"sprayInterval\":", fileptr);
		fputs(temp, fileptr);
		fputs(",\n", fileptr);

		sprintf(temp, "%d", b->sprayDuration);
		fputs("\t", fileptr);
		fputs("\"sprayDuration\":", fileptr);
		fputs(temp, fileptr);
		fputs(",\n", fileptr);

		// Relays loop
		fputs("\t", fileptr);
		fputs("\"relays\": [\n", fileptr);

		for (int i = 0; i < b->count; i++) {
			fputs("\t\t{", fileptr);

			char cTemp[2];
			cTemp[0] = b->relays[i]->label;
			cTemp[1] = '\0';

			fputs("\"label\": \"", fileptr);
			fputs(cTemp, fileptr);
			fputs("\", ", fileptr);

			sprintf(temp, "%d", b->relays[i]->number);
			fputs("\"number\": ", fileptr);
			fputs(temp, fileptr);
			fputs(", ", fileptr);

			fputs("\"status\": ", fileptr);
			if (b->relays[i]->number == 0) {
				fputs("0", fileptr);
			} else {
				fputs("1", fileptr);
			}
			fputs("},\n", fileptr);
		}

		fputs("\t]\n", fileptr);
		fputs("}\n", fileptr);



	fclose(fileptr);
	return 0;
}
