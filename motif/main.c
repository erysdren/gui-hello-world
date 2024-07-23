/*
 * adapted from:
 * https://www.oreilly.com/openbook/motif/vol6a/Vol6a_html/ch02.html
 */

#include <Xm/PushB.h>

void clickme(Widget widget, XtPointer client_data, XtPointer call_data)
{
	printf("Hello World!");
}

int main(int argc, char **argv)
{
	Widget toplevel, button;
	XtAppContext app;
	XmString label;

	XtSetLanguageProc(NULL, NULL, NULL);

	toplevel = XtVaAppInitialize(&app, "Hello", NULL, 0, &argc, argv, NULL, NULL);

	label = XmStringCreateLocalized("Click Me!");
	button = XtVaCreateManagedWidget("clickme", xmPushButtonWidgetClass, toplevel, XmNlabelString, label, NULL);
	XmStringFree(label);
	XtAddCallback(button, XmNactivateCallback, clickme, NULL);

	XtRealizeWidget(toplevel);
	XtAppMainLoop(app);

	return 0;
}
