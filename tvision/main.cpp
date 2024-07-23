/*
 * adapted from:
 * https://github.com/magiblot/tvision/blob/master/hello.cpp
 */

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_MsgBox
#define Uses_TFileDialog
#include <tvision/tv.h>

enum {
	cmButtonClicked = 100
};

class HelloApp : public TApplication
{
public:
	static TMenuBar *initMenuBar(TRect r)
	{
		r.b.y = r.a.y + 1;

		return new TMenuBar(r,
			*new TSubMenu("~H~ello", kbAltH) +
				*new TMenuItem("~C~lick Me!", cmButtonClicked, kbAltC) +
				newLine() +
				*new TMenuItem("E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X")
		);
	}

	HelloApp() : TProgInit(&HelloApp::initStatusLine, &HelloApp::initMenuBar, &HelloApp::initDeskTop)
	{

	}

	virtual void handleEvent(TEvent &event)
	{
		TApplication::handleEvent(event);

		if (event.what == evCommand)
		{
			switch (event.message.command)
			{
				case cmButtonClicked:
					messageBox("Hello World!", mfInformation | mfOKButton);
					clearEvent(event);
					break;

				default:
					break;
			}
		}
	}
};

int main(int argc, char **argv)
{
	HelloApp app;
	app.run();
	return 0;
}
