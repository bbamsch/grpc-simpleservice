from concurrent import futures
import logging

import grpc

import service_pb2
import service_pb2_grpc

class SimpleServer(service_pb2_grpc.SimpleServiceServicer):

    def TestMethod(self, request, context):
        return service_pb2.TestMethodResponse(echo=request.echo)


if __name__ == '__main__':
    logging.basicConfig()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    service_pb2_grpc.add_SimpleServiceServicer_to_server(SimpleServer(), server)
    server.add_insecure_port('[::]:8080')
    server.start()
    server.wait_for_termination()
