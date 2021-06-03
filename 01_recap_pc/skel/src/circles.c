#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

typedef struct {
    int x, y;
    int raza;
} circle;

int intersect(circle a, circle b){
    double distance = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    int sum = a.raza + b.raza;
    
    if (distance <= sum) {
        return 1;
    }
    
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    circle *circles = (circle *)malloc(n * sizeof(circle));
    if (!circles) {
        fprintf(stderr, "ERROR in malloc()\n");
    }

    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &circles[i].x, &circles[i].y, &circles[i].raza);
    }
    
    int intersections = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (intersect(circles[i], circles[j])) {
                intersections++;
            }
        }
    }

    printf("%d\n", intersections);

    free(circles);
    return 0;
}
