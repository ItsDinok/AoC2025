#include <iostream>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

// Data is 3732 x 5

void parse_input(const std::string& filename, std::vector<std::string>& input)
{
	std::vector<std::string> lines;

	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	// I checked, every row is the same length
	std::string column;
	for (int i = 0; i < lines[0].size(); ++i)
	{
		column = "";
		for (int j = 0; j < lines.size(); ++j)
		{
			if (lines[j][i] == ' ') continue;
			column += lines[j][i];
		}

		input.push_back(column);
		if (i == 0) std::cout << "First column: " << column << std::endl;
		if (i == 1) std::cout << "Second column: " << column << std::endl;
	}
}

// Sum total of multiplication and addition equations arranged vertically???
uint64_t task_one()
{
	// Get puzzle input
	std::vector<std::string> input;
	parse_input("DaySix.txt", input);

	uint64_t total = 0;

	// Run through each equation
	std::string equation;
	for (int i = 0; i < input.size(); ++i)
	{
		// Get operand
		equation = input[i];
		char symbol = equation.back();
		equation.pop_back();

		//if (symbol == ' ') std::cout << equation << std::endl;

		// Some values are blank
		std::vector<int> numbers;
		for (int j = 0; j < 4; ++j)
		{
			if (equation[j] == ' ') continue;
			numbers.push_back(equation[j] - '0');
		}

		// Apply transform to all numbers in vector
		switch(symbol)
		{
			case '+':
				total += std::accumulate(numbers.begin(), numbers.end(), 0);
				break;
			case '*':
				total += std::accumulate(numbers.begin(), numbers.end(), 1,
						[](int a, int b) { return a * b; });
				break;
		}
	}

	return total;
}

int main()
{
	int result_one = task_one();
	std::cout << "Task one: " << result_one << std::endl;
	return 0;
}
