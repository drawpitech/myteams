from server import Team
from pprint import pprint
import event_test
from event_test import *

def team_creation(team: Team, uuid1):
    team_name = "TEAM"
    team_description = "descrpition aaaaaaa"
    serv, cli = team.run([f'/create "{team_name}" "{team_description}"'])
    team_uuid = serv_team_created(serv[0], team_name, uuid1).strip()
    cli_print_team_created(cli[0], team_uuid, team_name, team_description)
    cli_event_team_created(cli[1], team_uuid, team_name, team_description)

    serv, cli = team.run([f'/subscribe "{team_uuid}"'], 0.2)
    serv_usr_sub(serv[0], uuid1, team_uuid)
    cli_prin_sub(cli[0], uuid1, team_uuid)

    return team_uuid, team_name, team_description

def chan_creation(team: Team, uuid1, team_uuid):
    chan_name = "CHAN"
    chan_description = "never gonna give you up"
    serv, cli = team.run([f'/create "{chan_name}" "{chan_description}"'])
    chan_uuid = serv_chan_created(serv[0], chan_name, team_uuid)
    cli_print_chan_created(cli[0], chan_uuid, chan_name, chan_description)
    cli_event_chan_created(cli[1], chan_uuid, chan_name, chan_description)

    return chan_uuid, chan_name, chan_description

def thread_creation(team: Team, uuid1, team_uuid, chan_uuid):
    thread_name = "THREAD"
    thread_description = "thread body"
    serv, cli = team.run([f'/create "{thread_name}" "{thread_description}"'])
    thread_uuid = serv_thread_created(serv[0], thread_name, thread_description, chan_uuid, uuid1)
    timestamp = cli_print_thread_created(cli[0], thread_name, thread_description, thread_uuid, uuid1)
    cli_event_thread_created(cli[1], thread_name, thread_description, thread_uuid, uuid1, timestamp)

    return thread_uuid, timestamp, thread_name, thread_description

def reply_creation(team: Team, user, team_uuid, chan, thread):
    body = "reply"
    serv, cli = team.run([f'/create "{body}"'])
    serv_reply_created(serv[0], thread, user, body)
    timestamp = cli_print_reply_created(cli[0], thread, user, body)
    cli_event_reply_created(cli[1], team_uuid, thread, user, body)
    return timestamp




def test_create_team():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/create\n'],0.2)
    assert cli[0][0] == 'client_error_unauthorized'
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    uuid1 = serv_usr_created(serv[0], name)

    team_uuid, team_name, team_description = team_creation(team, uuid1)
    serv, cli = team.run([f'/list'], 0.2)
    cli_print_teams(cli[0], team_uuid, team_name, team_description)
    serv, cli = team.run([f'/use "{team_uuid}"'], 0.2)
    serv, cli = team.run([f'/info'], 0.2)
    cli_print_team(cli[0], team_uuid, team_name, team_description)
    return


def test_create_chan():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    uuid1 = serv_usr_created(serv[0], name)

    team_uuid, team_name, team_description = team_creation(team, uuid1)
    serv, cli = team.run([f'/use "{team_uuid}"'], 0.2)
    chan_uuid, chan_name, chan_description = chan_creation(team, uuid1, team_uuid)
    serv, cli = team.run([f'/list'], 0.2)
    cli_print_chans(cli[0], chan_uuid, chan_name, chan_description)
    serv, cli = team.run([f'/use "{team_uuid}" "{chan_uuid}"'], 0.2)
    serv, cli = team.run([f'/info'], 0.2)
    cli_print_chan(cli[0], chan_uuid, chan_name, chan_description)
    return

def test_create_thread():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    uuid1 = serv_usr_created(serv[0], name)

    team_uuid, team_name, team_description = team_creation(team, uuid1)
    serv, cli = team.run([f'/use "{team_uuid}"'], 0.2)
    chan_uuid, chan_name, chan_description = chan_creation(team, uuid1, team_uuid)
    serv, cli = team.run([f'/use "{team_uuid}" "{chan_uuid}"'], 0.2)
    thread_uuid, timestamp, thread_name, thread_description = thread_creation(team, uuid1, team_uuid, chan_uuid)
    serv, cli = team.run([f'/list'], 0.2)
    cli_print_threads(cli[0], thread_name, thread_description, thread_uuid, uuid1, timestamp)
    serv, cli = team.run([f'/use "{team_uuid}" "{chan_uuid}" "{thread_uuid}"'], 0.2)
    serv, cli = team.run([f'/info'], 0.2)
    cli_print_thread(cli[0], thread_name, thread_description, thread_uuid, uuid1, timestamp)
    return

def test_create_reply():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    uuid1 = serv_usr_created(serv[0], name)

    team_uuid, team_name, team_description = team_creation(team, uuid1)
    serv, cli = team.run([f'/use "{team_uuid}"'], 0.2)
    chan_uuid, chan_name, chan_description = chan_creation(team, uuid1, team_uuid)
    serv, cli = team.run([f'/use "{team_uuid}" "{chan_uuid}"'], 0.2)
    thread_uuid, timestamp, thread_name, thread_description = thread_creation(team, uuid1, team_uuid, chan_uuid)
    serv, cli = team.run([f'/use "{team_uuid}" "{chan_uuid}" "{thread_uuid}"'], 0.2)
    reply_creation(team, uuid1, team_uuid, chan_uuid, thread_uuid)

    serv, cli = team.run([f'/list'], 0.2)
    return

if __name__ == "__main__":
    # test_create_team()
    # test_create_chan()
    # test_create_thread()
    test_create_reply()
