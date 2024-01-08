#include <stdio.h>

// Time:      7  15   30
// Distance:  9  40  200

unsigned long long distance_traveled(unsigned long long velocity, unsigned long long total_time)
{
    unsigned long long time_left, distance;
    time_left = total_time - velocity;
    distance = velocity * time_left;
    return distance;
}

unsigned long long part1(int size, unsigned long long times[size], unsigned long long dists[size])
{
    unsigned long long sum, n, dist, time, record;
    sum = 0;
    for (int i = 0; i < size; i++)
    {
        n = 0;
        time = times[i];
        record = dists[i];
        for (unsigned long long j = 0; j < time; j++)
        {
            dist = distance_traveled(j, time);
            if (dist > record)
            {
                n++;
            }
        }
        printf("%d: %lld\n", i, n);
        if (sum == 0)
        {
            sum = n;
        }
        else
        {
            sum *= n;
        }
    }
    return sum;
}

unsigned long long part2(int size, unsigned long long times[size], unsigned long long dists[size])
{
    unsigned long long sum, n, dist, time, record;
    sum = 0;
    for (int i = 0; i < size; i++)
    {
        n = 0;
        time = times[i];
        record = dists[i];
        for (unsigned long long j = 0; j < time; j++)
        {
            dist = distance_traveled(j, time);
            if (dist > record)
            {
                n++;
            }
        }
        if (sum == 0)
        {
            sum = n;
        }
        else
        {
            sum *= n;
        }
    }
    return sum;
}

int main(void)
{
    //const int example_size = 3;
    //const int size_1 = 4;
    unsigned long long result1;
    unsigned long long result2;
    
    //unsigned long long timesE[1] = {71530};
    //unsigned long long distsE[1] = {940200};

    unsigned long long times1[4] = {53, 91, 67, 68};
    unsigned long long dists1[4] = {250, 1330, 1081, 1025};
    
    unsigned long long times2[1] = {53916768};
    unsigned long long dists2[1] = {250133010811025};

    result1 = part1(4, times1, dists1);
    printf("result 1: %lld\n", result1);

    result2 = part2(1, times2, dists2);
    printf("result 2: %lld", result2);

    return 0;
}
