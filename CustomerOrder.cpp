
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const std::string& record) {
	Utilities util;
	size_t pos = 0;
	bool more = true;

	if (record.empty()) {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}
	else {
		m_name = util.extractToken(record, pos, more);

		if (more) {
			m_product = util.extractToken(record, pos, more);

			m_cntItem = std::count(record.begin(), record.end(), util.getDelimiter()) - 1;
			if (m_cntItem > 0) {
				m_lstItem = new ItemInfo * [m_cntItem];

				for (auto i = 0u; i < m_cntItem && more; i++) {
					m_lstItem[i] = new ItemInfo(util.extractToken(record, pos, more));
				}
			}
		}
		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& co) {
	throw "Error: Copy is not allowed";
}

CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	*this = std::move(co);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) {
	if (this != &co) {
		if (m_cntItem != 0) { // without this check it has memory access violation
			for (auto i = 0u; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}

		m_name = co.m_name;
		m_product = co.m_product;
		m_cntItem = co.m_cntItem;

		m_lstItem = co.m_lstItem;
		co.m_lstItem = nullptr;
		co.m_cntItem = 0;
	}
	// 1. deallocate dynamic memory 2. copy into new static data mbers 3. copy into new dynamic data mbr 4. set old pointer to nullptr
	return *this;
}

CustomerOrder::~CustomerOrder() {

	for (auto i = 0u; i < m_cntItem; i++) 
		delete m_lstItem[i];

	delete[] m_lstItem;
	m_lstItem = nullptr;
}

bool CustomerOrder::getItemFillState(std::string itemName) const {
	//algorithms
	for (auto i = 0u; i < m_cntItem; i++) {
		if (itemName == m_lstItem[i]->m_itemName) {
			return m_lstItem[i]->m_fillState;
		}
	}
	return true;
}

bool CustomerOrder::getOrderFillState() const {
	size_t cnt = 0;
	while (cnt < m_cntItem && getItemFillState(m_lstItem[cnt]->m_itemName)) {
		cnt++;
	}
	if (cnt == m_cntItem) {
		return true;
	}
	else {
		return false;
	}
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {

	for (size_t i = 0; i < m_cntItem; ++i) {
		if (item.getName() == m_lstItem[i]->m_itemName) {
			if (item.getQuantity() > 0) {
				item.updateQuantity();
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else {
				os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
}

// some display has a return type.. some doesnt...? bc this is a reference so it directly changes the ostream
void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << endl;
	for (auto i = 0u; i < m_cntItem; i++) {

		os << "[" << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] "
			<< std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";

		if (getItemFillState(m_lstItem[i]->m_itemName)) {
			os << "FILLED";
		}
		else {
			os << "MISSING";
		}

		os << endl;
	}
}