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

def serv_thread_created(reply, name, description, chan_uuid, user_uuid):
    assert reply[0] == "server_event_thread_created"
    assert reply[1] == chan_uuid
    uuid = reply[2]
    assert reply[3] == user_uuid
    assert reply[4] == name
    assert reply[5] == description
    return uuid

def serv_reply_created(reply, thread_uuid, user, body):
    assert reply[0] == "server_event_reply_created"
    assert reply[1] == thread_uuid
    assert reply[2] == user
    assert reply[3] == body


def serv_usr_sub(reply, user_uuid, team_uuid):
    assert reply[0] == "server_event_user_subscribed"
    assert reply[1] == team_uuid
    assert reply[2] == user_uuid


def cli_print_user(reply, uuid, name):
    assert reply[0] == "client_print_users"
    if (uuid != ""):
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

def cli_print_thread_created(reply, name, description, thread_uuid, user_uuid):
    assert reply[0] == "client_print_thread_created"
    assert reply[1] == thread_uuid
    assert reply[2] == user_uuid
    timestamp = reply[3]
    assert reply[4] == name
    assert reply[5] == description
    return timestamp

def cli_print_reply_created(reply, thread, user, body):
    assert reply[0] == "client_print_reply_created"
    assert reply[1] == thread
    assert reply[2] == user
    timestamp = reply[3]
    assert reply[4] == body
    return timestamp


def cli_event_team_created(reply, uuid, name, description):
    assert reply[0] == "client_event_team_created"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_event_chan_created(reply, uuid, name, description):
    assert reply[0] == "client_event_channel_created"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_event_thread_created(reply, name, description, thread_uuid, user_uuid, timestamp):
    assert reply[0] == "client_event_thread_created"
    assert reply[1] == thread_uuid
    assert reply[2] == user_uuid
    assert reply[3] == timestamp
    assert reply[4] == name
    assert reply[5] == description

def cli_event_reply_created(reply, team, thread, user, body):
    assert reply[0] == "client_event_thread_reply_received"
    assert reply[1] == team
    assert reply[2] == thread
    assert reply[3] == user
    assert reply[4] == body



def cli_print_teams(reply, uuid, name, description):
    assert reply[0] == "client_print_teams"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_chans(reply, uuid, name, description):
    assert reply[0] == "client_team_print_channels"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_threads(reply, name, description, thread_uuid, user_uuid, timestamp):
    assert reply[0] == "client_channel_print_threads"
    assert reply[1] == thread_uuid
    assert reply[2] == user_uuid
    assert reply[3] == timestamp
    assert reply[4] == name
    assert reply[5] == description

def cli_print_replies(reply, thread, user, timestamp, body):
    assert reply[0] == "client_thread_print_replies"
    assert reply[1] == thread
    assert reply[2] == user
    assert reply[3] == timestamp
    assert reply[4] == body

def cli_print_team(reply, uuid, name, description):
    assert reply[0] == "client_print_team"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_chan(reply, uuid, name, description):
    assert reply[0] == "client_print_channel"
    check_uuid_name_desc(reply, uuid, name, description)

def cli_print_thread(reply, name, description, thread_uuid, user_uuid, timestamp):
    assert reply[0] == "client_print_thread"
    assert reply[1] == thread_uuid
    assert reply[2] == user_uuid
    assert reply[3] == timestamp
    assert reply[4] == name
    assert reply[5] == description


def cli_prin_sub(reply, user_uuid, team_uuid):
    assert reply[0] == "client_print_subscribed"
    assert reply[1] == user_uuid
    assert reply[2] == team_uuid
