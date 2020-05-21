// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include "Task.h"

Task::Task(const std::string& record) : Item(record) { // whats the other way of initializing the parent 1-arg constructor?
	m_pNextTask = nullptr;
}

void Task::runProcess(std::ostream& os) {
	/*runs a single cycle of the assembly line for the current task. If there are CustomerOrders in the queue, it will verify the fill
	status of the last CustomerOrder and fill it if the order contains the Item specified by the current Task.*/

	while (!m_orders.empty() && !(m_orders.back().getItemFillState(this->getName()))) {
		m_orders.back().fillItem(*this, os);
	}
}

bool Task::moveTask() {
	/*moves the last CustomerOrder in the queue to the next task on the assembly line if the orders fill state for the current Item is
	true. Otherwise, the CustomerOrder should remain in the queue for the next processing cycle. If the queue is empty, return false.*/

	// why do it when m_pNesxtTask != nullptr? --- when this is not the last task in the AL
	if (!m_orders.empty() && m_pNextTask != nullptr && m_orders.back().getItemFillState(this->getName())) {
		*m_pNextTask += std::move(m_orders.back());
		m_orders.pop_back(); // why pop back after std::move?
		return true;
	}
	else {
		return false;
	}
}

void Task::setNextTask(Task& task) {
	/*stores the provided Task object's reference into the m_pNextTask pointer.*/
	m_pNextTask = &task;
}

bool Task::getCompleted(CustomerOrder& co) {
	/*Removes the last CustomerOrder from the queue, places it in the parameter and returns true. If the CustomerOrder queue is empty,
	return false.*/
	if (!m_orders.empty() && m_orders.back().getOrderFillState()) {
		co = std::move(m_orders.back());
		m_orders.pop_back();
		return true;
	}
	else {
		return false;
	}
}

void Task::validate(std::ostream& os) {
	/*writes the name of the Item this Task is responsible for into the parameter: ITEM_NAME --> NEXT_ITEM_NAME
	if m_pNextTask does not exist it writes: ITEM_NAME --> END OF LINE.
	the messages are terminated with an endline*/
	os << getName() << " --> ";
	if (m_pNextTask != nullptr) {
		os << m_pNextTask->getName();
	}
	else {
		os << "END OF LINE";
	}
	os << endl;
}

Task& Task::operator+=(CustomerOrder&& co) {
	/*Moves the parameter onto the front of the CustomerOrder queue.*/
	m_orders.push_front(std::move(co));
	return *this; // why *this is Task? cuz this is in Task class
}
