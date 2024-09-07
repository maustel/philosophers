/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:20:11 by maustel           #+#    #+#             */
/*   Updated: 2024/09/07 10:41:38 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define COUNT_MAX 1000

pthread_mutex_t mutex;
volatile int count = 0;

void* increment_counter(void* arg)
{
    int iterations = *(int*)arg;
	int i = 0;

    while (i < iterations) {
        pthread_mutex_lock(&mutex);
        count++;
		// printf("count1: %d\n", count);
        pthread_mutex_unlock(&mutex);
        // Simulate some work
        usleep(rand() % 1000);
		i++;
    }

    return NULL;
}


int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int iterations_per_thread = COUNT_MAX / NUM_THREADS;
	int i = 0;

    printf("Creating %d threads...\n", NUM_THREADS);
	pthread_mutex_init(&mutex, NULL);
	/*create and start all threads*/
    while (i < NUM_THREADS)
	{
        thread_args[i] = iterations_per_thread;
		printf("thread %d started\n", i);
        if (pthread_create(&threads[i], NULL, increment_counter, &thread_args[i]))
			exit(1);
		/*wait for each thread to complete before creating a new one
		--> only one thread at a time. WRONG!!*/
        // if (pthread_join(threads[i], NULL))
		// 	exit(2);
		i++;
    }
    printf("Waiting for threads to complete...\n");
	/*wait for all threads to complete --> threads are working parallel */
	i = 0;
    while (i < NUM_THREADS) {
		printf("thread %d finished\n", i);
        pthread_join(threads[i], NULL);
		i++;
    }
    printf("Final count: %d\n", count);

    return 0;
}

/*
pthread_create(&threads[i], NULL, increment_counter, &thread_args[i]);
&threads[i] will receive a valid thread ID
NULL: specifies attributes for the thread. Null means default attributes
increment_counter: function pointer to the thread function we want to execute
&thread_args[i]: passes an argument to our thread function
*/