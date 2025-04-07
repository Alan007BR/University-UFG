#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Socket Python Doc: https://docs.python.org/3/library/socket.html

# Importe o pacote do socket
import socket

# Cria um objeto socket UDP
ipv4 = socket.AF_INET
udp = socket.SOCK_DGRAM
sock = socket.socket(ipv4, udp)

# Escolher a porta de origem (porta local)
porta_origem = int(input("Digite a porta de origem do servidor (ex: 12345): "))

# Defina a porta na qual vocÃª deseja se conectar
port = 12345

# Envia uma mensagem ao servidor
sock.sendto("Hi Server".encode(), ('127.0.0.1', porta_origem))

# Espera receber uma mensagem de resposta do servidor.
data, addr = sock.recvfrom(1024)
print(data.decode())

# Feche a conexÃ£o
sock.close()