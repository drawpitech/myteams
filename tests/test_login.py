from server import run_teams
from pprint import pprint


def test_login():
    name = "bob"
    serv, cli = run_teams([
        f'/login "{name}"\n',
    ])
    pprint(serv)
    pprint(cli)

    assert serv[0][0] == "server_event_user_created"
    uuid = serv[0][1]
    assert serv[0][2] == name

    assert cli[0][0] == "client_event_logged_in"
    assert cli[0][1] == uuid
    assert cli[0][2] == name


def test_logout():
    name = "bob"
    serv, cli = run_teams([
        f'/login "{name}"\n',
        '/logout\n',
    ])
    pprint(serv)
    pprint(cli)

    # login
    assert serv[0][0] == "server_event_user_created"
    uuid = serv[0][1]
    assert serv[0][2] == name

    assert serv[1][0] == "server_event_user_logged_in"
    assert serv[1][1] == uuid

    assert cli[0][0] == "client_event_logged_in"
    assert cli[0][1] == uuid
    assert cli[0][2] == name

    # logout

    assert serv[2][0] == "server_event_user_logged_out"
    assert serv[2][1] == uuid

    assert cli[1][0] == "client_event_logged_out"
    assert cli[1][1] == uuid
    assert cli[1][2] == name


if __name__ == "__main__":
    test_logout()
