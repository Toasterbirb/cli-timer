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

/* Function declarations */
#ifndef NO_NOTIFY
void TimeUpNotification();
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
		}
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
	TimeUpNotification();
#endif

	return 0;
}

#ifndef NO_NOTIFY
void TimeUpNotification()
{
	notify_init("CLI-Timer");
	NotifyNotification* n = notify_notification_new("CLI Timer", "Time is up", 0);
	notify_notification_set_timeout(n, 5000);

	if (!notify_notification_show(n, 0))
	{
		std::cout << "Notification wasn't shown properly" << std::endl;
	}
}
#endif /* NO_NOTIFY */
