// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.
#ifndef TASK_H
#define TASK_H

#include <deque>
#include "CustomerOrder.h"

class Task : public Item {
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;
public:
	Task(const std::string& record);
	Task(const Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(const Task&) = delete;
	Task& operator=(Task&&) = delete;
	void runProcess(std::ostream& os);
	bool moveTask();
	void setNextTask(Task& task);
	bool getCompleted(CustomerOrder& co);
	void validate(std::ostream& os);
	Task& operator+=(CustomerOrder&& co);
};

#endif // ! TASK_H