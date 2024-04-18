from server import Team
from pprint import pprint


def test_login():
    team = Team()
    name = "bob"
    serv, cli = team.run([
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
    team = Team()
    name = "bob"
    serv, cli = team.run([
        f'/login "{name}"\n',
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

    serv, cli = team.run([
        '/logout\n',
    ])
    # logout

    assert serv[0][0] == "server_event_user_logged_out"
    assert serv[0][1] == uuid

    assert cli[0][0] == "client_event_logged_out"
    assert cli[0][1] == uuid
    assert cli[0][2] == name


if __name__ == "__main__":
    test_login()
    # test_logout()
