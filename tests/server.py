import subprocess
import os
import pathlib
import socket
import time

OUTPUT = list[list[str]]

class Team:
    def __init__(self):
        port = find_available_port()
        print(f"Using port: {port}")
        path = pathlib.Path(__file__).parent.resolve()
        so_path = path / "mock"

        # Check if mock libary exists
        if not (so_path / "libmyteams.so").exists():
            subprocess.run(["make", "-C", so_path])
        if not (so_path / "libmyteams.so").exists():
            raise FileNotFoundError("libmyteams.so")

        envp = os.environ.copy()
        envp.clear()
        envp["LD_LIBRARY_PATH"] = str(so_path)

        self.server_proc = subprocess.Popen(
            ["./myteams_server", str(port)],
            env=envp,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )

        self.client_proc = subprocess.Popen(
            ["./myteams_cli", "0.0.0.0", str(port)],
            env=envp,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        if self.client_proc.stdin is None:
            raise Exception("Failed to open stdin")
        os.set_blocking(self.server_proc.stderr.fileno(), False)
        os.set_blocking(self.client_proc.stderr.fileno(), False)

    def __del__(self):
        self.server_proc.terminate()
        self.client_proc.stdin.close()
        if self.client_proc.wait() != 0:
            print(f"{self.client_proc=}")
            raise Exception("Client failed")

    def run(self, cmds: list[str]) -> tuple[OUTPUT, OUTPUT, OUTPUT]:
        for command in cmds:
            if (command[-1] != '\n'):
                command += '\n'
            print(f"Sending command: {command}")
            self.client_proc.stdin.write(command.encode())
            self.client_proc.stdin.flush()

        # Wait for the server to reply all the events
        time.sleep(0.5)

        out_server = self.server_proc.stderr
        out_client = self.client_proc.stderr
        if out_server is None or out_client is None:
            raise Exception("Server or client failed")

        if (read_server := out_server.read()):
            read_server = decode(read_server)
        if (read_client := out_client.read()):
            read_client = decode(read_client)
        return read_server, read_client


def find_available_port():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("localhost", 0))
    port = s.getsockname()[1]
    s.close()
    return port


def decode(input: bytes) -> OUTPUT:
    return [l.split("\t") for l in input.decode().splitlines()]
