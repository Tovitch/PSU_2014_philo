/*
** philo.c for philo in /home/kruszk_t/rendu/PSU_2014_philo
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Tue Jun 23 10:44:19 2015 Tony Kruszkewycz
** Last update Tue Jun 23 10:47:15 2015 Tony Kruszkewycz
*/

#include	<stdio.h>
#include	<pthread.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"philo.h"

void		p_eat(t_philo *p)
{
  pthread_mutex_trylock(&p->m_left_stick);
  pthread_mutex_lock(p->m_right_stick);
  p->state = EAT;
  p->rice -= QTY_EATEN;
  printf("Philosophe %d is eating (%d rice remaning)\n", p->id, p->rice);
  usleep(EAT_TIME);
  p_rest(p);
}

void		p_rest(t_philo *p)
{
  pthread_mutex_unlock(&p->m_left_stick);
  pthread_mutex_unlock(p->m_right_stick);
  printf("Philosophe %d is resting\n", p->id);
  p->state = REST;
  usleep(REST_TIME);
  return ;
}

void		p_think(t_philo *p)
{
  pthread_mutex_lock(&p->m_left_stick);
  printf("Philosophe %d is thinking\n", p->id);
  p->state = THINK;
  p_eat(p);
}

void		*finished(t_philo *p)
{
  printf("Philosophe %d finish\n", p->id);
  return (0);
}

void		*run_philo(void *arg)
{
  int		ret;
  t_philo	*p;

  p = (t_philo*)arg;
  while ((ret = rand() % 3) >= 0)
    {
      if (ret == EAT)
	{
	  while (p->prev->state == THINK || p->prev->state == EAT ||
		 p->next->state == THINK || p->next->state == EAT)
	    p_rest(p);
	  p_eat(p);
	}
      else if (ret == REST && p->state == EAT)
	p_rest(p);
      else if (ret == THINK)
	{
	  while (p->prev->state == THINK || p->next->state == THINK)
	    p_rest(p);
	  p_think(p);
	}
      if (p->rice <= 0)
	return (finished(p));
    }
  return (NULL);
}
