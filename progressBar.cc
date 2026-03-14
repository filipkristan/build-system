#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void printProgressBar(int percentage_done, float percentage_to_finish_at, int delay) {
	while (percentage_done <= percentage_to_finish_at) { // Update the bar to show the current progress
		system("clear");
		if (percentage_done > 100) {percentage_done = 100;};
		if (percentage_done < 1) {percentage_done = 0;};
		std::string start_text = "[" + std::to_string(percentage_done) + "%] - [";
		std::string end_text = "]";
		struct winsize cli;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &cli); // Get cli values
		// Calculate how many characters need to be printed to the console
		float percentValueMultplyer = (cli.ws_col - start_text.length() - end_text.length()) / 100.0;
		float hashtagsToMake = percentage_done * percentValueMultplyer;
		float dashesToMake = cli.ws_col - start_text.size() - hashtagsToMake - 2;

		cout << start_text;
		for (int i = 0; i < hashtagsToMake; i++) {
			printf("#");
		}
		for (int i = 0; i < dashesToMake; i++) {
			printf("-");
		}
		cout << end_text << endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		 	percentage_done++;
		}
	if (percentage_done == 100) {cout << "Finished!" << std::endl;}
}