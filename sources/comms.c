#include "../headers/comms.h"

// sendText(const char* tx)
// Sends text to port, defined by PIPORT, using RS232 library
// @param tx String to be sent to port
// @ret 1 on success, 0 on failure
int sendText(const char* tx) {

	// Copy string to buffer
	char buffer[1024];
	strcpy(buffer, tx);

	// Set mode: 8 bit comm., odd parity, one stop bit
	const char mode[] = {'8', 'O', '1', 0};

	// Open port
	int status = RS232_OpenComport(PIPORT, BAUDRATE, mode);

	if (status == 1) {
		// Error opening port
		printf("ERROR: Could not open communication port. (sendText) \n");
		return 0;
	}

	// Write to port
	RS232_cputs(PIPORT, buffer);

	// Close port
	RS232_CloseComport(PIPORT);

	// printf(" SENT: %s \n", tx);

	return 1;
}

// readText(char* rx)
// Reads text from port and saves to rx
// @param rx Character array to write to
void readText(unsigned char* rx) {
	// Set mode: 8 bit comm., odd parity, one stop bit
	const char mode[] = {'8', 'O', '1', 0};

	unsigned char buffer[100];

	int status = RS232_OpenComport(PIPORT, BAUDRATE, mode);

	if (status > 0) {
		// Error opening port
		printf("ERROR: Could not open communication port. (readText) \n");
		return;
	}

	int i = 0;
	while (i < 20) {
		int n = RS232_PollComport(PIPORT, buffer, 99);

		if (n > 0) {
			buffer[n] = 0;

			for (int x=0; x<n; x++) {
				if (buffer[x] < 32) {
					buffer[x] = '.';
				}
			}

			// printf("received %i bytes: %s\n", n, (char *)buffer);
			break;
		}

		#ifdef _WIN32
			Sleep(100);
		#else
			usleep(100000);  /* sleep for 100 milliSeconds */
		#endif

		i++;
		//printf("Read cycle\n");
	}


	// Assign the recieved text to the param
	unsigned char *cur = buffer;
	int r = 0;
	while (*cur != 0) {
		rx[r] = *cur;
		cur++;
		r++;
	}

	#ifdef _WIN32
		Sleep(2000);
	#else
		usleep(200000);  /* sleep for 100 milliSeconds */
	#endif

}

