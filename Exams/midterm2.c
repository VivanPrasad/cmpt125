#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct batteryType
{
    double voltage;
    double energyCapacity;
    double energyStored;
    int serialNum;
};

void printBattery(const struct batteryType *btype)
{
    
}
int compareBatteries(const struct batteryType *b1,
    const struct batteryType *b2)
{
    if (b1->voltage == b2->voltage && b1->energyCapacity == b2->energyCapacity)
    {
        return 1;
    }
    return 0;
}

struct batteryType *readBattery(FILE *inputStream)
{
    
}
int main(void)
{
    const struct batteryType bat1;
    const struct batteryType bat2;

}