from server import Team
from pprint import pprint
from event_test import serv_usr_created, cli_print_user


def test_users():
    team = Team()
    name1 = "toto"
    name2 = "tata"
    name3 = "titi"
    serv, cli = team.run([f'/users\n',])
    assert cli[0][0] == 'client_error_unauthorized'
    serv, cli = team.run([f'/login "{name1}"\n',])
    uuid1 = serv_usr_created(serv[0], name1)
    serv, cli = team.run([f'/login "{name2}"\n',])
    uuid2 = serv_usr_created(serv[0], name2)
    serv, cli = team.run([f'/login "{name3}"\n',])
    uuid3 = serv_usr_created(serv[0], name3)

    serv, cli = team.run(["/users"])
    assert len(cli) == 3
    cli_print_user(cli[0], uuid1, name1)
    cli_print_user(cli[1], uuid2, name2)
    cli_print_user(cli[2], uuid3, name3)


if __name__ == "__main__":
    test_users()
