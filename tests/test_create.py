from server import Team
from pprint import pprint
import event_test
from event_test import *

def check_team_creation(team: Team, uuid1):
    team_name = "TEAM"
    team_description = "descrpition aaaaaaa"
    serv, cli = team.run([f'/create "{team_name}" "{team_description}"'])
    team_uuid = serv_team_created(serv[0], team_name, uuid1).strip()
    cli_print_team_created(cli[0], team_uuid, team_name, team_description)
    cli_event_team_created(cli[1], team_uuid, team_name, team_description)


    serv, cli = team.run([f'/list'], 0.2)
    cli_print_teams(cli[0], team_uuid, team_name, team_description)


    serv, cli = team.run([f'/use "{team_uuid}"'], 0.2)
    serv, cli = team.run([f'/subscribe "{team_uuid}"'], 0.2)
    serv_usr_sub(serv[0], uuid1, team_uuid)
    cli_prin_sub(cli[0], uuid1, team_uuid)
    serv, cli = team.run([f'/info'], 0.2)
    cli_print_team(cli[0], team_uuid, team_name, team_description)
    return team_uuid

def check_chan_creation(team: Team, uuid1, team_uuid):
    chan_name = "CHAN"
    chan_description = "never gonna give you up"
    serv, cli = team.run([f'/create "{chan_name}" "{chan_description}"'])
    chan_uuid = serv_chan_created(serv[0], chan_name, team_uuid)
    cli_print_chan_created(cli[0], chan_uuid, chan_name, chan_description)
    cli_event_chan_created(cli[1], chan_uuid, chan_name, chan_description)

    serv, cli = team.run([f'/list'], 0.2)
    cli_print_chans(cli[0], chan_uuid, chan_name, chan_description)
    serv, cli = team.run([f'/use "{team_uuid}" "{chan_uuid}"'], 0.2)
    serv, cli = team.run([f'/info'], 0.2)
    cli_print_chan(cli[0], chan_uuid, chan_name, chan_description)
    return chan_uuid


def test_create_team():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/create\n'],0.2)
    assert cli[0][0] == 'client_error_unauthorized'
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    uuid1 = serv_usr_created(serv[0], name)

    check_team_creation(team, uuid1)
    return



def test_create_chan():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/create\n'],0.2)
    assert cli[0][0] == 'client_error_unauthorized'
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    uuid1 = serv_usr_created(serv[0], name)

    team_uuid = check_team_creation(team, uuid1)
    check_chan_creation(team, uuid1, team_uuid)
    return

if __name__ == "__main__":
    # test_create_team()
    test_create_chan()
