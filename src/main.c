/*
** main.c for philo in /home/kruszk_t/rendu/PSU_2014_philo
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Jun 22 14:58:39 2015 Tony Kruszkewycz
** Last update Tue Jun 23 10:49:41 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<pthread.h>
#include	<time.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"philo.h"

static t_philo	*add_philo(int i)
{
  t_philo	*new;

  if (!(new = malloc(sizeof(t_philo))))
    return (NULL);
  new->id = i;
  new->rice = MAX_RICE;
  new->state = REST;
  pthread_mutex_init(&new->m_left_stick, NULL);
  return (new);
}

static t_philo	*philo_init()
{
  t_philo	*first;
  t_philo	*philo;
  int		i;

  i = 1;
  if (!(philo = malloc(sizeof(t_philo))))
    return (NULL);
  first = philo;
  philo->id = i;
  philo->rice = MAX_RICE;
  philo->state = REST;
  pthread_mutex_init(&philo->m_left_stick, NULL);
  while (i < MAX_PHILO)
    {
      philo->next = add_philo(i + 1);
      philo->m_right_stick = &philo->next->m_left_stick;
      philo->next->prev = philo;
      philo = philo->next;
      ++i;
    }
  philo->next = first;
  philo->m_right_stick = &first->m_left_stick;
  first->prev = philo;
  return (philo);
}

static void	destroy_philo(t_philo *p)
{
  t_philo	*tmp;
  int		i;

  i = 0;
  while (i < MAX_PHILO)
    {
      tmp = p->next;
      free(p);
      p = tmp;
      ++i;
    }
}

int		main()
{
  t_philo	*philo;
  pthread_t	*th;
  int		i;

  srand(time(NULL));
  if (!(philo = philo_init()))
    return (EXIT_FAILURE);
  if (!(th = malloc(sizeof(pthread_t) * MAX_PHILO)))
    return (EXIT_FAILURE);
  i = 0;
  while (i < MAX_PHILO)
    {
      pthread_create(&(th[i]), NULL, run_philo, philo);
      philo = philo->next;
      ++i;
    }
  while (i > 0)
    {
      pthread_join(th[i-1], NULL);
      --i;
    }
  destroy_philo(philo);
  free(th);
  return (EXIT_SUCCESS);
}
