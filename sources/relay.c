#include "../headers/relay.h"


/* initRelay - initializes a relay by allocating memory address,
 * setting variables, and returning address
 * @param r - the relay pointer to assign
 * @param ab - the relay's label
 * @param n - the relay's sequence number
 * @ret - the address of the new relay
 */
struct relay* initRelay(char ab, int n) {
	struct relay* t = malloc(sizeof(struct relay));

	// Check for allocated memory
	if (t == 0) {
		printf("ERROR: Unable to create relay %c%i.\n", ab, n);
		return 0;
	}

	t->label = ab;
	t->number = n;
	t->status = 0;

	return t;
}



void setRelayNum(struct relay* r, int n) {
	r->number = n;
}

void setRelayLabel(struct relay* r, char ab) {
	r->label = ab;
}

int switchRelay(struct relay* r) {
	char tx[7];

	tx[0] = 'R';

	if (r->status == 1) {
		tx[1] = (char) '0';
	} else {
		tx[1] = '1';
	}

	tx[2] = r->label;
	tx[3] = '0';

	if (r->number > 10) {
		int firstDigit = r->number;
		firstDigit = firstDigit/10;

		tx[4] = (char) firstDigit + '0';
		tx[5] = (r->number%10) + '0';
	} else {
		tx[4] = '0';
		tx[5] = r->number + '0';
	}

	tx[6] = '\r';
	tx[7] = '\0';

	printf("TX: %s \n", tx);

	if (sendText(tx) == 1) {
		r->status = tx[1];

		#ifdef _WIN32
			Sleep(150);
		#else
			usleep(150000);  /* sleep for 100 milliSeconds */
		#endif

		return 1;
	}


	return 0;
}


int	onRelay(struct relay* r) {
	char tx[7];

	tx[0] = 'R';
	tx[1] = '1';
	tx[2] = r->label;
	tx[3] = '0';
	if (r->number >= 10) {
		int firstDigit = r->number;
		firstDigit = firstDigit/10;

		tx[4] = (char) firstDigit + '0';
		tx[5] = (r->number%10) + '0';
	} else {
		tx[4] = '0';
		tx[5] = r->number + '0';
	}

	tx[6] = '\r';
	tx[7] = '\0';

	if (sendText(tx) == 1) {
		r->status = 1;
		#ifdef _WIN32
			Sleep(150);
		#else
			usleep(150000);  /* sleep for 100 milliSeconds */
		#endif
		return 1;
	}

	return 0;
}


int	offRelay(struct relay* r) {
	char tx[7];

	tx[0] = 'R';
	tx[1] = '0';
	tx[2] = r->label;
	tx[3] = '0';

	if (r->number >= 10) {
		int firstDigit = r->number;
		firstDigit = firstDigit/10;

		tx[4] = (char) firstDigit + '0';
		tx[5] = (r->number%10) + '0';
	} else {
		tx[4] = '0';
		tx[5] = r->number + '0';
	}

	tx[6] = '\r';
	tx[7] = '\0';

	if (sendText(tx) == 1) {
		r->status = 0;
		#ifdef _WIN32
			Sleep(150);
		#else
			usleep(150000);  /* sleep for 100 milliSeconds */
		#endif
		return 1;
	}

	return 0;
}

char getLabelRelay(struct relay* r) {
	return r->label;
}

int	getNumRelay(struct relay* r) {
	return r->number;
}

int	getStatusRelay(struct relay* r) {
	return r->status;
}
