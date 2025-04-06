#include "includes/minitalk_bonus.h"

unsigned char g_byte;

void process_bit(int bit, int pid_client)
{
    static int bit_count = 0;
    static unsigned char buffer[10240] = {0};
    static int byte_count = 0;
    static int total_received = 0;

    g_byte <<= 1;
    g_byte += bit;
    bit_count++;
    if (bit_count == 8)
    {
        buffer[byte_count++] = g_byte;
        total_received++;
        if (g_byte == '\0')
        {
            write(1, buffer, byte_count - 1);
            write(1, "\n", 1);
            kill(pid_client, SIGUSR2);
            
            byte_count = 0;
            total_received = 0;
        }
        else if (byte_count >= 10230)
        {
            write(1, buffer, byte_count);
            byte_count = 0;
        }
        g_byte = 0;
        bit_count = 0;
        if (total_received % 100 == 0 && total_received > 0)
            ft_printf("\033[0;94mReceived %d bytes...\033[0m\n", total_received);
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

int main(void)
{
    struct sigaction act;

    g_byte = 0;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    ft_printf("\033[1;92mBonus Server started!\033[0m\n");
    ft_printf("\033[1;94m--> Server PID: \033[1;93m%d\033[0m\n", getpid());
    ft_printf("\033[1;90mWaiting for messages (Unicode supported)...\033[0m\n");
    while (1)
        pause();
    
    return (0);
}
