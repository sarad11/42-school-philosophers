/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saradominguez <saradominguez@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:43:04 by saradomingu       #+#    #+#             */
/*   Updated: 2025/05/17 21:49:11 by saradomingu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


    /* ---Enunciado ejercicio 1:
Escribe un programa en C que mida el tiempo que tarda en realizar una pausa de 1 segundo utilizando usleep. Debe mostrar en pantalla el tiempo transcurrido en microsegundos usando printf:---
int main(void)
{
    struct timeval  start;
    struct timeval  end;
    long long   elapsed;
    
    gettimeofday(&start, NULL);
    usleep(1000000);
    gettimeofday(&end, NULL);
    elapsed = (end.tv_sec -start.tv_sec) * 1000000;
    elapsed += (end.tv_usec - start.tv_usec);
    printf("tiempo transcurrido: %lld microsegundos\n", elapsed);
    elapsed /= 1000;
    printf("tiempo transcurrido: %lld milisegundos\n", elapsed); 
    return (0);
}*/
    
    /*Ejercicio 2 (combinado)
Título: “Medición de inicialización dinámica”
Enunciado completo:
Modifica el programa del Ejercicio 1 para que, además de medir el tiempo, haga lo siguiente:
    1. Reserve dinámicamente memoria para un array de 1 millón de caracteres (char) usando malloc.
    2. Inicialice todos los caracteres a 'Z' utilizando memset.
    3. Termine la cadena con '\0'.
    4. Mida el tiempo total que tarda en ejecutar desde la reserva hasta la inicialización.
    5. Imprima los primeros 50 caracteres como muestra.6. Libere la memoria con free.

int main(void)
{
    struct timeval  start;
    struct timeval  end;
    long long   enabled;
    char    *array;

    gettimeofday(&start, NULL);
    array = (char *)malloc(1000000 * sizeof(char));
    gettimeofday(&end, NULL);
    enabled = (end.tv_sec - start.tv_sec) * 1000000;
    enabled += (end.tv_usec - start.tv_usec);
    printf("Tiempo transcurrido: %lld microsegundos\n", enabled);
    enabled /= 1000;
    printf("Tiempo transcurrido: %lld milisegundos\n", enabled);
    memset(array, 'Z', 1000000);
    array[1000000 - 1] = '\0';
    free(array);
    return (0);
}*/

    /* Ejercicio 3 – Creación y unión de hilos
Enunciado:
Escribe un programa que:
    1. Cree un hilo con pthread_create.
    2. El hilo debe ejecutar una función que imprima un mensaje (por ejemplo, "Hola desde el hilo").
    3. El hilo debe usar usleep para dormir 1 segundo antes de imprimir.
    4. El hilo debe terminar y el hilo principal debe esperar a que termine usando pthread_join.
    5. El hilo principal imprime "Hilo terminado" después de que el hilo hijo haya acabado.


static void    *usleep_and_print()
{
    usleep(1000000);
    printf("Hola desde el hilo\n");
    return (NULL);
}
int main(void)
{
    pthread_t   hilo;
    if(pthread_create(&hilo, NULL, usleep_and_print, NULL) != 0)
    {
        write(2, "Error al crear el hilo\n", 23);
        return (1);
    }
    if(pthread_join(hilo, NULL) != 0)
    {
        write(2, "Error al esperar el hilo\n", 25);
        return (1);
    }
    printf("Hilo terminado\n");
    return (0);
}*/
/*Ejercicio 4 – Crear varios hilos que imprimen en paralelo
🧾 Enunciado:
    1. Crea 5 hilos (pthread_t).
    2. Cada hilo debe dormir 1 segundo (usleep) y luego imprimir: Hola desde el hilo X
    Donde X es su número (del 1 al 5).
    3. Usa pthread_create en un bucle.
    4. Usa pthread_join en otro bucle para esperar a que todos terminen.
    5. Al final, imprime desde el hilo principal: Todos los hilos han terminado

void    *ft_usleep_and_print(void *arg)
{
    int argument;

    argument = *(int *)arg;
    usleep(1000000);
    printf("Hola desde el hilo %d\n", argument);
    return (NULL);
}
int main(void)
{
    pthread_t   threads[5];
    int ids[5];
    int i;

    i = 0;
    while (i < 5)
    {
        ids[i] = i + 1;
        if(pthread_create(&threads[i], NULL, ft_usleep_and_print, &ids[i]) != 0)
        {
            write(2, "Error al crear el hilo\n", 23);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < 5)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            write(2, "Error al esperar al hilo\n", 25);
            return (1);
        }
        i++;
    }
    return (0);
}*/
/*Ejercicio 5:
Sincroniza la impresión de los hilos usando un pthread_mutex_t.
    1. Crea 5 hilos como en el ejercicio anterior.
    2. Cada hilo debe dormir 1 segundo (usleep(1000000)),
    3. Luego imprimir "Hola desde el hilo X\n" donde X es su número.
    4. Usa un mutex para proteger la llamada a printf para que ningún hilo interrumpa a otro mientras imprime.
    5. Al final, el hilo principal debe esperar a que terminen todos los hilos.

void    *usleep_and_print(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    usleep(1000000);
    pthread_mutex_lock(data->mutex);
    printf("Hola desde el hilo %d\n", data->id);
    pthread_mutex_unlock(data->mutex);
    return (NULL);
}
int main(void)
{
    pthread_t threads[5];
    pthread_mutex_t mutex;
    t_thread_data   thread_data[5];
    int i;

    i = 0;
    pthread_mutex_init(&mutex, NULL);
    while (i < 5)
    {
        thread_data[i].id = i + 1;
        thread_data[i].mutex = &mutex;
        if(pthread_create(&threads[i], NULL, usleep_and_print, &thread_data[i]) != 0)
        {
            write(2, "Error al crear el hilo\n", 23);
            pthread_mutex_destroy(&mutex);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < 5)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            write(2, "Error al esperar al hilo", 25);
            pthread_mutex_destroy(&mutex);
            return (1);
        }
        i++;
    }
    pthread_mutex_destroy(&mutex);
    return (0);
}*/
/*Ejercicio 6 – Contador compartido

    1. Crea 5 hilos que cada uno incremente una variable compartida 100.000 veces.
    2. El valor final del contador debe imprimirse y debe ser exactamente 500.000 (5 hilos × 100.000).
    3. Usa un mutex para proteger la variable compartida.

void    *print(void  *arg)
{
    t_thread_data   *data = (t_thread_data *)arg;
    int i;

    i = 0;    
    pthread_mutex_lock(data->mutex);
    printf("Hola hilo %i\n", data->id);
    while (i < 100000)
    {
        (*(data->counter))++;
        i++;
    }
    printf("El valor de la variable compartida es %lld\n", *(data->counter));
    printf("Hilo %d terminado\n\n", data->id);
    pthread_mutex_unlock(data->mutex);
    return (NULL);
}
int main(void)
{
    t_thread_data thread_data[5];
    pthread_t   threads[5];
    pthread_mutex_t mutex;
    int i;
    long long counter;

    i = 0;
    counter = 0;
    pthread_mutex_init(&mutex, NULL);
    while (i < 5)
    {
        thread_data[i].id = i + 1;
        thread_data[i].mutex = &mutex;
        thread_data[i].counter = &counter;
        if(pthread_create(&threads[i], NULL, print, &thread_data[i]))
        {
            write(2, "Error al crear el hilo\n", 23);
            pthread_mutex_destroy(&mutex);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < 5)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            write(2, "Error al esperar el hilo\n", 25);
            pthread_mutex_destroy(&mutex);
            return (1);
        }
        i++;
    }
    pthread_mutex_destroy(&mutex);
    return (0);
}*/