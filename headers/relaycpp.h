/* GROVOLUTION - relay.c
 * Class definitions for the relay object.
 *
 * Author: Dave Martinez
 * Created: 7/16/15
 *
 */

 #ifndef RELAY_H
 #define RELAY_H

 class relay {
 	private:
 		int number;
 		bool status;
 		char label;
 		RS232Connection connection;

	public:
		int getNumber();
		bool getStatus();
		getLabel();

		void setNumber();
		void setStatus();
		void setLabel();

		void on();
		void off();

		void printInfo();

 }






 #endif
