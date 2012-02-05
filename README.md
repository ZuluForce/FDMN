Frugal Distributed Media Network
================================

Author: Andrew Helgeson
Location: University of Minnesota

This is a learning project intended to resolve an issue with serving media spread across multiple network nodes. The idea is that there is one central (preferrably low-power), always on server which may or may not contain any of the served media files. Other nodes on the network can be sleeping and when a file is requested which is housed on one of these nodes, it is awakened (Wake-On-Lan). Here is what I hope to achieve from this project:

* Seamless scalablity of local media networks from extra PC's
* Maintain distributed network at relatively low power-consumption
* Personal Goals: Learn more C++, network programming and GUI development

Build Instructrions
-------------------

To build the project I have included a simple makefile.

To build use: `make` or `make fdmn_server`
With debugging: `make fdmn_server_debug`

As a convenience I also provided `make run_server` which builds and runs the server

There are other targets for building windows executables under mingw but the project is currently broken for Windows support.

###Dependencies
####Server
* Boost::Threads
* GNU Readline library
* Google-Breakpad
* Unix OS (Tested on Ubuntu 11.04)
* Tested with gcc compiler but no specific GNU C features are being used

####Client
* Python 3 or higher
* Qt4 UI framework
* PyQt bindings

Progress
--------

###Server
So far I have been building the framework of the server without the network functionality. I have most of the framework initialized so soon I will work on making the actual protocol and implementing more network code. Currently you can start the server and make a TCP connection but nothing happens beyond that.
	
####To-Do
	* Create message protocol
	* Create "mount" system for mapping distributed files to one node
	* Rewrite older code to make it cross-platform with Windows (maybe Mac but I don't have one to test on)

###Client
I decided to write the client in Python using PyQt for the GUI. I have experience with Python but not the Qt framework which is where the slow-down is. Python makes for quick development of the background networking code.
	
####To-Do
	* Read more about Qt Model/View Architecture
	* Continue adding to UI
	* Implement FDMN protocol after it is created
