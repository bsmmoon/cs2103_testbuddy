class Task {
private:
	string name;
	string dday;
public:
	Task(string n, string d) {
		name = n;
		dday = d;
	}

	string get_task_name() {
		return name;
	}

	string get_task_dday() {
		return dday;
	}

	string describe_task() {
		string out = name;
		
		if (dday != "NULL") {
			out += " by " + dday;
		}

		return out;
	}
};
