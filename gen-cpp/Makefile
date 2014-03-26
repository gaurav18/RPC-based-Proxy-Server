GEN_SRC := rpc_service.cpp rpc_proxy_constants.cpp rpc_proxy_types.cpp cache.cpp proxy.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

GEN_SRC1 := Something.cpp rpc_proxy_constants.cpp rpc_proxy_types.cpp
GEN_OBJ1 := $(patsubst %.cpp,%.o, $(GEN_SRC1))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY: all clean

all: rpc_service_server rpc_service_client

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@ -std=c++0x

rpc_service_server: rpc_service_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -lcurl

rpc_service_client: rpc_service_client.o $(GEN_OBJ1)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift

clean:
	$(RM) *.o rpc_service_server rpc_service_client
