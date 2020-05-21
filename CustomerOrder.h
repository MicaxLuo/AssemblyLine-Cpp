// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#ifndef CUSTOMER_ORDER_H
#define CUSTOMER_ORDER_H

#include <string>
#include "Item.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name; // the name of the customer (e.g., John, Sara, etc)
	std::string m_product; // the name of the product being assembled (e.g., Desktop, Laptop, etc)
	unsigned int m_cntItem; // a count of the number of items for the customer's order
	ItemInfo** m_lstItem; // must managed by the class
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(const std::string& record);
	CustomerOrder(const CustomerOrder& co);
	CustomerOrder(CustomerOrder&& co) noexcept;
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	CustomerOrder& operator=(CustomerOrder&& co);
	~CustomerOrder();
	bool getItemFillState(std::string itemName) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream& os);
	void display(std::ostream& os) const;
};

#endif

