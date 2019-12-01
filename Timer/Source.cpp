#include <iostream>
#include <ctime>
#include <map>
#include <chrono>
#include <string>
#include <unordered_map>
class Timer
{
	struct State{
		std::time_t time;
		int count;
		State() {}
		State(std::time_t time_, int count_) : time(time_), count(count_) {}
	};
	static std::unordered_map<std::string, Timer::State> TableTime;
public:
	Timer(std::string _name) : name(_name){
		start = std::time(0);
		Timer::TableTime.insert({ name, State(0, 0) });
	};
	~Timer()
	{
		std::time_t end = std::time(0);
		State& stt = TableTime[name];
		stt.time += (end - start);
		stt.count += 1;
	};
	void print()
	{
		for (const auto& stt : TableTime)
		{
			std::cout << stt.first << ", " << stt.second.count << ", "
				<< stt.second.time << std::endl;

		}
	};
private:
	std::string name;
	std::time_t start;

};

std::unordered_map<std::string, Timer::State> Timer::TableTime;



int main()
{
	std::string value = "value1";
	Timer a = Timer(value);
	Timer b = Timer("value2");
	Timer c = Timer("value3");
	a.~Timer();
	b.~Timer();
	c.print();
	system("pause");
	return 0;
}
