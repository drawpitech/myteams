from server import Team
from pprint import pprint
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

def test_subscribe():
    team = Team()
    name = "toto"
    serv, cli = team.run([f'/login "{name}"\n',],0.2)
    user1 = serv_usr_created(serv[0], name)

    team_uuid, team_name, team_description = team_creation(team, user1)
    serv, cli = team.run([
        f'/logout\n',
        f'/login "tata"\n',
        f'/subscribe "{team_uuid}"\n'], 1)
    serv, cli = team.run([
        f'/logout\n',
        f'/login "titi"\n',
        f'/subscribe "{team_uuid}"\n'], 1)
    serv, cli = team.run([
        f'/logout\n',
        f'/login "tutu"\n',
        f'/subscribe "{team_uuid}"\n'], 0.2)

    serv, cli = team.run(['/subscribed\n'])
    # cli_prin_sub(cli[0], flemme, team_uuid)
    cli_print_teams(cli[2], team_uuid, team_name, team_description)

    serv, cli = team.run([f'/subscribed "{team_uuid}"\n'])
    assert len(cli) == 4
    cli_print_user(cli[0], "", "toto")
    cli_print_user(cli[1], "", "tata")
    cli_print_user(cli[2], "", "titi")
    cli_print_user(cli[3], "", "tutu")

    serv, cli = team.run([f'/unsubscribe "{team_uuid}"\n'])
    serv, cli = team.run([f'/subscribed "{team_uuid}"\n'])
    assert len(cli) == 3
    cli_print_user(cli[0], "", "toto")
    cli_print_user(cli[1], "", "tata")
    cli_print_user(cli[2], "", "titi")



    return

if __name__ == "__main__":
    test_subscribe()
