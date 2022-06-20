#ifndef NO_NOTIFY
#include <libnotify/notify.h>
#endif

#include <iostream>
#include <thread>
#include <string.h>
#include "Timer.hpp"

/* Variables */
double targetTime = 0;
int seconds = 0;
int minutes = 0;
int hours = 0;

#ifndef NO_NOTIFY
void TimeUpNotification();
std::string notificationText = "Time is up";
bool showNotification = true;
#endif

int main(int argc, char** argv)
{
	/* Parse args */
	if (argc > 2)
	{
		for (int i = 1; i < argc - 1; i++)
		{
			/* Hours */
			if (strcmp(argv[i], "-h") == 0)
			{
				hours = atoi(argv[i + 1]);
			}

			/* Minutes */
			if (strcmp(argv[i], "-m") == 0)
			{
				minutes = atoi(argv[i + 1]);
			}

			/* Seconds */
			if (strcmp(argv[i], "-s") == 0)
			{
				seconds = atoi(argv[i + 1]);
			}

#ifndef NO_NOTIFY
			/* Notification properties */
			if (strcmp(argv[i], "-t") == 0)
			{
				notificationText = argv[i + 1];
			}

			if (strcmp(argv[i], "--no-notify") == 0)
			{
				showNotification = false;
			}
#endif /* NO_NOTIFY */
		}
	}
	else if (argc == 2 && strcmp(argv[1], "--help") == 0)
	{
#ifndef NO_NOTIFY
		std::cout << "Usage: ./timer [--no-notify] [options]\n\n" <<
#else
		std::cout << "Usage: ./timer [options]\n\n" <<
#endif /* NO_NOTIFY */
			"Options:\n" <<
			"  -s [seconds]\n" <<
			"  -m [minutes]\n" <<
			"  -h [hours]\n" <<
#ifndef NO_NOTIFY
			"  --no-notify\t\tDon't show any notifications when the time is up\n" <<
			"  -t [notification]\tCustom notification text\n" <<
#endif /* NO_NOTIFY */
			"  --help\t\tShows this text wall that your are reading right now " << std::endl;

		/* No need to do anything else */
		return 0;
	}

	targetTime = hours * 3600 + minutes * 60 + seconds;

	/* Start the timer */
	Birb::Timer timer;
	timer.Start(targetTime * 1000);

	while (timer.ElapsedSeconds() > 0)
	{
		/* Print out the remaining time */
		std::cout << timer.DigitalFormat() << "\t\r";
		std::cout.flush();

		/* Sleep for a second. Lets not waste any CPU cycles */
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

#ifndef NO_NOTIFY
	if (showNotification)
		TimeUpNotification();
#endif

	return 0;
}

#ifndef NO_NOTIFY
void TimeUpNotification()
{
	notify_init("CLI-Timer");
	NotifyNotification* n = notify_notification_new("CLI Timer", notificationText.c_str(), 0);
	notify_notification_set_timeout(n, 5000);

	if (!notify_notification_show(n, 0))
	{
		std::cout << "Notification wasn't shown properly" << std::endl;
	}
}
#endif /* NO_NOTIFY */
