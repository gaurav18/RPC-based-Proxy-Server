#include "Something.h"  // As an example
#include "common.h"

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <iostream>
#include <fstream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Test;
using namespace std;

int main(int argc, char **argv) {
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	string batch = "batch1.txt";
	if (argv[1]) {
		batch = argv[1];
	}

	ifstream infile;
	infile.open (batch);
	string _ret;
	SomethingClient client(protocol);
	transport->open();

	for( std::string line; getline( infile, line ); ) // To get you all the lines.
	{
		_ret = "";
	    cout << line; // Prints our url.
	    client.ping(_ret,line);
	    printf("%.100s\n", _ret.c_str()); // print first 100 characters of returned body of doc
	    cout << endl;
	}

	infile.close();
	transport->close();
	return 0;
}
