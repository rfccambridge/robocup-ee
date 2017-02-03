#!/usr/bin/env python

import proto.messages_robocup_ssl_wrapper_pb2 as wrapper_pb2
import socket
import sys
import struct

MCAST_GRP = '224.5.23.2'
MCAST_PORT = 10002

IF_IP = sys.argv[1]

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    try:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except AttributeError:
        pass
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 32)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 1)

    host = socket.gethostbyname(socket.gethostname())
    sock.setsockopt(socket.SOL_IP, socket.IP_MULTICAST_IF, socket.inet_aton(host))
    sock.setsockopt(socket.SOL_IP, socket.IP_ADD_MEMBERSHIP, socket.inet_aton(MCAST_GRP) + socket.inet_aton(IF_IP))

    sock.bind((MCAST_GRP, MCAST_PORT))

    sock.settimeout(4)

    while 1:
        try:
            data, addr = sock.recvfrom(8192)
            msg = wrapper_pb2.SSL_WrapperPacket()
            msg.ParseFromString(data)
            print msg
            print '====================================================='
        except socket.timeout:
            print "Timed Out"
        except socket.error, e:
            print 'Exception'
    return sock

if __name__ == '__main__':
    main()
