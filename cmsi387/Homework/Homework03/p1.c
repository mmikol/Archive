
//Code adapted from https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define HUNGRY 0
#define EATING 1
#define THINKING 2
#define LEFT (name + 4) % N
#define RIGHT (name + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

void test(int name)
{
    if (state[name] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[name] = EATING;

        sleep(2);

        printf("Philosopher %d takes fork %d and %d\n",
               name + 1, LEFT + 1, name + 1);

        printf("Philosopher %d is Eating\n", name + 1);

        sem_post(&S[name]);
    }
}
void take_fork(int name)
{

    sem_wait(&mutex);

    state[name] = HUNGRY;

    printf("Philosopher %d is Hungry\n", name + 1);

    test(name);

    sem_post(&mutex);

    sem_wait(&S[name]);

    sleep(1);
}

void put_fork(int name)
{

    sem_wait(&mutex);

    state[name] = THINKING;

    printf("Philosopher %d putting fork %d and %d down\n",
           name + 1, LEFT + 1, name + 1);
    printf("Philosopher %d is thinking\n", name + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void *philospher(void *num)
{

    while (1)
    {

        int i = num;

        sleep(1);

        take_fork(i);

        put_fork(i);
    }
}

int main()
{

    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL,
                       philospher, &phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)

        pthread_join(thread_id[i], NULL);
}
