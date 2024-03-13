#include<bits/stdc++.h>
using namespace std;

class process
{
    public:
    int pid,at,bt,ct,tat,wt,rt,rbt;
    process(){}
    process(int p,int a,int b):pid(p),at(a),bt(b),rbt(b){}
};

class SRTF{
    string chart;
    public:
    void findcomptime(process p[],int n,multimap<int,int> &m1,multimap<int,int> &m2)
    {
        int t=0,f=0,tbt=0;
        for(int i=0;i<n;i++)
        tbt+=p[i].bt;
        string s;
        multimap<int,int> :: reverse_iterator it;
        multimap<int,int> :: iterator itr;
        it=m2.rbegin();
        while(t<=tbt)
        {
            int min_bt,min_pid,flag=0;
            min_bt=it->first;
            min_pid=it->second;
            for(itr=m1.begin();itr!=m1.end();itr++)
            {
                if(itr->first<=t)
                {
                    if(p[itr->second-1].rbt!=0 && min_bt>=p[itr->second-1].rbt)
                    {
                        flag=1;
                        min_bt=p[itr->second-1].rbt;
                        min_pid=itr->second;
                    }
                }
            }
            t++;
            if(flag==1)
            {
                char c=min_pid+48;
                string s1;
                s1=s1+c;
                if(!(s.find(s1)>=0 && s.find(s1)<tbt))
                {
                    p[min_pid-1].rt=t-p[min_pid-1].at-1;
                }
                s=s+c;
                p[min_pid-1].ct=t;
                p[min_pid-1].rbt--;
            }
        }
        chart=s;
    }
    void findtimeterm(process p[],int n)
    {
        for(int i=0;i<n;i++)
        {
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
        }
    }
    void calculate(process p[],int n)
    {
        double s1=0,s2=0;
        int max_ct=p[0].ct,min_at=p[0].at,scl;
        for(int i=0;i<n;i++)
        {
            s1+=p[i].tat;
            s2+=p[i].wt;
            if(max_ct<=p[i].ct)
            max_ct=p[i].ct;
            if(min_at>=p[i].at)
            min_at=p[i].at;
        }
        double r1,r2,tp;
        r1=s1/n;
        r2=s2/n;
        scl=max_ct-min_at;
        tp=(double )n/(double )scl;
        cout<<"Average turnaround time: "<<r1<<endl;
        cout<<"Average waiting time: "<<r2<<endl;
        cout<<"Scheduling length: "<<scl<<endl;
        cout<<"Throughput: "<<tp<<endl;
        cout<<"Gantt chart: "<<chart<<endl;
    }
    void display(process p[],int n){
        cout<<"PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
        for(int i=0;i<n;i++)
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<p[i].rt<<endl;
    }
};

int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    process p[n];
    multimap<int,int> m1,m2;
    for(int i=0;i<n;i++)
    {
        int a,b;
        cout<<"Enter arrival time and burst time of process "<<i+1<<" : ";
        cin>>a>>b;
        m1.insert(pair<int,int> (a,i+1));
        m2.insert(pair<int,int> (b,i+1));
        p[i]=process(i+1,a,b);
    }
    SRTF s;
    s.findcomptime(p,n,m1,m2);
    s.findtimeterm(p,n);
    s.display(p,n);
    s.calculate(p,n);
}