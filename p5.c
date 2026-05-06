#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
int main() {
int n, m; // n = number of processes, m = number of resources
int alloc[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int avail[MAX_RESOURCES];
int finish[MAX_PROCESSES] = {0};
int safeSequence[MAX_PROCESSES];
int count = 0;
// Input
printf("Enter number of processes: ");
scanf("%d", &n);
printf("Enter number of resources: ");
scanf("%d", &m);
printf("Enter Allocation Matrix (%d x %d):\n", n, m);
for (int i = 0; i < n; i++)
for (int j = 0; j < m; j++)
scanf("%d", &alloc[i][j]);
printf("Enter Maximum Matrix (%d x %d):\n", n, m);
for (int i = 0; i < n; i++)
for (int j = 0; j < m; j++)
scanf("%d", &max[i][j]);
printf("Enter Available Resources (%d):\n", m);
for (int i = 0; i < m; i++)
scanf("%d", &avail[i]);
// Calculate Need Matrix
for (int i = 0; i < n; i++)
for (int j = 0; j < m; j++)
need[i][j] = max[i][j] - alloc[i][j];
// Banker's Algorithm
while (count < n) {
bool found = false;

for (int i = 0; i < n; i++) {
if (!finish[i]) {
bool canAllocate = true;
for (int j = 0; j < m; j++) {
if (need[i][j] > avail[j]) {
canAllocate = false;
break;
}
}
if (canAllocate) {
for (int j = 0; j < m; j++)
avail[j] += alloc[i][j];
safeSequence[count++] = i;
finish[i] = 1;
found = true;
}
}
}
if (!found) {
printf("\nSystem is in an UNSAFE state. Deadlock may occur.\n");
return 1;
}
}
// Safe State
printf("\nSystem is in a SAFE state.\nSafe sequence: ");
for (int i = 0; i < n; i++) {
printf("P%d", safeSequence[i]);
if (i != n - 1)
printf(" -> ");
}
printf("\n");
return 0;
}
