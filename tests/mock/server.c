#include <stdio.h>
#include <myteams/logging_server.h>

int server_event_team_created(
    char const *team_uuid,
    char const *team_name,
    char const *user_uuid)
{
    fprintf(stderr, "server_event_team_created\t%s\t%s\t%s\n", team_uuid, team_name, user_uuid);
    return 0;
}

int server_event_channel_created(
    char const *team_uuid,
    char const *channel_uuid,
    char const *channel_name)
{
    fprintf(stderr, "server_event_channel_created\t%s\t%s\t%s\n", team_uuid, channel_uuid, channel_name);
    return 0;
}

int server_event_thread_created(
    char const *channel_uuid,
    char const *thread_uuid,
    char const *user_uuid,
    char const *thread_title,
    char const *thread_body)
{
    fprintf(stderr, "server_event_thread_created\t%s\t%s\t%s\t%s\t%s\n", channel_uuid, thread_uuid, user_uuid, thread_title, thread_body);
    return 0;
}

int server_event_reply_created(
    char const *thread_uuid,
    char const *user_uuid,
    char const *reply_body)
{
    fprintf(stderr, "server_event_reply_created\t%s\t%s\t%s\n", thread_uuid, user_uuid, reply_body);
    return 0;
}

int server_event_user_subscribed(char const *team_uuid, char const *user_uuid)
{
    fprintf(stderr, "server_event_user_subscribed\t%s\t%s\n", team_uuid, user_uuid);
    return 0;
}

int server_event_user_unsubscribed(char const *team_uuid, char const *user_uuid)
{
    fprintf(stderr, "server_event_user_unsubscribed\t%s\t%s\n", team_uuid, user_uuid);
    return 0;
}

int server_event_user_created(char const *user_uuid, char const *user_name)
{
    fprintf(stderr, "server_event_user_created\t%s\t%s\n", user_uuid, user_name);
    return 0;
}

int server_event_user_loaded(char const *user_uuid, char const *user_name)
{
    fprintf(stderr, "server_event_user_loaded\t%s\t%s\n", user_uuid, user_name);
    return 0;
}

int server_event_user_logged_in(char const *user_uuid)
{
    fprintf(stderr, "server_event_user_logged_in\t%s\n", user_uuid);
    return 0;
}

int server_event_user_logged_out(char const *user_uuid)
{
    fprintf(stderr, "server_event_user_logged_out\t%s\n", user_uuid);
    return 0;
}

int server_event_private_message_sended(
    char const *sender_uuid,
    char const *receiver_uuid,
    char const *message_body)
{
    fprintf(stderr, "server_event_private_message_sended\t%s\t%s\t%s\n", sender_uuid, receiver_uuid, message_body);
    return 0;
}
