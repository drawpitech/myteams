#include <myteams/logging_client.h>
#include <stdio.h>
#include <time.h>

int client_event_logged_in(char const *user_uuid, const char *user_name)
{
    fprintf(stderr, "client_event_logged_in\t%s\t%s\n", user_uuid, user_name);
    return 0;
}

int client_event_logged_out(char const *user_uuid, const char *user_name)
{
    fprintf(stderr, "client_event_logged_out\t%s\t%s\n", user_uuid, user_name);
    return 0;
}

int client_event_private_message_received(
    char const *user_uuid, char const *message_body)
{
    fprintf(
        stderr, "client_event_private_message_received\t%s\t%s\n", user_uuid,
        message_body);
    return 0;
}

int client_event_thread_reply_received(
    char const *team_uuid, char const *thread_uuid, char const *user_uuid,
    char const *reply_body)
{
    fprintf(
        stderr, "client_event_thread_reply_received\t%s\t%s\t%s\t%s\n",
        team_uuid, thread_uuid, user_uuid, reply_body);
    return 0;
}

int client_event_team_created(
    char const *team_uuid, char const *team_name, char const *team_description)
{
    fprintf(
        stderr, "client_event_team_created\t%s\t%s\t%s\n", team_uuid,
        team_name, team_description);
    return 0;
}

int client_event_channel_created(
    char const *channel_uuid, char const *channel_name,
    char const *channel_description)
{
    fprintf(
        stderr, "client_event_channel_created\t%s\t%s\t%s\n", channel_uuid,
        channel_name, channel_description);
    return 0;
}

int client_event_thread_created(
    char const *thread_uuid, char const *user_uuid, time_t thread_timestamp,
    char const *thread_title, char const *thread_body)
{
    fprintf(
        stderr, "client_event_thread_created\t%s\t%s\t%ld\t%s\t%s\n",
        thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body);
    return 0;
}

int client_print_users(
    char const *user_uuid, char const *user_name, int user_status)
{
    fprintf(
        stderr, "client_print_users\t%s\t%s\t%d\n", user_uuid, user_name,
        user_status);
    return 0;
}

int client_print_teams(
    char const *team_uuid, char const *team_name, char const *team_description)
{
    fprintf(
        stderr, "client_print_teams\t%s\t%s\t%s\n", team_uuid, team_name,
        team_description);
    return 0;
}

int client_team_print_channels(
    char const *channel_uuid, char const *channel_name,
    char const *channel_description)
{
    fprintf(
        stderr, "client_team_print_channels\t%s\t%s\t%s\n", channel_uuid,
        channel_name, channel_description);
    return 0;
}

int client_channel_print_threads(
    char const *thread_uuid, char const *user_uuid, time_t thread_timestamp,
    char const *thread_title, char const *thread_body)
{
    fprintf(
        stderr, "client_channel_print_threads\t%s\t%s\t%ld\t%s\t%s\n",
        thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body);
    return 0;
}

int client_thread_print_replies(
    char const *thread_uuid, char const *user_uuid, time_t reply_timestamp,
    char const *reply_body)
{
    fprintf(
        stderr, "client_thread_print_replies\t%s\t%s\t%ld\t%s\n", thread_uuid,
        user_uuid, reply_timestamp, reply_body);
    return 0;
}

int client_private_message_print_messages(
    char const *sender_uuid, time_t message_timestamp,
    char const *message_body)
{
    fprintf(
        stderr, "client_private_message_print_messages\t%s\t%ld\t%s\n",
        sender_uuid, message_timestamp, message_body);
    return 0;
}

int client_error_unknown_team(char const *team_uuid)
{
    fprintf(stderr, "client_error_unknown_team\t%s\n", team_uuid);
    return 0;
}

int client_error_unknown_channel(char const *channel_uuid)
{
    fprintf(stderr, "client_error_unknown_channel\t%s\n", channel_uuid);
    return 0;
}

int client_error_unknown_thread(char const *thread_uuid)
{
    fprintf(stderr, "client_error_unknown_thread\t%s\n", thread_uuid);
    return 0;
}

int client_error_unknown_user(char const *user_uuid)
{
    fprintf(stderr, "client_error_unknown_user\t%s\n", user_uuid);
    return 0;
}

int client_error_unauthorized(void)
{
    fprintf(stderr, "client_error_unauthorized\n");
    return 0;
}

int client_error_already_exist(void)
{
    fprintf(stderr, "client_error_already_exist\n");
    return 0;
}

int client_print_user(
    char const *user_uuid, char const *user_name, int user_status)
{
    fprintf(
        stderr, "client_print_user\t%s\t%s\t%d\n", user_uuid, user_name,
        user_status);
    return 0;
}

int client_print_team(
    char const *team_uuid, char const *team_name, char const *team_description)
{
    fprintf(
        stderr, "client_print_team\t%s\t%s\t%s\n", team_uuid, team_name,
        team_description);
    return 0;
}

int client_print_channel(
    char const *channel_uuid, char const *channel_name,
    char const *channel_description)
{
    fprintf(
        stderr, "client_print_channel\t%s\t%s\t%s\n", channel_uuid,
        channel_name, channel_description);
    return 0;
}

int client_print_thread(
    char const *thread_uuid, char const *user_uuid, time_t thread_timestamp,
    char const *thread_title, char const *thread_body)
{
    fprintf(
        stderr, "client_print_thread\t%s\t%s\t%ld\t%s\t%s\n", thread_uuid,
        user_uuid, thread_timestamp, thread_title, thread_body);
    return 0;
}

int client_print_team_created(
    char const *team_uuid, char const *team_name, char const *team_description)
{
    fprintf(
        stderr, "client_print_team_created\t%s\t%s\t%s\n", team_uuid, team_name,
        team_description);
    return 0;
}

int client_print_channel_created(
    char const *channel_uuid, char const *channel_name,
    char const *channel_description)
{
    {
        fprintf(
            stderr, "client_print_channel_created\t%s\t%s\t%s\n", channel_uuid, channel_name,
            channel_description);
        return 0;
    }
}

int client_print_thread_created(
    char const *thread_uuid, char const *user_uuid, time_t thread_timestamp,
    char const *thread_title, char const *thread_body)
{
    fprintf(
        stderr, "client_print_thread_created\t%s\t%s\t%ld\t%s\t%s\n",
        thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body);
    return 0;
}

int client_print_reply_created(
    char const *thread_uuid, char const *user_uuid, time_t reply_timestamp,
    char const *reply_body)
{
    fprintf(
        stderr, "client_print_reply_created\t%s\t%s\t%ld\t%s\n", thread_uuid,
        user_uuid, reply_timestamp, reply_body);
    return 0;
}

int client_print_subscribed(char const *user_uuid, char const *team_uuid)
{
    fprintf(stderr, "client_print_subscribed\t%s\t%s\n", user_uuid, team_uuid);
    return 0;
}

int client_print_unsubscribed(char const *user_uuid, char const *team_uuid)
{
    fprintf(
        stderr, "client_print_unsubscribed\t%s\t%s\n", user_uuid, team_uuid);
    return 0;
}
