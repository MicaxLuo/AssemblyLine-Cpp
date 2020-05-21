// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.
#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include "CustomerOrder.h"
#include "Task.h"

/*The LineManager class is responsible for the executionand movement of CustomerOrders along the assembly line(from start to finish).The line
manager moves orders along the assembly line one step at a time.At each step, each station fills one order.The manager moves orders that are
ready from station to station.Once an order has reached the end of the line, it is either completed or is incomplete.An order can be
incomplete due to insufficient items in stock to cover its requests.*/
class LineManager {
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	size_t first = 0;
public:
	LineManager(const std::string& fname, std::vector<Task*>& task, std::vector<CustomerOrder>& co);
	bool run(std::ostream& os);
	void displayCompleted(std::ostream& os) const;
	void validateTasks() const;
};

#endif // !LINEMANAGER_H
