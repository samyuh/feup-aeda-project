#ifndef AEDA_PERSON_H
#define AEDA_PERSON_H

#include <string>
#include "Date.h"

/// \brief Class for a Person
class Person {
private:
    std::string name; /*!< Person's name */
	Date birth;  /*!< Person's date of birth */
public:
    /// \brief An empty constructor for a Person.
    Person();
    /// \brief Person Constructor with the following data.
    /// \param name Person's name
    /// \param birth Person's birthday
	Person(std::string name, Date birth);
    /// \brief Get Method.
    /// \return Person's name
    std::string getName() const;
    /// \brief Get Method.
    /// \return Person's birthday
	Date getBirthday() const;
	/// \brief Set Method.
	/// \param name sets this name as the Person's name
	void setName(std::string name);
    /// \brief Set Method.
    /// \param birth sets this Date as the Person's birthday
	void setBirthday(Date birth);
    /// \brief Shows Person's data in a table.
	virtual void infoTable() const;
	/// \brief Shows Person's data.
    virtual void info() const;
};

/// \brief Class for throwing exceptions when a Person is not found
class PersonNotFound{
private:
    std::string name;
public:
    PersonNotFound(std::string name): name(name) {}
    std::string getName() const{
        return name;
    }
};
/// \brief Class for throwing exceptions when too many People are found
class TooManyPeopleFound{
private:
    std::string name;
public:
    TooManyPeopleFound(std::string name): name(name) {}
    std::string getName() const{
        return name;
    }
};


#endif
