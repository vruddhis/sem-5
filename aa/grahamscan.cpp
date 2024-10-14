#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <iostream.h>

struct Point {
    int x, y;
};

void ConvexHull(struct Point arr[], int n) {
    if (n < 3) return;  
    struct Point stack[n];  
    int top = -1;

    stack[++top] = arr[0];
    stack[++top] = arr[1];
    line(stack[top-1].x, stack[top-1].y, stack[top].x, stack[top].y);  
    stack[++top] = arr[2];
    line(stack[top-1].x, stack[top-1].y, stack[top].x, stack[top].y);  

   
    for (int j = 3; j < n; j++) {
        while (top >= 1 && 
              (stack[top - 1].x * (stack[top].y - arr[j].y) -
               stack[top - 1].y * (stack[top].x - arr[j].x) + 
               stack[top].x * arr[j].y - stack[top].y * arr[j].x) < 0) 
        {
            setcolor(BLACK);
            line(stack[top-1].x, stack[top-1].y, stack[top].x, stack[top].y);
            top--; 
        }
        stack[++top] = arr[j];
        setcolor(WHITE);  
        line(stack[top-1].x, stack[top-1].y, stack[top].x, stack[top].y);

        delay(4000);
    }
}

int main() {
    int gd = DETECT, gm;

    initgraph(&gd, &gm, NULL);
    struct Point points[6];
    int n = 6;
    points[0].x = 100; points[0].y = 200;
    points[1].x = 200; points[1].y = 300;
    points[2].x = 300; points[2].y = 250;
    points[3].x = 400; points[3].y = 400;
    points[4].x = 350; points[4].y = 150;
    points[5].x = 250; points[5].y = 100;
    for (int i = 0; i < n; i++) {
        circle(points[i].x, points[i].y, 3);  
    }
    ConvexHull(points, n);
    getch();
    closegraph();

    return 0;
}
