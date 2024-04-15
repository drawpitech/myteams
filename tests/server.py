import subprocess
import os
import pathlib
import socket
import time

OUTPUT = list[list[str]]


def run_teams(cmds: list[str]) -> tuple[OUTPUT, OUTPUT]:
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

    server_proc = subprocess.Popen(
        ["./myteams_server", str(port)],
        env=envp,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )

    client_proc = subprocess.Popen(
        ["./myteams_cli", "0.0.0.0", str(port)],
        env=envp,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    if client_proc.stdin is None:
        raise Exception("Failed to open stdin")

    for command in cmds:
        print(f"Sending command: {command}")
        client_proc.stdin.write(command.encode())
        client_proc.stdin.flush()

    # Wait for the server to reply all the events
    time.sleep(0.5)

    client_proc.stdin.close()
    if client_proc.wait() != 0:
        print(f"{client_proc=}")
        raise Exception("Client failed")

    server_proc.terminate()

    out_server = server_proc.stderr
    out_client = client_proc.stderr
    if out_server is None or out_client is None:
        raise Exception("Server or client failed")

    return decode(out_server.read()), decode(out_client.read())


def find_available_port():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("localhost", 0))
    port = s.getsockname()[1]
    s.close()
    return port


def decode(input: bytes) -> OUTPUT:
    return [l.split("\t") for l in input.decode().splitlines()]
