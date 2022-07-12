#include<Windows.h> 
#include<GL/glut.h> 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 

void* currentfont;

int size=7, MAX=10;

int flag = 0;
class button
{
	int x1, y1, x2, y2;
	int state;
	char str[10];
public:
	button()
	{
	}
	button(int x11, int y11, int x22, int y22,const char* str1)
	{
		x1 = x11;
		y1 = y11;
		x2 = x22;
		y2 = y22;
		state = 1;
		strcpy_s(str, str1);
	}
	void draw();
	void togglestate();
	int insidebutton(int x, int y);
};
class stack
{
	button s[10];
	int top;
	
public:
	stack()
	{
		top = -1;
	}
	int stfull();
	button pop();
	void push(int item);
	int stempty();
	void displaystack();
};
stack st;
class queue
{
	button que[10];
	int front, rear;
public:
	queue()
	{
		front = -1;
		rear = -1;
	}
	void displayqueue();
	void insert_element();
	void delete_element();
	bool is_queue_full();
};
queue q;
void setFont(void* font)
{
	currentfont = font;
}
void drawstring(float x, float y, const char* str)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for(i=0;i<len;i++)
		glutBitmapCharacter(currentfont, str[i]);
	
}

void button::draw()
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.000, 0.647, 0.000);
	drawstring(x1 + 10, y1 + 10, str);
	glColor3f(1.000, 0.271, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
	if (state == 0)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glEnd();
	}
	else if (state == 1)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glEnd();
	}
}
void button::togglestate(void)
{
	state = (state == 1) ? 0 : 1;
}

int button::insidebutton(int x, int y)
{
	if (x > x1 && x<x2 && y>y1 && y < y2)
		return 1;
	else return 0;
}
button st_btn(160, 100, 235, 150, "Stack");
button q_btn(300, 100, 375, 150, "Queue");
button btn1(150, 100, 225, 150, "Push");
button btn2(375, 100, 450, 150, "Pop");
button btn3(150, 100, 225, 150, "Insert");
button btn4(375, 100, 450, 150, "Delete");
// 
// Stack functions start 
// 
int stack::stfull() {
	if (st.top >= size - 1)
		return 1;
	else
		return 0;
}
void stack::push(int item) {
	char str[10];
	printf("enter the element into stack:");
	scanf_s("%d", &item);
	snprintf(str, sizeof(str), "%d", item);
	button btn(160, 250 + st.top * 50, 210, 300 + st.top * 50, str);
	st.top++;
	st.s[st.top] = btn;
}
int stack::stempty() {
	if (st.top == -1)
		return 1;
	else
		return 0;
}
button stack::pop() {

	button item;
	item = st.s[st.top];
	st.top--;
	return (item);
}
void stack::displaystack() {
	int i;
	if (st.stempty())
	{
		glColor3f(0, 0, 0);
		drawstring(370, 350, "Stack Is Empty!");
	}
		
	else if (st.stfull())
	{
		for (i = st.top; i >= 0; i--)
			st.s[i].draw();
		glColor3f(1, 0, 0);
		drawstring(370, 350, "Stack is Full!");
	}
	else {
		for (i = st.top; i >= 0; i--)
			st.s[i].draw();
	}
}

// 
//stack functions end 
// 
// 
// queue function starts 
// 
void queue::insert_element()
{
	static int num = 0;
	char str[10];
	if (!is_queue_full()) {
		printf("enter the element into queue :");
		scanf_s("%d", &num);
		snprintf(str, sizeof(str), "%d", num++);

		button btn(100 + rear * 50, 250, 150 + rear * 50, 300, str);
		if (front == 0 && rear == MAX-1)
		{
			drawstring(10, 10, " Queue OverFlow Occured!");
		}
		else if (front == -1 && rear == -1)
		{
			front = rear = 0;
			que[rear] = btn;
		}

		else if (rear == MAX - 1 && front != 0)
		{
			rear=0;
			que[rear] = btn;
		}
		else
		{
			rear++;
			que[rear] = btn;
		}
	}
	else
	{
		glColor3f(1, 0, 0);
		drawstring(200, 400, "Queue is full!");
	}
	
}
void queue::delete_element()
{
	button element;
	if (front > rear)
	{
		drawstring(260, 10, " Underflow");
	}
	element = que[front];
	if (front == rear)
	{
		front = rear = -1;
	}
	else
	{
		if (front == MAX - 1)
			front = 0;
		else
			front++; 
	}
}
void queue::displayqueue()
{
	int i;
	if (front == -1)
		drawstring(150, 400, " No elements to display in queue");
	else if (rear == MAX - 1)
	{
		for (i = front; i <= rear; i++)
		{
			que[i].draw();
		}
		glColor3f(1, 0, 0);
		drawstring(250, 400, "Queue is full!");
	}
	else
	{
 
		for (i = front; i <= rear; i++)
		{
			que[i].draw();
		}
	}
}

bool queue::is_queue_full()
{
	if (rear == MAX - 1) {
		return true;
	}
	return false;
}
// 
// queue function ends 
// 

void stackWindow();
void queueWindow();

void idle_stack()
{
	stackWindow();
}

void idle_queue()
{
	queueWindow();
}

void draw_border_stack()
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(50, 200);
	glVertex2f(550, 200);
	glVertex2f(550, 550);
	glVertex2f(50, 550);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(300, 200);
	glVertex2f(300, 550);
	glEnd();
	glFlush();
}

void draw_border_queue()
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(50, 170);
	glVertex2f(550, 170);
	glVertex2f(550, 550);
	glVertex2f(50, 550);
	glEnd();
}


void stackWindow()
{
	glClearColor(1.000, 1.000, 0.878, 0.000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutIdleFunc(idle_stack);
	btn1.draw();
	btn2.draw();
	draw_border_stack();
	st.displaystack();
	glutSwapBuffers();
	glFlush();
}

void queueWindow()
{
	glClearColor(1.000, 1.000, 0.878, 0.000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutIdleFunc(idle_queue);
	
	btn3.draw();
	btn4.draw();
	draw_border_queue();
	q.displayqueue();
	glutSwapBuffers();
	glFlush();	
}


void menu(int id)
{
	switch (id)
	{
		case 1: flag = 1;
				printf("Enter the size of the stack (choose in the range 2-7): ");
				while (1) {
					scanf_s("%d", &size);
					if (size < 2 || size > 7)
					{
						printf("Wrong input!, Please choose in the range 2-7: ");
						continue;
					}
					break;
				}
				stackWindow();
				break;

		case 2: flag = 2;
				printf("Enter the size of the queue (choose in the range 2-10): ");
				while (1) {
					scanf_s("%d", &MAX);
					if (MAX < 2 || MAX > 10)
					{
						printf("Wrong input!, Please choose in the range 2-10: ");
						continue;
					}
					break;
				}
				queueWindow();
				break;
	}
}
void displaystacknqueue()
{
	st.displaystack();
	q.displayqueue();
}
void display()
{
	glClearColor(1.000, 1.000, 0.878, 0.000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 0, 0);
	drawstring(100, 400, "IMPLEMENTATION OF STACK AND QUEUE");
	drawstring(150, 350, "This project is done by");
	drawstring(150, 300, "Varun Thantry (1RN19CS175)");
	drawstring(150, 250, "Yeshwanth P L (1RN19CS190)");
	st_btn.draw();
	q_btn.draw();
	glFlush();
	glutSwapBuffers();
}
void mouse(int btn, int state, int x, int y)
{
	static int itemno = 0;
	y = 600 - y;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (flag == 1)
		{
			if (btn1.insidebutton(x, y))
			{
				btn1.togglestate();
				if (!st.stfull())
					st.push(itemno++);
			}
			if (btn2.insidebutton(x, y))
			{
				btn2.togglestate();
				if (!st.stempty())
					st.pop();
			}
		}
		else if (flag == 2)
		{
			if (btn3.insidebutton(x, y))
			{
				btn3.togglestate();
				q.insert_element();
			}
			if (btn4.insidebutton(x, y))
			{
				btn4.togglestate();
				q.delete_element();
			}
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (flag == 1)
		{
			if (btn1.insidebutton(x, y))
			{
				btn1.togglestate();
			}
			if (btn2.insidebutton(x, y))
			{
				btn2.togglestate();
			}
		}
		else if (flag == 2)
		{
			if (btn3.insidebutton(x, y))
			{
				btn3.togglestate();
			}
			if (btn4.insidebutton(x, y))
			{
				btn4.togglestate();
			}
		}
	}
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("IMPLEMENTATION OF STACK AND QUEUE");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutIdleFunc(NULL);
	glutCreateMenu(menu);
	glutAddMenuEntry("Stack", 1);
	glutAddMenuEntry("Queue", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
	return 0;
}