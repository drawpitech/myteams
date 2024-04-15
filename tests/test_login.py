from server import run_server


def test_login():
    name = "bob"
    serv, cli = run_server([f'/login "{name}"\n'])
    print(serv, cli)

    assert serv[0][0] == "server_event_user_created"
    uuid = serv[0][1]
    assert serv[0][2] == name

    assert cli[0][0] == "client_event_logged_in"
    assert cli[0][1] == uuid
    assert cli[0][2] == name


if __name__ == "__main__":
    serv, cli = run_server(['/login "uwu"\n'])
    print(serv, cli)
