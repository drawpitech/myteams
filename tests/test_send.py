from server import Team
from pprint import pprint
from event_test import *

def test_send():
    team = Team()
    serv, cli = team.run([f'/login "toto"\n',],0.2)
    user1 = serv_usr_created(serv[0], "toto")

    serv, cli = team.run([f'/logout\n'])
    serv, cli = team.run([f'/login "tata"\n'])
    user2 = serv_usr_created(serv[0], "tata")

    body = "this is a message"
    serv, cli = team.run([f'/send "{user1}" "{body}"\n'])
    assert serv[0][0] == "server_event_private_message_sended"
    assert serv[0][1] == user2
    assert serv[0][2] == user1
    assert serv[0][3] == body

    serv, cli = team.run([f'/messages "{user1}"\n'])
    assert cli[0][0] == "client_private_message_print_messages"
    assert cli[0][1] == user2
    assert cli[0][3] == body
    return

if __name__ == "__main__":
    test_send()
