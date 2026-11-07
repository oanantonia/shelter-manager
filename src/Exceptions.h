#pragma once
#include <stdexcept>
#include <string>

class ValidationException : public std::exception
{
private:
	std::string message;

public:
	ValidationException(std::string message);
	const char* what() const noexcept override;
};

class RepositoryException : public std::exception
{
private:
	std::string message;

public:
	RepositoryException(std::string message);
	const char* what() const noexcept override;
};

class UIException : public std::exception
{
private:
	std::string message;

public:
	UIException(std::string message);
	const char* what() const noexcept override;
};

class ServiceException : public std::exception
{
private:
	std::string message;

public:
	ServiceException(std::string message);
	const char* what() const noexcept override;
};
