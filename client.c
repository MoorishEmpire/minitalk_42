#include "includes/minitalk.h"

int g_sync_bit;

/* Signal handler for client: 
 * SIGUSR1: Acknowledgment from server (ready for next bit)
 * SIGUSR2: Message fully received confirmation from server
 */
void handle_signal(int signum)
{
    if (signum == SIGUSR2)
        exit(0);
    else if (signum == SIGUSR1)
        g_sync_bit = 1;
}

void send_byte(unsigned char byte, int pid)
{
    int i;
    int bit;

    i = 0;
    while (i < 8)
    {
        if (kill(pid, 0) < 0)
        {
            ft_printf("Error: Invalid or null PID: %d\n", pid);
            exit(1);
        }
        g_sync_bit = 0;
        bit = byte & 128;
        byte <<= 1;
        if (bit == 128)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        while (g_sync_bit != 1)
            usleep(50);
        i++;
    }
}

void send_message(char *message, int pid)
{
    int i;

    i = 0;
    ft_printf("Sending message to server (PID: %d)...\n", pid);
    while (message[i])
    {
        send_byte(message[i], pid);
        i++;
    }
    send_byte('\0', pid);
    ft_printf("Message sent. Waiting for confirmation...\n");
}

int main(int argc, char **argv)
{
    int pid_server;
    char *message;

    if (argc != 3)
    {
        ft_printf("Error: Invalid arguments\n");
        ft_printf("Usage: ./client [SERVER_PID] [MESSAGE]\n");
        return (1);
    }
    signal(SIGUSR1, &handle_signal);
    signal(SIGUSR2, &handle_signal);
    pid_server = ft_atoi(argv[1]);
    if (!pid_server)
    {
        ft_printf("Error: Invalid PID!\n");
        exit(1);
    }
    message = ft_strdup(argv[2]);
    send_message(message, pid_server);
    free(message);
    while (1)
        pause();
    return (0);
}
