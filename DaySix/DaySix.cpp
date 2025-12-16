#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

// TODO: Before moving onto the next problem the code should be commented for legibility

void parse_input(const std::string& filename, std::vector<std::vector<std::string>>& input)
{
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<std::string> tokens;
		std::string token;

		for (int j = 0; j < line.size(); ++j)
		{
			if (line[j] == ' ')
			{
				if (!token.empty())
				{
					tokens.push_back(token);
					token.clear();
				}
			}
			else
			{
				token += line[j];
			}
		}
		if (!token.empty()) tokens.push_back(token);
		if (!tokens.empty()) input.push_back(tokens);
	}
}

// Sum total of multiplication and addition equations arranged vertically???
uint64_t task_one()
{
	// Get puzzle input
	std::vector<std::vector<std::string>> input;
	parse_input("DaySix.txt", input);

	uint64_t total = 0;

	// Run through each equation
	std::vector<std::string> column;
	for (int i = 0; i < input[0].size(); ++i)
	{
		column.clear();
		for (int j = 0;  j < input.size(); ++j)
		{
			column.push_back(input[j][i]);
		}

		std::string operand = column.back();

		if (operand == "+")
		{
			uint64_t start = std::stoull(column[0]);
			for (int j = 1; j < column.size() - 1; ++j)
			{
				start += std::stoull(column[j]);
			}
			total += start;
		}
		else if (operand == "*")
		{
			uint64_t start = std::stoull(column[0]);
			for (int j = 1; j < column.size() - 1; ++j)
			{
				start *= std::stoull(column[j]);
			}
			total += start;
		}
		else
		{
			std::cout << "Unrecognised token: " << operand << std::endl;
		}

	}

	return total;
}

// In this problem the numbers are written vertically in the column. It is complicated
uint64_t task_two()
{
	// Get puzzle input
	std::vector<std::vector<std::string>> input;
	parse_input("DaySix.txt", input);
	uint64_t total = 0;

	// Run through each equation
	std::vector<std::string> column;
	int value = -1;
	for (int i = 0; i < input[0].size(); ++i)
	{
		column.clear();
		for (int j = 0; j < input.size(); ++j)
		{
			column.push_back(input[j][i]);
		}
	
		std::string operand = column.back();
		column.pop_back();

		// Each column should be sorted into ascending string size
		// Each row should be inverted
		// The left column should be read, then deleted
		// If the row is now empty, it is removed
		// This is repeated until all rows are empty
		std::sort(column.begin(), column.end(), [](const std::string &a, const std::string &b) {
					return a.size() < b.size();
				});

		for (int j = 0; j < column.size(); ++j)
		{
			std::reverse(column[j].begin(), column[j].end());
		}

		// Add the numbers to the value
		std::string number = "";
		for (int j = 0; j < column.size(); ++j)
		{
			number += column[j][0];
			column[j].erase(0, 1);
			if (column[j].size() == 0) column.erase(column.begin() + j);
		}

		if (value == -1)
		{
			value = std::stoi(number);
		}
		else
		{
			std::cout << number << std::endl;
			if (operand == "+") value += std::stoi(number);
			else value *= std::stoi(number);
		}
	}

		

	return total;
}

int main()
{
	uint64_t result_one = task_one();
	std::cout << "Task one: " << result_one << std::endl;
	uint64_t result_two = task_two();
	std::cout << "Task two: " << result_two << std::endl;
	return 0;
}
