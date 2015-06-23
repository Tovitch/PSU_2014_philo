/*
** philo.h for philo in /home/kruszk_t/rendu/PSU_2014_philo
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Jun 22 15:00:28 2015 Tony Kruszkewycz
** Last update Tue Jun 23 11:08:15 2015 Tony Kruszkewycz
*/

#ifndef PHILO_H_
# define PHILO_H_

# define		MAX_PHILO 20000
# define		MAX_RICE 50
# define		QTY_EATEN 5

/*
** usleep times
*/

# define		EAT_TIME 500000
# define		REST_TIME EAT_TIME

enum
  {
    LEFT, RIGHT
  };

typedef enum
  {
    EAT = 0, REST, THINK
  }			e_state;

typedef struct		s_philo
{
  int			id;
  int			rice;
  e_state		state;
  pthread_mutex_t	m_left_stick;
  pthread_mutex_t	*m_right_stick;
  struct s_philo	*prev;
  struct s_philo	*next;
}			t_philo;

void			*run_philo(void *arg);
void			p_eat(t_philo *p);
void			p_rest(t_philo *p);
void			p_think(t_philo *p);

#endif /* !PHILO_H_ */
