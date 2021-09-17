all: client server

protos-cpp:
	mkdir -p gen/ && \
		protoc -I=proto/ --cpp_out=gen/ proto/service.proto && \
		protoc -I=proto/ --grpc_out=gen/ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/service.proto

protos-python:
	mkdir -p gen/ && \
		protoc -I=proto/ --python_out=. proto/service.proto && \
		protoc -I=proto/ --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_python_plugin` proto/service.proto

service-grpc.o: protos-cpp
	g++ -o service-grpc.o -c gen/service.grpc.pb.cc

service.o: protos-cpp
	g++ -o service.o -c gen/service.pb.cc

client: client.cpp service.o service-grpc.o
	g++ -Igen client.cpp service.o service-grpc.o `pkg-config --libs protobuf grpc++` -o client

server: protos-python
