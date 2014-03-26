GEN_SRC := Something.cpp test_constants.cpp test_types.cpp cache.cpp proxy.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

GEN_SRC1 := Something.cpp test_constants.cpp test_types.cpp
GEN_OBJ1 := $(patsubst %.cpp,%.o, $(GEN_SRC1))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: something_server something_client

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@ -std=c++0x

something_server: Something_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -lcurl 

something_client: Something_client.o $(GEN_OBJ1)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift 

clean:
	$(RM) *.o something_server something_client
