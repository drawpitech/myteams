from server import Team
from pprint import pprint


def test_info_user():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/login "{name}"\n'])
    uuid = serv[0][1]
    serv, cli = team.run(['/info'])
    assert serv == None
    assert cli[0][0] == 'client_print_user'
    assert cli[0][1] == uuid
    assert cli[0][2] == 'toto'
    assert cli[0][3] == '1'

def test_info_errors():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/login "{name}"\n', "/logout"])
    uuid = serv[0][1]
    serv, cli = team.run(['/info'])
    assert cli[1][0] == 'client_error_unauthorized'

if __name__ == "__main__":
    # test_info_user()
    test_info_errors()
