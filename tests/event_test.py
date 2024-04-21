from pprint import pprint

def serv_usr_created(reply, name):
    assert reply[0] == "server_event_user_created"
    uuid = reply[1]
    assert reply[2] == name
    return uuid

def serv_team_created(reply, name, user_uuid):
    assert reply[0] == "server_event_team_created"
    uuid = reply[1]
    assert reply[2] == name
    assert reply[3] == user_uuid
    return uuid

def serv_chan_created(reply, name, team_uuid):
    assert reply[0] == "server_event_channel_created"
    assert reply[1] == team_uuid
    uuid = reply[2]
    assert reply[3] == name
    return uuid

def serv_usr_sub(reply, user_uuid, team_uuid):
    assert reply[0] == "server_event_user_subscribed"
    assert reply[1] == team_uuid
    assert reply[2] == user_uuid


def cli_print_user(reply, uuid, name):
    assert reply[0] == "client_print_users"
    assert reply[1] == uuid
    assert reply[2] == name

def check_uuid_name_desc(reply, uuid, name, description):
    assert reply[1] == uuid
    assert reply[2] == name
    assert reply[3] == description


def cli_print_team_created(reply, uuid, name, description):
    assert reply[0] == "client_print_team_created"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_chan_created(reply, uuid, name, description):
    assert reply[0] == "client_print_channel_created"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_event_team_created(reply, uuid, name, description):
    assert reply[0] == "client_event_team_created"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_event_chan_created(reply, uuid, name, description):
    assert reply[0] == "client_event_channel_created"
    check_uuid_name_desc(reply, uuid, name, description)




def cli_print_teams(reply, uuid, name, description):
    assert reply[0] == "client_print_teams"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_chans(reply, uuid, name, description):
    assert reply[0] == "client_team_print_channels"
    check_uuid_name_desc(reply, uuid, name, description)



def cli_print_team(reply, uuid, name, description):
    assert reply[0] == "client_print_team"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_chan(reply, uuid, name, description):
    assert reply[0] == "client_print_channel"
    check_uuid_name_desc(reply, uuid, name, description)



def cli_prin_sub(reply, user_uuid, team_uuid):
    assert reply[0] == "client_print_subscribed"
    assert reply[1] == user_uuid
    assert reply[2] == team_uuid
