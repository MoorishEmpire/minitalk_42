#include "includes/minitalk.h"

unsigned char g_byte;

void process_bit(int bit, int pid_client)
{
    static int bit_count = 0;
    static char message[10000] = {0};
    static int char_count = 0;

    g_byte <<= 1;
    g_byte += bit;
    bit_count++;
    if (bit_count == 8)
    {
        if (g_byte != '\0')
        {
            message[char_count++] = g_byte;
            if (char_count >= 9990)
            {
                write(1, message, char_count);
                char_count = 0;
            }
        }
        else
        {
            message[char_count] = '\0';
            ft_printf("%s\n", message);
            char_count = 0;
            kill(pid_client, SIGUSR2);
        }
        g_byte = 0;
        bit_count = 0;
    }
    kill(pid_client, SIGUSR1);
}

void handle_signal(int signum, siginfo_t *info, void *context)
{
    (void)context;
    
    if (!info->si_pid)
        return;
    if (signum == SIGUSR1)
        process_bit(1, info->si_pid);
    else if (signum == SIGUSR2)
        process_bit(0, info->si_pid);
}

/* Main function */
int main(void)
{
    struct sigaction act;

    g_byte = 0;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    ft_printf("Server started!\n");
    ft_printf("--> Server PID: %d\n", getpid());
    ft_printf("Waiting for messages...\n");
    while (1)
        pause();
    
    return (0);
}
