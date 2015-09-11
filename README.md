The GroVolution PLC Interface
=============================


http://www.grovolution.net/
---------------------------


About
-----

This project is an interface for the GroVolution growing system written
in C++/Python/Django. The goal of the software is to provide users with
control of systems attached to a GroVolution aeroponic growing unit.

The bank controls provide a way to view timers and the current statuses
of pumps, lights and valves inside the box.


Authors
-------

This project's principal author is Dave Martinez (http://dmartinez.co)
with error code contributions from Stephanie Vetter. GroVolution is
co-owned by by Eric Wilson, Derek Pallet and Nathan. Visit 
http://www.grovolution.net for more information.


Requirements
------------

*	G++/GCC 4.9 or later
*	Python 3 or later
*	Django 1.7 or later
*	Django Crispy Forms
*	Linux Debian supported, but it'll probably work on other flavors


Installation
------------

### The following assumes the user is on a Debian/Raspian system 
### using apt-get.

### G++/GCC 4.9

As of the last update to this readme (Sept. 10, 2015), G++/GCC 4.9 is
not available on the default repositories for the Raspberry Pi. The
Raspberry Pi uses the Wheezy Debian distributioon. Therefore, the user
must use the Jessie repository to install G++ via apt-get.

> sudo nano /etc/apt/sources.list

Add the following:

> deb http://mirrordirector.raspbian.org/raspbian/ jessie main contrib non-free rpi

Press ctrl+o, then y. 

> sudo apt-get update
> sudo apt-get install g++-4.9 gcc-4.9


### Python 3

> sudo apt-get install python3

### Django

Django is a web framework for Python. Visit https://www.djangoproject.com/ for more
information. This install requires PIP, which is included with Python 3.4 and later.
To test if you have PIP3, type the following:

> pip3 --version

If the shell returns "command not found", type the following:

> sudo apt-get install pip3

Then:

> sudo pip3 install django

### Django Crispy Forms

Crispy Forms helps generate forms. It's pretty awesome. It is also installed via
PIP. Visit http://django-crispy-forms.readthedocs.org/en/latest/ for more 
information.

> sudo pip3 install --upgrade django-crispy-forms


Known bugs
----------

There are some bugs within the interface. 

*	Sending multiple commands quickly may cause the PLC to return bad data.
*	Plugging a ttyusb device while the PLC is on requires a reset of the PLC.
*	Starting the C++ program 'gv' requires a clear of the comport buffer (this
	is currently handled by the 'gv' program by polling the comport twice for
	a response)
