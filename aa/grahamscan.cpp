#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <iostream.h>
#include <math.h>

struct Point {
    int x, y;
};

float sine(struct Point p) {
    float x = (float)p.x;
    float y = (float)p.y;
    float mag = sqrt(x * x + y * y);
    return y / mag;
}

float dist(struct Point p) {
    float x = (float)p.x;
    float y = (float)p.y;
    return sqrt(x * x + y * y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  
    return (val > 0) ? 1 : 2; 
}

void bubbleSort(Point arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            float sine1 = sine(arr[j]);
            float sine2 = sine(arr[j + 1]);
            if (sine1 > sine2 || (sine1 == sine2 && dist(arr[j]) > dist(arr[j + 1]))) {
                Point temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void ConvexHull(struct Point arr[], int n) {
    if (n < 3) return;

    struct Point temp;
    struct Point stack[20];
    int bottommost = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].y < arr[bottommost].y || (arr[i].y == arr[bottommost].y && arr[i].x < arr[bottommost].x)) {
            bottommost = i;
        }
    }

    temp = arr[0];
    arr[0] = arr[bottommost];
    arr[bottommost] = temp; // bottommost becomes P0

    bubbleSort(arr + 1, n - 1); //by sine

    int top = -1;

    stack[++top] = arr[0];
    stack[++top] = arr[1];

    int screen_height = getmaxy(); 

    setcolor(WHITE);
    line(stack[top - 1].x, screen_height - stack[top - 1].y, stack[top].x, screen_height - stack[top].y);

    stack[++top] = arr[2];
    line(stack[top - 1].x, screen_height - stack[top - 1].y, stack[top].x, screen_height - stack[top].y);

    for (int j = 3; j < n; j++) {
        while (top >= 1 && orientation(stack[top - 1], stack[top], arr[j]) != 2) {
            setcolor(BLACK);
            line(stack[top - 1].x, screen_height - stack[top - 1].y, stack[top].x, screen_height - stack[top].y);
            top--;
        }

        stack[++top] = arr[j];
        setcolor(WHITE);
        line(stack[top - 1].x, screen_height - stack[top - 1].y, stack[top].x, screen_height - stack[top].y);

        delay(4000);
    }
    line(stack[top].x, screen_height - stack[top].y, arr[0].x, screen_height - arr[0].y);
}

int main() {
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    struct Point points[6];
    int n = 6;
    points[0].x = 100; points[0].y = 200;
    points[1].x = 200; points[1].y = 300;
    points[2].x = 300; points[2].y = 250;
    points[3].x = 400; points[3].y = 400;
    points[4].x = 350; points[4].y = 150;
    points[5].x = 250; points[5].y = 100;

    int screen_height = getmaxy();

    for (int i = 0; i < n; i++) {
        circle(points[i].x, screen_height - points[i].y, 3); 
    }

    delay(4000);
    ConvexHull(points, n);
    getch();
    closegraph();

    return 0;
}
