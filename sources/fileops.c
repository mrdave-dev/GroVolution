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
			if (b->relays[i]->status == 0) {
				fputs("0", fileptr);
			} else {
				fputs("1", fileptr);
			}
			fputs("},\n", fileptr);
		}

		fputs("\t\t]\n", fileptr);
		fputs("\t}\n", fileptr);
		fputs("}\n", fileptr);

	fclose(fileptr);
	return 0;
}

struct Bank* bankLoad(char* fn) {
	struct Bank* t = bankInit();
	strcpy(t->fileName, "untitled.json");

	FILE * fileptr = fopen(t->fileName, "r");

	if (fileptr == NULL) {
		printf("ERROR: File not found. \n");
		return NULL;
	}

	char buffer[100];

	while(fgets(buffer, 100, fileptr) != NULL) {
		if (strstr(buffer, "\"count\"") != NULL) {
			//t->count = _getNumValueFromJSON(buffer, "\"count\"");

		} else if (strstr(buffer, "\"relayCapacity\"") != NULL) {
			t->relayCapacity = _getNumValueFromJSON(buffer, "\"relayCapacity\"");

		} else if (strstr(buffer, "\"wakeTime\"") != NULL) {
			t->wakeTime = _getNumValueFromJSON(buffer, "\"wakeTime\"");

		} else if (strstr(buffer, "\"lightDuration\"") != NULL) {
			t->lightDuration = _getNumValueFromJSON(buffer, "\"lightDuration\"");

		} else if (strstr(buffer, "\"sprayInterval\"") != NULL) {
			t->sprayInterval = _getNumValueFromJSON(buffer, "\"sprayInterval\"");

		} else if (strstr(buffer, "\"sprayDuration\"") != NULL) {
			t->sprayDuration = _getNumValueFromJSON(buffer, "\"sprayDuration\"");

		} else if (strstr(buffer, "\"relays\"") != NULL) {
			while (fgets(buffer, 100, fileptr) != NULL) {
				// break at end of array
				if (strcmp(buffer, "]") == 0) {
					break;
				}

				char ab = _getCharValueFromJSON(buffer, "\"label\"");
				int num = _getNumValueFromJSON(buffer, "\"number\"");
				int st = _getNumValueFromJSON(buffer, "\"status\"");

				bankAddRelay(t, ab, num);

			}
		}


	}

	return t;

}

int _getNumValueFromJSON(char* b, char* k) {
			char* placePtr = strstr(b, k);
			while (isdigit(*placePtr) == 0) {
				placePtr++;
			}

			int digitsLeft = 0;
			while ((*placePtr != '\0') && (*placePtr != ',')
					&& (*placePtr != '}')) {
				digitsLeft++;
				placePtr++;
			}

			placePtr -= digitsLeft;

			int val = 0;
			for (int i=1; i<=digitsLeft; i++) {
				val = val + ((*placePtr - '0') * pow(10, (digitsLeft - i)));
				placePtr++;
			}

			return val;
}

char _getCharValueFromJSON(char* b, char* k) {
			char* placePtr = strstr(b, k);
			placePtr += strlen(k);
			placePtr++;

			while (placePtr[0] != '\"') {
				placePtr++;
			}

			placePtr++;

			return *placePtr;
}
