David Morris
Professor Guanhua Yan
Programming Assignment 4
Due Friday May 8, 2015

Name:   David W. Morris
Email:  dmorris4@binghamton.edu
Compilation:
	run "make all", this will compile both server and client, plus will generate cert.pem and key.pem
Execution:
	DEFAULT CONDITIONS:
		I have provided two default runstates that require less typing
		They are:
			make runServerDefault
			make runClientDefault
		If you run both of these on the same machine, they will connect to eachoter

	CUSTOM CONDITIONS:
		Server Format:
			./server <cert.pem> <key.pem> <portNumber>
		Client Format:
			./client <hostName> <portNumber>

Algorithm Description:
	Meets all requirements

	EXIT CONDITION:
		Input a 0 from the Client, and both programs will exit.
		NOTE!
			This throws a make error when exiting if using the provided default options
			This is expected and not a problem
