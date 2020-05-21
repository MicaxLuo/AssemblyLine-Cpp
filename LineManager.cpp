
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string& fname, std::vector<Task*>& task, std::vector<CustomerOrder>& co) {
	Utilities util;
	bool more = true;
	size_t pos = 0;
	std::string record = "";
	std::string next = "";
	std::ifstream file(fname);
	m_cntCustomerOrder = co.size();

	if (!file)
	{
		std::cout << "*** Unable to open " + fname + " file" << std::endl;
	}
	while (!file.eof())
	{
		std::getline(file, record);
		pos = 0;
		std::string firstStr = util.extractToken(record, pos, more);

		if (more) {
			next = util.extractToken(record, pos, more);
			for (size_t i = 0; i < task.size(); i++) {
				if (task[i]->getName() == firstStr) {
					first = i;
					break;
				}
			}
			if (next.size() != 0) {
				for (size_t i = 0; i < task.size(); i++) {
					if (task[i]->getName() == next) {
						task[first]->setNextTask(*task[i]); // set m_pNextTask
						break;
					}
				}
			}
			else {
				task[first]->setNextTask(*AssemblyLine[0]); // link to first task in the AL
				m_cntCustomerOrder = first;
			}
		}
	}
	for (size_t i = 0; i < task.size(); i++) {
		AssemblyLine.push_back(task[i]); // copy all tasks into AL
	}
	for (size_t i = 0; i < co.size(); i++) {
		ToBeFilled.push_front(std::move(co[i])); // add all CO into ToBeFilled
	}
}

bool LineManager::run(std::ostream& os) {
	bool res = true;

	// move the last CO to the start point of AssemblyLine
	if (!ToBeFilled.empty()) {
		*AssemblyLine[m_cntCustomerOrder] += std::move(ToBeFilled.back());
		ToBeFilled.pop_back();
	}

	// Loop through all tasks on the assembly line and fill item at each task station
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}

	// Loop through all tasks on the assembly line and move the CustomerOrder objects down the line.
	// return true if all customer orders have been filled, otherwise returns false
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->moveTask();

		// Completed orders should be moved into the Completed queue.
		CustomerOrder order;
		if (AssemblyLine[i]->getCompleted(order)) {
			Completed.push_back(std::move(order));
		}
	}
	return Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompleted(std::ostream& os) const {
	/*displays all the orders that were completed*/
	for (auto i = 0u; i < Completed.size(); i++) {
		Completed[i].display(os);
	}
}

void LineManager::validateTasks() const {
	/*validates each task on the assembly line*/
	for (auto i = 0u; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->validate(cout);
	}
}