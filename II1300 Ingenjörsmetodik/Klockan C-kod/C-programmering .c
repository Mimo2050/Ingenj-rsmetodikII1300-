//Murtadha Alobaidi 
#include <stdio.h>

int increment_time_by_one(int tid)
{
    int s, m, h;
    int ny_tid;
    s=tid%100;
    m=(tid%10000)/100;
    h=tid/10000;
    
    s++;
    if(s==60)
    {
        s=0;
        m++;
        if(m==60)
        {
            m=0;
            h++;
            if(h==24)
            {
                h=0;
            }
        }
    }
    
    ny_tid=h*10000+m*100+s;
   
    return ny_tid;
}


int main()

{
    int tid, alarm;
    
    printf("Skriv in tiden HHMMSS:");
    scanf("%d",&tid);
    
    printf("Alarm: ");
    scanf("%d", &alarm);
    
    while (tid != alarm)
    {
        int s, m, h;
        s=tid%100;
        m=(tid%10000)/100;
        h=tid/10000;
         
        if (h < 10) {
            printf("0%d:", h);
        } else {
            printf("%d:", h);
        }
        
        if (m < 10) {
            printf("0%d:", m);
        } else {
            printf("%d:", m);
        }
        
        if (s < 10) {
            printf("0%d\n", s);
        } else {
            printf("%d\n", s);
        }
                
        tid = increment_time_by_one(tid);
    }
    
    printf("ALARM!");
    
    return 0;
}

