
1 of 1,281
(no subject)
Inbox

Vruddhi
Attachments
12:05 PM (4 hours ago)
to me


 One attachment
  •  Scanned by Gmail
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <iostream.h>
#include <math.h>

struct Point {
    int x, y;
};
float sine(struct Point p){
	float x = (float)p.x;
	float y = (float)p.y;
	float mag;
	mag = sqrt(x*x+y*y);
	return y/mag;

}

float dist(struct Point p){
	float x = (float)p.x;
	float y = (float)p.y;
	float mag;
	mag = sqrt(x*x+y*y);
	return mag;

}

void ConvexHull(struct Point arr[], int n) {
    if (n < 3) return;
	struct Point temp;
    struct Point stack[20];
    for (int i=0; i<n; i++){
	for (int j=i; j<n; j++){
		if(sine(arr[i]) > sine(arr[j])){
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else if(sine(arr[i]) == sine(arr[j]))
		{
			if(dist(arr[i]) > dist(arr[j])){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
    }
    int top = -1;

    stack[++top] = arr[0];
    stack[++top] = arr[1];
	setcolor(WHITE);
    line(stack[top-1].x, stack[top-1].y, stack[top].x, stack[top].y);

				     z

    for (int j = 2; j < n; j++) {
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
    line(stack[top].x, stack[top].y, arr[0].x, arr[0].y);
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
    for (int i = 0; i < n; i++) {
	circle(points[i].x, points[i].y, 3);
    }
    delay(4000);
	ConvexHull(points, n);
    getch();
    closegraph();

    return 0;
}