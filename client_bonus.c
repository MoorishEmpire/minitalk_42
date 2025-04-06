#include "includes/minitalk_bonus.h"

int g_sync_bit;

/* Signal handler for client: 
 * SIGUSR1: Acknowledgment from server (ready for next bit or byte ack)
 * SIGUSR2: Message fully received confirmation from server
 */
void handle_signal(int signum)
{
    if (signum == SIGUSR2)
    {
        ft_printf("\n\033[0;92mMessage successfully received and acknowledged by server!\033[0m\n");
        exit(0);
    }
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
            ft_printf("\033[0;91mError: Invalid or null PID: %d\033[0m\n", pid);
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
    ft_printf("\033[0;94mSending message to server (PID: %d)...\033[0m\n", pid);
    while (message[i])
    {
        send_byte((unsigned char)message[i], pid);
        i++;
        if (i % 10 == 0)
            ft_printf("\033[0;94m%d bytes sent...\033[0m\n", i);
    }
    
    send_byte('\0', pid);
    ft_printf("\033[0;94mMessage sent. Waiting for final acknowledgment...\033[0m\n");
}

int main(int argc, char **argv)
{
    int pid_server;
    char *message;

    if (argc != 3)
    {
        ft_printf("\033[0;95mError: Invalid arguments\n");
        ft_printf("Usage: ./client_bonus [SERVER_PID] [MESSAGE]\033[0m\n");
        return (1);
    }
    signal(SIGUSR1, &handle_signal);
    signal(SIGUSR2, &handle_signal);
    pid_server = ft_atoi(argv[1]);
    if (!pid_server)
    {
        ft_printf("\033[0;91mError: Invalid PID!\033[0m\n");
        exit(1);
    }
    message = (char *)malloc(sizeof(char) * (ft_strlen(argv[2]) + 1));
    send_message(message, pid_server);
    free(message);
    while (1)
        pause();
    
    return (0);
}
