#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Socket Python Doc: https://docs.python.org/3/library/socket.html

# Importe o pacote do socket
import socket

# Cria um objeto socket TCP/IP.
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Defina a porta na qual vocÃª deseja se conectar
port = 12345

# Conecte-se ao servidor
sock.connect(("127.0.0.1", port))

# Envia uma mensagem ao servidor
sock.send("Hi Server".encode())

# Espera receber uma mensagem de resposta do servidor.
data = sock.recv(1024)
print(data.decode())

# Feche a conexÃ£o
sock.close()