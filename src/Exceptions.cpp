#include "Exceptions.h"

ValidationException::ValidationException(std::string message) : message{ message }
{}

const char* ValidationException::what() const noexcept
{
	return message.c_str();
}

RepositoryException::RepositoryException(std::string message) : message{ message }
{}

const char* RepositoryException::what() const noexcept
{
	return message.c_str();
}

UIException::UIException(std::string message) : message{ message }
{}

const char* UIException::what() const noexcept
{
	return message.c_str();
}

ServiceException::ServiceException(std::string message) : message{ message }
{}

const char* ServiceException::what() const noexcept
{
	return message.c_str();
}

