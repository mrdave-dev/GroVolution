#include "../headers/relay.h"


/* initRelay - initializes a relay by allocating memory address,
 * setting variables, and returning address
 * @param r - the relay pointer to assign
 * @param ab - the relay's label
 * @param n - the relay's sequence number
 * @ret - the address of the new relay
 */
struct relay* initRelay(struct relay* r, char ab, int n) {
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
	char tx[6];

	tx[0] = 'R';

	if (r->status == 1) {
		tx[1] = (char) '0';
	} else {
		tx[1] = '1';
	}

	tx[2] = r->label;

	int firstDigit = r->number;
	firstDigit = firstDigit/10;

	tx[3] = (char) firstDigit + '0';
	tx[4] = (firstDigit%10) + '0';
	tx[5] = '\r';
	tx[6] = '\0';

	printf("TX: %s \n", tx);

	return sendText(tx);
}


int	onRelay(struct relay* r) {
	char tx[6];

	tx[0] = 'R';
	tx[1] = '1';
	tx[2] = r->label;

	int firstDigit = r->number;
	firstDigit = firstDigit/10;

	tx[3] = firstDigit;
	tx[4] = firstDigit%10;
	tx[5] = '\r';
	tx[6] = '\0';

	return sendText(tx);

}
/*
int		offRelay(struct relay* r);
char	getLabelRelay(struct relay* r);
int		getNumRelay(struct relay* r);
int		getStatusRelay(struct relay* r);
*/
