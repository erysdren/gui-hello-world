/*
 * adapted from:
 * https://www.haiku-os.org/development/learning_to_program_with_haiku
 */

#include <Application.h>
#include <Window.h>
#include <Button.h>
#include <View.h>
#include <String.h>
#include <Alert.h>

enum
{
	M_BUTTON_CLICKED = 'BCLK'
};

class HelloApp : public BApplication
{
public:
	HelloApp(void) : BApplication("application/x-vnd.HelloApp")
	{
		// create window
		window = new BWindow(BRect(100, 100, 500, 400), "Hello", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE);

		// create button
		BButton *button = new BButton(BRect(10, 10, 11, 11), "clickme", "Click Me!", new BMessage(M_BUTTON_CLICKED));
		button->SetTarget(this);
		button->ResizeToPreferred();

		// add button to window
		window->AddChild(button);

		// show window
		window->Show();
	}

	void MessageReceived(BMessage *msg)
	{
		switch(msg->what)
		{
			case M_BUTTON_CLICKED:
			{
				BAlert *alert = new BAlert("Alert", "Hello World!", "Ok");
				alert->Go();
				break;
			}

			default:
			{
				BApplication::MessageReceived(msg);
				break;
			}
		}
	}

private:
	BWindow *window;
};

int main(int argc, char **argv)
{
	HelloApp *app = new HelloApp();
	app->Run();
	delete app;
	return 0;
}
