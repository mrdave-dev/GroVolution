To do
=====

This is a general to do list for the Grovolution CLI. The bulk
of the interface's functions were written during the month of
June 2013. This list is meant to weed out bugs and
inconsistencies across the entire platform.

Tracking
--------

Each issue may be assigned a tracking number to provide the
ability to branch from the master and work in upgrades
without disturbing the current release. Branches shoudl be
named after their tracking number.

Issues
------

* 	GV0001 - main.c - The current use of strstr() to identify
	the proper execution of userResponse is unstable. Refactor
	these statements with an overall strtok() to grab the first
	word of response. This will improve the accuracy of the
	if/else statements

*	GV0002 - all - Refactor all of this to c++...

*	GV0003 - main.c - Add additional verfications and error
	messages to help with userResponse.

*	GV0004 - main.c - In 'load' call in if/else tree, a char[]
	is created? Unsure. Check for memory leak here. Also,
	previous struct is not destroyed. Free memory here.

*	GV0005 - bank.c - Need way to rename and report on the name
	of the bank.

*	GV0006 - main.c - Need function to 'save as...'

* 	GV0007 - all - Begin work on a web interface to execute ./gv


