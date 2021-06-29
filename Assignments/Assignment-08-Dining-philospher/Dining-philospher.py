# -*- coding: utf-8 -*-
"""Untitled2.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1VQ4YN4fK5mze5aOaFi82N_PLw1-u7OAQ

*italicized text*
## Dining Philospher

Dining Philosophers Problem



Problems:
 The problem faced on the dinning table is that when philosopher p1 take fork from left side and then right side then its oky because in this time only philosopher want to take meal but the problem become when more then philosopher want to take meals at the same time . For example philosopher p took fork f1 from left side and then took f2 from right side in this moment philosopher p2 come and want to take meal but there is no spoon for him .in this way  the Race Condition is occoured.
Solution:
 We are going to solve this problem using binary semaphore. Philosopher has must have two work
think and eat. We used Array of semaphore number of fork(spoon). [S0,S1,S2,S3,S4]. In this way we will remove the race condition.
Sudo Code:
Void philosopher(void)
{
	while(True)
	{
		Thinking();
		wait(table_fork(Si)
		wait(table_fork(S(i+1)mod N)
		
		Eat() ; //critical section
		
		signal(put_fork(i));
		signal(put_fork(i+1)mod N);
	}
}

Case 1:
if p0 has come to eat:
	then it will take s0, s1
	In such moment if p1 has come to eat
	 then it will take s1,s2 but s1 has already down then p1 have to wait for the S1

Case 2 : 
if p0 has come to eat : 
	then it it will take s0,s1 ( in wait call s0 , s1 become down until finish the task
	in such moment if p2 has come to eat
	then it will take s2 and s3 .He can take it because s2 and s3 already up!

Calling Table
Philosopher
Semaphore s0
Semaphore s1
P0
S0
S1
p1
S1
S2
p2
S2
S3
p3
S3
S4
p4
S4
S0

Is There any Deadlock in Dining philosopher?
Yes , There is deadlock if all the philosopher take only left spoon and they are not able to get right spoon due to high priority processes like if all the s0,s1,s2,s3 , s4 all semaphore become down then no one can enter in the critical section (eat()) that would become deadlock state.
"""

import threading
import random
import time

#inheriting threading class in Thread module
class Philosopher(threading.Thread):
    running = True  #used to check if everyone is finished eating

 #Since the subclass overrides the constructor, it must make sure to invoke the base class constructor (Thread.__init__()) before doing anything else to the thread.
    def __init__(self, index, forkOnLeft, forkOnRight):
        threading.Thread.__init__(self)
        self.index = index
        self.forkOnLeft = forkOnLeft
        self.forkOnRight = forkOnRight

    def run(self):
        while(self.running):
            # Philosopher is thinking (but really is sleeping).
            time.sleep(30)
            print ('Philosopher %s is hungry.' % self.index)
            self.dine()

    def dine(self):
        # if both the semaphores(forks) are free, then philosopher will eat
        fork1, fork2 = self.forkOnLeft, self.forkOnRight
        while self.running:
            fork1.acquire() # wait operation on left fork
            locked = fork2.acquire(False) 
            if locked: break #if right fork is not available leave left fork
            fork1.release()
            print ('Philosopher %s swaps forks.' % self.index)
            fork1, fork2 = fork2, fork1
        else:
            return
        self.dining()
        #release both the fork after dining
        fork2.release()
        fork1.release()
 
    def dining(self):			
        print ('Philosopher %s starts eating. '% self.index)
        time.sleep(30)
        print ('Philosopher %s finishes eating and leaves to think.' % self.index)

def main():
    print("Main called")
    forks = [threading.Semaphore() for n in range(5)] #initialising array of semaphore i.e forks

    #here (i+1)%5 is used to get right and left forks circularly between 1-5
    philosophers= [Philosopher(i, forks[i%5], forks[(i+1)%5])
            for i in range(5)]

    Philosopher.running = True
    for p in philosophers: p.start()
    time.sleep(100)
    Philosopher.running = False
    print ("Now we're finishing.")

main()
