# Philosophers

The philosophers project is a parallel computing project.
</br>
A classic computer science project invented by Dijkstra. (Grade 125/100)

Main concepts used : thread and mutexes for mandatory part, semaphoras and processes for bonus.
 
## Rules
 
<ul>
<li> A number of philosophers sit at a round table where a large bowl of spaghetti lies in the center.</li>
<li> Each philosopher has a routine of eating, sleeping and thinking that repeats.</li>
<li> There are as many forks as there are philosophers on the table. </li>
<li> Each philosopher needs the two closest forks to eat.</li>
<li> Philosophers can’t speak with each other.</li>
<li> Every philosopher needs to eat and should never starve.</li>
<li> Unless the conditions do not allow it. No philosophers should die.</li>
</ul>
 
### Available parameters:
 
<ul>
<li> number_of_philosophers: The number of philosophers and also the number of forks.</li>
<li> time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.</li>
<li> time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks. </li>
<li> time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.</li>
<li> number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.</li>
</ul>
 
In case of invalid arguments, the program must display an appropriate error message.
Errors include for example: some arguments are not integers, some arguments are
bigger than an integer and/or zero or negative values are present in places it does not make sense.
 
# Usage
 
Use `make` to compile the program.
 
Add the desired parameters:
 
```
./philo <parameters>
```

# Output

Program outputs actions by every individual philosopher including its index and timestamp from the begining of the action. It looks somewhat like this

| timestamp in ms | index | action |
| :------------ |:---------------:| :----- |

```
0 ms: 1 has taken a fork
0 ms: 1 has taken a fork
0 ms: 1 is eating
0 ms: 3 has taken a fork
0 ms: 3 has taken a fork
0 ms: 3 is eating
0 ms: 5 has taken a fork
200 ms: 3 is sleeping
200 ms: 1 is sleeping
200 ms: 4 has taken a fork
200 ms: 2 has taken a fork
200 ms: 2 has taken a fork
200 ms: 2 is eating
200 ms: 5 has taken a fork

```

##
### 🌟 A Quick Note
I hope this repository proves useful to you, whether you're working on the Push Swap project yourself, exploring my profile, or just curious about the 42 curriculum.
<br />Feel free to dive in, learn, and adapt the code as you see fit.
<br />Best of luck on your coding journey! 🚀
