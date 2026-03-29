#include "RANDOM.H"
#include <iostream>
#include <vector>

using namespace std;

namespace p2_sim {

enum ErrorCode { success, overflow, underflow, fail };
enum PlaneStatus { null_status, arriving, departing };

class Plane {
public:
	Plane() : flt_num(-1), clock_start(-1), state(null_status) {}

	Plane(int flt, int time, PlaneStatus status)
		: flt_num(flt), clock_start(time), state(status) {
		cout << "Plane number " << flt_num << " ready to ";
		if (state == arriving) {
			cout << "land." << endl;
		} else {
			cout << "take off." << endl;
		}
	}

	void refuse() const {
		cout << "Plane number " << flt_num;
		if (state == arriving) {
			cout << " directed to another airport" << endl;
		} else {
			cout << " told to try to take off again later" << endl;
		}
	}

	void land(int time) const {
		int wait = time - clock_start;
		cout << time << ": Plane number " << flt_num << " landed after " << wait
			 << " time unit" << ((wait == 1) ? "" : "s")
			 << " in the landing queue." << endl;
	}

	void fly(int time) const {
		int wait = time - clock_start;
		cout << time << ": Plane number " << flt_num << " took off after " << wait
			 << " time unit" << ((wait == 1) ? "" : "s")
			 << " in the takeoff queue." << endl;
	}

	int started() const {
		return clock_start;
	}

private:
	int flt_num;
	int clock_start;
	PlaneStatus state;
};

class PlaneQueue {
public:
	explicit PlaneQueue(int max_size)
		: entries(max_size), count(0), front_index(0), rear_index(max_size - 1), maxqueue(max_size) {}

	bool empty() const {
		return count == 0;
	}

	bool full() const {
		return count >= maxqueue;
	}

	int size() const {
		return count;
	}

	ErrorCode append(const Plane &item) {
		if (full()) {
			return overflow;
		}
		count++;
		rear_index = ((rear_index + 1) == maxqueue) ? 0 : (rear_index + 1);
		entries[rear_index] = item;
		return success;
	}

	ErrorCode serve() {
		if (empty()) {
			return underflow;
		}
		count--;
		front_index = ((front_index + 1) == maxqueue) ? 0 : (front_index + 1);
		return success;
	}

	ErrorCode retrieve(Plane &item) const {
		if (empty()) {
			return underflow;
		}
		item = entries[front_index];
		return success;
	}

private:
	vector<Plane> entries;
	int count;
	int front_index;
	int rear_index;
	int maxqueue;
};

class Airport {
public:
	explicit Airport(int limit)
		: landing_queue(limit),
		  takeoff_queue(limit),
		  queue_limit(limit),
		  num_land_requests(0),
		  num_takeoff_requests(0),
		  num_landings(0),
		  num_takeoffs(0),
		  num_land_accepted(0),
		  num_takeoff_accepted(0),
		  num_land_refused(0),
		  num_takeoff_refused(0),
		  land_wait(0),
		  takeoff_wait(0),
		  land_idle_time(0),
		  takeoff_idle_time(0) {}

	ErrorCode can_land(const Plane &current) {
		ErrorCode result;
		if (landing_queue.size() < queue_limit) {
			result = landing_queue.append(current);
		} else {
			result = fail;
		}
		num_land_requests++;
		if (result != success) {
			num_land_refused++;
		} else {
			num_land_accepted++;
		}
		return result;
	}

	ErrorCode can_depart(const Plane &current) {
		ErrorCode result;
		if (takeoff_queue.size() < queue_limit) {
			result = takeoff_queue.append(current);
		} else {
			result = fail;
		}
		num_takeoff_requests++;
		if (result != success) {
			num_takeoff_refused++;
		} else {
			num_takeoff_accepted++;
		}
		return result;
	}

	bool landing_activity(int time, Plane &moving) {
		if (!landing_queue.empty()) {
			landing_queue.retrieve(moving);
			land_wait += time - moving.started();
			num_landings++;
			landing_queue.serve();
			return true;
		} else {
			land_idle_time++;
			return false;
		}
	}

	bool takeoff_activity(int time, Plane &moving) {
		if (!takeoff_queue.empty()) {
			takeoff_queue.retrieve(moving);
			takeoff_wait += time - moving.started();
			num_takeoffs++;
			takeoff_queue.serve();
			return true;
		} else {
			takeoff_idle_time++;
			return false;
		}
	}

	void shut_down(int time) const {
		cout << "\nSimulation has concluded after " << time << " time units." << endl
			 << "Total number of planes processed "
			 << (num_land_requests + num_takeoff_requests) << endl
			 << "Total number of planes asking to land " << num_land_requests << endl
			 << "Total number of planes asking to take off " << num_takeoff_requests << endl
			 << "Total number of planes accepted for landing " << num_land_accepted << endl
			 << "Total number of planes accepted for takeoff " << num_takeoff_accepted << endl
			 << "Total number of planes refused for landing " << num_land_refused << endl
			 << "Total number of planes refused for takeoff " << num_takeoff_refused << endl
			 << "Total number of planes that landed " << num_landings << endl
			 << "Total number of planes that took off " << num_takeoffs << endl
			 << "Total number of planes left in landing queue " << landing_queue.size() << endl
			 << "Total number of planes left in takeoff queue " << takeoff_queue.size() << endl;

		double land_idle_percent = (time > 0) ? (100.0 * static_cast<double>(land_idle_time) / static_cast<double>(time)) : 0.0;
		double takeoff_idle_percent = (time > 0) ? (100.0 * static_cast<double>(takeoff_idle_time) / static_cast<double>(time)) : 0.0;
		cout << "Percentage of time landing runway idle " << land_idle_percent << "%" << endl;
		cout << "Percentage of time takeoff runway idle " << takeoff_idle_percent << "%" << endl;

		if (num_landings > 0) {
			cout << "Average wait in landing queue "
				 << (static_cast<double>(land_wait) / static_cast<double>(num_landings))
				 << " time units" << endl;
		} else {
			cout << "Average wait in landing queue 0 time units" << endl;
		}

		if (num_takeoffs > 0) {
			cout << "Average wait in takeoff queue "
				 << (static_cast<double>(takeoff_wait) / static_cast<double>(num_takeoffs))
				 << " time units" << endl;
		} else {
			cout << "Average wait in takeoff queue 0 time units" << endl;
		}

		double observed_land_rate = (time > 0) ? (static_cast<double>(num_land_requests) / static_cast<double>(time)) : 0.0;
		double observed_takeoff_rate = (time > 0) ? (static_cast<double>(num_takeoff_requests) / static_cast<double>(time)) : 0.0;

		cout << "Average observed rate of planes wanting to land " << observed_land_rate
			 << " per time unit" << endl
			 << "Average observed rate of planes wanting to take off " << observed_takeoff_rate
			 << " per time unit" << endl;
	}

private:
	PlaneQueue landing_queue;
	PlaneQueue takeoff_queue;
	int queue_limit;
	int num_land_requests;
	int num_takeoff_requests;
	int num_landings;
	int num_takeoffs;
	int num_land_accepted;
	int num_takeoff_accepted;
	int num_land_refused;
	int num_takeoff_refused;
	int land_wait;
	int takeoff_wait;
	int land_idle_time;
	int takeoff_idle_time;
};

void initialize(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate) {
	cout << "This program simulates an airport with two separate runways." << endl
		 << "One runway is dedicated to landings, one to takeoffs." << endl
		 << "One plane can land and one can take off in each unit of time." << endl;

	cout << "Up to what number of planes can be waiting to land or take off at any time? " << flush;
	cin >> queue_limit;

	cout << "How many units of time will the simulation run? " << flush;
	cin >> end_time;

	bool acceptable = false;
	do {
		cout << "Expected number of arrivals per unit time? " << flush;
		cin >> arrival_rate;
		cout << "Expected number of departures per unit time? " << flush;
		cin >> departure_rate;

		if (arrival_rate < 0.0 || departure_rate < 0.0) {
			cerr << "These rates must be nonnegative." << endl;
			acceptable = false;
		} else {
			acceptable = true;
		}

		if (acceptable && arrival_rate + departure_rate > 2.0) {
			cerr << "Safety Warning: This airport will become saturated." << endl;
		}
	} while (!acceptable);
}

} // namespace p2_sim

void P2() {
	int end_time = 0;
	int queue_limit = 0;
	int flight_number = 0;
	double arrival_rate = 0.0;
	double departure_rate = 0.0;

	p2_sim::initialize(end_time, queue_limit, arrival_rate, departure_rate);

	Random variable(false);
	p2_sim::Airport airport(queue_limit);

	for (int current_time = 0; current_time < end_time; ++current_time) {
		int number_arrivals = variable.poisson(arrival_rate);
		for (int i = 0; i < number_arrivals; ++i) {
			p2_sim::Plane current_plane(flight_number++, current_time, p2_sim::arriving);
			if (airport.can_land(current_plane) != p2_sim::success) {
				current_plane.refuse();
			}
		}

		int number_departures = variable.poisson(departure_rate);
		for (int j = 0; j < number_departures; ++j) {
			p2_sim::Plane current_plane(flight_number++, current_time, p2_sim::departing);
			if (airport.can_depart(current_plane) != p2_sim::success) {
				current_plane.refuse();
			}
		}

		// Both runways operate independently in parallel
		p2_sim::Plane landing_plane;
		if (airport.landing_activity(current_time, landing_plane)) {
			landing_plane.land(current_time);
		}

		p2_sim::Plane takeoff_plane;
		if (airport.takeoff_activity(current_time, takeoff_plane)) {
			takeoff_plane.fly(current_time);
		}
	}

	airport.shut_down(end_time);
}