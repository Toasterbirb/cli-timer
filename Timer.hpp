#pragma once

#include <chrono>
#include <ctime>
#include <cmath>
#include <string>

namespace Birb
{
	/// Class for timing things. Accurate down to milliseconds
	class Timer
	{
	public:
		void Start(const double& targetMillis);
		void Stop();
		double ElapsedMilliseconds();
		double ElapsedSeconds();
		double ElapsedMinutes();
		double ElapsedHours();

		static double CalcSeconds(const double& mills); 	///< Converts milliseconds into seconds
		static double CalcMinutes(const double& mills); 	///< Converts milliseconds into minutes
		static double CalcHours(const double& mills); 	///< Converts milliseconds into hours

		std::string DigitalFormat(); 		///< Prints the current elapsed time in digital format (00:00:00:000)
		std::string SplitDigitalFormat(const double& previousmills /**< [in] elapsed milliseconds of the previous split */); ///< Used for calculating digital time for a split during timing
		bool running = false;
		double targetMillis;

	private:
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> endTime;
	};
}
