no_negative_rules:
    spin -run -bfs -ltl no_negative_rules task.pml
no_deadlocks:
    spin -run -bfs -ltl no_deadlock task.pml
pan.c:
    spin -a $<
clean:
    rm -f pan* task.pml.trail *.tmp