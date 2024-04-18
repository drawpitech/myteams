from server import Team
from pprint import pprint


def test_user_single():
    team = Team()
    name = "toto"
    serv, cli = team.run([
        f'/login "{name}"\n',
    ])
    pprint(serv)
    pprint(cli)

    #login
    assert serv[0][0] == "server_event_user_created"
    uuid = serv[0][1]
    assert serv[0][2] == name

    assert cli[0][0] == "client_event_logged_in"
    assert cli[0][1] == uuid
    assert cli[0][2] == name

    #user
    serv, cli = team.run([
        f'/user "{uuid}"\n',
    ])
    assert serv == None
    assert cli[0][0] == "client_print_user"
    assert cli[0][1] == uuid
    assert cli[0][2] == name
    assert cli[0][3] == '1'
    pprint(serv)
    pprint(cli)

def test_user_not_logged():
    team = Team()
    name = "toto"
    serv, cli = team.run([
        f'/login "{name}"\n',
        f'/logout\n'
    ])
    pprint(serv)
    pprint(cli)

    #login
    assert serv[0][0] == "server_event_user_created"
    uuid = serv[0][1]
    assert serv[0][2] == name

    assert cli[0][0] == "client_event_logged_in"
    assert cli[0][1] == uuid
    assert cli[0][2] == name

    #user
    serv, cli = team.run([
        f'/user "{uuid}"\n',
    ])
    pprint(serv)
    pprint(cli)

    assert serv[0][0] == "server_event_user_logged_out"
    assert serv[0][1] == uuid

    assert cli[0][0] == "client_event_logged_out"
    assert cli[0][1] == uuid
    assert cli[0][2] == name

    assert cli[1][0] == "client_error_unauthorized"

def test_user_wrong():
    team = Team()
    name = "toto"
    serv, cli = team.run([
        f'/login "{name}"\n',
    ])
    pprint(serv)
    pprint(cli)

    #login
    assert serv[0][0] == "server_event_user_created"
    uuid = serv[0][1]
    assert serv[0][2] == name

    assert cli[0][0] == "client_event_logged_in"
    assert cli[0][1] == uuid
    assert cli[0][2] == name

    #user
    serv, cli = team.run([
        f'/user "{"wrong uuid"}"\n',
    ])
    pprint(serv)
    pprint(cli)
    assert serv == None
    assert cli[0][0] == "client_error_unknown_user"
    assert cli[0][1] == "00000000-0000-0000-0000-000000000000"

    serv, cli = team.run([
        f'/user\n',
    ])
    pprint(serv)
    pprint(cli)
    assert serv == None
    assert cli == None

if __name__ == "__main__":
    # test_user_single()
    # test_user_not_logged()
    test_user_wrong()
