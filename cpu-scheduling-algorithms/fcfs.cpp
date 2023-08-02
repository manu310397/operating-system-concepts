// Simple implementation of First Come First Serve CPU Scheduling Algorithm
#include<iostream>
#define MAX_PROCESS 10

using namespace std;

class process {
    public:
        int process_id;
        int arrival_time;
        int burst_time;
        int schedule_time;
        int completion_time;
        int turn_around_time;
        int waiting_time;

        void input_process(int);

        int get_arrival_time() {
            return arrival_time;
        }
};

void process::input_process(int id) {
    process_id = id + 1;

    cout << "\nEnter Burst Time For Process " << process_id << ": ";
    cin >> burst_time;

    cout << "Enter Arrival Time For Process " << process_id << ": ";
    cin >> arrival_time;
}

void sort_based_on_at(process *p, int n) {
    process temp;

    for (int i=0; i<n; ++i) {
        for(int j=i+1; i<n; ++i) {
            if(p[i].get_arrival_time() > p[j].get_arrival_time()) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calc_completion_time(process *p, int n) {
    p[0].schedule_time = 0;

    for(int i=1; i<n; ++i)
        p[i].schedule_time = p[i-1].burst_time + p[i-1].schedule_time;

    for(int i=0; i<n; i++) 
        p[i].completion_time = p[i].burst_time + p[i].schedule_time;
}

void calc_wait_tat(process *p, int n) {
    for(int i=1; i<n; ++i) {
        if(p[i].schedule_time<p[i].arrival_time)
            p[i].schedule_time=p[i].arrival_time;
    }

    for(int i=0; i<n; ++i)
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;

    for(int i=0; i<n; ++i)
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
}

void average(process *p, int n) {
    float avg_wt=0,avg_tat=0;
  
    for(int i=0;i<n;++i) {
        avg_wt += (float)p[i].waiting_time;
        avg_tat += (float)p[i].turn_around_time;
    }

    avg_wt /= n;
    avg_tat /= n;
  
    cout<<"\n\nAVERAGE WAITING TIME : "<<avg_wt;
    cout<<"\nAVERAGE TURN AROUND TIME : "<<avg_tat << "\n";
}

void display(process *p, int n) {
    cout<<"PID \t"<<" AT \t"<<" BT \t"<<" ST \t"<<" CT \t"<<" TAT \t"<< " WT \t"<<"\n";
        for (int i=0;i<n;++i) {
            cout<<"\n"<<p[i].process_id<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].schedule_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turn_around_time<<"\t"<<p[i].waiting_time;
        }

        average(p,n);
}

int main() {
    process p[MAX_PROCESS];

    int i, number_of_process;

    cout << "\nEnter Numbre Of Processes : ";
    cin >> number_of_process;

    for(i=0; i<number_of_process; ++i)
        p[i].input_process(i);

    calc_completion_time(p, number_of_process);

    sort_based_on_at(p, number_of_process);

    calc_wait_tat(p, number_of_process);

    display(p, number_of_process);
}