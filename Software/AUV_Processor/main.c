typedef struct {
    signed char state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task_t;


int main() {
    
    const unsigned long R1_period = 0;          //period for each state to change
    const unsigned long Mov_period = 0;
    const unsigned long Sens_period = 0;
    const unsigned long Fl_period = 0;

    const unsigned long GCD = 50;                //lowest number that divides evenly into all periods

    unsigned char i = 0;

    static task_t     task1, task2, task3, task4;
    task_t *tasks[] = { &task1, &task2, &task3, &task4 };

    const unsigned short numTasks = sizeof(tasks) / sizeof(task_t*);

    task1.state = -1;
    task1.period = R1_period;
    task1.elapsedTime = R1_period;
    task1.TickFct = &R1_Tick;

    task2.state = -1;
    task2.period = Sens_period;
    task2.elapsedTime = Sens_period;
    task2.TickFct = &Sens_Tick;

    task3.state = -1;
    task3.period = Mov_period;
    task3.elapsedTime = Mov_period;
    task3.TickFct = &Mov_Tick;

    task4.state = -1;
    task4.period = Fl_period;
    task4.elapsedTime = Fl_period;
    task4.TickFct = &Fl_Tick;

    Timer t;            //insert timer here
    t.start();
    
    while (1) {
        for (i = 0; i < numTasks; ++i) {
            if (tasks[i]->elapsedTime == tasks[i]->period) {            
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += GCD;           
        }
        while (!TimerFlag);
        TimerFlag = 0;
    }
    return 0;
}