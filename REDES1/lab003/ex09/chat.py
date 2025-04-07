import socket
import threading
import sys

HOST = '127.0.0.1'
PORT = 12345

def send_msg(conn):
    while True:
        try:
            msg = conn.recv(1024).decode()
            if msg.lower() == "sair":
                print("Conexão encerrada.")
                break
            print("\n[Remoto]:", msg)
        except KeyboardInterrupt:
            print("\nConexão encerrada pelo usuário.")
            break
        except ConnectionResetError:
            print("\nConexão perdida.")
            sys.exit(0)
            break
        except Exception as e:
            print(f"\nErro: {e}")
            break

def server():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind((HOST, PORT))
        sock.listen(1)
        print(f"Servidor TCP esperando conexão na porta {PORT}...")
        conn, addr = sock.accept()
        print(f"Conexão estabelecida com {addr}")
        print(f"[Servidor] IP local: {conn.getsockname()} | IP remoto: {conn.getpeername()}")

        threading.Thread(target=send_msg, args=(conn,), daemon=True).start()

        while True:
            msg = input("[Você]: ")
            conn.send(msg.encode())
            if msg.lower() == "sair":
                break
    except KeyboardInterrupt:
        print("\nServidor encerrado pelo usuário.")
        sys.exit(0)
    except Exception as e:
        print(f"Erro: {e}")
        sys.exit(1)
    finally:
        if 'conn' in locals():
            conn.close()
            sys.exit(0)
        if 'sock' in locals():
            sock.close()
            sys.exit(0)
        if 'addr' in locals():
            print(f"Conexão com {addr} encerrada.")
            sys.exit(0)
        if 'sock' in locals():
            sock.close()
            sys.exit(0)
        if 'conn' in locals():
            conn.close()
            sys.exit(0)
        print("Servidor encerrado.")

def client():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #TCP
        sock.connect((HOST, PORT))
        # sock.bind((HOST, 0))
        print(sock.dup())
        print(f"Conectado ao servidor em {HOST}:{PORT}")

        print(f"[Cliente] Conectado ao servidor {sock.getpeername()}")
        print(f"[Cliente] IP local: {sock.getsockname()} | IP remoto: {sock.getpeername()}")

        threading.Thread(target=send_msg, args=(sock,), daemon=True).start()

        while True:
            msg = input("[Você]: ")
            sock.send(msg.encode())
            print(f"[Cliente] Enviado {len(msg.encode())} bytes")
            if msg.lower() == "sair":
                break
    except ConnectionRefusedError:
        print("Erro: O servidor não está disponível, verifique se você iniciou o servidor.")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nConexão encerrada pelo usuário.")
        sock.close()
        sys.exit(0)

    sock.close()

# main
if __name__ == "__main__":
    if len(sys.argv) != 2 or sys.argv[1] not in ["-s", "-c"]:
        print("Uso: python chat.py -s  (modo servidor)")
        print("     python chat.py -c  (modo cliente)")
        sys.exit(1)

    if sys.argv[1] == "-s":
        server()
    else:
        client()
